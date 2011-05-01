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

#ifndef KXUSERINPUTS_H
#define KXUSERINPUTS_H

#include <QtCore/qobject.h>
#include <QtCore/qmap.h>
#include <QtCore/qmutex.h>
#include <QtCore/qmetaobject.h>
#include <QtGui/qvector2d.h>

class QKeyEvent;

class KxUserInputs : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool grabMouse READ isGrabMouse WRITE setGrabMouse NOTIFY grabMouseChanged FINAL)
    Q_PROPERTY(QVector2D mouseSensitivity READ mouseSensitivity WRITE setMouseSensitivity FINAL)

public:
    KxUserInputs(QObject *parent = 0);
    ~KxUserInputs();

    const QVector2D &mouseSensitivity() const;
    void setMouseSensitivity(const QVector2D &value);

    bool isGrabMouse() const;
    void setGrabMouse(bool value);

    //Q_INVOKABLE void reset();

signals:
    //void startAction(const QString& actionName);
    //void finishAction(const QString& actionName);
    void grabMouseChanged();

    //keyboard
    void keyPressed(int key);
    void keyReleased(int key);

    //mouse
    void mouseDeltaMoved(const QVector2D& delta);
    void mousePressed(int button);
    void mouseReleased(int button);

private:
    virtual bool eventFilter(QObject *, QEvent *);
    Q_SLOT void updateMouseSensitivity();
    //void addAction(const QString &input, const QString &actName);
    //int strToQtKey(const QString &keyName);

    QMutex m_mutex;
    //QMap<int, QString> m_namedActions;
    QVector2D m_mouseSensitivity;
    bool m_grabMouse : 1;

};

Q_DECLARE_METATYPE(KxUserInputs*);


#endif // KXUSERINPUTS_H
