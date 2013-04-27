
/*==============================================================================
 Imanolgo on 25/04/13.
 ==============================================================================*/
/*! \file WeatherThread.h
 * \authors Imanol Gómez
 * \copyright{2012}
 *///============================================================================


#ifndef __WEATHER_THREAD_H__
#define __WEATHER_THREAD_H__

#define OK_SIZE 4 ///< defines the size of the input OK command
#define CONDITIONS_SIZE 70 ///< defines the size of the input current conditions

#include "ofMain.h"

typedef enum {
    IDLE=0,
    WAKE_UP_STATION,
    READ_DATA,
    END_SESSION
} SERIAL_STATE;


class WeatherThread : public ofThread{
    
    static const double REFRESH_TIME;       ///< defines the refresh time 
    static const int BAUD_RATE;             ///< defines communication's baud rate 

	public:

        //! Constructor
        WeatherThread();
    
        //! Destructor
        virtual ~WeatherThread();
    
        //! Start Thread
        void start();
    
        //! Stop Thread
        void stop();
    
		 //! Run threaded function
        void threadedFunction();

private:
    
    char		m_bytesOK[OK_SIZE];	// data from serial, we will be trying to read the Ok message
    char		m_bytesOKString[OK_SIZE +1]; // a string needs a null terminator
    char		m_bytesConditions[CONDITIONS_SIZE];	// data from serial, we will be trying to read the Ok message
    char		m_bytesConditionsString[CONDITIONS_SIZE +1]; // a string needs a null terminator
    int         m_nBytesRead;                             // how much did we read?	

    ofSerial        m_serial;             ///< a serial object
    SERIAL_STATE    m_serialState;        ///< defines the current state of the serial communication
    int             m_maxWaitingLoops;    ///< defines the maximum number of loops 
    
    

};

#endif
