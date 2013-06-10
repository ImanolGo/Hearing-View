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

const double WeatherStationManager::REFRESH_TIME = 1*10*1000; ///< the refresh tim, every 10 seconds

WeatherStationManager::WeatherStationManager(): m_dateManager(NULL),m_elapsedTime(0.0),
m_T(0.0f),m_W(0.0f),m_S(0.0f),m_R(0.0f)
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
    m_elapsedTime+=dt;
    
    if(m_elapsedTime>=REFRESH_TIME)
    {
        // lock access to the resources
        m_weatherThread.lock();
        
        if(m_T!=m_weatherThread.m_T){
            m_T = m_weatherThread.m_T;
            AppManager::getInstance().getEventManager().setEvent(Event("Temperature (T(°C))", m_T));
        }
        
        if(m_W!=m_weatherThread.m_W){
            m_W = m_weatherThread.m_W;
            AppManager::getInstance().getEventManager().setEvent(Event("Wind Speed (W(Kph))", m_W));
        }
        
        if(m_S!=m_weatherThread.m_S){
            m_S = m_weatherThread.m_S;
            AppManager::getInstance().getEventManager().setEvent(Event("Insolation (S(W/m2))", m_S));
        }
        
        if(m_R!=m_weatherThread.m_R){
            m_R = m_weatherThread.m_R;
            AppManager::getInstance().getEventManager().setEvent(Event("Precipitation (R(mm))", m_R));
        }
            
        // done with the resources
        m_weatherThread.unlock();
        
        m_elapsedTime = 0.0;
    }
}

void WeatherStationManager::handleEvent(const Event& event)
{
   //Intentionaly left empty    
}





