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
#include "GuiManager.h"


GuiManager::GuiManager(): m_gui(NULL),m_eventManager(NULL)
{
}

GuiManager::~GuiManager()
{
    delete m_gui;
    m_gui = NULL;
    m_eventManager = NULL;
}


void GuiManager::setup()
{
    float dim = 32; 
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float length = dim*12-xInit; 
    m_gui = new ofxUICanvas(0,0,length+xInit*2.0,ofGetHeight());
    m_gui->addWidgetDown(new ofxUILabel("HEARING VIEW", OFX_UI_FONT_LARGE)); 
    m_gui->addWidgetDown(new ofxUIToggle(dim, dim, false, "SENSOR"));
    vector<string> vnames; vnames.push_back("Dry"); vnames.push_back("Rain");
    ofxUIRadio* radio = (ofxUIRadio *) m_gui->addWidgetDown(new ofxUIRadio(dim, dim, "WEATHER CONDITIONS", vnames, OFX_UI_ORIENTATION_HORIZONTAL)); 
    radio->activateToggle("Dry"); 
    
    vnames.clear();
    vnames.push_back("Summer"); vnames.push_back("Autumn"); vnames.push_back("Winter");
    vnames.push_back("Spring");
    radio = (ofxUIRadio *) m_gui->addWidgetDown(new ofxUIRadio(dim, dim, "SEASONS", vnames, OFX_UI_ORIENTATION_HORIZONTAL)); 
    radio->activateToggle("Summer");
    
    vnames.clear();
    vnames; vnames.push_back("Day"); vnames.push_back("Night");
    radio = (ofxUIRadio *) m_gui->addWidgetDown(new ofxUIRadio(dim, dim, "DAILY CYCLE", vnames, OFX_UI_ORIENTATION_HORIZONTAL)); 
    radio->activateToggle("Day"); 
    
    m_gui->addWidgetDown(new ofxUISlider(12*dim - 2*xInit, dim, 0.0,1.0,0.0, "TUBE VOLUME"));
    m_gui->addWidgetDown(new ofxUISlider(12*dim - 2*xInit, dim, 0.0,1.0,0.0, "SAMPLE VOLUME"));
    
    ofAddListener(m_gui->newGUIEvent, this, &GuiManager::guiEvent);
    m_eventManager = &AppManager::getInstance().getEventManager();
    
    std::cout<< "GuiManager-> initialized "<<std::endl;
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
        std::cout << "GuiManager-> guiEvent: "<< name << ", "<< toggle->getValue() << std::endl; 
        m_eventManager->setEvent(Event(name,(double)toggle->getValue()));
    }

    
    else if(name =="TUBE VOLUME" || name == "SAMPLE VOLUME")
    {
	    ofxUISlider *slider = (ofxUISlider*) e.widget; 
        std::cout << "GuiManager-> guiEvent: "<< name << ", "<< slider->getValue() << std::endl; 
        m_eventManager->setEvent(Event(name,slider->getValue()));
    }
    
    else
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget; 
        std::cout << "GuiManager-> guiEvent: "<< name << ", "<< toggle->getValue() << std::endl;
        m_eventManager->setEvent(Event(name));
        
    }
    
}






