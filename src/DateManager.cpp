//
//  DateWatcher.cpp
//  HearingView
//
//  Created by Imanolgo on 6/24/12.
//

#include "ofxXmlSettings.h"
#include "ofxDate.h"
#include "ofxUI.h"
#include "AppManager.h"

#include "DateManager.h"


DateManager::DateManager(): m_currentDay(0),m_currentMonth(0),m_currentYear(0)
{
    m_Date = new ofxDate();
    
}

DateManager::~DateManager()
{
    delete m_Date;
}

void DateManager::setup()
{
    m_url = "http://weather.yahooapis.com/forecastrss?w=12814970&u=c";
    m_sunrise = "07:00 am";
    m_sunset = "07:00 pm";
    
}

bool DateManager::readURL()
{
    std::string xmlFromServer = m_loader.loadFromUrl(m_url);  
    m_XML.loadFromBuffer(xmlFromServer);

    
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
    numTags = m_XML.getNumTags("channel");
    
    if(numTags == 0){
        
        std::cout<< "DateManager-> readURL: no channel Tag found" << std::endl;
        return false;
    }
    
    //we push into the first rss tag this temporarirly treats the tag as the document root.
    m_XML.pushTag("channel", 1);
    
    //we see how many points we have stored in <yweather:astronomy> tags
    numTags = m_XML.getNumTags("yweather:astronomy");  
    
    if(numTags == 0){
        
        std::cout<< "DateManager-> readURL: no yweather:astronomy Tag found" << std::endl;
        return false;
    }
    
    //we push into the first rss tag this temporarirly treats the tag as the document root.
    m_XML.pushTag("yweather:astronomy", 1);
    
    m_sunrise = m_XML.getValue("sunrise","07:00 am");
    m_sunrise = ofSplitString(m_sunrise, " ")[0]; //get rid of am
    
    m_sunset =  m_XML.getValue("sunset","07:00 pm");
    m_sunset = ofSplitString(m_sunset, " ")[0];  //get rid of pm
    
    std::cout<< "DateManager-> sunrise = " << m_sunrise << "sunset = "<< m_sunset <<std::endl;
            
    //m_XML.popTag();
    
    return true;

}

void DateManager::update(double dt)
{
    int day   = m_Date->getDay();
    int month = m_Date->getMonth();
    int year = m_Date->getYear();
    
    if(m_currentDay != day || m_currentMonth!= month|| m_currentYear!= year)
    {
        m_currentDay = m_Date->getDay();
        m_currentMonth = m_Date->getMonth();
        m_currentYear = m_Date->getYear();
        this->readURL();
        this->updateSeason();
    }
    
    this->updateDayTime();
    
}


void DateManager::updateDayTime()
{
    time_t now;
    struct tm *current;
    now = time(0);
    current = localtime(&now);
    
    int currentHour = current->tm_hour;
    int currentMin = current->tm_min;
    
    cout << "hour: " << current->tm_hour << endl;
    cout << "mins: " << current->tm_min << endl;
    cout << "sec: " << current->tm_sec << endl;
    
    int hourSunrise = atoi(ofSplitString(m_sunrise, ":")[0].c_str());
    int minSunrise = atoi(ofSplitString(m_sunrise, ":")[1].c_str());
    
    int hourSunset = atoi(ofSplitString(m_sunset, ":")[0].c_str()) + 12; // 24 hour 
    int minSunset = atoi(ofSplitString(m_sunset, ":")[1].c_str());
    
    
    if(hourSunrise<=currentHour<=hourSunset && minSunrise<=currentMin<=minSunset)
    {
        m_dayTime = "Day";
    }
    
    else
    {
         m_dayTime = "Night";
    }


}

void DateManager::updateSeason()
{
    
    std::string season;
    
    std::cout << "DateManager -> Date: " << m_currentDay << "/"<<m_currentMonth << "/" << m_currentYear << std::endl;
    
    if(1 <= m_currentMonth && m_currentMonth <=3)
    {
        season = "Winter";
    }
    
    else if (4 <= m_currentMonth && m_currentMonth <=6)
    {
        season = "Spring";
    }
    
    else if (7 <=m_currentMonth && m_currentMonth <=9)
    {
        season = "Summer";
    }
    
    else if (10 <= m_currentMonth && m_currentMonth <= 12)
    {
        season = "Autumn";
    }
    
    
    if ( (m_currentMonth % 3 == 0) && (m_currentDay >= 21))
    {
        if (season=="Winter")
        {
            season = "Spring";
            
        }
        
        else if (season=="Spring")
        {
            season = "Summer";
        }
        
        else if (season=="Summer")
        {
            season = "Autumn";
        }
        
        else if (season=="Autumn")
        {
            season = "Winter";
        }
        
        else 
        {
            season = "Winter";
        }    			
    }
        
    std::cout << "DateManager -> Season: " << m_season <<std::endl;
    
    if(m_season!=season)
    {
        m_season = season;
        ofxUIRadio *radio = (ofxUIRadio *) AppManager::getInstance().getGUI().getWidget("SEASONS");
        radio->activateToggle(m_season);
        
    }
    
}
