
/*==============================================================================
 Imanolgo on 6/25/12.
 ==============================================================================*/
/*! \file WeatherManager.h
 * \authors Imanol Gómez
 * \copyright{2012}
 *///============================================================================


#ifndef __WEATHER_MANAGER_H__
#define __WEATHER_MANAGER_H__


#include <string>
#include "ofxFileLoader.h"


class ofxXmlSettings;

//========================== class WeatherManager =======================================
//==============================================================================
/** \class WeatherManager WeatherManager.h
 *	\brief class for accessing the current weather conditions
 *	\details It constantly monitors the weather conditions from the Yahoo! API
 */

class WeatherManager
{
public:
    //! Constructor
    WeatherManager();
    
    //! Destructor
    virtual ~WeatherManager() {}
    
    //! setups the day watcher
    void setup();
    
    //! setups the class
    void setUrl(std::string url) {m_url = url;}
    
    //! setups the class
    void update(double dt);
    
protected:
    
    //! reads and parses the information from Yahoo's weather API
    bool parseXML(); 
    
    //! creates events according to the updated information
    void eventHandler();
    
    
protected:
    
    std::string           m_url;                ///< stores the url to send the request
    ofxFileLoader         m_loader;             ///< loads file given an url
    ofxXmlSettings        m_XML;                ///< it saves the url xml information
    std::string           m_condition;          ///< stores the current weather conditions
    std::string           m_dayTime;            ///< stores the current day time
    std::string           m_dayTime_Weather;    ///< stores the current day time and weather conditions
    
    
};

#endif