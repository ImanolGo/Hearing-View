//
//  EvenManager.cpp
//  HearingView
//
//  Created by Imanolgo on 05/07/12.
//


#include "Event.h"
#include "EventManager.h"
#include "StateManager.h"
#include "WeatherManager.h"
#include "DateManager.h"
#include "SoundManager.h"
#include "GuiManager.h"
#include "AppManager.h"



EventManager::EventManager(): 
m_stateManager(NULL),
m_weatherManager(NULL),
m_dateManager(NULL),
m_soundManager(NULL),
m_guiManager(NULL)
{
    
}

EventManager::~EventManager()
{
    m_stateManager = NULL;
    m_weatherManager = NULL;
    m_dateManager = NULL;
    m_soundManager = NULL;
    
}


void EventManager::setup()
{
    m_stateManager = &AppManager::getInstance().getStateManager();
    m_soundManager = &AppManager::getInstance().getSoundManager();
    m_dateManager = &AppManager::getInstance().getDateManager();
    m_weatherManager = &AppManager::getInstance().getWeatherManager();
    m_guiManager = &AppManager::getInstance().getGuiManager();
    
    std::cout<< "EventManager-> initialized "<<std::endl;
}


void EventManager::update(double dt)
{
	for(TimedEventList::iterator it = m_timeEvents.begin(); it != m_timeEvents.end();) {
		(*it)->update(dt);	
	}
}

void EventManager::setEvent(Event event)
{
    std::cout << "EventManager-> SetEvent: " << event.getName() << ", " << event.getValue()<<std::endl; 
    m_stateManager->handleEvent(event);
    m_weatherManager->handleEvent(event);
    m_dateManager->handleEvent(event);
    m_soundManager->handleEvent(event);
    m_guiManager->handleEvent(event);
}

void EventManager::setTimedEvent(const std::string& name, double delay)
{
    std::cout << "EventManager-> setTimedEvent: " << name <<", delay "<<delay<<std::endl;
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

