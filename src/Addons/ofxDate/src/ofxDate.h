#ifndef OFXDATE_H
#define OFXDATE_H

#include "ofUtils.h"
#include <iostream>
#include <iomanip>

class ofxDate
{
    public:
        ofxDate();
        ofxDate(long days);
        ofxDate(int year, int month, int day);
        virtual ~ofxDate();
        unsigned int getDay() { return m_day; }
        void setDay(unsigned int day) { m_day = day;calcDaysPast();}
        unsigned int getMonth() { return m_month; }
        void setMonth(unsigned int month) { m_month = month;calcDaysPast(); }
        unsigned int getYear() { return m_year; }
        void setYear(unsigned int year) { m_year = year; calcDaysPast();}
        void checkDate();
        string getIsoDate() const {
            // YYYY-MM-DD
            stringstream str;
            str.fill('0');
            str << setw(4) << m_year << "-";
            str << setw(2) << m_month << "-";
            str << setw(2) << m_day;
            return str.str();
        }
        bool isLeapyear(int year)
        {
            if(year<1) {
                ofLogError() << "isLeapyear of " << year;
                return false;
            }
            if(year%4) return false;
            if(year<=1582) return true;
            if(year%100) return true;
            if(year%400) return false;
            return true;
        }
        bool isLeapyear()
        {
            return isLeapyear(m_year);
        }
        int daysPerMonth(int month)
        {
            switch(month) {
                case 1:
                case 3:
                case 5:
                case 7:
                case 8:
                case 10:
                case 12:
                    return 31;
                case 4:
                case 6:
                case 9:
                case 11:
                    return 30;
                case 2: return (28 + isLeapyear());
                default:
                    // ofLogError() << "daysPerMonth";
                    return -1;
            }
        }
        int daysPerMonth()
        {
            return daysPerMonth(m_month);
        }
        int getCalendarWeek()
        {
            char timebuf[64];
            time_t rawtime;
            struct tm * timeinfo;
            time ( &rawtime );
            timeinfo = localtime ( &rawtime );
            timeinfo->tm_year = m_year;
            timeinfo->tm_mon = m_month;
            timeinfo->tm_mday = m_day;
            mktime(timeinfo);
            if (strftime(timebuf, sizeof(timebuf), "%W", timeinfo) != 0) {
                return ofToInt(std::string(timebuf));
            }
        }
        int getCalendarWeeksOfYear(int year)
        {
            if ((ofxDate(1,1,year).getWeekday() == 3) ||
                (ofxDate(31,12,year).getWeekday() == 3))
                return 53;
            else
                return 52;
        }
        int getCalendarWeeksOfYear()
        {
            return getCalendarWeeksOfYear(m_year);
        }
        int getWeekday()
        {
            time_t rawtime;
            struct tm * timeinfo;
            time ( &rawtime );
            timeinfo = localtime ( &rawtime );
            timeinfo->tm_year = m_year;
            timeinfo->tm_mon = m_month;
            timeinfo->tm_mday = m_day;
            mktime(timeinfo);
            return timeinfo->tm_wday;
        }
        void inspect();
        ofxDate operator+(long days) const;
        ofxDate operator-(long days) const;
        long operator-(const ofxDate &d) const;
        bool operator< (const ofxDate &d) const;
        bool operator<= (const ofxDate &d) const;
        bool operator> (const ofxDate &d) const;
        bool operator>= (const ofxDate &d) const;
        bool operator==(const ofxDate &d) const;

    protected:
    private:
        void calcDate();
        void calcDaysPast();
        unsigned int m_day;
        unsigned int m_month;
        unsigned int m_year;
        unsigned int m_daysPast;
};

#endif

