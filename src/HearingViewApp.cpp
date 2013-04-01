#include "HearingViewApp.h"
#include "AppManager.h"

//--------------------------------------------------------------
void HearingViewApp::setup(){
    
    m_appManager = &AppManager::getInstance();
    m_appManager->setup();
}

//--------------------------------------------------------------
void HearingViewApp::update(){

    double dt = ofGetLastFrameTime();
	m_appManager->update(dt);
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
