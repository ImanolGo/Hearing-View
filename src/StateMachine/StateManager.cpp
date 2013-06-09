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


StateManager::StateManager(): m_stateMachine(NULL), m_dateManager(NULL), m_t1(3.0f),m_t2(6.0f),m_t3(180.0f),m_t4(8.0f),m_t5(1.0f),
m_t6(60.0f),m_t7(2.0f),m_V1(70.0f),m_V2(70.0f),m_V3(100.0f)
{
    m_stateMachine = new StateMachine();
    //m_dateManager = &AppManager::getInstance().getDateManager();
}

StateManager::~StateManager()
{
    delete m_stateMachine;
    m_stateMachine = NULL;
    m_dateManager = NULL;
}


void StateManager::setup()
{
     //Add to state machine and create transition
    //STATES
    
     m_dateManager = &AppManager::getInstance().getDateManager();
    
    float margin = ofGetHeight()/70.0;
    
    float widthGUI = ofGetWidth() - 4*margin; 
    float heightGUI = ofGetHeight()/3.0 - 4*margin;
    float w = widthGUI/5 - 2*margin;
    float h = heightGUI - 4*margin;
    float x =  3*margin + 0.5*w;
    float y =  4*margin + heightGUI + heightGUI*0.5;
    
    IdleState* idleState = new IdleState("IdleState",ofPoint(x,y));
    idleState->initialize();
    m_stateMachine->addState(idleState);
    
    x =  5*margin + 1.5*w;
    TransitionState* transitionState = new TransitionState("TransitionState",ofPoint(x,y));
    transitionState->initialize();
    m_stateMachine->addState(transitionState);

    x =  7*margin + 2.5*w;
    TubeState* tubeState = new TubeState("TubeState",ofPoint(x,y));
    tubeState->initialize();
    m_stateMachine->addState(tubeState);
    
    x =  9*margin + 3.5*w;
    SamplerState* samplerState = new SamplerState("SamplerState",ofPoint(x,y));
    samplerState->initialize();
    m_stateMachine->addState(samplerState);
    
    x =  11*margin + 4.5*w;
    ShortTubeState* shortTubeState = new ShortTubeState("TubeStateShort",ofPoint(x,y));
    shortTubeState->initialize();
    m_stateMachine->addState(shortTubeState);
   
    m_stateMachine->createTransition("IdleState", "TubeState",Event("SENSOR",1));
    m_stateMachine->createTransition("TubeState", "TransitionState",Event("SENSOR",0));
    m_stateMachine->createTransition("TubeState", "SamplerState",Event("END_TUBE_STATE"));
    m_stateMachine->createTransition("SamplerState", "TubeStateShort", Event("END_SAMPLE"));
    m_stateMachine->createTransition("SamplerState", "TubeState", Event("END_ALL_SAMPLES"));
    m_stateMachine->createTransition("SamplerState", "TransitionState", Event("SENSOR",0));
    m_stateMachine->createTransition("TubeStateShort", "TransitionState", Event("SENSOR",0));
    m_stateMachine->createTransition("TubeStateShort", "SamplerState", Event("END_TUBE_STATE_SHORT"));
    m_stateMachine->createTransition("TransitionState", "TubeState",Event("SENSOR",1));
     m_stateMachine->createTransition("TransitionState", "IdleState",Event("ENTER_IDLE_STATE"));
    
    std::cout<< m_dateManager->getTime() <<"- StateManager-> initialized "<<std::endl;
    ofLogNotice()<< m_dateManager->getTime() <<"- StateManager-> initialized ";
}


void StateManager::start()
{
     std::cout<< m_dateManager->getTime() <<"- StateManager-> start "<<std::endl;
     ofLogNotice()<< m_dateManager->getTime() <<"- StateManager-> start ";
     m_stateMachine->setCurrentState("IdleState");
}

void StateManager::handleEvent(const Event& event)
{
    m_stateMachine->handleEvent(event);
    
    std::string name = event.getName();
    
    if(name=="t1 (s)")
    {
        m_t1 = (float) event.getValue();
        std::cout <<m_dateManager->getTime()<<"- StateManager-> t1 = " << m_t1 <<"s"<<std::endl;
        ofLogNotice() <<m_dateManager->getTime()<<"- StateManager-> t1 = " << m_t1 <<"s";
    }
    
    else if(name=="t2 (s)")
    {
        m_t2 = (float) event.getValue();
        std::cout <<m_dateManager->getTime()<<"- StateManager-> t2 = " << m_t2 <<"s"<<std::endl;
        ofLogNotice() <<m_dateManager->getTime()<<"- StateManager-> t2 = " << m_t2 <<"s";
    }
    
    else if(name=="t3 (s)")
    {
        m_t3 = (float) event.getValue();
        std::cout <<m_dateManager->getTime()<<"- StateManager-> t3 = " << m_t3 <<"s"<<std::endl;
        ofLogNotice() <<m_dateManager->getTime()<<"- StateManager-> t3 = " << m_t3 <<"s";
    }
    
    else if(name=="t4 (s)")
    {
        m_t4 = (float) event.getValue();
        std::cout <<m_dateManager->getTime()<<"- StateManager-> t4 = " << m_t4 <<"s"<<std::endl;
        ofLogNotice() <<m_dateManager->getTime()<<"- StateManager-> t4 = " << m_t4 <<"s";
    }
    
    else if(name=="t5 (s)")
    {
        m_t5 = (float) event.getValue();
        std::cout <<m_dateManager->getTime()<<"- StateManager-> t5 = " << m_t5 <<"s"<<std::endl;
        ofLogNotice() <<m_dateManager->getTime()<<"- StateManager-> t5 = " << m_t5 <<"s";
    }
    
    else if(name=="t6 (s)")
    {
        m_t6 = (float) event.getValue();
        std::cout <<m_dateManager->getTime()<<"- StateManager-> t6 = " << m_t6 <<"s"<<std::endl;
        ofLogNotice() <<m_dateManager->getTime()<<"- StateManager-> t6 = " << m_t6 <<"s";
    }
    
    else if(name=="t7 (s)")
    {
        m_t7 = (float) event.getValue();
        std::cout <<m_dateManager->getTime()<<"- StateManager-> t7 = " << m_t7 <<"s"<<std::endl;
        ofLogNotice() <<m_dateManager->getTime()<<"- StateManager-> t7 = " << m_t7 <<"s";
    }
    
    if(name=="V1 (%)")
    {
        m_V1 = (float) event.getValue();
        std::cout <<m_dateManager->getTime()<<"- StateManager-> V1 = " << m_V1 <<"s"<<std::endl;
        ofLogNotice() <<m_dateManager->getTime()<<"- StateManager-> V1 = " << m_V1 <<"s";
    }
    
    else if(name=="V2 (%)")
    {
        m_V2 = (float) event.getValue();
        std::cout <<m_dateManager->getTime()<<"- StateManager-> V2 = " << m_V2 <<"s"<<std::endl;
        ofLogNotice() <<m_dateManager->getTime()<<"- StateManager-> V2 = " <<m_V2 <<"s";
    }
    
    else if(name=="V3 (%)")
    {
        m_V3 = (float) event.getValue();
        std::cout <<m_dateManager->getTime()<<"- StateManager-> V3 = " << m_V3 <<"s"<<std::endl;
        ofLogNotice() <<m_dateManager->getTime()<<"- StateManager-> V3 = " << m_V3 <<"s";
    }
}









