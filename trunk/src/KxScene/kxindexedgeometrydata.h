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

#ifndef KXINDEXEDGEOMETRYDATA_H
#define KXINDEXEDGEOMETRYDATA_H

#include "kxgeometrydata.h"

class KxIndexedGeometryData : public KxGeometryData
{
    Q_OBJECT

public:
    explicit KxIndexedGeometryData(QObject *parent = 0);

    virtual inline int trianglesCount() const;

    virtual void draw() const;

    inline const QVector<uint> &indices() const;
    inline void setIndices(const QVector<uint> &indices);

    virtual bool computeNormals();

    virtual bool computeTangents();

protected:   
    QVector<uint> m_indices;

    friend class KxTriangleMeshShape;
    friend class KxMd5Model;
    friend class KxMd5ModelMesh;
};

inline int KxIndexedGeometryData::trianglesCount() const
{
    return m_indices.count() / 3;
}

inline const QVector<uint>& KxIndexedGeometryData::indices() const
{
    return m_indices;
}

inline void KxIndexedGeometryData::setIndices(const QVector<uint>& indices)
{
    m_indices = indices;
}


#endif // KXINDEXEDGEOMETRYDATA_H
