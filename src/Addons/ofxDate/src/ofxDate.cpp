#include "ofxDate.h"

ofxDate::ofxDate()
{
    setYear(ofGetYear());
    setMonth(ofGetMonth());
    setDay(ofGetDay());
    calcDaysPast();
}

ofxDate::ofxDate(long days) : m_daysPast(days)
{
    if(days<0) ofLogError() << "days is not valid " << days << " ofxDate(long days)";
    // "reversed" init for overloaded operator
    calcDate();
    // calcDaysPast();
}

ofxDate::ofxDate(int year, int month, int day)
{
    setYear(year);
    setMonth(month);
    setDay(day);
    calcDaysPast();
}

ofxDate::~ofxDate() {}

void ofxDate::calcDaysPast()
{
    m_daysPast=0;
    int x=1;
    while(x<m_year)
        m_daysPast+=365+isLeapyear(x++);
    x=1;
    while(x<m_month)
        m_daysPast+=daysPerMonth(x++);
    m_daysPast+=m_day-1;
    if(m_daysPast>577736)
        m_daysPast-=10;
}

void ofxDate::calcDate()
{
    long days=m_daysPast;
    if(days>577736)
        days+=10;
    m_year=1;
    while( ((days>=365) && (!isLeapyear()))
            ||
            ((days>=366)&&(isLeapyear()))) {
        days-=365+isLeapyear();
        m_year++;
    }
    m_month=1;
    while (days >= daysPerMonth()) {
        days-=daysPerMonth();
        m_month++;
    }
    m_day=1+days;
    checkDate();
}


void ofxDate::checkDate()
{
    if((m_year<1) || (m_year>32767))
        ofLogError() << "year is not valid " << m_year << " ofxDate::checkDate";
    if((m_month<1) || (m_month>12))
        ofLogError() << "month is not valid " << m_year << " ofxDate::checkDate";
    if((m_day<1) || (m_day > daysPerMonth()))
        ofLogError() << "day is not valid " << m_year << " ofxDate::checkDate";

    if((m_year==1582)&&(m_month==10)&&(m_day>4)&&(m_day<15))
        ofLogError() << "date is not valid " << m_year << " ofxDate::checkDate";
}

void ofxDate::inspect()
{
    ofLogVerbose() << "year :" << m_year;
    ofLogVerbose() << "month :" << m_month;
    ofLogVerbose() << "day:" << m_day;
    ofLogVerbose() << "daysPast:" << m_daysPast;
    ofLogVerbose() << "CalendarWeek:" << getCalendarWeek();
}


ofxDate ofxDate::operator+(long days) const {
  return(ofxDate(m_daysPast+days));
}

ofxDate ofxDate::operator-(long days) const {
  return(ofxDate(m_daysPast-days));
}

long ofxDate::operator-(const ofxDate &d) const {
  return(labs(m_daysPast-d.m_daysPast));
}

bool ofxDate::operator== (const ofxDate &d) const {
  return(m_daysPast==d.m_daysPast);
}

bool ofxDate::operator< (const ofxDate &d) const {
  return(m_daysPast<d.m_daysPast);
}

bool ofxDate::operator<= (const ofxDate &d) const {
  return(m_daysPast<=d.m_daysPast);
}

bool ofxDate::operator> (const ofxDate &d) const {
  return(m_daysPast>d.m_daysPast);
}

bool ofxDate::operator>= (const ofxDate &d) const {
  return(m_daysPast>=d.m_daysPast);
}
