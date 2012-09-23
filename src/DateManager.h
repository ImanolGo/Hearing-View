
/*==============================================================================
 Imanolgo on 6/24/12.
 ==============================================================================*/
/*! \file DateManager.h
 * \authors Imanol Gómez
 * \copyright{2012}
 *///============================================================================


#ifndef __DATE_MANAGER_H__
#define __DATE_MANAGER_H__


#include <string>
#include "ofxFileLoader.h"

class ofxXmlSettings;
class ofxDate;

//========================== class DateManager =======================================
//==============================================================================
/** \class DateManager DateManager.h
 *	\brief class for accessing the current date and time
 *	\details It constantly monitors the current date and calculates the actual season
 */

class DateManager
{
    
    static const double   REFRESHING_TIME; //determines the time ro refresh the calculations (s)
    
public:
    
    enum DayCycle {
        Day,
        Night
    } ;
        
public:
    //! Constructor
    DateManager();
    //! Destructor
    virtual ~DateManager();
    
    //! setups the day watcher
    void setup();
    
    //! returns the year's seasons
    const std::string& getSeason(){return m_season;}
    
    //! returns the current day time
    const std::string& getDayTime() {return m_dayTime;}
    
    //! updates the date manager
    void update(double dt);
    
private:
    
    //! calculates if it is night or day
    void calcDayTime();
    
    //! calculates the current season
    void calcSeason();
    
    // calculates the European Summer Time offset (0 if winter, 1 if summer)
    void calcEST();
    
    // Get the days to J2000.
    double FNday();
    
    // the function below returns an angle in the range 0 to 2*pi
    double FNrange (double x);
    
    // Calculating the hourangle
    double f0(double lat, double declin);
    
    // Calculating the hourangle for twilight times
    double f1(double lat, double declin);
    
    // Find the ecliptic longitude of the Sun
    void FNsun (double d, double& L, double& g, double& lambda);
    
    // Calculates the sunrise and sunset hours
    void calcSunEqs();
    
    // Displays the current date, season, day time and sunset and sunrise information
    void displayDate();
    
    
private:
    
    ofxDate*                m_Date;         ///< current date and time
        
    double                  m_sunset;       ///< it saves the sunset time as a double number
    double                  m_sunrise;      ///< it saves the sunrise time as a double number
    int                     m_day;          ///< saves the current day
    int                     m_month;        ///< saves the current month
    int                     m_year;         ///< saves the current year
    
    double                  m_elapsedTime;  ///< elapsed time since the last refreshing
    
    double                  m_latitude;     ///< longitude of the location
    double                  m_longitude;    ///< longitude of the location
    int                     m_timezone;     ///< offset from Coordinated Universal Time (UTC) 
    int                     m_EST;          ///< European Summer Time value (0 if winter, 1 if summer)
    
    std::string             m_season;       ///< saves the current season
    std::string             m_dayTime;      ///< saves the current day time
    
};


#endif