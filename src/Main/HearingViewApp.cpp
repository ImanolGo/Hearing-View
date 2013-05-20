#include "HearingViewApp.h"
#include "AppManager.h"
#include "SoundManager.h"

//--------------------------------------------------------------
void HearingViewApp::setup(){
    
    //setup Sou
    outputVolume = 1.0;
    ofSoundStreamListDevices();
	ofSoundStreamSetup(2,2,this, SAMPLE_RATE, BUFFER_SIZE, 4);
	audioBuf = new float[BUFFER_SIZE];
    ofSoundStreamStop();
    
    m_appManager = &AppManager::getInstance();
    m_appManager->setup();
    ofSoundStreamStart();
    
    
}

//--------------------------------------------------------------
void HearingViewApp::update(){

    double dt = ofGetLastFrameTime();
	m_appManager->update(dt);
    
    outputVolume = m_appManager->getSoundManager().getTubeVolume();
    
}

//--------------------------------------------------------------
void HearingViewApp::draw(){

    m_appManager->draw();

}

void HearingViewApp::exit()
{
    delete m_appManager; 
    m_appManager = NULL;
}

//--------------------------------------------------------------
void HearingViewApp::keyPressed(int key)
{
    switch (key) 
    {            
        case ' ':
        {
            //m_appManager->getGUI().toggleVisible(); 
        }
            break; 
        default:
            break;
    }
}


//--------------------------------------------------------------
void HearingViewApp::audioReceived 	(float * input, int bufferSize, int nChannels){
    
	for (int i = 0; i < bufferSize; i++){
        audioBuf[i] = input[i*nChannels];
	}
    
    
}

void HearingViewApp::audioRequested 	(float * output, int bufferSize, int nChannels){
    
    for(int i=0; i<bufferSize;i++) {
        output[i*nChannels]   = audioBuf[i]*outputVolume;
        output[i*nChannels+1]   = audioBuf[i]*outputVolume;
    }
}


//--------------------------------------------------------------
void HearingViewApp::keyReleased(int key){

}

//--------------------------------------------------------------
void HearingViewApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void HearingViewApp::mouseDragged(int x, int y, int button){


}

//--------------------------------------------------------------
void HearingViewApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void HearingViewApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void HearingViewApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void HearingViewApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void HearingViewApp::dragEvent(ofDragInfo dragInfo){

}
