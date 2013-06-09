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


SoundEffect::SoundEffect(SoundObject& sound,EasingFunction function, EasingType type): m_sound(sound), m_function(function), m_isActive(false), m_animationTime(1000.0), m_elapsedTime(0.0),	m_elaspedTimeToStart(0.0), m_type(type)
{
	// intentionally left empty
}

void SoundEffect::start(double startTime)
{
	m_elapsedTime = 0.0;
	m_elaspedTimeToStart = 0.0;
	m_isActive = true; 
	m_startTime = startTime;

    AppManager::getInstance().getSoundEffectsManager().addSoundEffect(*this);
    
}


void SoundEffect::stop()
{
	m_isActive = false;
	AppManager::getInstance().getSoundEffectsManager().removeSoundEffect(*this);
}

double SoundEffect::function(double t, double from, double to, double duration) const 
{
	double c = to - from;
	switch (m_function)
	{
		case LINEAR:
			return  c*(t / duration) + from;
			break;
            
		case EXPONENTIAL:
			if (m_type== EASE_IN_OUT)
			{
				t /= duration/2;
				if (t < 1) return c/2 * std::pow( 2, 10 * (t - 1) ) + from;
				t--;
				return c/2 * ( -std::pow( 2, -10 * t) + 2 ) + from;
				
			}
			else if (m_type==EASE_OUT)
			{
				return c * ( -std::pow( 2, -10 * t/duration ) + 1 ) + from;
			}
			else
			{
				return c * std::pow( 2, 10 * (t/duration - 1) ) + from;
                
			}
			break;
            
		case CIRCULAR:
			if (m_type==EASE_IN_OUT)
			{
				t /= duration/2;
				if (t < 1) return -c/2 * (std::sqrt(1 - t*t) - 1) + from;
				t -= 2;
				return c/2 * (std::sqrt(1 - t*t) + 1) + from;
			}
			else if (m_type==EASE_OUT)
			{
				t /= duration;
				t--;
				return c * std::sqrt(1 - t*t) + from;
			}
			else
			{
				t /= duration;
				return -c * (std::sqrt(1 - t*t) - 1) + from;
			}
			break;
            
		case QUADRATIC:
			if (m_type==EASE_IN_OUT)
			{
				t /= duration/2;
				if (t < 1) return c/2*t*t + from;
				t--;
				return -c/2 * (t*(t-2) - 1) + from;
                
			}
			else if (m_type==EASE_OUT)
			{
				t /= duration;
				return -c * t*(t-2) + from;
				
			}
			else
			{
				t/=duration;
				return c*t*t + from;
			}
			break;
            
		case CUBIC:
			if (m_type==EASE_IN_OUT)
			{
				t /= duration/2;
				if (t < 1) return c/2*t*t*t + from;
				t -= 2;
				return c/2*(t*t*t + 2) + from;
                
			}
			else if (m_type==EASE_OUT)
			{
				t /= duration;
				t--;
				return c*(t*t*t + 1) + from;
			}
			else
			{
				t /= duration;
				return c*t*t*t + from;
			}
			break;
            
		case QUARTIC:
			if (m_type==EASE_IN_OUT)
			{
				t /= duration/2;
				if (t < 1) return c/2*t*t*t*t + from;
				t -= 2;
				return -c/2 * (t*t*t*t - 2) + from;
                
			}
			else if (m_type==EASE_OUT)
			{
				t /= duration;
				t--;
				return -c * (t*t*t*t - 1) + from;
				
			}
			else
			{
				t /= duration;
				return c*t*t*t*t + from;
			}
			break;
            
		case QUINTIC:
			if (m_type==EASE_IN_OUT)
			{
				t /= duration/2;
				if (t < 1) return c/2*t*t*t*t*t + from;
				t -= 2;
				return c/2*(t*t*t*t*t + 2) + from;
                
			}
			else if (m_type==EASE_OUT)
			{
				t /= duration;
				t--;
				return c*(t*t*t*t*t + 1) + from;
                
			}
			else
			{
				t /= duration;
				return c*t*t*t*t*t + from;
			}
			break;
            
		case SINUSOIDAL:
			if (m_type==EASE_IN_OUT)
			{
				return -c/2 * (std::cos(PI*t/duration) - 1) + from;
			}
			else if (m_type==EASE_OUT)
			{
				return c * std::sin(t/duration * (PI/2)) + from;
                
			}
			else
			{
				return -c * std::cos(t/duration * (PI/2)) + c + from;
			}
			break;
            
		default: 
        {
            double percent = c*(t/duration) + from;
            return  c*(t/duration) + from; //linear is the default
        }
			
	}
}

//==============================================================================
//================================  FADE SOUND =================================
//==============================================================================

FadeSound::FadeSound(SoundObject& sound,EasingFunction function, EasingType type): SoundEffect(sound,function,type),
    m_volume(1.0), m_startVolume(0.0),m_endVolume(1.0)    
{
	// intentionally left empty
}


void FadeSound::setParameters(double startVolume,double endVolume, double animationTime)
{
	m_elapsedTime = 0.0;
	m_sound.setVolume(startVolume);
	m_startVolume = startVolume;
	m_endVolume = endVolume;
	m_animationTime = animationTime;
}

void FadeSound::setParameters(double endVolume, double animationTime)
{
	m_elapsedTime = 0.0;
	m_startVolume = m_sound.getVolume();
	m_endVolume = endVolume;
	m_animationTime = animationTime;
}


void FadeSound::stop(){
	SoundEffect::stop();
}

void FadeSound::start(double startTime){
	SoundEffect::start(startTime);
}

void FadeSound::update(double dt)
{
    if(m_elaspedTimeToStart < m_startTime) {
        m_elaspedTimeToStart += dt;
		return;
	}

	m_elapsedTime = m_elapsedTime + dt;
 
	if(m_elapsedTime >= m_animationTime || m_sound.getVolume() == m_endVolume) {	
        m_sound.setVolume(m_endVolume);
		this->stop();
		return;
	}
    
	m_volume = this->function(m_elapsedTime,m_startVolume,m_endVolume,m_animationTime);
	m_sound.setVolume(m_volume);
    
    Event event("SAMPLE VOLUME",m_volume);
    if(m_sound.getName()=="tube")
    {
        event.setName("TUBE VOLUME");
    }
    
    AppManager::getInstance().getEventManager().setEvent(event);
}





