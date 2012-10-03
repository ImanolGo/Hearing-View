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
#include "ViewManager.h"

#include "DateManager.h"


const double DateManager::REFRESH_TIME = 5*60;
const double DateManager::FADE_TIME = 3;

DateManager::DateManager(): 
    m_latitude(0.0),
    m_longitude(0.0),
    m_timezone(0),
    m_sunrise(6),
    m_sunset(19),
    m_elapsedTime(0.0),
    m_EST(0),
    m_season("Summer"),
    m_dayTime("Day")
{
    m_Date = new ofxDate();
    m_day = m_Date->getDay();
    m_month = m_Date->getMonth();
    m_year = m_Date->getYear();
}

DateManager::~DateManager()
{
    delete m_Date;
    
    for (SeasonMap::iterator it= m_seasonImages.begin() ; it != m_seasonImages.end(); it++ )
    {
        delete it->second;
        it->second = NULL;
    }

}

void DateManager::setup()
{
    //location: Linz
    m_latitude = 48.303056;
    m_longitude = 14.290556;
    m_timezone = 1;
    
    m_day = m_Date->getDay();
    m_month = m_Date->getMonth();
    m_year = m_Date->getYear();
    
    this->loadSeasons();
    this->calcSunEqs();
    this->calcSeason();
    this->calcDayTime();
    this->displayDate();
    std::cout<<this->getTime()<< "- DateManager-> initialized "<<std::endl;
    ofLogNotice()<<this->getTime()<< "- DateManager-> initialized ";
    
}

void DateManager::update(double dt)
{
    m_elapsedTime+=dt;
    if(m_elapsedTime>= REFRESH_TIME)
    {
        m_elapsedTime = 0;
        this->calcDayTime();
        
        int day = m_Date->getDay(); // if we change day
        if(m_day != day)
        {
            m_day = day;
            m_month = m_Date->getMonth();
            m_year = m_Date->getYear();
            this->calcSunEqs();
            this->calcSeason();
        }
        
    }
    
}

std::string DateManager::getTime()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%H:%M:%S", &tstruct);
    
    std::string date = ofToString(m_day) + "/" +  ofToString(m_month) + "/" +  ofToString(m_year) + "," + buf;

    return  date;

}
void DateManager::calcDayTime()
{
    time_t now;
    struct tm *current;
    now = time(0);
    current = localtime(&now);
    
    int currentHour = current->tm_hour;
    int currentMin = current->tm_min;
    
    int hourSunrise = (int) m_sunrise;
    int minSunrise =(m_sunrise - (double) hourSunrise)*60;
    
    int hourSunset = (int) m_sunset;
    int minSunset = (m_sunset - (double) hourSunset)*60;
    
    string dayTime;
    if (currentHour == hourSunrise) {
        if (currentMin>=minSunrise) {
            dayTime = "Day";
        }
        else{
            dayTime = "Night";
        }
    }
    
    if (currentHour == hourSunset) {
        if (currentMin < minSunset) {
            dayTime = "Day";
        }
        else{
            dayTime = "Night";
        }
    }
    
    
    if(currentHour > hourSunrise && currentHour<hourSunset)
    {
        dayTime = "Day";
    }
    
    else
    {
        dayTime = "Night";
    }
    
    if(m_dayTime!=dayTime)
    {
        m_dayTime = dayTime;
        AppManager::getInstance().getEventManager().setEvent(Event(m_dayTime));
        
    }
    
}

void DateManager::calcSeason()
{
    string season;
    if(1 <= m_month && m_month <=3)
    {
        season = "Winter";
    }
    
    else if (4 <= m_month && m_month <=6)
    {
        season = "Spring";
    }
    
    else if (7 <=m_month && m_month <=9)
    {
        season = "Summer";
    }
    
    else if (10 <= m_month && m_month <= 12)
    {
        season = "Autumn";
    }
    
    
    if ( (m_month % 3 == 0) && (m_day >= 21))
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
    
    
    if(m_season!=season)
    {
        AppManager::getInstance().getViewManager().fadeVisual(*m_seasonImages[m_season], 0, DateManager::FADE_TIME);
        AppManager::getInstance().getViewManager().fadeVisual(*m_seasonImages[season], 255, DateManager::FADE_TIME);
        m_season = season;
        AppManager::getInstance().getEventManager().setEvent(Event(m_season));
    }
    
}

void DateManager::handleEvent(const Event& event)
{
    std::string name = event.getName();
    if(name=="Winter" || name=="Summer" ||name=="Autumn" ||name=="Spring")
    {
        if(m_season!=name)
        {
            AppManager::getInstance().getViewManager().fadeVisual(*m_seasonImages[m_season], 0, DateManager::FADE_TIME,ViewManager::LINEAR);
            AppManager::getInstance().getViewManager().fadeVisual(*m_seasonImages[name], 255, DateManager::FADE_TIME,ViewManager::LINEAR);
            m_season = name;
            AppManager::getInstance().getEventManager().setEvent(Event(m_season));
        }

    }
    
    else if(name== "Day" || name=="Night" )
    {
        m_dayTime = name;
    }
    
}

void DateManager::displayDate()
{
    std::cout<<this->getTime() << "- DateManager-> Date:  "<< m_day<< "/"<<m_month<<"/"<<m_year<<std::endl;
    std::cout<<this->getTime() << "- DateManager-> Season:  "<< m_season<< std::endl;
    std::cout<<this->getTime() << "- DateManager-> Status:  "<< m_dayTime<< std::endl;
    
    ofLogNotice()<<this->getTime() << "- DateManager-> Date:  "<< m_day<< "/"<<m_month<<"/"<<m_year;
    ofLogNotice()<<this->getTime() << "- DateManager-> Season:  "<< m_season;
    ofLogNotice()<<this->getTime() << "- DateManager-> Status:  "<< m_dayTime;
       
    std::cout<<this->getTime() << "- DateManager-> Sunrise:  ";
    ofLogNotice()<<this->getTime() << "- DateManager-> Sunrise:  ";
    int hourSunrise = (int) m_sunrise;
    int minSunrise =(m_sunrise - (double) hourSunrise)*60;
    
    if (hourSunrise < 10) cout << '0';
    
    cout << hourSunrise << ':';
    ofLogNotice()<< hourSunrise << ':';
    
    if (minSunrise < 10) cout << '0';
    
    cout << minSunrise << std::endl;
    ofLogNotice()<< minSunrise;


    std::cout<<this->getTime() << "- DateManager-> Sunset:  ";
    ofLogNotice()<<this->getTime() << "- DateManager-> Sunset:  ";
    int hourSunset = (int) m_sunset;
    int minSunset = (m_sunset - (double) hourSunset)*60;
    
    if (hourSunset < 10) cout << '0';
    
    cout << hourSunset << ':';
    ofLogNotice()<< hourSunset << ':';

    if (minSunset < 10) cout << '0';
    
    cout << minSunset << std::endl;
    ofLogNotice()<< minSunset;
    
            
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
    double b = x / (2*pi);
    double a = 2*pi * (b - (long)(b));
    if (a < 0) a = 2*pi + a;
    return a;
}

double DateManager::f0(double lat, double declin)
{    
    double SunDia = 0.53;  // Sunradius degrees
    double AirRefr = 34.0/60.0; // athmospheric refraction degrees 
    double rads = pi/180.0;
    
    double fo,dfo;
    // Correction: different sign at S HS
    dfo = rads*(0.5*SunDia + AirRefr); if (lat < 0.0) dfo = -dfo;
    fo = tan(declin + dfo) * tan(lat*rads);
    
    if (fo > 0.99999) fo=1.0; // to avoid overflow //
    fo = asin(fo) + pi/2.0;
    return fo;
}

double DateManager::f1(double lat, double declin) 
{
    double rads = pi/180.0;
    double fi,df1;
    // Correction: different sign at S HS
    df1 = rads * 6.0; if (lat < 0.0) df1 = -df1;
    fi = tan(declin + df1) * tan(lat*rads);
    
    if (fi > 0.99999) fi=1.0; // to avoid overflow //
    fi = asin(fi) + pi/2.0;
    return fi;
}

void DateManager::FNsun (double d,double& L, double& g, double& lambda) {
    
    double rads = pi/180.0;
    // mean longitude of the Sun
    L = FNrange(280.461 * rads + .9856474 * rads * d);
    // mean anomaly of the Sun
    g = FNrange(357.528 * rads + .9856003 * rads * d);
    // Ecliptic longitude of the Sun
    lambda =  FNrange(L + 1.915 * rads * sin(g) + .02 * rads * sin(2 * g));
}

void DateManager::calcSunEqs()
{
    double degs = 180.0/pi;
    double rads = pi/180.0;
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
    if (L < pi) LL += 2*pi;
    double equation = 1440.0 * (1.0 - LL / (2*pi));
    
    double ha = f0(m_latitude,delta);
    double hb = f1(m_latitude,delta);
    double twx = hb - ha;   // length of twilight in radians
    twx = 12.0*twx/pi;      // length of twilight in degrees
    // Conversion of angle to hours and minutes //
    double daylen = degs * ha / 7.5;
    if (daylen<0.0001) {daylen = 0.0;}
    // arctic winter   //
    
    this->calcEST(); //calculate the European Summer Time offset
    m_sunrise = 12.0 - 12.0 * ha/pi + (m_timezone+ m_EST) - m_longitude/15.0 + equation/60.0;
    m_sunset = 12.0 + 12.0 * ha/pi + (m_timezone+ m_EST) - m_longitude/15.0 + equation/60.0;
}


void DateManager::loadSeasons()
{
    //some path, may be absolute or relative to bin/data
    std::string samplesPath = "pictures/Seasons/";
    std::cout<<this->getTime() << "- DateManager-> loadSamples: loading icons from \""<<samplesPath<<"\"..."<<std::endl;
    ofLogNotice()<<this->getTime() << "- DateManager-> loadSamples: loading icons from \""<<samplesPath<<"\"...";
    ofDirectory dir(samplesPath);
    //only show png files
    dir.allowExt("png");
    //populate the directory object
    if(dir.listDir()==0)
    {
        std::cout<<this->getTime() << "- DateManager-> loadSeasons: No season images found at \""<< samplesPath <<"\"" << std::endl;
        ofLogNotice()<<this->getTime() << "- DateManager-> loadSeasons: No season images found at \""<< samplesPath <<"\"";
        return;
    }
    
    float widthSeasons = ofGetWidth()/3.0; 
    float heightSeason = 4*ofGetHeight()/10.0; 
    float hightIcon = 9*heightSeason/10;
    
    //go through and print out all the paths
    for(int n = 0; n < dir.numFiles(); n++)
    {
        std::string seasonName = this->getSeasonsName(dir.getPath(n));
        ImageVisual* seasonImage =  new ImageVisual(ofPoint(widthSeasons*2 + widthSeasons/20,heightSeason/10),widthSeasons - widthSeasons/10,hightIcon);
        seasonImage->setImage(dir.getPath(n));
        m_seasonImages[seasonName] = seasonImage;
        std::cout<<this->getTime() << "- DateManager-> loaded sample \""<< seasonName <<"\"" << std::endl;
        ofLogNotice()<<this->getTime() << "- DateManager-> loaded sample \""<< seasonName <<"\"";
        AppManager::getInstance().getViewManager().addVisual(*seasonImage);
        m_seasonImages[seasonName]->setColor(ofColor(255,255,255,0));
    }
    
    AppManager::getInstance().getViewManager().fadeVisual(*m_seasonImages[m_season], 255, DateManager::FADE_TIME, ViewManager::LINEAR);

}


std::string DateManager::getSeasonsName(const std::string& path)
{
    std::vector<std::string> strs = ofSplitString(path, "/");
    std::string str = strs.back();
    strs = ofSplitString(str, ".");
    return strs.front();
}


