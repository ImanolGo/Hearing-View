//
//  WeatherStationManager.cpp
//  HearingView
//
//  Created by Imanolgo on 01/04/13.
//


#include "Event.h"
#include "AppManager.h"
#include "EventManager.h"
#include "DateManager.h"

#include "WeatherStationManager.h"


WeatherStationManager::WeatherStationManager(): m_dateManager(NULL)
{
    //Intentionaly left empty
}

WeatherStationManager::~WeatherStationManager() 
{
    m_weatherThread.stop();
}


//--------------------------------------------------------------
void WeatherStationManager::setup()
{
    m_dateManager = &AppManager::getInstance().getDateManager();
    
    m_weatherThread.start();
    
    std::cout << m_dateManager->getTime() << "- WeatherStationManager-> initialized " << std::endl;
    ofLogNotice() << m_dateManager->getTime() << "- WeatherStationManager->initialized " ;

    
}

void WeatherStationManager::update(double dt)
{
    //Intentionaly left empty
}

void WeatherStationManager::handleEvent(const Event& event)
{
   //Intentionaly left empty    
}





