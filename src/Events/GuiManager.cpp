//
//  GuiManager.cpp
//  HearingView
//
//  Created by Imanolgo on 23/09/12.
//

#include "Event.h"
#include "EventManager.h"
#include "AppManager.h"
#include "ofxUI.h"
#include "DateManager.h"
#include "ViewManager.h"
#include "Visuals.h"
#include "GuiManager.h"


GuiManager::GuiManager(): m_gui(NULL),m_eventManager(NULL), m_dateManager(NULL)
{
}

GuiManager::~GuiManager()
{
    m_gui->saveSettings("settings.xml");
    delete m_gui;
    m_gui = NULL;
    m_eventManager = NULL;
    m_dateManager = NULL;
}


void GuiManager::setup()
{
    m_gui = new ofxUICanvas("fonts/Klavika-Regular.otf");
    
    float H = (float)ofGetHeight();
    float W  = (float)ofGetWidth();
    float margin = H/70;
    float x = 0.0f;
    float y = 0.0f;
    
    //BACKGROUND
    x = 0.0f;
    y = 0.0f;
    ImageVisual* imageVisual = new ImageVisual(ofPoint(x,y),W,H);
    imageVisual->setImage("images/GUI/background.png");
    AppManager::getInstance().getViewManager().addVisual(*imageVisual,20);
    
    //TITLE
    x = 2*margin;
    y = margin/2;
    m_gui->addWidget(new ofxUILabel(x,y, "HEARING VIEW", OFX_UI_FONT_LARGE));
    
    //UPPER Frame
    float widthGUI = W - 4*margin; 
    float heightGUI = H/3.0 - 4*margin;
    float w = widthGUI;
    float h = heightGUI;
    x = 2*margin;
    y = 2*margin;
    
    RectangleVisual* rectVisual = new RectangleVisual(ofPoint(x,y),w,h);
    rectVisual->setColor(ofColor(85,126,227,100));
    AppManager::getInstance().getViewManager().addVisual(*rectVisual,10);
    
    //Status
    w = widthGUI/4 - 2*margin;
    h = heightGUI - 4*margin;
    y = 4*margin;
    for(int i = 0; i< 4; i++)
    {
        x = 3*margin + 2*margin*i + w*i;
        imageVisual = new ImageVisual(ofPoint(x,y),w,h);
        imageVisual->setImage("images/GUI/blue_bck.jpg");
        AppManager::getInstance().getViewManager().addVisual(*imageVisual,5);
        
    }
    
    float buttom = h/8;
    x = 4*margin;
    y = 5*margin;
    m_gui->addWidget(new ofxUILabel(x,y, "STATUS", OFX_UI_FONT_MEDIUM));
    y = 7*margin;
    m_gui->addWidget(new ofxUIToggle(x,y,buttom, buttom, false,"SENSOR"));
    
    //Weather Conditions
    x = 6*margin + w;
    y = 5*margin;
    m_gui->addWidget(new ofxUILabel(x,y, "WEATHER CONDITIONS", OFX_UI_FONT_MEDIUM));
    
    // Volume Tube
    x = 8*margin + 2*w;
    y = 5*margin;
    m_gui->addWidget(new ofxUILabel(x,y, "TUBE", OFX_UI_FONT_MEDIUM));
    y = 2*margin + heightGUI*0.5;
    m_gui->addWidget(new ofxUISlider(x,y,w-2*margin,h*0.1,0.0,1.0,0.7, "TUBE VOLUME"));
    
    // Volume Sample
    x = 10*margin + 3*w;
    y = 5*margin;
    m_gui->addWidget(new ofxUILabel(x,y, "SAMPLE", OFX_UI_FONT_MEDIUM));
    y = 2*margin + heightGUI*0.5;
    m_gui->addWidget(new ofxUISlider(x,y,w-2*margin,h*0.1,0.0,1.0,0.0, "SAMPLE VOLUME"));
    
    
    //STATES
    w = widthGUI;
    h = heightGUI;
    x = 2*margin;
    y = 4*margin + h;
    
    rectVisual = new RectangleVisual(ofPoint(x,y),w,h);
    rectVisual->setColor(ofColor(85,126,227,100));
    AppManager::getInstance().getViewManager().addVisual(*rectVisual,10);
    
    x = 3*margin;
    y = 6*margin + h;
    m_gui->addWidget(new ofxUILabel(x,y, "STATES", OFX_UI_FONT_MEDIUM));
    
    //Volumes GUI
    w = widthGUI/4;
    h = heightGUI + margin;
    x = 2*margin;
    y = 6*margin + 2*heightGUI;

    rectVisual = new RectangleVisual(ofPoint(x,y),w,h);
    rectVisual->setColor(ofColor(85,126,227,100));
    AppManager::getInstance().getViewManager().addVisual(*rectVisual,10);
    
    x = 4*margin;
    y = 9*margin + 2*heightGUI;
    m_gui->addWidget(new ofxUILabel(x,y, "VOLUMES GUI", OFX_UI_FONT_MEDIUM));
    
    w = widthGUI/4 - 4*margin;
    h = 2*margin;
    x = 4*margin;
    y = 10*margin + 2*heightGUI + h;
    m_gui->addWidget(new ofxUISlider(x,y,w,h,0,100,0, "V1 (%)"));
    y = 10*margin + 2*heightGUI + 3*h;
    m_gui->addWidget(new ofxUISlider(x,y,w,h,0,100,0, "V2 (%)"));
    y = 10*margin + 2*heightGUI + 5*h;
    m_gui->addWidget(new ofxUISlider(x,y,w,h,0,100,0, "V3 (%)"));
    
    w = widthGUI/4 - 2*margin;
    h = heightGUI - 2*margin;
    x = 3*margin;
    y = 8*margin + 2*heightGUI;
    imageVisual = new ImageVisual(ofPoint(x,y),w,h);
    imageVisual->setImage("images/GUI/blue_bck.jpg");
    AppManager::getInstance().getViewManager().addVisual(*imageVisual,5);
    
    //Times GUI
    w = widthGUI/2 - 2*margin;
    h = heightGUI + margin;
    x = 4*margin + widthGUI/4;
    y = 6*margin + 2*heightGUI;
    
    rectVisual = new RectangleVisual(ofPoint(x,y),w,h);
    rectVisual->setColor(ofColor(85,126,227,100));
    AppManager::getInstance().getViewManager().addVisual(*rectVisual,10);
    
    w = margin*5;
    x = 7*margin + widthGUI/4;
    y = 11*margin + 2*heightGUI;
    m_gui->addWidget(new ofxUIRotarySlider(x,y,w, 0, 15, 3, "t1 (s)")); 
    y = 13*margin + 2*heightGUI + w;
    m_gui->addWidget(new ofxUIRotarySlider(x,y,w,0, 15, 1, "t5 (s)"));
    x = 9*margin + widthGUI/4 + w;
    y = 11*margin + 2*heightGUI;
    m_gui->addWidget(new ofxUIRotarySlider(x,y,w,  0, 15, 6, "t2 (s)"));
    y = 13*margin + 2*heightGUI + w;
    m_gui->addWidget(new ofxUIRotarySlider(x,y,w, 0, 360, 60, "t6 (s)"));
    x = 11*margin + widthGUI/4 + 2*w;
    y = 11*margin + 2*heightGUI;
    m_gui->addWidget(new ofxUIRotarySlider(x,y,w,0, 360, 180, "t3 (s)"));
    y = 13*margin + 2*heightGUI + w;
    m_gui->addWidget(new ofxUIRotarySlider(x,y,w,0, 15, 2, "t7 (s)"));
    x = 13*margin + widthGUI/4 + 3*w;
    y = 11*margin + 2*heightGUI;
    m_gui->addWidget(new ofxUIRotarySlider(x,y,w,  0, 15, 8, "t4 (s)"));
    
    x = 6*margin + widthGUI/4;
    y = 9*margin + 2*heightGUI;
    m_gui->addWidget(new ofxUILabel(x,y, "TIMES GUI", OFX_UI_FONT_MEDIUM));
    
    w = widthGUI/2 - 4*margin;
    h = heightGUI - 2*margin;
    x = 5*margin + widthGUI/4;
    y = 8*margin + 2*heightGUI;
    imageVisual = new ImageVisual(ofPoint(x,y),w,h);
    imageVisual->setImage("images/GUI/blue_bck.jpg");
    AppManager::getInstance().getViewManager().addVisual(*imageVisual,5);
    
    
    //Add elements to GUI
    ofAddListener(m_gui->newGUIEvent, this, &GuiManager::guiEvent);
    m_eventManager = &AppManager::getInstance().getEventManager();
    
    m_dateManager = &AppManager::getInstance().getDateManager();
    
    m_gui->loadSettings("settings.xml");
    
    std::cout << m_dateManager->getTime() << "- GuiManager-> initialized "<<std::endl;
    ofLogNotice() << m_dateManager->getTime() << "- GuiManager-> initialized ";
}


void GuiManager::update(double dt)
{

}

void GuiManager::handleEvent(const Event& event)
{
    string name = event.getName(); 
    double value = event.getValue();
    ofxUIWidget *widget;
    
    if(name == "SENSOR")
	{
        widget = m_gui->getWidget(name);
        ofxUIToggle *toggle = (ofxUIToggle *) widget;
        if(value!=toggle->getValue()){
             toggle->setValue(value);
        }
       
    }
    
    else if(name == "TUBE VOLUME" || name == "SAMPLE VOLUME")
	{
        widget = m_gui->getWidget(name);
        ofxUISlider *slider = (ofxUISlider *) widget;
        if(value!=slider->getValue()){
            slider->setValue(value);
        }
    }
    
}

void GuiManager::guiEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName(); 
	int kind = e.widget->getKind(); 
	//cout << "got event from: " << name << endl; 
    
    if(name =="SENSOR")
    {
	    ofxUIToggle *toggle = (ofxUIToggle*) e.widget; 
        std::cout << m_dateManager->getTime() << "-  GuiManager-> guiEvent: "<< name << ", "<< toggle->getValue() << std::endl; 
        ofLogNotice()  << m_dateManager->getTime() << "-  GuiManager-> guiEvent: "<< name << ", "<< toggle->getValue();
        m_eventManager->setEvent(Event(name,(double)toggle->getValue()));
    }

    
    else if(name =="TUBE VOLUME" || name == "SAMPLE VOLUME")
    {
	    ofxUISlider *slider = (ofxUISlider*) e.widget; 
        std::cout << m_dateManager->getTime() << "- GuiManager-> guiEvent: "<< name << ", "<< slider->getValue() << std::endl; 
        ofLogNotice() << m_dateManager->getTime() << "- GuiManager-> guiEvent: "<< name << ", "<< slider->getValue(); 
        m_eventManager->setEvent(Event(name,slider->getValue()));
    }
    
    else if(name =="V1 (%)" || name == "V2 (%)" || name == "V3 (%)")
    {
	    ofxUISlider *slider = (ofxUISlider*) e.widget; 
        std::cout << m_dateManager->getTime() << "- GuiManager-> guiEvent: "<< name << ", "<< slider->getValue() << std::endl; 
        ofLogNotice() << m_dateManager->getTime() << "- GuiManager-> guiEvent: "<< name << ", "<< slider->getValue(); 
        m_eventManager->setEvent(Event(name,slider->getValue()));
    }
    
    else if(name =="t1 (s)" || name == "t2 (s)" || name == "t3 (s)" || name == "t4 (s)" || name == "t5 (s)" || name == "t6 (s)" || name == "t7 (s)")
    {
	    ofxUIRotarySlider *rotatorySlider = (ofxUIRotarySlider*) e.widget; 
        std::cout << m_dateManager->getTime() << "- GuiManager-> guiEvent: "<< name << ", "<< rotatorySlider->getValue() << std::endl; 
        ofLogNotice() << m_dateManager->getTime() << "- GuiManager-> guiEvent: "<< name << ", "<< rotatorySlider->getValue(); 
        m_eventManager->setEvent(Event(name,rotatorySlider->getValue()));
    }
    
    else
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget; 
        std::cout << m_dateManager->getTime() << "- GuiManager-> guiEvent: "<< name << ", "<< toggle->getValue() << std::endl;
        ofLogNotice() << m_dateManager->getTime() << "- GuiManager-> guiEvent: "<< name << ", "<< toggle->getValue();
        m_eventManager->setEvent(Event(name));
        
    }
    
}






