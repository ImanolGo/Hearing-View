//
//  WeatherWatcher.cpp
//  HearingView
//
//  Created by Imanolgo on 6/24/12.
//

#include "ofxXmlSettings.h"
#include "ofxUI.h"
#include "DateManager.h"

#include "WeatherManager.h"
#include "AppManager.h"


WeatherManager::WeatherManager()
{
}


//--------------------------------------------------------------
void WeatherManager::setup()
{
    m_url = "http://weather.yahooapis.com/forecastrss?w=12814970&u=c";
}

void WeatherManager::update(double dt)
{
    std::string xmlFromServer = m_loader.loadFromUrl(m_url);  
    m_XML.loadFromBuffer(xmlFromServer);
    
    m_dayTime = AppManager::getInstance().getDateManager().getDayTime();
    
    if(this->parseXML())
    {
        this->eventHandler();
    }
    
}

void WeatherManager::eventHandler()
{
    std::string dayTime_Weather;
    if(ofIsStringInString(m_condition,"storm"))
    {
        dayTime_Weather = m_dayTime + "_" + "Rain";
           
    }
       
    else if (ofIsStringInString(m_condition,"drizzle"))
    {
        dayTime_Weather = m_dayTime + "_" + "Rain";         
    }
    
    else if (ofIsStringInString(m_condition,"rain"))
    {
        dayTime_Weather = m_dayTime + "_" + "Rain";         
    }
    
    else if (ofIsStringInString(m_condition,"shower"))
    {
        dayTime_Weather = m_dayTime + "_" + "Rain";         
    }
    
    else
    {
        dayTime_Weather = m_dayTime + "_" + "Rain";
    }
    
    
    if (m_dayTime_Weather!=dayTime_Weather) //create weather conditions event
    {
        m_dayTime_Weather = dayTime_Weather;
        ofxUIRadio *radio = (ofxUIRadio *) AppManager::getInstance().getGUI().getWidget("WEATHER CONDITIONS");
        radio->activateToggle(m_dayTime_Weather);
    }
       
}


bool WeatherManager::parseXML()
{
    
    //lets see how many <rss> </rss> tags there are in the xml file
	int numTags = m_XML.getNumTags("rss");
    
	//if there is at least one <rss> tag we can read the list of points
	//and then try and draw it as a line on the screen
	if(numTags == 0){
        
        std::cout<< "DateManager-> readURL: no rss Tag found" << std::endl;
        return false;
    }
    
    //we push into the first rss tag this temporarirly treats the tag as the document root.
    m_XML.pushTag("rss", 1);
    
    //we see how many points we have stored in <channel> tags
    numTags = m_XML.getNumTags("item");
    
    if(numTags == 0){
        
        std::cout<< "DateManager-> readURL: no item Tag found" << std::endl;
        return false;
    }
    
    //we push into the first rss tag this temporarirly treats the tag as the document root.
    m_XML.pushTag("item", 1);
    
    //we see how many points we have stored in <yweather:astronomy> tags
    numTags = m_XML.getNumTags("yweather:condition");  
    
    if(numTags == 0){
        
        std::cout<< "DateManager-> readURL: no yweather:condition Tag found" << std::endl;
        return false;
    }
    
    //we push into the first rss tag this temporarirly treats the tag as the document root.
    m_XML.pushTag("yweather:condition", 1);
    
    std::string m_condition = m_XML.getValue("text"," ");
    
}


