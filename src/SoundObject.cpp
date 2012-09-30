//
//  SoundObject.cpp
//  HearingView
//
//  Created by Imanolgo on 08/07/12.
//
//

#include "SoundObject.h"


SoundObject::SoundObject(std::string name): m_name(name), m_volume(1.0)
{
    m_soundPlayer = new ofSoundPlayer();
}

SoundObject::~SoundObject()
{
    delete m_soundPlayer;
    m_soundPlayer = new ofSoundPlayer();
}

void SoundObject::setVolume(float volume)
{
    
    if (volume<0.0) 
    {
       // std::cout << "SoundObject::setVolume -> volume out of range (" << volume <<") for sample " << m_name << std::endl ;
        m_volume = 0.0;
        return;
    }
    
    if (volume>1.0) 
    {
        // std::cout << "SoundObject::setVolume -> volume out of range (" << volume <<") for sample " << m_name << std::endl ;
        m_volume = 1.0;
    }

    
    m_volume = volume;
    m_soundPlayer->setVolume(m_volume);
}

