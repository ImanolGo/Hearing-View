//
//  Sates.cpp
//  HearingView
//
//  Created by Imanolgo on 6/24/12.
//

#include "Visuals.h"
#include "AppManager.h"
#include "SoundManager.h"
#include "StateManager.h"
#include "ViewManager.h"
#include "Event.h"
#include "EventManager.h"
#include "DateManager.h"

#include "States.h"

const double State::FADE_TIME = 3;

State::State(const std::string& name,const ofPoint& pos):
    m_name(name),
    m_pos(pos),
    m_circleState(NULL),
    m_textState(NULL),
    m_dateManager(NULL),
    m_stateManager(NULL)
{
    //Intentionally left empty
}


State::~State()
{
    if(m_circleState)
    {
        AppManager::getInstance().getViewManager().removeVisual(*m_circleState);
        delete m_circleState;
        m_circleState = NULL;
    }
    
    if(m_circleState)
    {
        AppManager::getInstance().getViewManager().removeVisual(*m_textState);
        delete m_textState;
        m_textState = NULL;
    }
    
    m_dateManager = NULL;
}


void State::initialize()
{
    m_dateManager = &AppManager::getInstance().getDateManager();
    m_stateManager = &AppManager::getInstance().getStateManager();

    m_circleState = new ImageVisual(m_pos,50,50,true);
    m_circleState->setImage("images/icons/button_selected.png");
    m_circleState->setColor(ofColor(255,255,255,100));
    m_textState = new TextVisual(m_pos,20,20, true);
    m_textState->setColor(ofColor(240,240,240,100));
    m_textState->setText(this->getName(),"Klavika-Bold.otf",13);
    AppManager::getInstance().getViewManager().addVisual(*m_textState,-1);
    AppManager::getInstance().getViewManager().addVisual(*m_circleState);
    
    std::cout<<m_dateManager->getTime()<<"- State->" <<m_name<< " initialized." <<std::endl;
    ofLogNotice()<<m_dateManager->getTime()<<"- State->" <<m_name<< " initialized.";
    
}

void IdleState::onEnter()
{
    std::cout<<m_dateManager->getTime()<<"- IdleState-> OnEnter." <<std::endl;
    ofLogNotice()<<m_dateManager->getTime()<<"- IdleState-> OnEnter.";
    AppManager::getInstance().getEventManager().removeAllTimedEvents();
    AppManager::getInstance().getViewManager().fadeVisual(*m_circleState, 255, State::FADE_TIME);
    AppManager::getInstance().getViewManager().fadeVisual(*m_textState, 255, State::FADE_TIME);
    AppManager::getInstance().getSoundManager().fadeTube(m_stateManager->m_V1,m_stateManager->m_t1);
    
    
}

void IdleState::onExit()
{
    std::cout<<m_dateManager->getTime()<<"- IdleState-> OnExit." <<std::endl;
    ofLogNotice()<<m_dateManager->getTime()<<"- IdleState-> OnExit.";
    AppManager::getInstance().getViewManager().fadeVisual(*m_circleState, 100, State::FADE_TIME);
    AppManager::getInstance().getViewManager().fadeVisual(*m_textState, 100, State::FADE_TIME);
}


void SensorOffTransitionState::onEnter()
{
    std::cout<<m_dateManager->getTime()<<"- SensorOffTransitionState-> OnEnter." <<std::endl;
    ofLogNotice()<<m_dateManager->getTime()<<"- SensorOffTransitionState-> OnEnter.";
    AppManager::getInstance().getEventManager().removeAllTimedEvents();
    AppManager::getInstance().getViewManager().fadeVisual(*m_circleState, 255, State::FADE_TIME);
    AppManager::getInstance().getViewManager().fadeVisual(*m_textState, 255, State::FADE_TIME);
    
    
    if(AppManager::getInstance().getSoundManager().getTubeVolume()>0.0f){
        AppManager::getInstance().getSoundManager().fadeTube(0.0f,m_stateManager->m_t4);
        AppManager::getInstance().getEventManager().setTimedEvent("ENTER_IDLE_STATE",m_stateManager->m_t4 +m_stateManager->m_t5);
        AppManager::getInstance().getSoundManager().fadeSample(0.0f,m_stateManager->m_t7);
    }
    else{
        AppManager::getInstance().getSoundManager().fadeSample(0.0f,m_stateManager->m_t7);
        AppManager::getInstance().getEventManager().setTimedEvent("ENTER_IDLE_STATE",m_stateManager->m_t7 +m_stateManager->m_t5);
        AppManager::getInstance().getSoundManager().fadeTube(0.0f,m_stateManager->m_t4);
        
    }
    
    AppManager::getInstance().getSoundManager().resetSamples();
}

void SensorOffTransitionState::onExit()
{
    std::cout<<m_dateManager->getTime()<<"- TransitionState-> OnExit." <<std::endl;
    ofLogNotice()<<m_dateManager->getTime()<<"- TransitionState-> OnExit.";
    AppManager::getInstance().getViewManager().fadeVisual(*m_circleState, 100, State::FADE_TIME);
    AppManager::getInstance().getViewManager().fadeVisual(*m_textState, 100, State::FADE_TIME);
}


void TubeOffTransitionState::onEnter()
{
    std::cout<<m_dateManager->getTime()<<"- TubeOffTransitionState-> OnEnter." <<std::endl;
    ofLogNotice()<<m_dateManager->getTime()<<"- TubeOffTransitionState-> OnEnter.";
    AppManager::getInstance().getViewManager().fadeVisual(*m_circleState, 255, State::FADE_TIME);
    AppManager::getInstance().getViewManager().fadeVisual(*m_textState, 255, State::FADE_TIME);
    
    AppManager::getInstance().getSoundManager().fadeTube(0.0f,m_stateManager->m_t4);
    AppManager::getInstance().getEventManager().setTimedEvent("ENTER_SAMPLER_STATE",m_stateManager->m_t4 +m_stateManager->m_t5);
    AppManager::getInstance().getSoundManager().fadeSample(0.0f,m_stateManager->m_t7);
}

void TubeOffTransitionState::onExit()
{
    std::cout<<m_dateManager->getTime()<<"- TubeOffTransitionState-> OnExit." <<std::endl;
    ofLogNotice()<<m_dateManager->getTime()<<"- TubeOffTransitionState-> OnExit.";
    AppManager::getInstance().getViewManager().fadeVisual(*m_circleState, 100, State::FADE_TIME);
    AppManager::getInstance().getViewManager().fadeVisual(*m_textState, 100, State::FADE_TIME);
}


void TubeState::onEnter()
{
    std::cout<<m_dateManager->getTime()<<"- TubeState-> OnEnter." <<std::endl;
    ofLogNotice()<<m_dateManager->getTime()<<"- TubeState-> OnEnter.";
    AppManager::getInstance().getSoundManager().fadeTube(m_stateManager->m_V3,m_stateManager->m_t2);
    AppManager::getInstance().getSoundManager().fadeSample(0.0f,m_stateManager->m_t2);
    AppManager::getInstance().getViewManager().fadeVisual(*m_circleState, 255, State::FADE_TIME);
    AppManager::getInstance().getViewManager().fadeVisual(*m_textState, 255, State::FADE_TIME);
    
    
    //if (m_dateManager->getDayTime()!= "NIG") { //if not night
         AppManager::getInstance().getEventManager().setTimedEvent("END_TUBE_STATE",m_stateManager->m_t2 + m_stateManager->m_t3);
    //}
    
}

void TubeState::onExit()
{
    std::cout<<m_dateManager->getTime()<<"- TubeState-> OnExit." <<std::endl;
    ofLogNotice()<<m_dateManager->getTime()<<"- TubeState-> OnExit.";
    AppManager::getInstance().getViewManager().fadeVisual(*m_circleState, 100, State::FADE_TIME);
    AppManager::getInstance().getViewManager().fadeVisual(*m_textState, 100, State::FADE_TIME);
}

void SamplerState::onEnter()
{
    std::cout<<m_dateManager->getTime()<<"- SamplerState-> OnEnter." <<std::endl;
    ofLogNotice()<<m_dateManager->getTime()<<"- SamplerState-> OnEnter.";
    AppManager::getInstance().getSoundManager().playNextSample(m_stateManager->m_V2);
    AppManager::getInstance().getViewManager().fadeVisual(*m_circleState, 255, State::FADE_TIME);
    AppManager::getInstance().getViewManager().fadeVisual(*m_textState, 255, State::FADE_TIME);
    
}

void SamplerState::onExit()
{
    std::cout<<m_dateManager->getTime()<<"- SamplerState-> OnExit." <<std::endl;
    ofLogNotice()<<m_dateManager->getTime()<<"- SamplerState-> OnExit.";
    AppManager::getInstance().getViewManager().fadeVisual(*m_circleState, 100, State::FADE_TIME);
    AppManager::getInstance().getViewManager().fadeVisual(*m_textState, 100, State::FADE_TIME);
    
}


void ShortTubeState::onEnter()
{
    std::cout<<m_dateManager->getTime()<<"- ShortTubeState-> OnEnter." <<std::endl;
    ofLogNotice()<<m_dateManager->getTime()<<"- ShortTubeState-> OnEnter.";
    AppManager::getInstance().getSoundManager().fadeTube(m_stateManager->m_V3,m_stateManager->m_t2);
    AppManager::getInstance().getSoundManager().fadeSample(0.0f,m_stateManager->m_t2);
    AppManager::getInstance().getEventManager().setTimedEvent("END_TUBE_STATE_SHORT", m_stateManager->m_t6); //3 min timed event
    AppManager::getInstance().getViewManager().fadeVisual(*m_circleState, 255, State::FADE_TIME);
    AppManager::getInstance().getViewManager().fadeVisual(*m_textState, 255, State::FADE_TIME);
    
}

void ShortTubeState::onExit()
{
    std::cout<<m_dateManager->getTime()<<"- ShortTubeState-> OnExit." <<std::endl;
    ofLogNotice()<<m_dateManager->getTime()<<"- ShortTubeState-> OnExit.";
    AppManager::getInstance().getViewManager().fadeVisual(*m_circleState, 100, State::FADE_TIME);
    AppManager::getInstance().getViewManager().fadeVisual(*m_textState, 100, State::FADE_TIME);
}


