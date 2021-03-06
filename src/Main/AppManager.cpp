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
#include "GuiManager.h"
#include "SoundEffectsManager.h"
#include "VisualEffectsManager.h"
#include "WeatherStationManager.h"
#include "SensorManager.h"


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
    m_dateManager = new DateManager();
    m_eventManager = new EventManager();
    m_guiManager = new GuiManager();
    m_stateManager = new StateManager();
    m_viewManager = new ViewManager();
    m_soundManager = new SoundManager();
    m_weatherManager = new WeatherManager();
    m_soundEffectsManager = new SoundEffectsManager();
    m_visualEffectsManager = new VisualEffectsManager();
    m_weatherStationManager = new WeatherStationManager();
    m_sensorManager = new SensorManager();
}


AppManager::~AppManager()
{
    delete m_eventManager;
    delete m_stateManager;
    delete m_guiManager;
    delete m_weatherManager;
    delete m_dateManager;
    delete m_soundManager;
    delete m_viewManager;
    delete m_soundEffectsManager;
    delete m_visualEffectsManager;
    delete m_weatherStationManager;
    delete m_sensorManager;
}


void AppManager::setup()
{
    std::string fileName = "logFiles/HearingView_" + m_dateManager->getLogDate() + ".log";  
    ofSetLogLevel(OF_LOG_NOTICE);
    ofLogToFile(fileName, true);
    
    m_eventManager->setup();
    m_viewManager->setup();
    m_soundManager->setup();
    m_stateManager->setup();
    m_sensorManager->setup();
    m_guiManager->setup();
    //m_weatherManager->setup();
    m_weatherStationManager->setup();
    m_dateManager->setup();
    
    m_soundManager->start();
    m_stateManager->start();
    
}

void AppManager::update(double dt)
{
    m_soundManager->update(dt);
    m_soundEffectsManager->update(dt);
    m_visualEffectsManager->update(dt);
    m_eventManager->update(dt);
    m_dateManager->update(dt);
    m_guiManager->update(dt);
    m_viewManager->update(dt);
    //m_weatherManager->update(dt);
    m_weatherStationManager->update(dt);
    m_sensorManager->update(dt);

}


void AppManager::draw()
{
    m_viewManager->draw();
    
}



