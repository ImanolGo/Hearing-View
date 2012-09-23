//
//  Sates.cpp
//  HearingView
//
//  Created by Imanolgo on 6/24/12.
//

#include "Visuals.h"
#include "AppManager.h"
#include "SoundManager.h"
#include "Event.h"
#include "EventManager.h"
#include "ViewManager.h"

#include "States.h"


State::State(const std::string& name,const ofPoint& pos):
    m_name(name),
    m_pos(pos),
    m_circleState(NULL),
    m_textState(NULL)

{
    //Intentionally left empty
}


State::~State()
{
    if(m_circleState)
    {
        AppManager::getInstance().getViewManager().removeVisual(*m_circleState);
    }
    
    delete m_circleState;
    m_circleState = NULL;
    
    if(m_textState)
    {
        AppManager::getInstance().getViewManager().removeVisual(*m_textState);
    }
    
    delete m_textState;
    m_textState = NULL;
}


void State::initialize()
{
    std::cout<<"State-> " << m_name << ": initialized." <<std::endl;
    m_circleState = new CircleVisual(m_pos,100,100);
    m_circleState->setColor(ofColor(255,255,255,100));
    m_textState = new TextVisual(m_pos,20,20);
    m_textState->setColor(ofColor(0,0,0,100));
    m_textState->setText(this->getName(),20);
    AppManager::getInstance().getViewManager().addVisual(*m_textState);
    AppManager::getInstance().getViewManager().addVisual(*m_circleState,1);

    
}

void IdleState::onEnter()
{
    std::cout<<"IdleState-> OnEnter." <<std::endl;
    AppManager::getInstance().getSoundManager().fadeTube(0.7,10.0);
    AppManager::getInstance().getEventManager().removeAllTimedEvents();
    m_circleState->setColor(ofColor(255,255,255,255));
    m_textState->setColor(ofColor(0,0,0,255));
    
    
}

void IdleState::onExit()
{
    std::cout<<"IdleState-> OnExit." <<std::endl;
    m_circleState->setColor(ofColor(255,255,255,100));
    m_textState->setColor(ofColor(0,0,0,100));
}


void AmbienceState::onEnter()
{
    std::cout<<"AmbienceState-> OnEnter." <<std::endl;
    AppManager::getInstance().getSoundManager().fadeTube(1.0,5.0);
    AppManager::getInstance().getEventManager().setTimedEvent("TimeOut", 20); //3 min timed event
    m_circleState->setColor(ofColor(255,255,255,255));
    m_textState->setColor(ofColor(0,0,0,255));
    
}

void AmbienceState::onExit()
{
    std::cout<<"AmbienceState-> OnExit." <<std::endl;
    m_circleState->setColor(ofColor(255,255,255,100));
    m_textState->setColor(ofColor(0,0,0,100));
    
}

void SamplerState::onEnter()
{
    std::cout<<"SamplerState-> OnEnter." <<std::endl;
    AppManager::getInstance().getSoundManager().fadeTube(0.0,5.0);
    AppManager::getInstance().getSoundManager().playSamples();
    m_circleState->setColor(ofColor(255,255,255,255));
    m_textState->setColor(ofColor(0,0,0,255));
    
}

void SamplerState::onExit()
{
    std::cout<<"SamplerState-> OnExit." <<std::endl;
    AppManager::getInstance().getSoundManager().fadeSample(0.0, 5.0);
    m_circleState->setColor(ofColor(255,255,255,100));
    m_textState->setColor(ofColor(0,0,0,100));
    
}


