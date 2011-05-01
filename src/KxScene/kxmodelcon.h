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

#ifndef KXMODELINFO_H
#define KXMODELINFO_H

#include "kxdrawablescenenodecon.h"
#include "kxmodel.h"


class KxModelCon : public KxDrawableSceneNodeCon
{
    Q_OBJECT
    Q_PROPERTY(QString source WRITE setSource READ source FINAL)

public:
    explicit KxModelCon(QObject *parent = 0);

    inline const QString& source() const;
    void setSource(const QString& value);

    virtual bool loadFromFile(const QString& fileName);

    virtual KxModel *create(QObject *parent = 0) const;

protected:
    bool loadObjFile(const QString& fileName);
    QString m_source;

};

QML_DECLARE_TYPE(KxModelCon);


inline const QString& KxModelCon::source() const
{
    return m_source;
}

#endif // KXMODELINFO_H
