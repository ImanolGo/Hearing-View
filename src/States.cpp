//
//  Sates.cpp
//  HearingView
//
//  Created by Imanolgo on 6/24/12.
//

#include "ofMain.h"
#include "AppManager.h"
#include "SoundManager.h"

#include "States.h"



void IdleState::onEnter()
{
    AppManager::getInstance().getSoundManager().fadeTube(0.7,10.0);
    
}

void IdleState::onExit()
{
    
}


void AmbienceState::onEnter()
{
    AppManager::getInstance().getSoundManager().fadeTube(1.0,5.0);
    
}

void AmbienceState::onExit()
{
    
}

void SamplerState::onEnter()
{
    AppManager::getInstance().getSoundManager().fadeTube(0.0,5.0);
    AppManager::getInstance().getSoundManager().playSamples();
    
}

void SamplerState::onExit()
{
    AppManager::getInstance().getSoundManager().fadeSample(0.0, 5.0);
    
}


