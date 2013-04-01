//
//  SensorManager.cpp
//  HearingView
//
//  Created by Imanolgo on 01/04/13.
//

#include "Event.h"
#include "AppManager.h"
#include "EventManager.h"
#include "DateManager.h"

#include "SensorManager.h"
 
const int SensorManager::BAUD_RATE = 9600; ///< the baud rate

SensorManager::SensorManager():m_elapsedTime(0.0),m_nBytesRead(0), m_dateManager(NULL)
{
    //Intentionaly left empty
}

SensorManager::~SensorManager() 
{
    //Intentionaly left empty
}


//--------------------------------------------------------------
void SensorManager::setup()
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
    
    std::cout << m_dateManager->getTime() << "- SensorManager-> setup " << std::endl;
    ofLogNotice() << m_dateManager->getTime() << "- SensorManager->setup " ;

    
}

void SensorManager::update(double dt)
{
    if ( m_serial.available() > 0 )
    {
        unsigned char bytesReturned[MESSAGE_LENGTH];
        
        memset(m_bytesReadString, 0, MESSAGE_LENGTH+1);
        memset(bytesReturned, 0, MESSAGE_LENGTH);
        int nRead;
        while( (nRead = m_serial.readBytes( bytesReturned, MESSAGE_LENGTH)) > 0){
            m_nBytesRead = nRead;
        };
        
        memcpy(m_bytesReadString, bytesReturned, MESSAGE_LENGTH);  
        
        if(strcmp(m_bytesReadString,"1")==0)
        {
            AppManager::getInstance().getEventManager().setEvent(Event("SENSOR",1));
            std::cout << m_dateManager->getTime() << "- SensorManager-> update: SENSOR 1 " << std::endl;
            ofLogNotice() << m_dateManager->getTime() << "- SensorManager->update: SENSOR 1 " ;
            
        }
        else if(strcmp(m_bytesReadString,"0")==0)
        {
            AppManager::getInstance().getEventManager().setEvent(Event("SENSOR",0));
            std::cout << m_dateManager->getTime() << "- SensorManager-> update: SENSOR 0 " << std::endl;
            ofLogNotice() << m_dateManager->getTime() << "- SensorManager->update: SENSOR 0 " ;
        }

    }
}

void SensorManager::handleEvent(const Event& event)
{
   //Intentionaly left empty    
}





