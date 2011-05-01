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

#include "kxmd5animation.h"
#include <QtCore/qregexp.h>
#include <QtCore/qdebug.h>
#include <QtCore/qfile.h>
#include <QtCore/qmath.h>

KxMd5Animation::KxMd5Animation(QObject *parent) :
        QObject(parent)
{
    m_frameRate = 0;
    m_jointCount = 0;
}

KxMd5Animation::KxMd5Animation(const QString &fileName, QObject *parent) :
        QObject(parent)
{
    m_frameRate = 0;
    m_jointCount = 0;
    setSource(fileName);
}

KxMd5Animation::~KxMd5Animation()
{
}

void KxMd5Animation::computeQuatScallar(QQuaternion &quat)
{
    qreal t = 1.0f - (quat.x() * quat.x()) - (quat.y() * quat.y()) - (quat.z() * quat.z());
    if (t < 0.0f)
        quat.setScalar(0);
    else
        quat.setScalar(-qSqrt(t));
}

void KxMd5Animation::setSource(const QString &value)
{
    if(loadFromFile(value))
        m_source = value;
}

bool KxMd5Animation::loadFromFile(const QString &fileName)
{
    if(QFile::exists(fileName)) {
        if(fileName.endsWith(".md5anim", Qt::CaseInsensitive))
            return loadMd5File(fileName);
        qWarning() << "KxMd5Animation::loadFromFile uknow format addictive" << fileName;
        return false;
    } else {
        qWarning() << "KxMd5Animation::loadFromFile file not exist" << fileName;
        return false;
    }
}

bool KxMd5Animation::loadMd5File(const QString &fileName)
{
    qDebug() << "KxMd5Animation::loadMd5File" << fileName;
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) {
        qWarning() << "KxMd5Animation::loadMd5File cant read file" << fileName;
        return false;
    }
    QTextStream stream(&file);
    QString line;
    QRegExp regex("\\s*numFrames\\s+(\\d+).*");
    do {
        line = stream.readLine();
    } while((regex.indexIn(line) == -1) && (!line.isNull()));
    const int framesCount = regex.cap(1).toInt();
    m_frames.resize(framesCount);
    regex.setPattern("\\s*numJoints\\s+(\\d+).*");
    do {
        line = stream.readLine();
    } while((regex.indexIn(line) == -1) && (!line.isNull()));
    m_jointCount = regex.cap(1).toInt();
    struct JointHierarchy
    {
        QQuaternion m_rotation;
        QVector3D m_position;
        int m_parent;
        int m_frameIndex;
        quint8 m_flag;
        //QString m_name;
    } joints[m_jointCount];
    regex.setPattern("\\s*frameRate\\s+(\\d+).*");
    do {
        line = stream.readLine();
    } while((regex.indexIn(line) == -1) && (!line.isNull()));
    m_frameRate = regex.cap(1).toInt();
    regex.setPattern("\\s*numAnimatedComponents\\s+(\\d+).*");
    do {
        line = stream.readLine();
    } while((regex.indexIn(line) == -1) && (!line.isNull()));
    const int numAnimComp = regex.cap(1).toInt();
    qreal frameData[numAnimComp];   //c++0x  :)
    regex.setPattern("\\s*hierarchy\\s*\\{.*");
    do {
        line = stream.readLine();
    } while((!regex.exactMatch(line)) && (!line.isNull()));
    regex.setPattern("\\s*\\\"(.*)\\\"\\s+(\\S+)\\s+(\\S+)\\s+(\\S+).*");
    for(int i = 0; i < m_jointCount; i++) {
        do {
            line = stream.readLine();
        } while((regex.indexIn(line) == -1) && (!line.isNull()));
        struct JointHierarchy &j = joints[i];
        //j.m_name = regex.cap(1);
        j.m_parent = regex.cap(2).toInt();
        j.m_flag = regex.cap(3).toUInt();
        j.m_frameIndex = regex.cap(4).toInt();
    }
    regex.setPattern("\\s*bounds\\s*\\{.*");
    do {
        line = stream.readLine();
    } while((!regex.exactMatch(line)) && (!line.isNull()));
    regex.setPattern("\\s*\\(\\s+(\\S+)\\s+(\\S+)\\s+(\\S+)\\s+\\)\\s+\\(\\s+(\\S+)\\s+(\\S+)\\s+(\\S+)\\s+\\).*");
    for(int i = 0; i < framesCount; i++) {
        do {
            line = stream.readLine();
        } while((regex.indexIn(line) == -1) && (!line.isNull()));
        Frame &f = m_frames[i];
        f.m_aabb.min().setX(regex.cap(1).toFloat());
        f.m_aabb.min().setZ(-regex.cap(2).toFloat());
        f.m_aabb.min().setY(regex.cap(3).toFloat());
        f.m_aabb.max().setX(regex.cap(4).toFloat());
        f.m_aabb.max().setZ(-regex.cap(5).toFloat());
        f.m_aabb.max().setY(regex.cap(6).toFloat());
    }
    regex.setPattern("\\s*baseframe\\s*\\{.*");
    do {
        line = stream.readLine();
    } while((!regex.exactMatch(line)) && (!line.isNull()));
    regex.setPattern("\\s*\\(\\s+(\\S+)\\s+(\\S+)\\s+(\\S+)\\s+\\)\\s+\\(\\s+(\\S+)\\s+(\\S+)\\s+(\\S+)\\s+\\).*");
    for(int i = 0; i < m_jointCount; i++) {
        do {
            line = stream.readLine();
        } while((regex.indexIn(line) == -1) && (!line.isNull()));
        struct JointHierarchy &j = joints[i];
        j.m_position.setX(regex.cap(1).toFloat());
        j.m_position.setZ(-regex.cap(2).toFloat());
        j.m_position.setY(regex.cap(3).toFloat());
        j.m_rotation.setX(regex.cap(4).toFloat());
        j.m_rotation.setZ(-regex.cap(5).toFloat());
        j.m_rotation.setY(regex.cap(6).toFloat());
    }
    regex.setPattern("\\s*frame\\s+\\d+\\s+\\{.*");
    for(int i = 0; i < framesCount; i++) {
        m_frames[i].m_joints.resize(m_jointCount);
        for(int j = 0; j < m_jointCount; j++) {
            m_frames[i].m_joints[j].setRotation(joints[j].m_rotation);
            m_frames[i].m_joints[j].setPosition(joints[j].m_position);
        }
        do {
            line = stream.readLine();
        } while((!regex.exactMatch(line)) && (!line.isNull()));
        for(int j = 0; j < numAnimComp; j++)
            stream >> frameData[j];
        for(int j = 0; j < m_jointCount; j++) {
            int count = 0;
            KxTransform &frameJoint = m_frames[i].m_joints[j];
            int &frameIndex(joints[j].m_frameIndex);
            //TODO do jedneho riadka
            if(joints[j].m_flag & 1 << 0)
                frameJoint.position().setX(frameData[frameIndex + count++]);
            if(joints[j].m_flag & 1 << 1)
                frameJoint.position().setZ(-frameData[frameIndex + count++]);
            if(joints[j].m_flag & 1 << 2)
                frameJoint.position().setY(frameData[frameIndex + count++]);
            if(joints[j].m_flag & 1 << 3)
                frameJoint.rotation().setX(frameData[frameIndex + count++]);
            if(joints[j].m_flag & 1 << 4)
                frameJoint.rotation().setZ(-frameData[frameIndex + count++]);
            if(joints[j].m_flag & 1 << 5)
                frameJoint.rotation().setY(frameData[frameIndex + count]);
            computeQuatScallar(frameJoint.rotation());
        }
    }
    file.close();
    return true;
}
