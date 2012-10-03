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
    
    //SAMPLER
    float widthVol = ofGetWidth()/3.0; 
    float heightVol = 4*ofGetHeight()/10.0; 
    float heightSlider =heightVol/10.0 ; 
    m_gui = new ofxUICanvas();
    m_gui->addWidget(new ofxUILabel(widthVol/12,0, "HEARING VIEW", OFX_UI_FONT_LARGE));
    m_gui->addWidget(new ofxUISlider(widthVol/12,3*heightVol/5,2*widthVol/3,heightSlider,0.0,1.0,0.0, "TUBE VOLUME"));
    
    float widthStates = widthVol; 
    float heightStates = heightVol;
    
    m_gui->addWidget(new ofxUILabel(widthVol + widthStates/12,0, "STATES", OFX_UI_FONT_MEDIUM));
    
    float widthSeasons = widthVol; 
    float heightSeasons = heightVol;
    
    m_gui->addWidget(new ofxUILabel(widthVol +widthStates + widthSeasons/12,0, "SEASONS", OFX_UI_FONT_MEDIUM));
    
    float widthSampler = widthVol; 
    float heightSampler = 3*ofGetHeight()/10.0;
    
    m_gui->addWidget(new ofxUILabel(widthSampler/6,heightVol, "SAMPLER", OFX_UI_FONT_MEDIUM));
    m_gui->addWidgetDown(new ofxUISlider(widthSampler/6,heightVol+ 3*heightSampler/5,2*widthSampler/3,heightSlider,0.0,1.0,0.0, "SAMPLE VOLUME"));
    
    float widthWeather = 2*ofGetWidth()/3; 
    float heightWeather = heightSampler;
    
    m_gui->addWidget(new ofxUILabel( widthSampler+ widthWeather/6,heightVol, "WEATHER CONDITIONS", OFX_UI_FONT_MEDIUM));
    
    float widthControl = ofGetWidth(); 
    float heightControl = 3*ofGetHeight()/10.0;
    float yOffset = heightSampler + heightVol;
    float buttom = heightControl/10;
    
    m_gui->addWidget(new ofxUILabel(widthControl/8,yOffset, "CONTROL", OFX_UI_FONT_MEDIUM));
    m_gui->addWidget(new ofxUIToggle(widthControl/8,yOffset + buttom,buttom, buttom, false, "SENSOR"));
    
    vector<string> vnames; vnames.push_back("Day"); vnames.push_back("Night");
  
    ofxUIRadio* radio = new  ofxUIRadio(3*widthControl/8,yOffset + buttom, buttom, buttom, "DAILY CYCLE", vnames, OFX_UI_ORIENTATION_VERTICAL);
    
    m_gui->addWidget(radio);
    radio->activateToggle("Day");
    
    vnames.clear();
    vnames.push_back("Summer"); vnames.push_back("Autumn"); vnames.push_back("Winter");
    vnames.push_back("Spring");
    
    radio = new  ofxUIRadio(5*widthControl/8,yOffset + buttom, buttom, buttom, "SEASONS", vnames, OFX_UI_ORIENTATION_VERTICAL);
    
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






