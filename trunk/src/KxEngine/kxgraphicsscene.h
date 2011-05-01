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

#ifndef KXGRAPHICSSCENE_H
#define KXGRAPHICSSCENE_H

#include <QtGui/qgraphicsscene.h>
#include <QtCore/qmetatype.h>

class KxCamera;
class QDeclarativeItem;

class KxGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
    Q_PROPERTY(QGraphicsView *view READ view FINAL)
    Q_PROPERTY(KxCamera *camera READ camera WRITE setCamera FINAL)
    Q_PROPERTY(QDeclarativeItem *declarativeItem READ declarativeItem WRITE setDeclarativeItem FINAL)

public:
    explicit KxGraphicsScene(QWidget *parent = 0);
    ~KxGraphicsScene();

    void setCamera(KxCamera *value);
    KxCamera* camera() const;

    QGraphicsView *view() const;

    QDeclarativeItem *declarativeItem();
    void setDeclarativeItem(QDeclarativeItem *value);

private:
    virtual void drawBackground(QPainter *painter, const QRectF &rect);

    QDeclarativeItem *m_declarativeItem;
    KxCamera *m_camera;
    QGraphicsView *m_view;

};

Q_DECLARE_METATYPE(KxGraphicsScene*);

#endif // KXGRAPHICSSCENE_H
