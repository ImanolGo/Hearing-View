//
//  EvenManager.cpp
//  HearingView
//
//  Created by Imanolgo on 05/07/12.
//


#include "Event.h"
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
}

EventManager::~EventManager()
{
    delete m_gui;
    m_gui = NULL;
    m_stateManager = NULL;
}


void EventManager::setup()
{
    
    float dim = 32; 
    m_gui->addWidgetDown(new ofxUILabel("HEARING VIEW", OFX_UI_FONT_LARGE)); 
    m_gui->addWidgetDown(new ofxUIToggle(dim, dim, false, "SENSOR"));
    vector<string> vnames; vnames.push_back("Day_Dry"); vnames.push_back("Night_Dry"); vnames.push_back("Day_Rain");
    vnames.push_back("Night_Rain");
    ofxUIRadio* radio = (ofxUIRadio *) m_gui->addWidgetDown(new ofxUIRadio(dim, dim, "WEATHER CONDITIONS", vnames, OFX_UI_ORIENTATION_VERTICAL)); 
    radio->activateToggle("Day_Dry"); 
    
    vnames.clear();
    vnames.push_back("Summer"); vnames.push_back("Autumn"); vnames.push_back("Winter");
    vnames.push_back("Spring");
    radio = (ofxUIRadio *) m_gui->addWidgetDown(new ofxUIRadio(dim, dim, "SEASONS", vnames, OFX_UI_ORIENTATION_VERTICAL)); 
    radio->activateToggle("Summer");
    
    vnames.clear();
    vnames.push_back("EndSampler"); vnames.push_back("TimeOut");
    radio = (ofxUIRadio *) m_gui->addWidgetDown(new ofxUIRadio(dim, dim, "SAMPLER", vnames, OFX_UI_ORIENTATION_VERTICAL)); 
    radio->activateToggle("End");
    
    ofAddListener(m_gui->newGUIEvent, this, &EventManager::guiEvent);
    m_stateManager = &AppManager::getInstance().getStateManager();
}


void EventManager::update(double dt)
{
	for(TimedEventList::iterator it = m_timeEvents.begin(); it != m_timeEvents.end();) {
		(*it)->update(dt);	
	}
}

void EventManager::setEvent(Event event)
{
    ofxUIToggle *toggle = (ofxUIToggle*) m_gui->getWidget(event.getName());
    //toggle->setValue();
    
    std::cout << "EventManager-> SetEvent: " << event.getName() <<std::endl; 
    m_stateManager->handleEvent(event);
}

void EventManager::setTimedEvent(const std::string& name, double delay)
{
   m_timeEvents.push_back(new TimedEvent(name,delay));
	
}

void EventManager::removeTimedEvent(TimedEvent& timeEvent)
{
    for(TimedEventList::iterator it = m_timeEvents.begin(); it != m_timeEvents.end();) {
		if(*it == &timeEvent) {
			delete *it; 
			it = m_timeEvents.erase(it);
		}		
	}
}

void EventManager::removeAllTimedEvents()
{
    for(TimedEventList::iterator it = m_timeEvents.begin(); it != m_timeEvents.end();) {
		delete *it; 
	}

     m_timeEvents.clear();
}

void EventManager::triggerTimedEvent(TimedEvent& timedEvent)
{
    this->setEvent(timedEvent);
    this->removeTimedEvent(timedEvent);	
}

void EventManager::guiEvent(ofxUIEventArgs &e)
{
    
    string name = e.widget->getName(); 
	int kind = e.widget->getKind(); 
	cout << "got event from: " << name << endl; 
    
    
    if(name == "SENSOR")
	{
		ofxUIToggle *toggle = (ofxUIToggle *) e.widget; 
        std::cout << name << "\t value: " << toggle->getValue() << std::endl; 
        
        if(toggle->getValue() == 1)
        {
            m_stateManager->handleEvent(Event("SensorON"));
        }
        else
        {
            m_stateManager->handleEvent(Event("SensorOFF"));
        }
        
	}
    
    else
    {
	    ofxUIToggle *toggle = (ofxUIToggle *) e.widget; 
        std::cout << name << "\t value: " << toggle->getValue() << std::endl; 
        m_stateManager->handleEvent(Event(name));
    }
       
    
}






