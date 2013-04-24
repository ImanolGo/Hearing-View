
/*==============================================================================
 Imanolgo on 25/04/13.
 ==============================================================================*/
/*! \file WeatherThread.h
 * \authors Imanol Gómez
 * \copyright{2012}
 *///============================================================================


#ifndef __WEATHER_THREAD_H__
#define __WEATHER_THREAD_H__

#define MESSAGE_LENGTH 3

#include "ofMain.h"

typedef enum {
    IDLE=0,
    WAKE_UPSTATION,
    READ_TEMPERATURE,
    WIND_HUMIDITY
} SERIAL_STATE;


class DateManager;

class WeatherThread : public ofThread{
    
    static const int BAUD_RATE;		///< defines communication's baud rate 

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
    
    char		m_bytesRead[MESSAGE_LENGTH];				// data from serial, we will be trying to read 3
    char		m_bytesReadString[MESSAGE_LENGTH +1];		// a string needs a null terminator, so we need 3 + 1 bytes
    int			m_nBytesRead;                             // how much did we read?	

    DateManager*    m_dateManager;        ///< pointer to the date manager
    ofSerial        m_serial;             ///< a serial object
    SERIAL_STATE    m_serialState;        ///< defines the current state of the serial communication
    int             m_maxWaitingLoops;    ///< defines the maximum number of loops 
    
    

};

#endif
