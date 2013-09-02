//
//  EvenManager.cpp
//  HearingView
//
//  Created by Imanolgo on 05/07/12.
//


#include "Event.h"
#include "EventManager.h"
#include "StateManager.h"
#include "WeatherStationManager.h"
#include "DateManager.h"
#include "SoundManager.h"
#include "GuiManager.h"
#include "SensorManager.h"
#include "AppManager.h"



EventManager::EventManager(): 
m_stateManager(NULL),
m_weatherStationManager(NULL),
m_dateManager(NULL),
m_soundManager(NULL),
m_guiManager(NULL),
m_sensorManager(NULL)
{
    
}

EventManager::~EventManager()
{
    m_stateManager = NULL;
    m_weatherStationManager = NULL;
    m_dateManager = NULL;
    m_soundManager = NULL;
    m_guiManager = NULL;
    m_sensorManager = NULL;
    
}


void EventManager::setup()
{
    m_stateManager = &AppManager::getInstance().getStateManager();
    m_guiManager = &AppManager::getInstance().getGuiManager();
    m_soundManager = &AppManager::getInstance().getSoundManager();
    m_dateManager = &AppManager::getInstance().getDateManager();
    m_weatherStationManager = &AppManager::getInstance().getWeatherStationManager();
    m_sensorManager = &AppManager::getInstance().getSensorManager();
    
    std::cout<< m_dateManager->getTime() <<"- EventManager-> initialized "<<std::endl;
    ofLogNotice() << m_dateManager->getTime() <<"- EventManager-> initialized ";
}


void EventManager::update(double dt)
{
    for (unsigned int i = 0; i < m_timeEvents.size(); i++ ) {
		m_timeEvents[i]->update(dt);
    }
}

void EventManager::setEvent(Event event)
{
    if(event.getValue()==0.0 || event.getValue()==1.0)
    {
        
        std::cout << m_dateManager->getTime() << "- EventManager-> SetEvent: " << event.getName() << ", " << event.getValue()<<std::endl;
        ofLogNotice() << m_dateManager->getTime() << "- EventManager-> SetEvent: " << event.getName() << ", " << event.getValue();
    }
     
    m_stateManager->handleEvent(event);
    m_dateManager->handleEvent(event);
    m_weatherStationManager->handleEvent(event);
    m_soundManager->handleEvent(event);
    m_guiManager->handleEvent(event);
    m_sensorManager->handleEvent(event);
    
}

void EventManager::setTimedEvent(const std::string& name, double delay)
{
    std::cout << m_dateManager->getTime() << " - EventManager-> setTimedEvent: " << name <<", delay "<<delay<<std::endl;
    ofLogNotice() << m_dateManager->getTime() << "- EventManager-> setTimedEvent: " << name <<", delay "<<delay;
    m_timeEvents.push_back(new TimedEvent(name,delay));
	
}

void EventManager::deleteTimedEvent(const TimedEvent& timedEvent)
{
    for(TimedEventList::iterator it = m_timeEvents.begin(); it != m_timeEvents.end();) {
		if(*it == &timedEvent) {
			delete *it; 
			it = m_timeEvents.erase(it);
		}	
        else
        {
            ++it;
        }
	}
}

void EventManager::removeAllTimedEvents()
{
    for(TimedEventList::iterator it = m_timeEvents.begin(); it != m_timeEvents.end();it++) {
		delete *it; 
	}
    
    m_timeEvents.clear();
}

void EventManager::triggerTimedEvent(const TimedEvent& timedEvent)
{
    this->setEvent(timedEvent);
    this->deleteTimedEvent(timedEvent);	
}

