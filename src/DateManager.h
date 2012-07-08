
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
    
    //! updates the date manager
    void updateDayTime();
    
    //! updates the date manager
    void updateSeason();
    
    //! reads the URL information
    bool readURL();
    
private:
    
    ofxDate*               m_Date;         ///< current date and time
    std::string            m_url;          ///< stores the url to send the request
    ofxFileLoader          m_loader;       ///< loads file given an url
    ofxXmlSettings         m_XML;          ///< it saves the url xml information
    
    std::string            m_sunset;       ///< it saves the sunset time in a string
    std::string            m_sunrise;      ///< it saves the sunrise time in a string
    int                    m_currentDay;   ///< saves the current day
    int                    m_currentMonth; ///< saves the current month
    int                    m_currentYear;  ///< saves the current year
    
    std::string            m_season;       ///< saves the current season
    std::string            m_dayTime;      ///< saves the current day time
    
};


#endif