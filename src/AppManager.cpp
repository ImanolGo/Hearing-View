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
#include "ofxUI.h"
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


AppManager::AppManager(): m_gui(NULL), m_stateManager(NULL), m_viewManager(NULL), m_soundManager(NULL),
m_dateManager(NULL),m_weatherManager(NULL), m_soundEffectsManager(NULL),m_visualEffectsManager(NULL)
{
    float dim = 32; 
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float length = 320-xInit; 
    
    m_gui = new ofxUICanvas(0,0,length+xInit*2.0,ofGetHeight());
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
    delete m_gui;
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
    this->setupGUI();
    m_viewManager->setup();
    m_dateManager->setup();
    m_weatherManager->setup();
    m_soundManager->setup();
    m_stateManager->setup();
    
    
}

void AppManager::setupGUI()
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
    
     m_gui->addWidgetDown(new ofxUIToggle(dim, dim, false, "End Samples"));
    
    //ofAddListener(m_gui->newGUIEvent, this, &AppManager::guiEvent);

}

//--------------------------------------------------------------
void AppManager::update(double dt)
{
    m_viewManager->update(dt);
    m_soundManager->update(dt);
    m_soundEffectsManager->update(dt);
    m_visualEffectsManager->update(dt);
}


void AppManager::draw()
{
    m_viewManager->draw();
    
}



