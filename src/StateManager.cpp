//
//  SoundManager.cpp
//  HearingView
//
//  Created by Imanolgo on 07/05/12.
//


#include "StateMachine.h"
#include "States.h"
#include "StateManager.h"
#include "AppManager.h"
#include "ofxUI.h"


StateManager::StateManager(): m_stateMachine(NULL)
{
    m_stateMachine = new StateMachine();
}

StateManager::~StateManager()
{
    delete m_stateMachine;
    m_stateMachine = NULL;
}


void StateManager::setup()
{
    
     //Add to state machine and create transition
    
    IdleState* idleState = new IdleState("IdleState");

    m_stateMachine->addState(idleState);
    
    SamplerState* samplerState = new SamplerState("SamplerState");
    m_stateMachine->addState(samplerState);
    
    AmbienceState* ambienceState = new AmbienceState("AmbienceState");
    m_stateMachine->addState(ambienceState);
   
    m_stateMachine->createTransition("IdleState", "AmbienceState", "SensorON");
    m_stateMachine->createTransition("AmbienceState", "IdleState", "SensorOFF");
    m_stateMachine->createTransition("AmbienceState", "SamplerState", "TimeOut");
    m_stateMachine->createTransition("SamplerState", "AmbienceState", "EndSampler");
    m_stateMachine->createTransition("SamplerState", "IdleState", "SensorOFF");
    
    m_stateMachine->setCurrentState("IdleState");
    
    
}


void StateManager::guiEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName(); 
	int kind = e.widget->getKind(); 
	cout << "got event from: " << name << endl; 
    
    if(name == "EndSampler")
	{
		m_stateMachine->handleEvent(name);
	}
    
    else if(name == "Sensor")
	{
		ofxUIToggle *toggle = (ofxUIToggle *) e.widget; 
        
        if(toggle->getValue() == true)
        {
            m_stateMachine->handleEvent("SensorON");
        }
        else
        {
            m_stateMachine->handleEvent("SensorOFF");
        }
        
	}
    
}





