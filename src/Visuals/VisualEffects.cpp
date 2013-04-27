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


VisualEffect::VisualEffect(Visual& visual):m_visual(visual),m_elapsedTime(0.0),m_isActive(false)
{
	// intentionally left empty
}

void VisualEffect::start()
{
	m_isActive = true;
    AppManager::getInstance().getVisualEffectsManager().addVisualEffect(*this);
    
}


void VisualEffect::stop()
{
	m_isActive = false;
	AppManager::getInstance().getVisualEffectsManager().removeVisualEffect(*this);
}


//==============================================================================
//================================  FADE VISUAL ================================
//==============================================================================

FadeVisual::FadeVisual(Visual& visual): VisualEffect(visual),
    m_elapsedTime(0),
    m_from(0),
    m_to(1),
    m_fadeTime(1000)

{
	// intentionally left empty
}



void FadeVisual::setParameters(float from, float to, float fadeTime)
{
	m_from = from;
	m_to = to;
    m_fadeTime = fadeTime;
}

void FadeVisual::stop(){
	VisualEffect::stop();
}

void FadeVisual::start(){
	VisualEffect::start();
}


FadeVisualLinear::FadeVisualLinear(Visual& visual): FadeVisual(visual)
{
    
}

void FadeVisualLinear::update(double dt)
{
    m_elapsedTime = m_elapsedTime + dt;
    
    if (m_elapsedTime>=m_fadeTime) {
        m_visual.setAlpha(m_to);
        this->stop();
        return;
        
    }
    
    float pct = 1.0 - (m_elapsedTime / m_fadeTime); 
    float fadeValue = (pct * (m_from - m_to) + m_to);
    m_visual.setAlpha(fadeValue);
    
}

FadeVisualLog::FadeVisualLog(Visual& visual): FadeVisual(visual)
{
    
}

void FadeVisualLog::update(double dt)
{
    m_elapsedTime = m_elapsedTime + dt;
    
    if (m_elapsedTime>=m_fadeTime) {
        m_visual.setAlpha(m_to);
        this->stop();
        return;
        
    }
    
    float base = 10; //2.71828182845904523536028747135266249775724709369995;  
    float pct = log10(m_fadeTime/(m_fadeTime + (base-1) * m_elapsedTime)) + 1; 
    float fadeValue = (pct * (m_from - m_to) + m_to);
    m_visual.setAlpha(fadeValue);
    
}

FadeVisualExp::FadeVisualExp(Visual& visual): FadeVisual(visual)
{
    
}

void FadeVisualExp::update(double dt)
{
    m_elapsedTime = m_elapsedTime + dt;
    
    if (m_elapsedTime>=m_fadeTime) {
        m_visual.setAlpha(m_to);
        this->stop();
        return;
        
    }
    
    float base = 10.0f;
    float pct = - pow(base,(float)((m_elapsedTime * 1.04 - m_fadeTime)/m_fadeTime)) + 1.09; 
    float fadeValue = (pct * (m_from - m_to) + m_to);
    m_visual.setAlpha(fadeValue);
    
}


