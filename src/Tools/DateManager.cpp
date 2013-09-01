//
//  DateWatcher.cpp
//  HearingView
//
//  Created by Imanolgo on 6/24/12.
//

#include <time.h>

#include "ofxXmlSettings.h"
#include "ofxDate.h"
#include "Event.h"
#include "AppManager.h"
#include "EventManager.h"
#include "Visuals.h"
#include "VisualEffectsManager.h"
#include "ViewManager.h"

#include "DateManager.h"


const double DateManager::REFRESH_TIME = 1*60;
const double DateManager::FADE_TIME = 3;
const int    DateManager::FONT_SIZE = 10;

DateManager::DateManager(): 
    m_latitude(0.0),
    m_longitude(0.0),
    m_timezone(0),
    m_sunrise(6),
    m_sunset(19),
    m_elapsedTime(0.0),
    m_EST(0),
    m_season(" "),
    m_dayTime(" ")
{
    m_Date = new ofxDate();
    m_day = m_Date->getDay();
    m_month = m_Date->getMonth();
    m_year = m_Date->getYear();
}

DateManager::~DateManager()
{
    delete m_Date;
    m_Date = NULL;
    
    for (TextVisualMap::iterator it= m_textVisuals.begin() ; it != m_textVisuals.end(); it++ )
    {
       AppManager::getInstance().getVisualEffectsManager().removeAllVisualEffects(*(it->second));
       AppManager::getInstance().getViewManager().removeVisual(*(it->second));
       delete it->second;
       it->second = NULL;
    }
}

void DateManager::setup()
{
    //location: Linz
    //m_latitude = 48.303056;
    //m_longitude = 14.290556;
    //m_timezone = 1;
    
    //location: Rheinau psychiatric clinic
    m_latitude = 47.635572;
    m_longitude = 8.607203;
    m_timezone = 1;
    
    m_location = "Rheinau Psychiatric Clinic";
    
    m_day = m_Date->getDay();
    m_month = m_Date->getMonth();
    m_year = m_Date->getYear();
    
    this->calcSunEqs();
    this->calcSeason();
    this->initTextVisuals();
    this->calcDayTime();
    this->displayDate();
    
    
    std::cout<<this->getTime()<< "- DateManager-> initialized "<<std::endl;
    ofLogNotice()<<this->getTime()<< "- DateManager-> initialized ";
    
}

void DateManager::initTextVisuals()
{
    float H = (float)ofGetHeight();
    float W  = (float)ofGetWidth();
    float margin = H/70;
    float widthGUI = W - 4*margin;
    float heightGUI = H/3.0 - 4*margin;

    int w = widthGUI/4;
    int h = FONT_SIZE;
    float x = 5*margin + 2*w;
    float y = 7*margin;
    
    y = y + h + margin;
    TextVisual* textVisual = new TextVisual(ofPoint(x,y),widthGUI,h);
    textVisual->setText("Date: " + this->getDate(),"Klavika-Regular.otf", h);
    textVisual->setColor(ofColor(255,255,255));
    m_textVisuals["Date"] = textVisual;
    
    y = y + h + margin;
    textVisual = new TextVisual(ofPoint(x,y),widthGUI,h);
    textVisual->setText("Hour: " + this->getHour() + "h","Klavika-Regular.otf", h);
    textVisual->setColor(ofColor(255,255,255));
    m_textVisuals["Hour"] = textVisual;
    
    y = y + h + margin;
    textVisual = new TextVisual(ofPoint(x,y),widthGUI,h);
    textVisual->setText("Dawn: " + this->timeToString(m_dawn) + "h" + ", Sunrise: " + this->timeToString(m_sunrise) + "h","Klavika-Regular.otf", h);
    textVisual->setColor(ofColor(255,255,255));
    m_textVisuals["Sunrise"] = textVisual;
    
    y = y + h + margin;
    textVisual = new TextVisual(ofPoint(x,y),widthGUI,h);
    textVisual->setText("Sunset: " + this->timeToString(m_sunset) + "h" + ", Dusk: " + this->timeToString(m_dusk) + "h","Klavika-Regular.otf", h);
    textVisual->setColor(ofColor(255,255,255));
    m_textVisuals["Sunset"] = textVisual;
    
    y = y + h + margin;
    textVisual = new TextVisual(ofPoint(x,y),widthGUI,h);
    textVisual->setText("Season: " + m_season,"Klavika-Regular.otf", h);
    textVisual->setColor(ofColor(255,255,255));
    m_textVisuals["Season"] = textVisual;
    
    y = y + h + margin;
    textVisual = new TextVisual(ofPoint(x,y),widthGUI,h);
    textVisual->setText("Status: " + m_dayTime,"Klavika-Regular.otf", h);
    textVisual->setColor(ofColor(255,255,255));
    m_textVisuals["DayTime"] = textVisual;
    
    x = x + w;
    y = 7*margin;
    
    y = y + h + margin;
    textVisual = new TextVisual(ofPoint(x,y),widthGUI,h);
    textVisual->setText("Location: " + m_location,"Klavika-Regular.otf", h);
    textVisual->setColor(ofColor(255,255,255));
    m_textVisuals["Location"] = textVisual;
    
    y = y + h + margin;
    textVisual = new TextVisual(ofPoint(x,y),widthGUI,h);
    textVisual->setText("Latitude: " + ofToString(m_latitude) + "º","Klavika-Regular.otf", h);
    textVisual->setColor(ofColor(255,255,255));
    m_textVisuals["Lat"] = textVisual;
    
    y = y + h + margin;
    textVisual = new TextVisual(ofPoint(x,y),widthGUI,h);
    textVisual->setText("Longitude: " +  ofToString(m_longitude) + "º","Klavika-Regular.otf", h);
    textVisual->setColor(ofColor(255,255,255));
    m_textVisuals["Lon"] = textVisual;
    
    
    for (TextVisualMap::iterator it= m_textVisuals.begin() ; it != m_textVisuals.end(); it++ )
    {
        AppManager::getInstance().getViewManager().addVisual(*(it->second));
        AppManager::getInstance().getViewManager().fadeVisual(*(it->second),0.0,255, FADE_TIME);
    }
    
}  
void DateManager::update(double dt)
{
    m_elapsedTime+=dt;
    if(m_elapsedTime>= REFRESH_TIME)
    {
        m_elapsedTime = 0;
        this->calcDayTime();
        AppManager::getInstance().getVisualEffectsManager().removeAllVisualEffects(*(m_textVisuals["Hour"]));
        AppManager::getInstance().getViewManager().fadeVisual(*(m_textVisuals["Hour"]),0.0,255, FADE_TIME);
        m_textVisuals["Hour"]->setText("Hour: " + this->getHour() + "h","Klavika-Regular.otf", FONT_SIZE);
        
        int day = m_Date->getDay(); // if we change day
        if(m_day != day)
        {
            m_day = day;
            m_month = m_Date->getMonth();
            m_year = m_Date->getYear();
        
            this->calcSunEqs();
            this->calcSeason();
            this->displayDate();
            
            m_textVisuals["Date"]->setText("Date: " + this->getDate(),"Klavika-Regular.otf", FONT_SIZE);
            m_textVisuals["Season"]->setText("Season: " + m_season,"Klavika-Regular.otf", FONT_SIZE);
            m_textVisuals["Sunset"]->setText("Sunset: " + this->timeToString(m_sunset) + "h" + ", Dusk: " + this->timeToString(m_dusk) + "h","Klavika-Regular.otf", FONT_SIZE);
            m_textVisuals["Sunrise"]->setText("Dawn: " + this->timeToString(m_dawn) + "h" + ", Sunrise: " + this->timeToString(m_sunrise) + "h","Klavika-Regular.otf", FONT_SIZE);
        }
        
    }
    
}

std::string DateManager::getTime()
{
    return  (this->getDate() + "," + this->getHour());
}

std::string DateManager::getHour()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%H:%M", &tstruct);
    
    return  buf;
    
}

std::string DateManager::getDate()
{
    
    std::string day = ofToString(m_day);
    if (m_day < 10) day = "0" + day;
    
    std::string month = ofToString(m_month);
    if (m_month < 10) month = "0" + month;
    
    return  (day + "/" + month + "/" + ofToString(m_year));
    
}

std::string DateManager::getLogDate()
{
    
    std::string day = ofToString(m_day);
    if (m_day < 10) day = "0" + day;
    
    std::string month = ofToString(m_month);
    if (m_month < 10) month = "0" + month;
    
    return  (day + "_" + month + "_" + ofToString(m_year));
    
}

std::string DateManager::timeToString(double timeInt)
{
    
    int hourTime = (int) timeInt;
    int minTime =(timeInt - (double) hourTime)*60;
    
    string hours = ofToString(hourTime);
    if (hourTime < 10) hours = "0" + hours;
    
    string minutes = ofToString(minTime);
    if (minTime < 10) minutes = "0" + minutes;
    
    return (hours + ":" + minutes);
    
}

void DateManager::calcDayTime()
{
    time_t now;
    struct tm *current;
    now = time(0);
    current = localtime(&now);
    
    double time = current->tm_hour + current->tm_min/60.0;
    
    string dayTime;
    if (time>=m_dawn&&time<m_sunrise) {
        dayTime = "DWN";
    }
    
    else if(time>=m_sunrise&&time<m_sunset) {
        dayTime = "DAY";
    }
    
    else if(time>=m_sunset&&time<m_dusk) {
        dayTime = "DSK";
    }
    else{
         dayTime = "NIG";
    }
    
    if(m_dayTime!=dayTime)
    {
        m_dayTime = dayTime;
        AppManager::getInstance().getEventManager().setEvent(Event(m_dayTime));
        std::cout<<this->getTime() << "- DateManager-> Status:  "<< m_dayTime<< std::endl;
        ofLogNotice()<<this->getTime() << "- DateManager-> Status:  "<< m_dayTime;
    
        AppManager::getInstance().getVisualEffectsManager().removeAllVisualEffects(*(m_textVisuals["DayTime"]));
        AppManager::getInstance().getViewManager().fadeVisual(*(m_textVisuals["DayTime"]),0.0,255, FADE_TIME);
        m_textVisuals["DayTime"]->setText("Status: " + m_dayTime,"Klavika-Regular.otf", FONT_SIZE);
        
        if(m_dayTime=="NIG" || m_dayTime=="DSK"){
            AppManager::getInstance().getEventManager().setEvent(Event("LIGHT",1));
            std::cout << this->getTime() << "- DateManager-> Night: Light On " << std::endl;
            ofLogNotice() << this->getTime() << "- DateManager->Night: Light On " ;
        }
        
        if(m_dayTime=="DAY" || m_dayTime=="DWN"){
            AppManager::getInstance().getEventManager().setEvent(Event("LIGHT",0));
            std::cout << this->getTime() << "- DateManager-> Day: Light Off " << std::endl;
            ofLogNotice() << this->getTime() << "- DateManager->Day: Light Off " ;
        }
        
    }
    
}

void DateManager::calcSeason()
{
    string season;
    if(1 <= m_month && m_month <=3)
    {
        season = "WIN";
    }
    
    else if (4 <= m_month && m_month <=6)
    {
        season = "SPR";
    }
    
    else if (7 <=m_month && m_month <=9)
    {
        season = "SUM";
    }
    
    else if (10 <= m_month && m_month <= 12)
    {
        season = "FAL";
    }
    
    
    if ( (m_month % 3 == 0) && (m_day >= 21))
    {
        if (season=="WIN")
        {
            season = "SPR";
            
        }
        
        else if (season=="SPR")
        {
            season = "SUM";
        }
        
        else if (season=="SUM")
        {
            season = "FAL";
        }
        
        else if (season=="FAL")
        {
            season = "WIN";
        }
        
        else 
        {
            season = "WIN";
        }    			
    }
    
    
    if(m_season!=season)
    {
        m_season = season;
        AppManager::getInstance().getEventManager().setEvent(Event(m_season));
    }
    
}

void DateManager::handleEvent(const Event& event)
{
    std::string name = event.getName();
    if(name=="WIN" || name=="SUM" ||name=="FAL" ||name=="SPR")
    {
        if(m_season!=name)
        {
            m_season = name;
            AppManager::getInstance().getEventManager().setEvent(Event(m_season));
        }

    }
    
    else if(name== "DAY" || name=="NIG" || name=="DSK" || name=="DWN" )
    {
        m_dayTime = name;
    }
    
}

void DateManager::displayDate()
{
    std::cout<<std::endl;
    std::cout<<this->getTime() << "- DateManager-> Date:  "<< this->getDate()<< std::endl;
    std::cout<<this->getTime() << "- DateManager-> Season:  "<< m_season<< std::endl;
    std::cout<<this->getTime() << "- DateManager-> Status:  "<< m_dayTime<< std::endl;
    
    ofLogNotice()<<std::endl;
    ofLogNotice()<<this->getTime() << "- DateManager-> Date:  "<< this->getDate();
    ofLogNotice()<<this->getTime() << "- DateManager-> Season:  "<< m_season;
    ofLogNotice()<<this->getTime() << "- DateManager-> Status:  "<< m_dayTime;
    
    std::cout<<this->getTime() << "- DateManager-> Dawn:  " + this->timeToString(m_dawn)<< std::endl;
    ofLogNotice()<<this->getTime() << "- DateManager-> Dawn:  " + this->timeToString(m_dawn);
    
    std::cout<<this->getTime() << "- DateManager-> Sunrise:  " + this->timeToString(m_sunrise)<< std::endl;
    ofLogNotice()<<this->getTime() << "- DateManager-> Sunrise: " +  this->timeToString(m_sunrise);
    
    std::cout<<this->getTime() << "- DateManager-> Sunset:  " + this->timeToString(m_sunset)<< std::endl;
    ofLogNotice()<<this->getTime() << "- DateManager-> Sunset: " +  this->timeToString(m_sunset);
    
    std::cout<<this->getTime() << "- DateManager-> Dusk:  " + this->timeToString(m_dusk)<< std::endl;
    std::cout<<std::endl;
    ofLogNotice()<<this->getTime() << "- DateManager-> Dusk: " +  this->timeToString(m_dusk);
    ofLogNotice()<<std::endl;
    
}

void DateManager::calcEST() {
    
    int month_begin = 3; // European Summer Time begins in march
    int month_end = 10; // European Summer Time ends in October
    
    //November, December, January and February are not ETS
    if (m_month < month_begin || m_month > month_end) { 
        m_EST = 0;
        return ; 
    }
    
    //April to September are ETS
    if (m_month > month_begin && m_month < month_end) { 
        m_EST = 1;
        return; 
    }
    
    //In march, European Summer Time could start
    if (m_month == month_begin) { 
    	int dayBegin = 31 - ((((5 * m_year) / 4) + 4) % 7);
    	if (m_day<dayBegin) {
    		m_EST = 0;
            return;
    	}
    	else
    	{
            m_EST = 1;
    		return;
    	}
    }
    
    //In October, European Summer Time could start
    if (m_month == month_end) { 
    	int dayEnd = 31 - ((((5 * m_year) / 4) + 1) % 7);
    	if (m_day<dayEnd) {
            m_EST = 1;
    		return;
    	}
    	else
    	{
            m_EST = 0;
    		return;
    	}
    }
}

double DateManager::FNday () 
{
    int h = 12;   //h is UT in decimal hours
    long int luku = - 7 * (m_year + (m_month + 9)/12)/4 + 275*m_month/9 + m_day;
    
    // Typecasting needed for TClite on PC DOS at least, to avoid product overflow
    luku+= (long int)m_year*367;
    
    return (double)luku - 730531.5 + h/24.0;
}

double DateManager::FNrange (double x) 
{
    double b = x / (2*PI);
    double a = 2*PI * (b - (long)(b));
    if (a < 0) a = 2*PI + a;
    return a;
}

double DateManager::f0(double lat, double declin)
{    
    double SunDia = 0.53;  // Sunradius degrees
    double AirRefr = 34.0/60.0; // athmospheric refraction degrees 
    double rads = PI/180.0;
    
    double fo,dfo;
    // Correction: different sign at S HS
    dfo = rads*(0.5*SunDia + AirRefr); if (lat < 0.0) dfo = -dfo;
    fo = tan(declin + dfo) * tan(lat*rads);
    
    if (fo > 0.99999) fo=1.0; // to avoid overflow //
    fo = asin(fo) + PI/2.0;
    return fo;
}

double DateManager::f1(double lat, double declin) 
{
    double rads = PI/180.0;
    double fi,df1;
    // Correction: different sign at S HS
    df1 = rads * 6.0; if (lat < 0.0) df1 = -df1;
    fi = tan(declin + df1) * tan(lat*rads);
    
    if (fi > 0.99999) fi=1.0; // to avoid overflow //
    fi = asin(fi) + PI/2.0;
    return fi;
}

void DateManager::FNsun (double d,double& L, double& g, double& lambda) {
    
    double rads = PI/180.0;
    // mean longitude of the Sun
    L = FNrange(280.461 * rads + .9856474 * rads * d);
    // mean anomaly of the Sun
    g = FNrange(357.528 * rads + .9856003 * rads * d);
    // Ecliptic longitude of the Sun
    lambda =  FNrange(L + 1.915 * rads * sin(g) + .02 * rads * sin(2 * g));
}

void DateManager::calcSunEqs()
{
    double degs = 180.0/PI;
    double rads = PI/180.0;
    double lambda = 0.0; // ecliptic longitude of the Sun
    double L = 0.0; // mean longitude of the Sun
    double g = 0.0; // mean anomaly of the Sun
    
    double d = this->FNday();
    
    // Use FNsun to find the ecliptic longitude of the Sun
    this->FNsun(d,L,g,lambda);
    
    // Obliquity of the ecliptic
    
    double obliq = 23.439 * rads - .0000004 * rads * d;
    
    // Find the RA and DEC of the Sun
    
    double alpha = atan2(cos(obliq) * sin(lambda), cos(lambda));
    double delta = asin(sin(obliq) * sin(lambda));
    
    
    // Find the Equation of Time in minutes
    // Correction suggested by David Smith
    
    double LL = L - alpha;
    if (L < PI) LL += 2*PI;
    double equation = 1440.0 * (1.0 - LL / (2*PI));
    
    double ha = f0(m_latitude,delta);
    double hb = f1(m_latitude,delta);
    double twx = hb - ha;   // length of twilight in radians
    twx = 12.0*twx/PI;      // length of twilight in degrees
    // Conversion of angle to hours and minutes //
    double daylen = degs * ha / 7.5;
    if (daylen<0.0001) {daylen = 0.0;}
    // arctic winter   //

    
    
    this->calcEST(); //calculate the European Summer Time offset
    m_sunrise = 12.0 - 12.0 * ha/PI + (m_timezone+ m_EST) - m_longitude/15.0 + equation/60.0;
    m_sunset = 12.0 + 12.0 * ha/PI + (m_timezone+ m_EST) - m_longitude/15.0 + equation/60.0;
    
    m_dawn = m_sunrise - twx;     // morning twilight begin
    m_dusk = m_sunset + twx;     // evening twilight end
    
    if (m_sunrise > 24.0) m_sunrise-= 24.0;
    if (m_sunset > 24.0) m_sunset-= 24.0;
    
}


std::string DateManager::getSeasonsName(const std::string& path)
{
    std::vector<std::string> strs = ofSplitString(path, "/");
    std::string str = strs.back();
    strs = ofSplitString(str, ".");
    return strs.front();
}


