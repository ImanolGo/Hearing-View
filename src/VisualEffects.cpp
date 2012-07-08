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

//==============================================================================
//========================= VISUAL EFFECT ==================================
//==============================================================================


VisualEffect::VisualEffect(ofImage& image):m_image(image),m_elapsedTime(0.0),m_isActive(false)
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

FadeVisual::FadeVisual(ofImage& image): VisualEffect(image),
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



