
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
#include <map>
#include "ofxFileLoader.h"
#include "ofxXmlSettings.h"


class ImageVisual;
class TextVisual;
class DataManager;

//========================== class WeatherManager =======================================
//==============================================================================
/** \class WeatherManager WeatherManager.h
 *	\brief class for accessing the current weather conditions
 *	\details It constantly monitors the weather conditions from the FreeWeather API
 */


class WeatherManager
{
    static const string	 WEATHER_API_KEY;   ///< defines the World Weather Online API key
    static const double REFRESH_TIME;		///< defines time (s) of the refresh of information 
    static const double FADE_TIME;          ///< defines the visuals fadeTime
    
public:
    //! Constructor
    WeatherManager();
    
    //! Destructor
    virtual ~WeatherManager();
    
    //! setups the day watcher
    void setup();
    
    //! setups the class
    void setUrl(std::string url) {m_url = url;}
    
    //! setups the class
    void update(double dt);
    
    //! handles the events
    void handleEvent(const Event& event);
    
protected:
    
    //! reads and parses the information from Yahoo's weather API
    bool parseXML(); 
    
    //! reads and parses the current weather conditions code
    void readConditionsCode();
    
    //! loads the icons into the icons map
    void loadIcons();
    
    //! loads the text visuals and add them
    void loadTextVisuals();
    
    //! returns the icon name given its path
    std::string getIconName(const std::string& path);
    
protected:
    
    typedef std::map <std::string, ImageVisual*>   IconMap;   ///< defines a map of weather icons sorted by the category name 
    
    typedef std::map <std::string, TextVisual*>     TextMap;   ///< defines a map of weather texts 
    
    std::string           m_url;                ///< stores the url to send the request
    ofxFileLoader         m_loader;             ///< loads file given an url
    ofxXmlSettings        m_XML;                ///< it saves the url xml information
    std::string           m_conditions;         ///< stores the current weather options for the sound manager
    std::string           m_conditionsDesc;     ///< stores the current weather conditions description
    float                 m_temperature;        ///< stores the current temperature in °C(Celcius)
    int                   m_humidity;           ///< stores the current relative humidty (%)
    float                 m_windSpeed;          ///< stores the current wind speed in kilometre per hour
    int                   m_precipMM;           ///< stores the precipititation amount in millimeter
    int                   m_code;               ///< stores the current weather conditions code
    std::string           m_location;			///< stores the name of the location for the weather query	
    std::string           m_iconName;			///< stores the icon name of the location for the weather query	
    double                m_elapsedTime;        ///< elapsed time since the last refreshing
    ImageVisual*          m_currentIcon;        ///< stores the current weather icon
    IconMap               m_icons;              ///< map of visuals representing the weather conditions
    TextMap               m_textVisuals;        ///< text visuals from the current weather conditions
    int                   m_fontSize;           ///< defines the text fontsize
    DateManager*          m_dateManager;        ///< pointer to the date manager
    
};

#endif