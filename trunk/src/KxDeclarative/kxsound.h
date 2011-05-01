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

#ifdef KIX_PHONON_SOUND
#ifndef KXSOUND_H
#define KXSOUND_H

#include <QtCore/qobject.h>
#include <QtCore/qdebug.h>
#include <QtCore/qurl.h>
#include <Phonon/MediaObject>
#include <QtDeclarative/qdeclarative.h>

class KxSound : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl source READ source WRITE setSource FINAL)

public:
    explicit KxSound(QObject *parent = 0);
    ~KxSound();
    inline QUrl source() const;
    inline void setSource(const QUrl& value);

public slots:
    inline void play();
    inline void stop();

private:
    Phonon::MediaObject *m_media;
    Phonon::MediaSource m_source;

};

QML_DECLARE_TYPE(KxSound);


inline QUrl KxSound::source() const
{
    return m_media->currentSource().url();
}

inline void KxSound::setSource(const QUrl &value)
{
    m_source = Phonon::MediaSource(value);
}

inline void KxSound::play()
{
    m_media->setCurrentSource(m_source);
    m_media->play();
}

inline void KxSound::stop()
{
    m_media->stop();
}

#endif // KXSOUND_H
#endif // KIX_PHONON_SOUND
