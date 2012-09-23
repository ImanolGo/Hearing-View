//
//  DateWatcher.cpp
//  HearingView
//
//  Created by Imanolgo on 6/24/12.
//

#include "ofxXmlSettings.h"
#include "ofxDate.h"
#include "Event.h"
#include "AppManager.h"
#include "EventManager.h"
#include "ofxUI.h"

#include "DateManager.h"


const double DateManager::REFRESHING_TIME = 5*60;

DateManager::DateManager(): 
    m_day(1),
    m_month(1),
    m_year(1900),
    m_latitude(0.0),
    m_longitude(0.0),
    m_timezone(0),
    m_sunrise(6),
    m_sunset(19),
    m_elapsedTime(0.0),
    m_EST(0)
{
    m_Date = new ofxDate();
    
}

DateManager::~DateManager()
{
    delete m_Date;
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

    this->calcSunEqs();
    this->calcSeason();
    this->calcDayTime();
    this->displayDate();
    std::cout<< "DateManager-> initialized "<<std::endl;
    
}

void DateManager::displayDate()
{
    std::cout<< "DateManager-> Date:  "<< m_day<< "/"<<m_month<<"/"<<m_year<<std::endl;
    std::cout<< "DateManager-> Season:  "<< m_season<< std::endl;
    std::cout<< "DateManager-> Status:  "<< m_dayTime<< std::endl;
    
        
    std::cout<< "DateManager-> Sunrise:  ";
    
    int hourSunrise = (int) m_sunrise;
    int minSunrise =(m_sunrise - (double) hourSunrise)*60;
    
    if (hourSunrise < 10) cout << '0';
    cout << hourSunrise << ':';
    if (minSunrise < 10) cout << '0';
    cout << minSunrise << std::endl;

    std::cout<< "DateManager-> Sunset:  ";
    int hourSunset = (int) m_sunset;
    int minSunset = (m_sunset - (double) hourSunset)*60;
    if (hourSunset < 10) cout << '0';
    cout << hourSunset << ':';
    if (minSunset < 10) cout << '0';
    cout << minSunset << std::endl;
    
            
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
    std::cout<< LL;
    
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

void DateManager::update(double dt)
{
    m_elapsedTime+=dt;
    if(m_elapsedTime>= REFRESHING_TIME)
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
    
    if (currentHour == hourSunrise) {
        if (currentMin>=minSunrise) {
            m_dayTime = "Day";
            return;
        }
        else{
            m_dayTime = "Night";
            return;
        }
    }
    
    if (currentHour == hourSunset) {
        if (currentMin < minSunset) {
            m_dayTime = "Day";
            return;
        }
        else{
            m_dayTime = "Night";
            return;
        }
    }

    
    if(currentHour > hourSunrise && currentHour<hourSunset)
    {
        m_dayTime = "Day";
    }
    
    else
    {
        m_dayTime = "Night";
    }
    
}

void DateManager::calcSeason()
{
    
    std::string season;
    
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
        m_season = season;
        AppManager::getInstance().getEventManager().setEvent(Event(m_season));
        
    }
    
}
