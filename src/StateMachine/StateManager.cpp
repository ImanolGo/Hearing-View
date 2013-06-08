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
    //STATES
    
    float margin = ofGetHeight()/70.0;
    float widthVisuals = ofGetWidth() - 4*margin; 
    float heightVisuals = ofGetHeight()/3.0 - 4*margin;
    float w = 2*widthVisuals/5 - 2*margin;
    float h = heightVisuals - 4*margin;
    float x =  3*margin;
    float y =  8*margin + 2*heightVisuals;
    
    IdleState* idleState = new IdleState("IdleState",ofPoint(x + w/2,y+h/4));
    idleState->initialize();
    m_stateMachine->addState(idleState);

    SamplerState* samplerState = new SamplerState("SamplerState",ofPoint(x+w/4,y+3*h/4));
    samplerState->initialize();
    m_stateMachine->addState(samplerState);
    
    TubeState* tubeState = new TubeState("TubeState",ofPoint(x+3*w/4,y+3*h/4));
    tubeState->initialize();
    m_stateMachine->addState(tubeState);
    
    TubeStateShort* tubeStateShort = new TubeStateShort("TubeStateShort",ofPoint(x+3*w/4,y+3*h/4));
    tubeStateShort->initialize();
    m_stateMachine->addState(tubeStateShort);
   
    m_stateMachine->createTransition("IdleState", "TubeState",Event("SENSOR",1));
    m_stateMachine->createTransition("TubeState", "IdleState",Event("SENSOR",0));
    m_stateMachine->createTransition("TubeState", "SamplerState",Event("END_TUBE_STATE"));
    m_stateMachine->createTransition("SamplerState", "TubeStateShort", Event("END_ONE_SAMPLE"));
    m_stateMachine->createTransition("SamplerState", "TubeState", Event("END_ALL_SAMPLES"));
    m_stateMachine->createTransition("SamplerState", "IdleState", Event("SENSOR",0));
    m_stateMachine->createTransition("TubeStateShort", "IdleState", Event("SENSOR",0));
    m_stateMachine->createTransition("TubeStateShort", "SamplerState", Event("END_TUBE_STATE_SHORT"));
    
    std::cout<< m_dateManager->getTime() <<"- StateManager-> initialized "<<std::endl;
    ofLogNotice()<< m_dateManager->getTime() <<"- StateManager-> initialized ";
    
    m_stateMachine->setCurrentState("IdleState");
    
}


void StateManager::handleEvent(const Event& event)
{
    m_stateMachine->handleEvent(event);
}









