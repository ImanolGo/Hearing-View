
/*==============================================================================
 Imanolgo on 01/04/13.
 ==============================================================================*/
/*! \file WeatherStationManager.h
 * \authors Imanol Gómez
 * \copyright{2013}
 *///============================================================================


#ifndef __WEATHER_STATION_MANAGER_H__
#define __WEATHER_STATION_MANAGER_H__

#include "ofMain.h"
#include "WeatherThread.h"

#define MESSAGE_LENGTH 3

//========================== class WeatherStationManager =======================================
//==============================================================================
/** \class WeatherStationManager WeatherStationManager.h
 *	\brief class for controlling the serial communication with the weather station
 *	\details It communicates with the WatchDog 2000 weather station through serial and sends
 *           the information to the weather manager
 */


class DateManager;

class WeatherStationManager
{
    static const double REFRESH_TIME;       ///< defines the refresh time
    
public:
    //! Constructor
    WeatherStationManager();
    
    //! Destructor
    virtual ~WeatherStationManager();
    
    //! setups the weather station manager
    void setup();
    
    //! updates the weather station manager
    void update(double dt);
    
    //! handles the events
    void handleEvent(const Event& event);
    
    //! get current wind speed
    float getWindSpeed() const {return m_W;}
    
    //! get current Temperature
    float getTemperature() const {return m_T;}
    
    //! get current wetness
    float getWetness() const {return m_R;}
    
    //! get current rain conditions
    bool getRainConditions() const {return m_isRaining;}
    
    //! get current sun radiation
    float getInsolation() const {return m_S;}
    
private:
    
    WeatherThread   m_weatherThread;      ///< class reading by serial from the weather station on a separate process
    DateManager*    m_dateManager;        ///< pointer to the date manager

    double          m_elapsedTime;        ///< elapsed time since the last data refresh
    
    float            m_T; // stores the temperature (°C) coming from the weather station
    float            m_W; // stores the wind speed (Kph) coming from the weather station
    float            m_S; // stores the sun radiation level (W/m2) coming from the weather station
    float            m_R; // stores the wetness (V) coming from the weather station
    bool             m_isRaining; // stores it is currently raining or not

};

#endif