//
//  EvenManager.cpp
//  HearingView
//
//  Created by Imanolgo on 05/07/12.
//


#include "EventManager.h"
#include "StateManager.h"
#include "AppManager.h"
#include "ofxUI.h"


EventManager::EventManager(): m_gui(NULL),m_stateManager(NULL)
{
    float dim = 32; 
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float length = 320-xInit; 
    
    m_gui = new ofxUICanvas(0,0,length+xInit*2.0,ofGetHeight());
    m_stateManager = AppManager::getInstance().getEventManager();
}

EventManager::~EventManager()
{
    delete m_gui;
    m_gui = NULL;
    m_stateManager = NULL;
}


void StateManager::setup()
{
    
    float dim = 32; 
    m_gui->addWidgetDown(new ofxUILabel("HEARING VIEW", OFX_UI_FONT_LARGE)); 
    m_gui->addWidgetDown(new ofxUIToggle(dim, dim, false, "SENSOR"));
    vector<string> vnames; vnames.push_back("Day_Dry"); vnames.push_back("Night_Dry"); vnames.push_back("Day_Rain");
    vnames.push_back("Night_Rain");
    ofxUIRadio *radio = (ofxUIRadio *) m_gui->addWidgetDown(new ofxUIRadio(dim, dim, "WEATHER CONDITIONS", vnames, OFX_UI_ORIENTATION_VERTICAL)); 
    radio->activateToggle("Day_Dry"); 
    
    vnames.clear();
    vnames.push_back("Summer"); vnames.push_back("Autumn"); vnames.push_back("Winter");
    vnames.push_back("Spring");
    ofxUIRadio *radio2 = (ofxUIRadio *) m_gui->addWidgetDown(new ofxUIRadio(dim, dim, "SEASONS", vnames, OFX_UI_ORIENTATION_VERTICAL)); 
    radio->activateToggle("Summer");
    
    m_gui->addWidgetDown(new ofxUIButton(dim, dim, false, "EndSampler"));
    m_gui->addWidgetDown(new ofxUIButton(dim, dim, false, "TimeOut"));
    
    ofAddListener(m_gui->newGUIEvent, this, &StateManager::guiEvent);
    
    
}


void StateManager::guiEvent(ofxUIEventArgs &e)
{
    
    string name = e.widget->getName(); 
	int kind = e.widget->getKind(); 
	cout << "got event from: " << name << endl; 
    
    
    if(name == "Sensor")
	{
		ofxUIToggle *toggle = (ofxUIToggle *) e.widget; 
        
        if(toggle->getValue() == true)
        {
            m_stateManager->handleEvent("SensorON");
        }
        else
        {
            m_stateManager->handleEvent("SensorOFF");
        }
        
	}
    
    else
    {
        m_stateManager->handleEvent(name);
        
    }
    
}






