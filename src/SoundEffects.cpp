//
//  SoundEffects.cpp
//  HearingView
//
//  Created by Imanolgo on 6/24/12.
//

#include <math.h>

#include "AppManager.h"
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



FadeLinear::FadeLinear(SoundObject& sound): FadeSound(sound)
{
    
}

void FadeLinear::update(double dt)
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
    
}

FadeLog::FadeLog(SoundObject& sound): FadeSound(sound)
{
    
}

void FadeLog::update(double dt)
{
    m_elapsedTime = m_elapsedTime + dt;
    
    if (m_elapsedTime>=m_fadeTime) {
        m_sound.setVolume(m_to);
        this->stop();
        return;
        
    }
    
    float base = 10; //2.71828182845904523536028747135266249775724709369995;  
    float pct = log10(m_fadeTime/(m_fadeTime + (base-1) * m_elapsedTime)) + 1; 
    float fadeValue = (pct * (m_from - m_to) + m_to);
    m_sound.setVolume(fadeValue);
    
}

FadeExp::FadeExp(SoundObject& sound): FadeSound(sound)
{
    
}

void FadeExp::update(double dt)
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
    
}




