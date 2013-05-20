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
    m_Date = NULL;
    
    for (SeasonMap::iterator it= m_seasonImages.begin() ; it != m_seasonImages.end(); it++ )
    {
       AppManager::getInstance().getViewManager().removeVisual(*it->second);
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

std::string DateManager::getDate()
{
    
    std::string date = ofToString(m_day) + "_" +  ofToString(m_month) + "_" +  ofToString(m_year);
    return  date;
    
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
        AppManager::getInstance().getViewManager().fadeVisual(*m_seasonImages[m_season], 0, DateManager::FADE_TIME);
        AppManager::getInstance().getViewManager().fadeVisual(*m_seasonImages[season], 255, DateManager::FADE_TIME);
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
            AppManager::getInstance().getViewManager().fadeVisual(*m_seasonImages[m_season], 0, DateManager::FADE_TIME);
            AppManager::getInstance().getViewManager().fadeVisual(*m_seasonImages[name], 255, DateManager::FADE_TIME);
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
    std::cout<<this->getTime() << "- DateManager-> Date:  "<< m_day<< "/"<<m_month<<"/"<<m_year<<std::endl;
    std::cout<<this->getTime() << "- DateManager-> Season:  "<< m_season<< std::endl;
    std::cout<<this->getTime() << "- DateManager-> Status:  "<< m_dayTime<< std::endl;
    
    ofLogNotice()<<this->getTime() << "- DateManager-> Date:  "<< m_day<< "/"<<m_month<<"/"<<m_year;
    ofLogNotice()<<this->getTime() << "- DateManager-> Season:  "<< m_season;
    ofLogNotice()<<this->getTime() << "- DateManager-> Status:  "<< m_dayTime;
    
    std::cout<<this->getTime() << "- DateManager-> Dawn:  ";
    ofLogNotice()<<this->getTime() << "- DateManager-> Dawn:  ";
    int hourDawn = (int) m_dawn;
    int minDawn =(m_dawn - (double) hourDawn)*60;
    
    if (hourDawn < 10) cout << '0';
    
    cout << hourDawn << ':';
    ofLogNotice()<< hourDawn << ':';
    
    if (minDawn < 10) cout << '0';
    
    cout << minDawn << std::endl;
    ofLogNotice()<< minDawn;
    
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
    
    std::cout<<this->getTime() << "- DateManager-> Dusk:  ";
    ofLogNotice()<<this->getTime() << "- DateManager-> Dusk:  ";
    int hourDusk = (int) m_dusk;
    int minDusk =(m_dusk - (double) hourDusk)*60;
    
    if (hourDusk < 10) cout << '0';
    
    cout << hourDusk << ':';
    ofLogNotice()<< hourDusk << ':';
    
    if (minDusk < 10) cout << '0';
    
    cout << minDusk << std::endl;
    ofLogNotice()<< minDusk;
    
            
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
    
    m_dawn = m_sunrise - twx;     // morning twilight begin
    m_dusk = m_sunset + twx;     // evening twilight end
    
    if (m_sunrise > 24.0) m_sunrise-= 24.0;
    if (m_sunset > 24.0) m_sunset-= 24.0;
    
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
    
    float margin = ofGetHeight()/70.0;
    float widthVisuals = ofGetWidth() - 4*margin; 
    float heightVisuals = ofGetHeight()/3.0 - 4*margin;
    float h = heightVisuals - 4*margin;
    float w = 2*widthVisuals/5 - 2*margin;
    float x = 3*margin + 3*widthVisuals/5 + widthVisuals/10 +  w/2;
    float y = 8*margin + 2*heightVisuals + h/2;
    
    //go through and print out all the paths
    for(int n = 0; n < dir.numFiles(); n++)
    {
        std::string seasonName = this->getSeasonsName(dir.getPath(n));
        ImageVisual* seasonImage =  new ImageVisual(ofPoint(x,y),h,h,true);
        seasonImage->setImage(dir.getPath(n));
        m_seasonImages[seasonName] = seasonImage;
        std::cout<<this->getTime() << "- DateManager-> loaded sample \""<< seasonName <<"\"" << std::endl;
        ofLogNotice()<<this->getTime() << "- DateManager-> loaded sample \""<< seasonName <<"\"";
        AppManager::getInstance().getViewManager().addVisual(*seasonImage);
        m_seasonImages[seasonName]->setColor(ofColor(255,255,255,0));
    }
    
    AppManager::getInstance().getViewManager().fadeVisual(*m_seasonImages[m_season], 255, DateManager::FADE_TIME);

}


std::string DateManager::getSeasonsName(const std::string& path)
{
    std::vector<std::string> strs = ofSplitString(path, "/");
    std::string str = strs.back();
    strs = ofSplitString(str, ".");
    return strs.front();
}


