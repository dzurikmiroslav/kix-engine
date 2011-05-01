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
#include "kxsound.h"
#include <Phonon/AudioOutput>

KxSound::KxSound(QObject *parent) :
    QObject(parent)
{
    m_media = Phonon::createPlayer(Phonon::MusicCategory);
    m_media->setParent(this);
}

KxSound::~KxSound()
{
    //if(m_source)   delete m_source;
}

#endif // KIX_PHONON_SOUND
