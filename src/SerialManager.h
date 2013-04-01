
/*==============================================================================
 Imanolgo on 01/04/13.
 ==============================================================================*/
/*! \file SerialManager.h
 * \authors Imanol Gómez
 * \copyright{2013}
 *///============================================================================


#ifndef __SERIAL_MANAGER_H__
#define __SERIAL_MANAGER_H__

#include "ofMain.h"


#define MESSAGE_LENGTH 3

//========================== class SerialManager =======================================
//==============================================================================
/** \class SerialManager SerialManager.h
 *	\brief class for controlling the serial communication
 *	\details It communicates with the WatchDog 2000 weather setation through serial and sends
 *           the information to the weather manager
 */

class DateManager;

class SerialManager
{

    static const int BAUD_RATE;		///< defines communication's baud rate 
    static const double REFRESH_TIME;		///< defines time (s) of the refresh of information 
    
public:
    //! Constructor
    SerialManager();
    
    //! Destructor
    virtual ~SerialManager();
    
    //! setups the serial manager
    void setup();
    
    //! updates the class
    void update(double dt);
    
    //! handles the events
    void handleEvent(const Event& event);
    
    
protected:
    
    char		m_bytesRead[MESSAGE_LENGTH];				// data from serial, we will be trying to read 3
    char		m_bytesReadString[MESSAGE_LENGTH +1];		// a string needs a null terminator, so we need 3 + 1 bytes
    int			m_nBytesRead;                             // how much did we read?	
    
    double          m_elapsedTime;        ///< elapsed time since the last refreshing
    DateManager*    m_dateManager;        ///< pointer to the date manager

    ofSerial	m_serial;    
};

#endif