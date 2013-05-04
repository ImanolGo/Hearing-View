
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
    
    
protected:
    
    WeatherThread         m_weatherThread;      ///< class reading by serial from the weather station on a separate process
    DateManager*    m_dateManager;        ///< pointer to the date manager

};

#endif