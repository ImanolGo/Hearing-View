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

SensorManager::SensorManager():m_elapsedTime(0.0), m_dateManager(NULL)
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
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    m_dateManager = &AppManager::getInstance().getDateManager();
    
    m_serial.enumerateDevices();
    vector <ofSerialDeviceInfo> deviceList = m_serial.getDeviceList();
    
    int portNum = 0;
	
	// this should be set to whatever com port your serial device is connected to.
	// (ie, COM4 on a pc, /dev/tty.... on linux, /dev/tty... on a mac)
	// arduino users check in arduino app....		
    
	//m_serial.setup(portNum, BAUD_RATE); //open the first device
	//serial.setup("COM4"); // windows example
    
    bool connected = false;
    for(int i= 0; i< deviceList.size();i++)
    {
        std::cout << deviceList[i].getDeviceName()<< std::endl;
        if(ofIsStringInString(deviceList[i].getDeviceName(), "tty.usbmodem")) //Arduino
        {
            m_serial.setup(deviceList[i].getDevicePath(),BAUD_RATE); // mac osx example
            //m_serial.setup("/dev/tty.usbmodem1421",BAUD_RATE); // mac osx example
            //serial.setup("/dev/ttyUSB0", 9600); //linux example

            std::cout << m_dateManager->getTime() << "- SensorManager-> serial connected to "<<deviceList[i].getDevicePath() << std::endl;
            ofLogNotice() << m_dateManager->getTime() << "- SensorManager-> serial connected to " << deviceList[i].getDevicePath() ;
            connected = true;
        }
    }
    
    if(!connected)
    {
        std::cout << m_dateManager->getTime() << "- SensorManager-> Unable to connect to Arduino "<< std::endl;
        ofLogNotice() << m_dateManager->getTime() << "- SensorManager-> serial connected to Arduino " ;
    }
	    
    std::cout << m_dateManager->getTime() << "- SensorManager-> initialized " << std::endl;
    ofLogNotice() << m_dateManager->getTime() << "- SensorManager->initialized " ;

    
}

void SensorManager::update(double dt)
{
    // check for data
    if ( m_serial.available() > 0 )
    {
        m_byteRead = m_serial.readByte();
        
        if (m_byteRead == '1') {
            AppManager::getInstance().getEventManager().setEvent(Event("SENSOR",1));
            
            std::cout << m_dateManager->getTime() << "- SensorManager-> update: Sensor On " << std::endl;
            ofLogNotice() << m_dateManager->getTime() << "- SensorManager->update: Sensor On " ;
            m_serial.writeByte('1');
        }
        
        else if (m_byteRead == '0') {
            AppManager::getInstance().getEventManager().setEvent(Event("SENSOR",0));
            std::cout << m_dateManager->getTime() << "- SensorManager-> update: Sensor On " << std::endl;
            ofLogNotice() << m_dateManager->getTime() << "- SensorManager->update: Sensor Off " ;
            if(m_dateManager->getDayTime() != "NIG"){ //if night always on
                m_serial.writeByte('0');
                
            }
        } 
        
        // (1) write the letter "a" to serial:
		    }
        
}

void SensorManager::handleEvent(const Event& event)
{
   //Intentionaly left empty    
}





