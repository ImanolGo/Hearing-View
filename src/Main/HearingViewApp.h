#pragma once

#include "ofMain.h"
#include "ofxUI.h"

#define BUFFER_SIZE 128
#define SAMPLE_RATE	44100

class AppManager;

class HearingViewApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void audioReceived 	(float * input, int bufferSize, int nChannels);
        void audioRequested 	(float * input, int bufferSize, int nChannels);
    
        void exit();
    
        AppManager*     m_appManager; //< it manages the whole application
    
    private:
    
        float   * audioBuf;      //< audio buffer saving the audion input stream
        float   outputVolume;    //< defines the volume of the output audi stream
		
};

