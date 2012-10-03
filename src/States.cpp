//
//  Sates.cpp
//  HearingView
//
//  Created by Imanolgo on 6/24/12.
//

#include "Visuals.h"
#include "AppManager.h"
#include "SoundManager.h"
#include "ViewManager.h"
#include "Event.h"
#include "EventManager.h"
#include "ViewManager.h"
#include "DateManager.h"

#include "States.h"

const double State::FADE_TIME = 3;

State::State(const std::string& name,const ofPoint& pos):
    m_name(name),
    m_pos(pos),
    m_circleState(NULL),
    m_textState(NULL),
    m_dateManager(NULL)

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
    
    m_dateManager = NULL;
}


void State::initialize()
{
    m_dateManager = &AppManager::getInstance().getDateManager();

    m_circleState = new CircleVisual(m_pos,100,100);
    m_circleState->setColor(ofColor(255,255,255,100));
    m_textState = new TextVisual(m_pos,20,20);
    m_textState->setColor(ofColor(0,0,0,100));
    m_textState->setText(this->getName(),20);
    AppManager::getInstance().getViewManager().addVisual(*m_textState);
    AppManager::getInstance().getViewManager().addVisual(*m_circleState,1);
    
    std::cout<<m_dateManager->getTime()<<"- State->" <<m_name<< " initialized." <<std::endl;
    ofLogNotice()<<m_dateManager->getTime()<<"- State->" <<m_name<< " initialized.";
    
}

void IdleState::onEnter()
{
    std::cout<<m_dateManager->getTime()<<"- IdleState-> OnEnter." <<std::endl;
    ofLogNotice()<<m_dateManager->getTime()<<"- IdleState-> OnEnter.";
    AppManager::getInstance().getViewManager().fadeVisual(*m_circleState, 255, State::FADE_TIME,ViewManager::LOGARITHMIC);
    AppManager::getInstance().getViewManager().fadeVisual(*m_textState, 255, State::FADE_TIME,ViewManager::LOGARITHMIC);
    AppManager::getInstance().getSoundManager().fadeTube(0.7,State::FADE_TIME, SoundManager::EXPONENTIAL);
    AppManager::getInstance().getEventManager().removeAllTimedEvents();
    
}

void IdleState::onExit()
{
    std::cout<<m_dateManager->getTime()<<"- IdleState-> OnExit." <<std::endl;
    ofLogNotice()<<m_dateManager->getTime()<<"- IdleState-> OnExit.";
    AppManager::getInstance().getViewManager().fadeVisual(*m_circleState, 100, State::FADE_TIME,ViewManager::LOGARITHMIC);
    AppManager::getInstance().getViewManager().fadeVisual(*m_textState, 100, State::FADE_TIME,ViewManager::LOGARITHMIC);
}


void AmbienceState::onEnter()
{
    std::cout<<m_dateManager->getTime()<<"- AmbienceState-> OnEnter." <<std::endl;
    ofLogNotice()<<m_dateManager->getTime()<<"- AmbienceState-> OnEnter.";
    AppManager::getInstance().getSoundManager().fadeTube(1.0,FADE_TIME,SoundManager::EXPONENTIAL);
    AppManager::getInstance().getEventManager().setTimedEvent("TimeOut", 10); //3 min timed event
    AppManager::getInstance().getViewManager().fadeVisual(*m_circleState, 255, State::FADE_TIME,ViewManager::LOGARITHMIC);
    AppManager::getInstance().getViewManager().fadeVisual(*m_textState, 255, State::FADE_TIME,ViewManager::LOGARITHMIC);
    
}

void AmbienceState::onExit()
{
    std::cout<<m_dateManager->getTime()<<"- AmbienceState-> OnExit." <<std::endl;
    ofLogNotice()<<m_dateManager->getTime()<<"- AmbienceState-> OnExit.";
    AppManager::getInstance().getViewManager().fadeVisual(*m_circleState, 100, State::FADE_TIME,ViewManager::LOGARITHMIC);
    AppManager::getInstance().getViewManager().fadeVisual(*m_textState, 100, State::FADE_TIME,ViewManager::LOGARITHMIC);
}

void SamplerState::onEnter()
{
    std::cout<<m_dateManager->getTime()<<"- SamplerState-> OnEnter." <<std::endl;
    ofLogNotice()<<m_dateManager->getTime()<<"- SamplerState-> OnEnter.";
    AppManager::getInstance().getSoundManager().fadeTube(0.0,FADE_TIME,SoundManager::EXPONENTIAL);
    AppManager::getInstance().getSoundManager().playSamples();
    AppManager::getInstance().getSoundManager().fadeSample(0.0,1.0, FADE_TIME,SoundManager::EXPONENTIAL);
    AppManager::getInstance().getViewManager().fadeVisual(*m_circleState, 255, State::FADE_TIME,ViewManager::LOGARITHMIC);
    AppManager::getInstance().getViewManager().fadeVisual(*m_textState, 255, State::FADE_TIME,ViewManager::LOGARITHMIC);
    
}

void SamplerState::onExit()
{
    std::cout<<m_dateManager->getTime()<<"- SamplerState-> OnExit." <<std::endl;
    ofLogNotice()<<m_dateManager->getTime()<<"- SamplerState-> OnExit.";
    AppManager::getInstance().getSoundManager().fadeSample(0.0, FADE_TIME,SoundManager::EXPONENTIAL);
    AppManager::getInstance().getViewManager().fadeVisual(*m_circleState, 100, State::FADE_TIME,ViewManager::LOGARITHMIC);
    AppManager::getInstance().getViewManager().fadeVisual(*m_textState, 100, State::FADE_TIME,ViewManager::LOGARITHMIC);
    
}


