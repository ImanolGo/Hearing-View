#include "testApp.h"
#include "AppManager.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    m_appManager = &AppManager::getInstance();
    m_appManager->setup();
}

//--------------------------------------------------------------
void testApp::update(){

    double dt = ofGetLastFrameTime();
	m_appManager->update(dt);
}

//--------------------------------------------------------------
void testApp::draw(){

    m_appManager->draw();

}

void testApp::exit()
{
    delete m_appManager; 
    m_appManager = NULL;
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
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
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){


}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
