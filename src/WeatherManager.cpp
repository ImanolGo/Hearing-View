//
//  WeatherWatcher.cpp
//  HearingView
//
//  Created by Imanolgo on 6/24/12.
//

#include "ofxXmlSettings.h"
#include "DateManager.h"
#include "Event.h"
#include "AppManager.h"
#include "EventManager.h"
#include "Visuals.h"
#include "ViewManager.h"

#include "WeatherManager.h"

const string WeatherManager::WEATHER_API_KEY = "630d17ff50223932122909"; 
const double WeatherManager::REFRESH_TIME = 60*1; ///< refreshing time every 1 minutes
const double WeatherManager::FADE_TIME = 3;

WeatherManager::WeatherManager(): m_icon(NULL),m_code(0)
{
}

WeatherManager::~WeatherManager() 
{
    if(m_icon)
    {
        delete m_icon;
        m_icon = NULL;
    }
}


//--------------------------------------------------------------
void WeatherManager::setup()
{
    m_location = "Linz";
    m_url = "http://free.worldweatheronline.com/feed/weather.ashx?q=" + m_location + "&format=xml&num_of_days=3&key=" + WEATHER_API_KEY;
    
    m_icon = new ImageVisual(ofPoint(500,500),128,128);
    m_conditionText = new TextVisual(ofPoint(500,500),128,128);
    
    AppManager::getInstance().getViewManager().addVisual(*m_conditionText);
    AppManager::getInstance().getViewManager().addVisual(*m_icon,1);
    
    m_conditionText->setColor(ofColor(255,255,255,0));
    m_icon->setColor(ofColor(255,255,255,0));
    AppManager::getInstance().getViewManager().fadeVisual(*m_conditionText, 255, WeatherManager::FADE_TIME);
    AppManager::getInstance().getViewManager().fadeVisual(*m_icon, 255, WeatherManager::FADE_TIME);
    
    m_conditions = m_conditionsDesc = "Dry";
    
    this->parseXML();
    this->readConditionsCode();
    
    std::cout<< "DateManager-> initialized "<<std::endl;
    
}

void WeatherManager::update(double dt)
{
    m_elapsedTime+=dt;
    if(m_elapsedTime>= REFRESH_TIME)
    {
        m_elapsedTime = 0;
        if(this->parseXML())
        {
            this->readConditionsCode();
        }
    }
    
}


bool WeatherManager::parseXML()
{
    std::string xmlFromServer = m_loader.loadFromUrl(m_url); 
    //std::cout <<xmlFromServer <<std::endl;
    m_XML.loadFromBuffer(xmlFromServer);
    
    //lets see how many <rss> </rss> tags there are in the xml file
	int numTags = m_XML.getNumTags("data");
    
	//if there is at least one <rss> tag we can read the list of points
	//and then try and draw it as a line on the screen
	if(numTags == 0){
        
        std::cout<< "WeatherManager-> parseXML: no data Tag found" << std::endl;
        return false;
    }
    
    //we push into the first rss tag this temporarirly treats the tag as the document root.
    m_XML.pushTag("data");
    
    //we see how many points we have stored in <channel> tags
    numTags = m_XML.getNumTags("current_condition");
    
    if(numTags == 0){
        
        std::cout<< "WeatherManager-> parseXML: no current_condition Tag found" << std::endl;
        return false;
    }
    
    //we push into the first rss tag this temporarirly treats the tag as the document root.
    m_XML.pushTag("current_condition");
    
    
    m_code = m_XML.getValue("weatherCode", 0);
    string conditionsDesc = m_XML.getValue("weatherDesc"," ");
    
    if(m_conditionsDesc!= conditionsDesc)
    {
        m_conditionsDesc= conditionsDesc;
        std::cout<< "WeatherManager-> parseXML: the current conditions are \""<<m_conditionsDesc<<"\"" << std::endl;
        m_conditionText->setText(m_conditionsDesc, 20);
        m_conditionText->setColor(ofColor(255,255,255,0));
        AppManager::getInstance().getViewManager().fadeVisual(*m_conditionText, 255, WeatherManager::FADE_TIME);
    }
    
    
}

void WeatherManager::handleEvent(const Event& event)
{
    std::string name = event.getName();
    if(name=="Dry")
    {
        m_conditions = m_conditionsDesc = name;
        m_code = 113;
        this->readConditionsCode();
    }
    
    if(name=="Rain")
    {
        m_conditions = m_conditionsDesc = name;
        m_code = 389;
        this->readConditionsCode();
    }
    
    if(name=="Day" || name=="Night")
    {
        this->readConditionsCode();
    }
    
}

void WeatherManager::readConditionsCode()
{
	string dayTime = AppManager::getInstance().getDateManager().getDayTime();
    string iconName;
    string conditions;
	if(m_code == 113) {
		iconName = "sunny_" + dayTime;
        conditions = "Dry";
	}
    
	else if(m_code==119 ||m_code == 122) {
		iconName = "cloudy_" + dayTime;
        conditions = "Dry";
	}
    
	else if(m_code == 116) {
		iconName = "partly_cloudy_" + dayTime;
        conditions = "Dry";
	}
    
	
	else if(m_code ==  395 || m_code ==  371 || m_code ==  338 || m_code ==  335 || m_code ==  230 || m_code ==  227||
            m_code ==  332|| m_code ==  329 || m_code ==  326 || m_code ==  323 ) 
    {
		iconName = "snow_" + dayTime;
        conditions = "Rain";
	}
    
	else if(m_code ==  365 || m_code ==  362 ||  m_code ==  320 || m_code ==  317 || m_code ==  314 || m_code ==  311 
            || m_code ==  284 || m_code ==  381 || m_code ==  185 || m_code ==  182 || m_code ==  179) {
		iconName = "sleet_" + dayTime;
        conditions = "Rain";
	}
    
	else if( m_code ==  296 || m_code ==  266 || m_code ==  353) {
		iconName = "light_rain_" + dayTime;
        conditions = "Rain";
	}
    
	else if( m_code ==  305 || m_code ==  299 || m_code ==  293 || m_code ==  263|| m_code ==  176) {
		iconName = "light_rain_" + dayTime;
        conditions = "Rain";
	}
    
	else if(m_code ==  389 || m_code ==  359 || m_code ==  356 || m_code ==  308 || m_code ==  302) {
		iconName = "rain_" + dayTime;
        conditions = "Rain";
	}
    
    
	else if(m_code ==  260|| m_code ==  248 || m_code ==  143) {
		iconName = "fog_" + dayTime;
        conditions = "Dry";
	}
    
	else if(m_code ==  386 || m_code ==  392) {
		iconName = "chance_of_storm_" + dayTime;
        conditions = "Rain";
	}
    
	else if(m_code ==  200) {
		iconName = "storm_" + dayTime;
        conditions = "Rain";
	}
    
	else {
		iconName = "sunny_" + dayTime;
	}

    if(iconName!=m_iconName)
    {
        m_iconName = iconName;
        std::cout<< "WeatherManager-> readConditionsCode: set image \""<<iconName<<".png\"" << std::endl;
        m_icon->setImage("pictures/WeatherIcons/" + iconName + ".png");
        m_icon->setColor(ofColor(255,255,255,0));
        AppManager::getInstance().getViewManager().fadeVisual(*m_icon, 255, WeatherManager::FADE_TIME);
        m_conditionText->setText(m_conditionsDesc, 20);
        m_conditionText->setColor(ofColor(255,255,255,0));
        AppManager::getInstance().getViewManager().fadeVisual(*m_conditionText, 255, WeatherManager::FADE_TIME);
    }
    
    if(conditions!=m_conditions)
    {
        m_conditions = conditions;
        AppManager::getInstance().getEventManager().setEvent(Event(m_conditions));
        
    }
}



