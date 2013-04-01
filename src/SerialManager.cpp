//
//  SerialManager.cpp
//  HearingView
//
//  Created by Imanolgo on 01/04/13.
//


#include "Event.h"
#include "AppManager.h"
#include "EventManager.h"
#include "DateManager.h"

#include "SerialManager.h"
 
const int SerialManager::BAUD_RATE = 9600; ///< the baud rate
const double SerialManager::REFRESH_TIME = 60*1; ///< refreshing time every 1 minutes

SerialManager::SerialManager():m_elapsedTime(0.0),m_nBytesRead(0), m_dateManager(NULL)
{
    //Intentionaly left empty
}

SerialManager::~SerialManager() 
{
    //Intentionaly left empty
}


//--------------------------------------------------------------
void SerialManager::setup()
{
    m_dateManager = &AppManager::getInstance().getDateManager();
    
    m_serial.listDevices();
	vector <ofSerialDeviceInfo> deviceList = m_serial.getDeviceList();
    
    int portNum = 0;
	
	// this should be set to whatever com port your serial device is connected to.
	// (ie, COM4 on a pc, /dev/tty.... on linux, /dev/tty... on a mac)
	// arduino users check in arduino app....		
    m_serial.enumerateDevices();
	m_serial.setup(portNum, BAUD_RATE); //open the first device
	//serial.setup("COM4"); // windows example
	//serial.setup("/dev/tty.usbserial-A4001JEC",9600); // mac osx example
	//serial.setup("/dev/ttyUSB0", 9600); //linux example
	
	m_nBytesRead = 0;
	memset(m_bytesReadString, 0, MESSAGE_LENGTH+1);
    
    std::cout << m_dateManager->getTime() << "- SerialManager-> setup " << std::endl;
    ofLogNotice() << m_dateManager->getTime() << "- SerialManager->setup " ;

    
}

void SerialManager::update(double dt)
{
    m_elapsedTime+=dt;
    if(m_elapsedTime>= REFRESH_TIME)
    {
        m_elapsedTime = 0;
        if ( m_serial.available() > 0 )
        {
            unsigned char bytesReturned[MESSAGE_LENGTH];
            
            memset(m_bytesReadString, 0, MESSAGE_LENGTH+1);
            memset(bytesReturned, 0, MESSAGE_LENGTH);
            int nRead;
            while( (nRead = m_serial.readBytes( bytesReturned, MESSAGE_LENGTH)) > 0){
                m_nBytesRead = nRead;
            };
            
            memcpy(m_bytesReadString, bytesReturned, 3);   
            
        }
    
    }
       
}

void SerialManager::handleEvent(const Event& event)
{
   //Intentionaly left empty    
}





