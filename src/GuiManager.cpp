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
    
    //TITLE
    float x = 2*margin;
    float y = margin/2;
    m_gui->addWidget(new ofxUILabel(x,y, "HEARING VIEW", OFX_UI_FONT_LARGE));
    
    //VOLUMES
    float widthVolumes = (1-0.25)*(W - 4*margin); 
    float heightVolumes = H/3.0 - 4*margin;
    x = 2*margin + widthVolumes/8;
    y = 4*margin + heightVolumes ;
    
    RectangleVisual* rectVisual = new RectangleVisual(ofPoint(x,y),widthVolumes,heightVolumes);
    rectVisual->setColor(ofColor(45,72,2,100));
    AppManager::getInstance().getViewManager().addVisual(*rectVisual,10);
    
    float w = widthVolumes/2 - 2*margin;
    float h = heightVolumes - 4*margin;
    y = 6*margin + heightVolumes;
    for(int i = 0; i< 2; i++)
    {
        x = 3*margin + widthVolumes/8 + 2*margin*i + w*i;
        rectVisual = new RectangleVisual(ofPoint(x,y),w,h);
        rectVisual->setColor(ofColor(46,85,18,100));
        AppManager::getInstance().getViewManager().addVisual(*rectVisual,5);
        
    }

    //TUBE
    x = 4*margin + widthVolumes/8;
    y = 5*margin + heightVolumes - margin/2;
    m_gui->addWidget(new ofxUILabel(x,y, "TUBE", OFX_UI_FONT_MEDIUM));
    w = widthVolumes/2 - 8*margin;
    h = heightVolumes/8;
    x = 6*margin + widthVolumes/8;
    y =  6*margin + heightVolumes + heightVolumes/3;
    m_gui->addWidget(new ofxUISlider(x,y,w,h,0.0,1.0,0.0, "TUBE VOLUME"));
    
    //SAMPLER
    x = 4*margin + widthVolumes/2 + widthVolumes/8;
    y = 5*margin + heightVolumes - margin/2;
    m_gui->addWidget(new ofxUILabel(x,y, "SAMPLER", OFX_UI_FONT_MEDIUM));
    x =  6*margin + widthVolumes/2 + widthVolumes/8;
    y =  6*margin + heightVolumes + heightVolumes/3;
    m_gui->addWidget(new ofxUISlider(x,y,w,h,0.0,1.0,0.0, "SAMPLE VOLUME"));
    
    //VISUALS
    float widthVisuals = W - 4*margin; 
    float heightVisuals = H/3.0 - 4*margin;
    x = 2*margin;
    y = 6*margin + 2*heightVisuals;
    
    rectVisual = new RectangleVisual(ofPoint(x,y),widthVisuals,heightVisuals);
    rectVisual->setColor(ofColor(45,72,2,100));
    AppManager::getInstance().getViewManager().addVisual(*rectVisual,10);
    
    //STATES
    w = 2*widthVisuals/5 - 2*margin;
    h = heightVisuals - 4*margin;
    x = 3*margin + margin/2;
    y = 6*margin + margin/2 + 2*heightVisuals;
    m_gui->addWidget(new ofxUILabel(x,y, "STATES", OFX_UI_FONT_MEDIUM));
    
    x = 3*margin;
    y = 8*margin + 2*heightVisuals;
    rectVisual = new RectangleVisual(ofPoint(x,y),w,h);
    rectVisual->setColor(ofColor(46,85,18,100));
    AppManager::getInstance().getViewManager().addVisual(*rectVisual,5);
    
    
    //WEATHER CONDITIONS
    w = 1*widthVisuals/5 - 2*margin;
    h = heightVisuals - 4*margin;
    x = 3*margin + 2*widthVisuals/5 + margin/2;
    y = 6*margin + margin/2 + 2*heightVisuals;
    m_gui->addWidget(new ofxUILabel(x,y, "WEATHER CONDITIONS", OFX_UI_FONT_MEDIUM));
    
    x = 3*margin + 2*widthVisuals/5;
    y = 8*margin + 2*heightVisuals;
    rectVisual = new RectangleVisual(ofPoint(x,y),w,h);
    rectVisual->setColor(ofColor(46,85,18,100));
    AppManager::getInstance().getViewManager().addVisual(*rectVisual,5);
        
    //SEASONS
    
    w = 2*widthVisuals/5 - 2*margin;
    h = heightVisuals - 4*margin;
    x = 3*margin + 3*widthVisuals/5 +  margin/2;
    y = 6*margin + margin/2 + 2*heightVisuals;
    m_gui->addWidget(new ofxUILabel(x,y, "SEASONS", OFX_UI_FONT_MEDIUM));
    
    x = 3*margin + 3*widthVisuals/5;
    y = 8*margin + 2*heightVisuals;
    rectVisual = new RectangleVisual(ofPoint(x,y),w,h);
    rectVisual->setColor(ofColor(46,85,18,100));
    AppManager::getInstance().getViewManager().addVisual(*rectVisual,5);
        
    //GUI
    float widthGUI = W - 4*margin; 
    float heightGUI = H/3.0 - 4*margin;
    x = 2*margin;
    y = 2*margin;
    
    rectVisual = new RectangleVisual(ofPoint(x,y),widthGUI,heightGUI);
    rectVisual->setColor(ofColor(45,72,2,100));
    AppManager::getInstance().getViewManager().addVisual(*rectVisual,10);
    
    w = widthGUI/4 - 2*margin;
    h = heightGUI - 4*margin;
    y = 4*margin;
    for(int i = 0; i< 4; i++)
    {
        x = 3*margin + 2*margin*i + w*i;
        rectVisual = new RectangleVisual(ofPoint(x,y),w,h);
        rectVisual->setColor(ofColor(46,85,18,100));
        AppManager::getInstance().getViewManager().addVisual(*rectVisual,5);
        
    }
    
    float buttom = h/8;
    x = 4*margin;
    y = 5*margin;
    m_gui->addWidget(new ofxUILabel(x,y, "CONTROL", OFX_UI_FONT_MEDIUM));
    y = 7*margin;
    m_gui->addWidget(new ofxUIToggle(x,y,buttom, buttom, false,"SENSOR"));
    
    vector<string> vnames; vnames.push_back("Day"); vnames.push_back("Night");
    x = 6*margin + w;
    y = 5*margin;
    ofxUIRadio* radio = new  ofxUIRadio(x,y, buttom, buttom, "DAILY CYCLE", vnames, OFX_UI_ORIENTATION_VERTICAL);
    m_gui->addWidget(radio);
    radio->activateToggle("Day");
    
    vnames.clear();
    vnames.push_back("Summer"); vnames.push_back("Autumn"); vnames.push_back("Winter");
    vnames.push_back("Spring");
    
    x = 8*margin + 2*w;
    radio = new  ofxUIRadio(x,y, buttom, buttom, "SEASONS", vnames, OFX_UI_ORIENTATION_VERTICAL);
    m_gui->addWidget(radio);
    radio->activateToggle("Summer");
    
    vnames.clear();
    vnames; vnames.push_back("Dry"); vnames.push_back("Rain");
    x = 10*margin + 3*w;
    radio = new  ofxUIRadio(x,y, buttom, buttom, "WEATHER CONDITIONS", vnames, OFX_UI_ORIENTATION_VERTICAL);
    m_gui->addWidget(radio);
    radio->activateToggle("Dry"); 
    vnames.clear();

    
    ofAddListener(m_gui->newGUIEvent, this, &GuiManager::guiEvent);
    m_eventManager = &AppManager::getInstance().getEventManager();
    
    m_dateManager = &AppManager::getInstance().getDateManager();
    
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
    
    else if(name == "Winter" || name == "Summer" || name == "Spring" || name == "Autumn")
	{
        widget = m_gui->getWidget("SEASONS");
        ofxUIRadio *radio = (ofxUIRadio *) widget;
        radio->activateToggle(name);
    }
    
    else if(name == "Day" || name == "Night")
	{
        widget = m_gui->getWidget("DAILY CYCLE");
        ofxUIRadio *radio = (ofxUIRadio *) widget;
        radio->activateToggle(name);
    }
    
    else if(name == "Dry" || name == "Rain")
	{
        widget = m_gui->getWidget("WEATHER CONDITIONS");
        ofxUIRadio *radio = (ofxUIRadio *) widget;
        radio->activateToggle(name);
    }

}

void GuiManager::guiEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName(); 
	int kind = e.widget->getKind(); 
	cout << "got event from: " << name << endl; 
    
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
    
    else
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget; 
        std::cout << m_dateManager->getTime() << "- GuiManager-> guiEvent: "<< name << ", "<< toggle->getValue() << std::endl;
        ofLogNotice() << m_dateManager->getTime() << "- GuiManager-> guiEvent: "<< name << ", "<< toggle->getValue();
        m_eventManager->setEvent(Event(name));
        
    }
    
}






