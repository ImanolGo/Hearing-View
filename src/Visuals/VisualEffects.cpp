//
//  VisualEffects.cpp
//  HearingView
//
//  Created by Imanolgo on 6/24/12.
//

#include <math.h>

#include "AppManager.h"
#include "VisualEffectsManager.h"
#include "VisualEffects.h"
#include "Visuals.h"

//==============================================================================
//========================= VISUAL EFFECT ==================================
//==============================================================================


VisualEffect::VisualEffect(Visual& visual, EasingFunction function, EasingType type): m_visual(visual), m_function(function), m_isActive(false), m_animationTime(1000.0), m_elapsedTime(0.0),	m_elaspedTimeToStart(0.0), m_type(type)
{
	// intentionally left empty
}


void VisualEffect::start(double startTime)
{
    m_elapsedTime = 0.0;
	m_elaspedTimeToStart = 0.0;
	m_isActive = true; 
	m_startTime = startTime;
    AppManager::getInstance().getVisualEffectsManager().addVisualEffect(*this);
    
}


void VisualEffect::stop()
{
	m_isActive = false;
	AppManager::getInstance().getVisualEffectsManager().removeVisualEffect(*this);
}

double VisualEffect::function(double t, double from, double to, double duration) const 
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
//================================  FADE VISUAL ================================
//==============================================================================

FadeVisual::FadeVisual(Visual& visual, EasingFunction function, EasingType type): VisualEffect(visual,function,type),
    m_alpha(1.0), m_startAlpha(0.0),m_endAlpha(1.0)
{
	// intentionally left empty
}



void FadeVisual::setParameters(double startAlpha,double endAlpha, double animationTime)
{
	m_elapsedTime = 0.0;
	m_visual.setAlpha(startAlpha);
	m_startAlpha = startAlpha;
	m_endAlpha = endAlpha;
	m_animationTime = animationTime;
}

void FadeVisual::setParameters(double endAlpha, double animationTime)
{
	m_elapsedTime = 0.0;
	m_startAlpha = m_visual.getAlpha();
	m_endAlpha = endAlpha;
	m_animationTime = animationTime;
}
void FadeVisual::stop(){
	VisualEffect::stop();
}

void FadeVisual::start(double startTime){
	VisualEffect::start(startTime);
}

void FadeVisual::update(double dt)
{
    if(m_elaspedTimeToStart < m_startTime) {
        m_elaspedTimeToStart += dt;
		return;
	}
    
	m_elapsedTime = m_elapsedTime + dt;
    
	if(m_elapsedTime >= m_animationTime) {	
        m_visual.setAlpha(m_endAlpha);
		this->stop();
		return;
	}
    
	m_alpha = this->function(m_elapsedTime,m_startAlpha,m_endAlpha,m_animationTime);
	m_visual.setAlpha(m_alpha);
    
}
