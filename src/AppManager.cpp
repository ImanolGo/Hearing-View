//
//  AppManager.cpp
//  HearingView
//
//  Created by Imanolgo on 6/24/12.
//

#include "ofMain.h"

#include "SoundManager.h"
#include "ViewManager.h"
#include "StateManager.h"
#include "WeatherManager.h"
#include "DateManager.h"
#include "EventManager.h"
#include "SoundEffectsManager.h"
#include "VisualEffectsManager.h"


#include "AppManager.h"

AppManager* AppManager::m_instance = NULL;

AppManager& AppManager::getInstance()
{
	if(!m_instance) {
		m_instance = new AppManager();
	}
	return *m_instance;
}


AppManager::AppManager(): m_eventManager(NULL), m_stateManager(NULL), m_viewManager(NULL), m_soundManager(NULL),
m_dateManager(NULL),m_weatherManager(NULL), m_soundEffectsManager(NULL),m_visualEffectsManager(NULL)
{
    m_eventManager = new EventManager();
    m_stateManager = new StateManager();
    m_viewManager = new ViewManager();
    m_soundManager = new SoundManager();
    m_weatherManager = new WeatherManager();
    m_dateManager = new DateManager();
    m_soundEffectsManager = new SoundEffectsManager();
    m_visualEffectsManager = new VisualEffectsManager();
    
}


AppManager::~AppManager()
{
    delete m_eventManager;
    delete m_stateManager;
    delete m_viewManager;
    delete m_soundManager;
    delete m_weatherManager;
    delete m_dateManager;
    delete m_soundEffectsManager;
    delete m_visualEffectsManager;
}


void AppManager::setup()
{
    m_eventManager->setup();
    m_viewManager->setup();
    m_dateManager->setup();
    m_weatherManager->setup();
    m_soundManager->setup();
    m_stateManager->setup();
    
    
}

void AppManager::update(double dt)
{
    m_soundManager->update(dt);
    m_soundEffectsManager->update(dt);
    m_visualEffectsManager->update(dt);
    m_eventManager->update(dt);
}


void AppManager::draw()
{
    m_viewManager->draw();
    
}



