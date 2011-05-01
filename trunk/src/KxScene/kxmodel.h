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

#ifndef KXMODEL_H
#define KXMODEL_H

#include "kxdrawablescenenode.h"

class KxModel;

//QML_DECLARE_TYPE(KxModelMesh);

class KxModel : public KxSceneNode
{
    Q_OBJECT
    Q_PROPERTY(QString source WRITE setSource READ source FINAL);

public:
    explicit KxModel(QObject *parent = 0);
    explicit KxModel(const QString& fileName, QObject *parent = 0);
    //~KxModel();

    virtual bool loadFromFile(const QString& fileName);

    void setSource(const QString& value);
    inline const QString& source() const;

    virtual int nodeType() const { return DrawableNode; }

private:
    bool loadObjFile(const QString& fileName);

    QString m_source;

    friend class KxModelInfo;
};

QML_DECLARE_TYPE(KxModel);


inline const QString& KxModel::source() const
{
    return m_source;
}

#endif // KXMODEL_H
