//
//  WeatherThread.cpp
//  HearingView
//
//  Created by Imanolgo on 25/04/13.
//


#include "Event.h"
#include "AppManager.h"
#include "EventManager.h"
#include "DateManager.h"

#include "WeatherThread.h"
 
const int WeatherThread::BAUD_RATE = 9600; ///< the baud rate
const double WeatherThread::REFRESH_TIME = 1*60*1000; ///< the refresh tim, every minute

WeatherThread::WeatherThread():m_nBytesRead(0)
{
    //Intentionaly left empty
}

WeatherThread::~WeatherThread() 
{
    //Intentionaly left empty
}

void WeatherThread::start(){
    
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
	memset(m_bytesOKString, 0, OK_SIZE+1);
    memset(m_bytesConditionsString, 0, CONDITIONS_SIZE+1);
    
    std::cout << "WeatherThread-> start " << std::endl;
    
    startThread(true, false);   // blocking, verbose
}

void WeatherThread::stop(){
    stopThread();
    std::cout << "WeatherThread-> stop " << std::endl;
}

void WeatherThread::threadedFunction(){
    
}






