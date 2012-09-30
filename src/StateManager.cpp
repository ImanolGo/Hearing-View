//
//  SoundManager.cpp
//  HearingView
//
//  Created by Imanolgo on 07/05/12.
//


#include "StateMachine.h"
#include "States.h"
#include "StateManager.h"
#include "DateManager.h"
#include "AppManager.h"
#include "ofxUI.h"
#include "Event.h"
#include "ofMain.h"


StateManager::StateManager(): m_stateMachine(NULL), m_dateManager(NULL)
{
    m_stateMachine = new StateMachine();
}

StateManager::~StateManager()
{
    delete m_stateMachine;
    m_stateMachine = NULL;
    m_dateManager = NULL;
}


void StateManager::setup()
{
    
    m_dateManager = &AppManager::getInstance().getDateManager();
    
     //Add to state machine and create transition
    IdleState* idleState = new IdleState("IdleState",ofPoint(1000,200));
    idleState->initialize();
    m_stateMachine->addState(idleState);
    
    SamplerState* samplerState = new SamplerState("SamplerState",ofPoint(800,400));
    samplerState->initialize();
    m_stateMachine->addState(samplerState);
    
    AmbienceState* ambienceState = new AmbienceState("AmbienceState",ofPoint(1200,400));
    ambienceState->initialize();
    m_stateMachine->addState(ambienceState);
   
    m_stateMachine->createTransition("IdleState", "AmbienceState",Event("SENSOR",1));
    m_stateMachine->createTransition("AmbienceState", "IdleState",Event("SENSOR",0));
    m_stateMachine->createTransition("AmbienceState", "SamplerState",Event("TimeOut"));
    m_stateMachine->createTransition("SamplerState", "AmbienceState", Event("END_SAMPLER"));
    m_stateMachine->createTransition("SamplerState", "IdleState", Event("SENSOR",0));
    
    std::cout<< m_dateManager->getTime() <<"- StateManager-> initialized "<<std::endl;
    ofLogNotice()<< m_dateManager->getTime() <<"- StateManager-> initialized ";
    
    m_stateMachine->setCurrentState("IdleState");
    
}


void StateManager::handleEvent(const Event& event)
{
    m_stateMachine->handleEvent(event);
}









