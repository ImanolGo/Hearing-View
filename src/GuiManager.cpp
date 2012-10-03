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
    m_dateManager = &AppManager::getInstance().getDateManager();
    
    //VOLUME
    float widthVol = ofGetWidth()/3.0; 
    float heightVol = 4*ofGetHeight()/10.0; 
    float heightSlider =heightVol/10.0 ;
    float x = widthVol/12;
    float y = 0;
    m_gui = new ofxUICanvas();
    m_gui->addWidget(new ofxUILabel(x,y, "HEARING VIEW", OFX_UI_FONT_LARGE));
    x = 3*heightVol/5;
    m_gui->addWidget(new ofxUISlider(x,y,2*widthVol/3,heightSlider,0.0,1.0,0.0, "TUBE VOLUME"));
    
    //STATES
    float widthStates = widthVol; 
    float heightStates = heightVol;
    x = widthVol + widthStates/12;
    y = 0;
    m_gui->addWidget(new ofxUILabel(x,y, "STATES", OFX_UI_FONT_MEDIUM));
    
    //SEASONS
    float widthSeasons = widthVol; 
    float heightSeasons = heightVol;
    x = widthVol +widthStates + widthSeasons/12;
    y = 0;
    m_gui->addWidget(new ofxUILabel(x,y, "SEASONS", OFX_UI_FONT_MEDIUM));
    
    //SAMPLER
    float widthSampler = widthVol; 
    float heightSampler = 3*ofGetHeight()/10.0;
    x = widthSampler/6;
    y = heightVol;
    m_gui->addWidget(new ofxUILabel(x,y, "SAMPLER", OFX_UI_FONT_MEDIUM));
    m_gui->addWidgetDown(new ofxUISlider(widthSampler/6,heightVol+ 3*heightSampler/5,2*widthSampler/3,heightSlider,0.0,1.0,0.0, "SAMPLE VOLUME"));
    
    //WEATHER
    float widthWeather = ofGetWidth()/3.0; 
    float heightWeather = 3*ofGetHeight()/10.0; 
    x = widthSampler;
    y = heightSeasons;
    m_gui->addWidget(new ofxUILabel( x,y, "WEATHER CONDITIONS", OFX_UI_FONT_MEDIUM));
    
    //CONTROL
    float widthControl = ofGetWidth(); 
    float heightControl = 3*ofGetHeight()/10.0;
    float yOffset = heightSampler + heightVol;
    float buttom = heightControl/10;
    x = widthControl/8;
    y = yOffset;
    m_gui->addWidget(new ofxUILabel(x,y, "CONTROL", OFX_UI_FONT_MEDIUM));
    y = yOffset + buttom;
    m_gui->addWidget(new ofxUIToggle(x,y,buttom, buttom, false, "SENSOR"));
    
    vector<string> vnames; vnames.push_back("Day"); vnames.push_back("Night");
  
    x = 3*widthControl/8;
    ofxUIRadio* radio = new  ofxUIRadio(x,y, buttom, buttom, "DAILY CYCLE", vnames, OFX_UI_ORIENTATION_VERTICAL);
    
    m_gui->addWidget(radio);
    radio->activateToggle("Day");
    
    vnames.clear();
    vnames.push_back("Summer"); vnames.push_back("Autumn"); vnames.push_back("Winter");
    vnames.push_back("Spring");
    
    x = 5*widthControl/8;
    radio = new  ofxUIRadio(x,y, buttom, buttom, "SEASONS", vnames, OFX_UI_ORIENTATION_VERTICAL);
    
    m_gui->addWidget(radio);
    radio->activateToggle("Summer");
    
    vnames.clear();
    vnames; vnames.push_back("Dry"); vnames.push_back("Rain");
    radio = new  ofxUIRadio(7*widthControl/8,yOffset + buttom, buttom, buttom, "WEATHER CONDITIONS", vnames, OFX_UI_ORIENTATION_VERTICAL);
    
    m_gui->addWidget(radio);
    radio->activateToggle("Dry"); 
    
    vnames.clear();
    
    
    ofAddListener(m_gui->newGUIEvent, this, &GuiManager::guiEvent);
    m_eventManager = &AppManager::getInstance().getEventManager();
    
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






