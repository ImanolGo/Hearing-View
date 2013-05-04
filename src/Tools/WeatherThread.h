
/*==============================================================================
 Imanolgo on 25/04/13.
 ==============================================================================*/
/*! \file WeatherThread.h
 * \authors Imanol Gómez
 * \copyright{2012}
 *///============================================================================


#ifndef __WEATHER_THREAD_H__
#define __WEATHER_THREAD_H__

#define OK_SIZE 4 ///< defines the size of the input OK command. OK <cr><lf>
#define HEADER_SIZE 86 ///< defines the size of the input header
#define DATA_SIZE 120 ///< defines the size of the input current conditions data

#include "ofMain.h"

typedef enum {
    IDLE=0,
    WAKE_UP_STATION,
    READ_DATA,
    END_SESSION
} SERIAL_STATE;


class WeatherThread : public ofThread{
    
    static const double REFRESH_TIME;       ///< defines the refresh time
    static const double WAKING_TIME;       ///< defines the time for the serial to wait for a response
    static const double TERMINATE_TIME;       ///< defines the time for the serial to wait for a response
    static const double DATA_TIME;       ///< defines the time for the serial to wait for a response
    static const int BAUD_RATE;             ///< defines communication's baud rate
    static const int WAKING_CHAR_GROUP;     ///< defines size of the "@" waking up command
    static const int NUM_WAKING_UPS;        ///< defines maximum number of groups sent to wake up the station
    
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
    
    unsigned char		m_bytesOK[OK_SIZE];	// data from serial, we will be trying to read the Ok message
    unsigned char		m_bytesOKString[OK_SIZE +1]; // a string needs a null terminator
    unsigned char		m_bytesData[DATA_SIZE];	// data from serial, we will be trying to read the Ok message
    unsigned char		m_bytesDataString[DATA_SIZE +1]; // a string needs a null terminator
    unsigned char		m_bytesHeader[HEADER_SIZE];	// data from serial, we will be trying to read the Ok message
    unsigned char		m_bytesHeaderString[HEADER_SIZE +1]; // a string needs a null terminator
    int         m_nBytesRead;                             // how much did we read?
    
    ofSerial        m_serial;             ///< a serial object
    SERIAL_STATE    m_serialState;        ///< defines the current state of the serial communication
    int             m_maxWaitingLoops;    ///< defines the maximum number of loops
    int             m_bytesRemaining;     ///< the bytes remaining
    int             m_wakingUp_num;    ///< number of waking ups requests
    
    
};

#endif
