//
//  WeatherThread.cpp
//  HearingView
//
//  Created by Imanolgo on 25/04/13.
//



#include "WeatherThread.h"

const int WeatherThread::BAUD_RATE = 9600; ///< the baud rate
const double WeatherThread::REFRESH_TIME = 1*10*1000; ///< the refresh tim, every minute
const double WeatherThread::WAKING_TIME = 300; ///< the response time should be less than 300ms
const double WeatherThread::TERMINATE_TIME = 500; ///< the response time should be less than 500ms
const double WeatherThread::DATA_TIME = 2000; ///< the response time should be less than 2000ms
const int WeatherThread::WAKING_CHAR_GROUP = 32; ///< "@@...@@@"
const int WeatherThread::NUM_WAKING_UPS = 30;

WeatherThread::WeatherThread():
m_nBytesRead(0),m_bytesRemaining(0),m_wakingUp_num(0),
m_T(0.0f),m_W(0.0f),m_S(0.0f),m_R(0.0f)
{
    //Intentionaly left empty
}

WeatherThread::~WeatherThread()
{
    //Intentionaly left empty
}

void WeatherThread::start(){
    
    m_serial.listDevices();
	//vector <ofSerialDeviceInfo> deviceList = m_serial.getDeviceList();
    
    int portNum = 0;
	
	// this should be set to whatever com port your serial device is connected to.
	// (ie, COM4 on a pc, /dev/tty.... on linux, /dev/tty... on a mac)
	// arduino users check in arduino app....
    m_serial.enumerateDevices();
	//m_serial.setup(portNum, BAUD_RATE); //open the first device
    m_serial.setup("/dev/tty.usbserial-FTGHPU55", BAUD_RATE); //open the first device
	//serial.setup("COM4"); // windows example
	//serial.setup("/dev/tty.usbserial-A4001JEC",9600); // mac osx example
	//serial.setup("/dev/ttyUSB0", 9600); //linux example
	
	m_nBytesRead = 0;
	memset(m_bytesOKString, 0, OK_SIZE+1);
    memset(m_bytesDataString, 0, DATA_SIZE+1);
    memset(m_bytesHeaderString, 0, HEADER_SIZE+1);
    
    std::cout << "WeatherThread-> start " << std::endl;
    
    startThread(true, false);   // blocking, verbose
    
    m_serialState = IDLE;
}

void WeatherThread::stop(){
    stopThread();
    std::cout << "WeatherThread-> stop " << std::endl;
}

void WeatherThread::mapValues(const std::string& data)
{
     std::vector<std::string> strs = ofSplitString(data, "\t"); //tab character (ASCII = 9)
     if(strs.size()==14)
     {
         std::cout << strs.size()<<std::endl;
         m_S = ofToFloat(strs[PORT_A]);
         m_R = ofToFloat(strs[PORT_B]);
         m_T = ofToFloat(strs[TEMPERATURE]);
         m_W = ofToFloat(strs[WIND_SPEED]);
     }
    
}

void WeatherThread::threadedFunction(){
    
    while( isThreadRunning() != 0 ){
        
        if( lock() ){
            
            //std::cout<< "llalalala" << std::endl;
            if ( m_serial.available() >= 0 )
            {
                std::cout<< "serial available" << std::endl;
                if (m_serialState == IDLE ) {
                    std::cout<< "idle" << std::endl;
                    m_wakingUp_num = 0;
                    m_serialState = WAKE_UP_STATION;
                }
                
                if (m_serialState == WAKE_UP_STATION)
                {
                    //std::cout<< "wake up station" << std::endl;
                    while( m_wakingUp_num < NUM_WAKING_UPS){
                        std::cout<< "wake up station" << std::endl;
                        
                        for (int j = 0; j<WAKING_CHAR_GROUP; j++) {
                            m_serial.writeByte('@'); // write the charachter "@" to serial:
                        }
                        
                        
                        ofSleepMillis(WAKING_TIME);
                        memset(m_bytesOKString, 0, OK_SIZE+1);
                        memset(m_bytesOK, 0, OK_SIZE);
                        m_bytesRemaining = OK_SIZE  ;
                        
                        while( m_bytesRemaining > 0){
                            
                            // try to read - note offset into the bytes[] array, this is so
                            // that we don't overwrite the bytes we already have
                            int bytesArrayOffset = OK_SIZE - m_bytesRemaining;
                            int result = m_serial.readBytes( &m_bytesOK[bytesArrayOffset],
                                                            m_bytesRemaining );
                            
                            // check for error code
                            if ( result == OF_SERIAL_ERROR ){
                                // something bad happened
                                std::cout<< "unrecoverable error reading from serial" << std::endl;
                                break;
                            }
                            else if ( result == OF_SERIAL_NO_DATA ){
                                // nothing was read, try again
                                //std::cout<< "no serial data" << std::endl;
                                break;
                            }
                            else{
                                // we read some data!
                                m_bytesRemaining -= result;
                            }
                            
                        };
                        
                        
                        memcpy(m_bytesOKString, m_bytesOK, OK_SIZE);
                        string strOK = ofToString(m_bytesOKString);
                        if(strOK == "OK\r\n"){
                            std::cout<< strOK <<std::endl;
                            m_serialState = READ_DATA;
                            m_wakingUp_num = WAKING_CHAR_GROUP;
                        }
                        else{
                            m_serialState = END_SESSION;
                        }
                        
                        m_wakingUp_num++;
                        
                    }
                    
                }
                
                if (m_serialState == READ_DATA )
                {
                    m_serial.writeByte('$'); // write the charachter "$" to serial:
                    m_serial.writeByte('C'); // write the charachter "C" (command) to serial
                    m_serial.writeByte('C'); // write the charachter "A" (page A) to serial
                    m_serial.writeByte('\r'); // write the charachter "cr" () to serial. Carriage return
                    m_serial.writeByte('\n'); // write the charachter "lf" () to serial. Line Feed
                    
                    std::cout<< "read data from logger" << std::endl;
                    
                    ofSleepMillis(DATA_TIME);
                    //ofSleepMillis(2*WAITING_TIME);
                    memset(m_bytesDataString, 0, DATA_SIZE+1);
                    memset(m_bytesData, 0, DATA_SIZE);
                    m_bytesRemaining = DATA_SIZE;
                    
                    while( m_bytesRemaining > 0){
                        
                        // try to read - note offset into the bytes[] array, this is so
                        // that we don't overwrite the bytes we already have
                        int bytesArrayOffset = DATA_SIZE - m_bytesRemaining;
                        int result = m_serial.readBytes( &m_bytesData[bytesArrayOffset],
                                                        m_bytesRemaining );
                        
                        // check for error code
                        if ( result == OF_SERIAL_ERROR ){
                            // something bad happened
                            ofLog( OF_LOG_ERROR, "unrecoverable error reading from serial" );
                            std::cout<< "unrecoverable error reading from serial" << std::endl;
                            // bail out
                            break;
                        }
                        else if ( result == OF_SERIAL_NO_DATA ){
                            // nothing was read, try again
                            std::cout<< "no conditions data" << std::endl;
                            break;
                        }
                        else{
                            // we read some data!
                            m_bytesRemaining -= result;
                        }
                        
                    };
                    
                    memcpy(m_bytesDataString, m_bytesData, DATA_SIZE);
                    std::cout<< ofToString(m_bytesDataString) <<std::endl;
                    this->mapValues(ofToString(m_bytesDataString));
                    m_serialState = END_SESSION;
                }
                
                if (m_serialState == END_SESSION )
                {
                    m_serial.writeByte('$'); // write the charachter "$" to serial:
                    m_serial.writeByte('X'); // write the charachter "C" (command) to serial
                    m_serial.writeByte('\r'); // write the charachter "cr" () to serial. Carriage return
                    m_serial.writeByte('\n'); // write the charachter "lf" () to serial. Line Feed
                    
                    std::cout<< "terminate session with logger" << std::endl;
                    
                    ofSleepMillis(TERMINATE_TIME);
                    memset(m_bytesOKString, 0, OK_SIZE+1);
                    memset(m_bytesOK, 0, OK_SIZE);
                    m_bytesRemaining = OK_SIZE  ;
                    
                    while( m_bytesRemaining > 0){
                        
                        // try to read - note offset into the bytes[] array, this is so
                        // that we don't overwrite the bytes we already have
                        int bytesArrayOffset = OK_SIZE - m_bytesRemaining;
                        int result = m_serial.readBytes( &m_bytesOK[bytesArrayOffset],
                                                        m_bytesRemaining );
                        
                        // check for error code
                        if ( result == OF_SERIAL_ERROR ){
                            // something bad happened
                            ofLog( OF_LOG_ERROR, "unrecoverable error reading from serial" );
                            std::cout<< "unrecoverable error reading from serial" << std::endl;
                            // bail out
                            break;
                        }
                        else if ( result == OF_SERIAL_NO_DATA ){
                            // nothing was read, try again
                            std::cout<< "no serial data" << std::endl;
                            break;
                        }
                        else{
                            // we read some data!
                            m_bytesRemaining -= result;
                        }
                        
                    };
                    
                    memcpy(m_bytesOKString, m_bytesOK, OK_SIZE);
                    string strOK = ofToString(m_bytesOKString);
                    if(strOK == "OK\r\n"){
                        std::cout<< strOK <<std::endl;
                    }
                    
                    m_serialState = IDLE;
                }
                
            }
            
            unlock();
            ofSleepMillis(REFRESH_TIME);
            
        }
        
    }
    
}






