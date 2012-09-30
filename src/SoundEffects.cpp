//
//  SoundEffects.cpp
//  HearingView
//
//  Created by Imanolgo on 6/24/12.
//

#include <math.h>

#include "AppManager.h"
#include "Event.h"
#include "EventManager.h"
#include "SoundManager.h"
#include "SoundObject.h"
#include "SoundEffectsManager.h"
#include "SoundEffects.h"

//==============================================================================
//========================= SOUND EFFECT ==================================
//==============================================================================


SoundEffect::SoundEffect(SoundObject& sound):m_sound(sound),m_elapsedTime(0.0),m_isActive(false)
{
	// intentionally left empty
}

void SoundEffect::start()
{
	m_isActive = true;
    AppManager::getInstance().getSoundEffectsManager().addSoundEffect(*this);
    
}


void SoundEffect::stop()
{
	m_isActive = false;
	AppManager::getInstance().getSoundEffectsManager().removeSoundEffect(*this);
}


//==============================================================================
//================================  FADE SOUND =================================
//==============================================================================

FadeSound::FadeSound(SoundObject& sound): SoundEffect(sound),

    m_elapsedTime(0),
    m_from(0),
    m_to(1),
    m_fadeTime(1000)
    
{
	// intentionally left empty
}



void FadeSound::setParameters(float from, float to, float fadeTime)
{
	m_from = from;
	m_to = to;
    m_fadeTime = fadeTime;
}

void FadeSound::stop(){
	SoundEffect::stop();
}

void FadeSound::start(){
	SoundEffect::start();
}


FadeSoundLinear::FadeSoundLinear(SoundObject& sound): FadeSound(sound)
{
    
}

void FadeSoundLinear::update(double dt)
{
    m_elapsedTime = m_elapsedTime + dt;
    
    if (m_elapsedTime>=m_fadeTime) {
        m_sound.setVolume(m_to);
        this->stop();
        return;
        
    }
     
    float pct = 1.0 - (m_elapsedTime / m_fadeTime); 
    float fadeValue = (pct * (m_from - m_to) + m_to);
    m_sound.setVolume(fadeValue);
    
    Event event("SAMPLE VOLUME",fadeValue);
    if(m_sound.getName()=="tube")
    {
        event.setName("TUBE VOLUME");
    }
    
    AppManager::getInstance().getEventManager().setEvent(event);
}

FadeSoundLog::FadeSoundLog(SoundObject& sound): FadeSound(sound)
{
    
}

void FadeSoundLog::update(double dt)
{
    m_elapsedTime = m_elapsedTime + dt;
    
    if (m_elapsedTime>=m_fadeTime|| m_sound.getVolume() == m_to) {
        m_sound.setVolume(m_to);
        this->stop();
        return;
        
    }
    
    float base = 10; //2.71828182845904523536028747135266249775724709369995;  
    float pct = log10(m_fadeTime/(m_fadeTime + (base-1) * m_elapsedTime)) + 1; 
    float fadeValue = (pct * (m_from - m_to) + m_to);
    m_sound.setVolume(fadeValue);
    
    Event event("SAMPLE VOLUME",fadeValue);
    if(m_sound.getName()=="tube")
    {
        event.setName("TUBE VOLUME");
    }
    
    AppManager::getInstance().getEventManager().setEvent(event);
    
}

FadeSoundExp::FadeSoundExp(SoundObject& sound): FadeSound(sound)
{
    
}

void FadeSoundExp::update(double dt)
{
    m_elapsedTime = m_elapsedTime + dt;
    
    if (m_elapsedTime>=m_fadeTime) {
        m_sound.setVolume(m_to);
        this->stop();
        return;
        
    }
    
    float base = 10.0f;
    float pct = - pow(base,(float)((m_elapsedTime * 1.04 - m_fadeTime)/m_fadeTime)) + 1.09; 
    float fadeValue = (pct * (m_from - m_to) + m_to);
    m_sound.setVolume(fadeValue);
    
    Event event("SAMPLE VOLUME",fadeValue);
    if(m_sound.getName()=="tube")
    {
        event.setName("TUBE VOLUME");
    }
    
    AppManager::getInstance().getEventManager().setEvent(event);
    
}




