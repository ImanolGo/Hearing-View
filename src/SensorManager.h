
/*==============================================================================
 Imanolgo on 01/04/13.
 ==============================================================================*/
/*! \file SensorManager.h
 * \authors Imanol Gómez
 * \copyright{2013}
 *///============================================================================


#ifndef __SENSOR_MANAGER_H__
#define __SENSOR_MANAGER_H__

#include "ofMain.h"

//========================== class SensorManager =======================================
//==============================================================================
/** \class SensorManager SensorManager.h
 *	\brief class for controlling the serial communication with the Arduino microcontroller
 *	\details It communicates with the Arduino which sends via serial the state of the sensor 
 *           "0" is for off, "1" is for on
 */

class DateManager;

class SensorManager
{

    static const int BAUD_RATE;		///< defines communication's baud rate 
    
public:
    //! Constructor
    SensorManager();
    
    //! Destructor
    virtual ~SensorManager();
    
    //! setups the serial manager
    void setup();
    
    //! updates the class
    void update(double dt);
    
    //! handles the events
    void handleEvent(const Event& event);
    
    
protected:

    char		m_byteRead;				// data from serial, we will be trying to read a byte
    
    double          m_elapsedTime;        ///< elapsed time since the last refreshing
    DateManager*    m_dateManager;        ///< pointer to the date manager

    ofSerial	m_serial;    
};

#endif