/*
* This file is part of Kix Engine
*
* Copyright (C) 2011 - Miroslav Dzurik
*
* Kix Engine is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 3 of the License, or (at your option) any later version.
*
* Kix Engine is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "kxgeometrydata.h"
#include <QtOpenGL/qgl.h>
#include <QtXml/qdom.h>
#include <QtCore/qfile.h>
#include <QtCore/qdebug.h>
#include <QtCore/qregexp.h>
#include <QtCore/qstringlist.h>
#include <QtCore/qtextstream.h>
#include "KxEngine/kxsimdutils.h"

KxGeometryData::KxGeometryData(QObject *parent) :
    QObject(parent)
{
}

bool KxGeometryData::loadFromFile(const QString &fileName)
{
    qDebug() << "KxGeometryData::loadFromFile" << fileName;
    if (fileName.endsWith(".obj", Qt::CaseInsensitive)) {
        return loadObjFile(fileName);
    }
    qWarning() << "KxGeometryData::loadFromFile uknow format addictive" << fileName;
    return true;
}

bool KxGeometryData::loadObjFile(const QString &fileName, QList<KxGeometryData *> &geometries, QStringList *materials)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "KxGeometryData::loadObjFile cant read file" << fileName;
        return false;
    }
    QTextStream stream(&file);
    QVector<QVector3D> vertices;
    QVector<QVector3D> normals;
    QVector<QVector2D> texCoords;
    vertices << QVector3D();    //meeh :-/
    normals << QVector3D();
    texCoords << QVector2D();
    QRegExp vReg("v\\s+(\\S+)\\s+(\\S+)\\s+(\\S+).*");
    QRegExp vtReg("vt\\s+(\\S+)\\s+(\\S+).*");
    QRegExp vnReg("n\\s+(\\S+)\\s+(\\S+)\\s+(\\S+).*");
    QRegExp matReg("usemtl\\s+(.*)$");
    QRegExp objReg("o\\s+.*");
    QRegExp fReg1("f\\s+(\\d+)\\s+(\\d+)\\s+(\\d+).*");
    QRegExp fReg2("f\\s+(\\d+)//(\\d+)\\s+(\\d+)//(\\d+)\\s+(\\d+)//(\\d+).*");
    QRegExp fReg3("f\\s+(\\d+)/(\\d+)/(\\d+)\\s+(\\d+)/(\\d+)/(\\d+)\\s+(\\d+)/(\\d+)/(\\d+).*");
    KxGeometryData *data;
    QString line;
    do {
        line = stream.readLine();
        if (vReg.indexIn(line) > -1)
            vertices << QVector3D(vReg.cap(1).toFloat(), vReg.cap(2).toFloat(), vReg.cap(3).toFloat());
        else if (vtReg.indexIn(line) > -1)
            texCoords << QVector2D(vtReg.cap(1).toFloat(), vtReg.cap(2).toFloat());
        else if (vnReg.indexIn(line) > -1)
            normals << QVector3D(vnReg.cap(1).toFloat(), vnReg.cap(2).toFloat(), vnReg.cap(3).toFloat());
        else if (fReg3.indexIn(line) > -1) {
            data->m_vertices << vertices[fReg3.cap(1).toInt()];
            data->m_vertices << vertices[fReg3.cap(4).toInt()];
            data->m_vertices << vertices[fReg3.cap(7).toInt()];
            data->m_texCoords << texCoords[fReg3.cap(2).toInt()];
            data->m_texCoords << texCoords[fReg3.cap(5).toInt()];
            data->m_texCoords << texCoords[fReg3.cap(8).toInt()];
            data->m_normals << normals[fReg3.cap(3).toInt()];
            data->m_normals << normals[fReg3.cap(6).toInt()];
            data->m_normals << normals[fReg3.cap(9).toInt()];
        } else if (fReg2.indexIn(line) > -1) {
            //bez textur
            data->m_vertices << vertices[fReg2.cap(1).toInt()];
            data->m_vertices << vertices[fReg2.cap(3).toInt()];
            data->m_vertices << vertices[fReg2.cap(5).toInt()];
            data->m_normals << normals[fReg2.cap(2).toInt()];
            data->m_normals << normals[fReg2.cap(4).toInt()];
            data->m_normals << normals[fReg2.cap(6).toInt()];
        } else if (fReg1.indexIn(line) > -1) {
            //len vrcholy
            data->m_vertices << vertices[fReg1.cap(1).toInt()];
            data->m_vertices << vertices[fReg1.cap(2).toInt()];
            data->m_vertices << vertices[fReg1.cap(3).toInt()];
        }
        else if (objReg.exactMatch(line)) {
            data = new KxGeometryData();
            geometries << data;
        }
        else if (materials) {
            if (matReg.indexIn(line) > -1)
                materials->append(matReg.cap(1));
        }
    } while (!line.isNull());
    file.close();
    foreach (KxGeometryData *gData, geometries) {
        if (!gData->hasNormals())
            gData->computeNormals();
        gData->computeTangents();
    }
    return true;
}

bool KxGeometryData::loadObjFile(const QString &fileaName)
{
    QList<KxGeometryData *> datas;
    if (!loadObjFile(fileaName, datas))
        return false;
    foreach (KxGeometryData *data, datas) {
        m_vertices << data->m_vertices;
        m_texCoords << data->m_texCoords;
        m_normals << data->m_normals;
        delete data;
    }
    return true;
}

bool KxGeometryData::computeNormals()
{
    if (m_vertices.isEmpty())
        return false;
    if (m_normals.count() != m_vertices.count())
        m_normals.resize(m_vertices.count());
    kxSIMDUtils->computeNormals(m_normals.data(), m_vertices.constData(), m_vertices.count());
    /*
    for (int i = 0; i < m_vertices.count(); i += 3) {
        QVector3D a = m_vertices[i + 0] - m_vertices[i + 1];
        QVector3D b = m_vertices[i + 0] - m_vertices[i + 2];
        QVector3D n = QVector3D::crossProduct(b, a).normalized();
        for (int j = 0; j < 3; j++)
            m_normals[i + j] = n;
    }*/
    return true;
}

/**
 Hmmmmm
void ComputeTangentBasis(
      const Vec3& P1, const Vec3& P2, const Vec3& P3,
      const Vec2& UV1, const Vec2& UV2, const Vec2& UV3,
      Vec3 &tangent, Vec3 &bitangent )
{
   Vec3 Edge1 = P2 - P1;
   Vec3 Edge2 = P3 - P1;
   Vec2 Edge1uv = UV2 - UV1;
   Vec2 Edge2uv = UV3 - UV1;

   float cp = Edge1uv.y * Edge2uv.x - Edge1uv.x * Edge2uv.y;

   if ( cp != 0.0f ) {
      float mul = 1.0f / cp;
      tangent   = (Edge1 * -Edge2uv.y + Edge2 * Edge1uv.y) * mul;
      bitangent = (Edge1 * -Edge2uv.x + Edge2 * Edge1uv.x) * mul;

      tangent.Normalize();
      bitangent.Normalize();
   }
}
*/

bool KxGeometryData::computeTangents()
{
    if (m_vertices.isEmpty() || m_normals.isEmpty() ||  m_texCoords.isEmpty())
        return false;
    if (m_tangents.count() != m_vertices.count())
        m_tangents.resize(m_vertices.count());
    kxSIMDUtils->computeTangents(m_tangents.data(), m_vertices.constData(), m_normals.constData(),
                                 m_texCoords.constData(), m_vertices.count());
    /*QVector<QVector3D> sTan(m_vertices.count());
    QVector<QVector3D> tTan(m_vertices.count());
    for (int i = 0; i < m_vertices.count(); i+= 3) {
        const QVector3D &v0 = m_vertices[i + 0];
        const QVector3D &v1 = m_vertices[i + 1];
        const QVector3D &v2 = m_vertices[i + 2];
        const QVector2D &w0 = m_texCoords[i + 0];
        const QVector2D &w1 = m_texCoords[i + 1];
        const QVector2D &w2 = m_texCoords[i + 2];
        float x1 = v1.x() - v0.x();
        float x2 = v2.x() - v0.x();
        float y1 = v1.y() - v0.y();
        float y2 = v2.y() - v0.y();
        float z1 = v1.z() - v0.z();
        float z2 = v2.z() - v0.z();
        float s1 = w1.x() - w0.x();
        float s2 = w2.x() - w0.x();
        float t1 = w1.y() - w0.y();
        float t2 = w2.y() - w0.y();
        float r = (s1 * t2) - (s2 * t1);
        if (r == 0.0f)
            r = 1.0f;
        float oneOverR = 1.0f / r;
        QVector3D sDir ((t2 * x1 - t1 * x2) * oneOverR,
                        (t2 * y1 - t1 * y2) * oneOverR,
                        (t2 * z1 - t1 * z2) * oneOverR);
        QVector3D tDir ((s1 * x2 - s2 * x1) * oneOverR,
                        (s1 * y2 - s2 * y1) * oneOverR,
                        (s1 * z2 - s2 * z1) * oneOverR);
        for (int j = 0; j < 3; ++j) {
            sTan[i + j] += sDir;
            tTan[i + j] += tDir;
        }
    }
    for (int i = 0; i < m_vertices.count(); i++) {
        const QVector3D &n = m_normals[i];
        const QVector3D &t = sTan[i];
        // Gram-Schmidt orthogonalize
        m_tangents[i] = (t - n * QVector3D::dotProduct(n, t));
        m_tangents[i].normalize();
        // Calculate handedness
        if (QVector3D::dotProduct(QVector3D::crossProduct(n, t), tTan[i]) < 0.0f)
            m_tangents[i] = -m_tangents[i];
    }
    */
    return true;
}

void KxGeometryData::draw() const
{
    glDrawArrays(GL_TRIANGLES, 0, m_vertices.count());
}
