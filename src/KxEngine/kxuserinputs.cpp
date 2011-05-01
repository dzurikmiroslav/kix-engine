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

#include "kxuserinputs.h"
#include "kxengine.h"
#include <QtCore/qdebug.h>
#include <QtCore/qcoreevent.h>
#include <QtGui/qapplication.h>
#include <QtGui/qevent.h>
#include <QtGui/qgraphicssceneevent.h>
#include <QtCore/qmetaobject.h>
#include <QtCore/qregexp.h>

KxUserInputs::KxUserInputs(QObject * parent) : QObject(parent)
{
    m_grabMouse = false;
    m_mouseSensitivity.setX(kxEngine->settings()["controls.mouse_sensitivity.x"].toReal());
    m_mouseSensitivity.setY(kxEngine->settings()["controls.mouse_sensitivity.y"].toReal());
    connect(kxEngine, SIGNAL(settingsChanged()), this, SLOT(updateMouseSensitivity()));
}

KxUserInputs::~KxUserInputs()
{
}

const QVector2D &KxUserInputs::mouseSensitivity() const
{
    return m_mouseSensitivity;
}

void KxUserInputs::setMouseSensitivity(const QVector2D& sensitivity)
{
    m_mouseSensitivity = sensitivity;
}

void KxUserInputs::setGrabMouse(bool enable)
{
    if (m_grabMouse != enable) {
        m_grabMouse = enable;
        if (enable)
            qApp->setOverrideCursor(QCursor(Qt::BlankCursor));
        else
            qApp->setOverrideCursor(QCursor(Qt::ArrowCursor));
        emit grabMouseChanged();
    }
}

bool KxUserInputs::isGrabMouse() const
{
    return m_grabMouse;
}

void KxUserInputs::updateMouseSensitivity()
{
    m_mouseSensitivity.setX(kxEngine->settings()["controls.mouse_sensitivity.x"].toReal());
    m_mouseSensitivity.setY(kxEngine->settings()["controls.mouse_sensitivity.y"].toReal());
}

bool KxUserInputs::eventFilter(QObject *obj, QEvent *ev)
{
    m_mutex.lock();
    QKeyEvent* keyEvent;
    QMouseEvent* mouseEvent;
    QHoverEvent* hoverEvent;
    QWidget* receiver;
    switch (ev->type()) {
    case QEvent::KeyPress:
        keyEvent = static_cast<QKeyEvent*>(ev);
        if (keyEvent->isAutoRepeat())
            break;
        emit keyPressed(keyEvent->key());
        break;
    case QEvent::KeyRelease:
        keyEvent = static_cast<QKeyEvent*>(ev);
        if (keyEvent->isAutoRepeat())
            break;
        emit keyReleased(keyEvent->key());
        break;
    case QEvent::HoverMove:
        if (m_grabMouse) {
            receiver = qobject_cast<QWidget*>(obj);
            QCursor::setPos(receiver->mapToGlobal(QPoint(receiver->size().width() / 2, receiver->size().height() / 2)));
            hoverEvent = static_cast<QHoverEvent*>(ev);
            QPointF delta = hoverEvent->pos() - QPoint(receiver->size().width() / 2, receiver->size().height() / 2);
            delta *= (qreal)0.05;
            emit mouseDeltaMoved(QVector2D(-delta) * m_mouseSensitivity);
        }
        break;
    case QEvent::MouseButtonPress:
        mouseEvent = static_cast<QMouseEvent*>(ev);
        emit mousePressed(mouseEvent->button());
        break;
    case QEvent::MouseButtonRelease:
        mouseEvent = static_cast<QMouseEvent*>(ev);
        emit mouseReleased(mouseEvent->button());
        break;
    default:
        break;
    }
    m_mutex.unlock();
    return QObject::eventFilter(obj, ev);
}
