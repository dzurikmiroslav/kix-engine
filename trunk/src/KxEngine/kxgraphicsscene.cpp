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

#include "kxgraphicsscene.h"
#include "KxScene/kxcamera.h"
#include <QtDeclarative/qdeclarativeitem.h>
#include <QtDeclarative/qdeclarativeview.h>
#include <QtGui/qevent.h>
#include "kxengine.h"
#include "kxuserinputs.h"

KxGraphicsScene::KxGraphicsScene(QWidget *parent) :
    QGraphicsScene(parent)
{
    m_view = new QDeclarativeView(parent);
    m_view->setScene(this);
    //m_view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate); robi somariny !!!
    m_camera = NULL;
    m_declarativeItem = NULL;
}

KxGraphicsScene::~KxGraphicsScene()
{
    delete m_view;
}

QDeclarativeItem *KxGraphicsScene::declarativeItem()
{
    return m_declarativeItem;
}

void KxGraphicsScene::setDeclarativeItem(QDeclarativeItem *value)
{
    if (m_declarativeItem)
        removeItem(m_declarativeItem);
    m_declarativeItem = value;
    addItem(m_declarativeItem);
}

void KxGraphicsScene::setCamera(KxCamera *camera)
{
    m_view->setViewport(kxEngine->glDrawer());
    m_camera = camera;
}

void KxGraphicsScene::drawBackground(QPainter *painter, const QRectF &r)
{
    painter->beginNativePainting();
    painter->setTransform(QTransform(), false);
    if (kxEngine->settings()["video.samples"].toInt() > 0)
        painter->setRenderHint(QPainter::Antialiasing, true);
    if (m_camera)
        kxEngine->glDrawer()->draw(m_camera);
    painter->endNativePainting();
    QGraphicsScene::drawBackground(painter, r);
}

KxCamera* KxGraphicsScene::camera() const
{
    return m_camera;
}

QGraphicsView *KxGraphicsScene::view() const
{
    return m_view;
}

