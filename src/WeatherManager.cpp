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

WeatherManager::WeatherManager(): m_currentIcon(NULL), m_dateManager(NULL), m_code(0)
{
}

WeatherManager::~WeatherManager() 
{
    for (IconMap::iterator it= m_icons.begin() ; it != m_icons.end(); it++ )
    {
        delete it->second;
        it->second = NULL;
    }
    
    m_currentIcon = NULL;
    m_dateManager = NULL;
}


//--------------------------------------------------------------
void WeatherManager::setup()
{
    m_dateManager = &AppManager::getInstance().getDateManager();
    
    m_location = "Linz";
    m_url = "http://free.worldweatheronline.com/feed/weather.ashx?q=" + m_location + "&format=xml&num_of_days=3&key=" + WEATHER_API_KEY;
    
    this->loadIcons();
    
    if(m_currentIcon)
    {
        AppManager::getInstance().getViewManager().addVisual(*m_currentIcon,1);
        m_currentIcon->setColor(ofColor(255,255,255,0));
        AppManager::getInstance().getViewManager().fadeVisual(*m_currentIcon, 255, WeatherManager::FADE_TIME,ViewManager::LOGARITHMIC);
    }
    
    m_conditions = m_conditionsDesc = "Dry";
    
    this->parseXML();
    this->readConditionsCode();
    
    std::cout << m_dateManager->getTime() << "- DateManager-> initialized "<<std::endl;
    ofLogNotice() << m_dateManager->getTime() << "- DateManager-> initialized ";
    
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
        
        std::cout << m_dateManager->getTime() << "- WeatherManager-> parseXML: no data Tag found" << std::endl;
        ofLogNotice() << m_dateManager->getTime() << "- WeatherManager-> parseXML: no data Tag found";
        return false;
    }
    
    //we push into the first rss tag this temporarirly treats the tag as the document root.
    m_XML.pushTag("data");
    
    //we see how many points we have stored in <channel> tags
    numTags = m_XML.getNumTags("current_condition");
    
    if(numTags == 0){
        
        std::cout << m_dateManager->getTime() << "- WeatherManager-> parseXML: no current_condition Tag found" << std::endl;
        ofLogNotice() << m_dateManager->getTime() << "- WeatherManager-> parseXML: no current_condition Tag found" ;
        return false;
    }
    
    //we push into the first rss tag this temporarirly treats the tag as the document root.
    m_XML.pushTag("current_condition");
    
    
    m_code = m_XML.getValue("weatherCode", 0);
    string conditionsDesc = m_XML.getValue("weatherDesc"," ");
    
    if(m_conditionsDesc!= conditionsDesc)
    {
        m_conditionsDesc= conditionsDesc;
        std::cout << m_dateManager->getTime() << "- WeatherManager-> parseXML: the current conditions are \""<<m_conditionsDesc<<"\"" << std::endl;
       ofLogNotice() << m_dateManager->getTime() << "- WeatherManager-> parseXML: the current conditions are \""<<m_conditionsDesc<<"\"";
        m_conditionText->setText(m_conditionsDesc, 20);
        m_conditionText->setColor(ofColor(255,255,255,0));
        AppManager::getInstance().getViewManager().fadeVisual(*m_conditionText, 255, WeatherManager::FADE_TIME,ViewManager::LOGARITHMIC);
    }
    
    
}

void WeatherManager::handleEvent(const Event& event)
{
    std::string name = event.getName();
    if(name=="Dry")
    {
        m_conditions = name;
        m_code = 113;
        this->readConditionsCode();
    }
    
    if(name=="Rain")
    {
        m_conditions = name;
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
    
	
	else if(m_code ==  395 || m_code ==  371 || m_code ==  338 || m_code ==  230 || m_code ==  227||
            m_code ==  335 ) 
    {
		iconName = "snow_" + dayTime;
        conditions = "Rain";
	}
    
    else if(m_code ==  392 || m_code ==  368 || m_code ==  332 || m_code ==  230 || m_code ==  227||
            m_code ==  332|| m_code ==  329 || m_code ==  326 || m_code ==  323 ) 
    {
		iconName = "light_snow_" + dayTime;
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
    
    
	else if(m_code ==  260|| m_code ==  248) {
		iconName = "fog_" + dayTime;
        conditions = "Dry";
	}
    
    else if(m_code ==  143) {
		iconName = "mist_" + dayTime;
        conditions = "Dry";
	}
    
	else if(m_code ==  386) {
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
        std::cout << m_dateManager->getTime() << "- WeatherManager-> readConditionsCode: set image \""<<m_iconName<<".png\"" << std::endl;
         ofLogNotice() << m_dateManager->getTime() << "- WeatherManager-> readConditionsCode: set image \""<<m_iconName<<".png\"";
        AppManager::getInstance().getViewManager().removeVisual(*m_currentIcon);
        m_currentIcon = m_icons[m_iconName];
        AppManager::getInstance().getViewManager().addVisual(*m_currentIcon);
        m_currentIcon->setColor(ofColor(255,255,255,0));
        AppManager::getInstance().getViewManager().fadeVisual(*m_currentIcon, 255, WeatherManager::FADE_TIME,ViewManager::LOGARITHMIC);
        m_conditionText->setText(m_conditionsDesc, 20);
        m_conditionText->setColor(ofColor(255,255,255,0));
        AppManager::getInstance().getViewManager().fadeVisual(*m_conditionText, 255, WeatherManager::FADE_TIME,ViewManager::LOGARITHMIC);
    }
    
    if(conditions!=m_conditions)
    {
        m_conditions = conditions;
        AppManager::getInstance().getEventManager().setEvent(Event(m_conditions));
        
    }
}

void WeatherManager::loadIcons()
{
    //some path, may be absolute or relative to bin/data
    std::string samplesPath = "pictures/WeatherIcons/";
    std::cout<< m_dateManager->getTime() <<"- WeatherManager-> loadSamples: loading icons from \""<<samplesPath<<"\"..."<<std::endl;
    ofLogNotice()<< m_dateManager->getTime() <<"- WeatherManager-> loadSamples: loading icons from \""<<samplesPath<<"\"...";
    ofDirectory dir(samplesPath);
    //only show jpg and png files
    dir.allowExt("png");
    dir.allowExt("jpg");
    //populate the directory object
    if(dir.listDir()==0)
    {
        std::cout << m_dateManager->getTime() << "- WeatherManager-> iconSamples: No icons found in \""<< samplesPath <<"\"" << std::endl;
        ofLogNotice() << m_dateManager->getTime() << "- WeatherManager-> iconSamples: No icons found in \""<< samplesPath <<"\"";
        return;
    }
    
    float widthWeather = ofGetWidth()/3.0; 
    float heightWeather = 3*ofGetHeight()/10.0; 
    float sizeIcon = heightWeather/3;
    float x = widthWeather+ widthWeather/10.0;
    float y = 4*heightWeather + heightWeather/3;
    
    //go through and print out all the paths
    for(int n = 0; n < dir.numFiles(); n++)
    {
        std::string iconName = this->getIconName(dir.getPath(n));
        ImageVisual* icon =  new ImageVisual(ofPoint(x,y),sizeIcon,sizeIcon);
        icon->setImage(dir.getPath(n));
        m_icons[iconName] = icon;
        std::cout << m_dateManager->getTime() << "- WeatherManager-> loaded sample \""<< iconName <<"\"" << std::endl;
        ofLogNotice() << m_dateManager->getTime() << "- WeatherManager-> loaded sample \""<< iconName <<"\"";
    }
    
    m_currentIcon = m_icons["sunny_Day"];
    
    x = x + 3*sizeIcon/2;
    m_conditionText = new TextVisual(ofPoint(x,y),2*widthWeather/3,sizeIcon);
    AppManager::getInstance().getViewManager().addVisual(*m_conditionText);
    m_conditionText->setColor(ofColor(255,255,255,0));
    AppManager::getInstance().getViewManager().fadeVisual(*m_conditionText, 255, WeatherManager::FADE_TIME,ViewManager::LOGARITHMIC);
}


std::string WeatherManager::getIconName(const std::string& path)
{
    std::vector<std::string> strs = ofSplitString(path, "/");
    std::string str = strs.back();
    strs = ofSplitString(str, ".");
    return strs.front();
}




