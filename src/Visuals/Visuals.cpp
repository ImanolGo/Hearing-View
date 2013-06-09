//
//  Visuals.cpp
//  HearingView
//
//  Created by Imanolgo on 7/8/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "SoundObject.h"
#include "Visuals.h"
#include "DateManager.h"
#include "AppManager.h"
#include "VisualEffectsManager.h"

Visual::Visual(ofPoint pos, float width, float height, bool centred): m_position(pos), m_width(width), m_height(height), m_centred(centred)
{
    m_dateManager = &AppManager::getInstance().getDateManager();
    
}



Visual::~Visual()
{
   AppManager::getInstance().getVisualEffectsManager().removeAllVisualEffects(*this);
}


TextVisual::~TextVisual()
{
    delete m_font;
    m_font = NULL;
    
}

void TextVisual::setText(std::string text, std::string fontName, int fontSize)
{
    m_text = text;
    m_font = new ofTrueTypeFont();
    m_font->loadFont("fonts/" + fontName,fontSize);
    m_box = m_font->getStringBoundingBox(m_text, m_position.x, m_position.y);
    
}

void TextVisual::draw() const
{
    ofPushStyle();  // push the current style for use later
    ofEnableAlphaBlending();
    ofSetColor(m_color);
    if (m_font) 
    {
        if(m_centred)
        {
            m_font->drawString(m_text,m_position.x - m_box.width/2.0,m_position.y + m_box.height/2.0);
        }
        
        else
        {
            m_font->drawString(m_text,m_position.x,m_position.y);
        }
       
    }
    ofDisableAlphaBlending();
    ofPopStyle();   // recall the pushed style
}

ImageVisual::ImageVisual(ofPoint pos, float width, float height,bool centred): 
    Visual(pos, width, height), 
    m_image(NULL) 
{
     m_image = new ofImage();
     m_image->allocate(m_width,m_height,OF_IMAGE_COLOR);
    
    if(centred)
    {
        m_position.x = m_position.x - m_width/2.0;
        m_position.y = m_position.y - m_height/2.0;
    }
}

ImageVisual::~ImageVisual()
{
    delete m_image;
    m_image = NULL;
    
}
void ImageVisual::setImage(std::string path)
{
    m_color = ofColor(255,255,255);
    if(m_image->loadImage(path)){
        m_image->resize(m_width,m_height);
        std::cout << m_dateManager->getTime() << " - ImageVisual-> setImage: "<< path <<std::endl;
        ofLogNotice() << m_dateManager->getTime() << " - ImageVisual-> setImage: " << path;
    }
    else{
        std::cout << m_dateManager->getTime() << " - ImageVisual-> setImage: Unable to find/load -> "<< path <<std::endl;
        ofLogNotice() << m_dateManager->getTime() << " - ImageVisual-> setImage: Unable to find/load ->" << path;
    }
}

void ImageVisual::draw() const
{
    ofPushStyle();  // push the current style for use later
    ofEnableAlphaBlending();
    ofSetColor(m_color);
    if (m_image) 
    {
        m_image->draw(m_position.x,m_position.y);
    }
    ofDisableAlphaBlending();
    ofPopStyle();   // recall the pushed style
    
}

CircleVisual::CircleVisual(ofPoint pos, float width, float height,bool centred): 
Visual(pos,width,height,centred) 
{
    if(centred)
    {
        m_position.x = m_position.x - m_width/2.0;
        m_position.y = m_position.y - m_height/2.0;
    }
}

void CircleVisual::draw() const
{
    ofPushStyle();  // push the current style for use later
    ofEnableAlphaBlending();
    ofSetColor(m_color);
    ofFill();
    ofEllipse(m_position,m_width,m_height);
    ofSetCircleResolution(100);
    //ofCircle(m_position,m_width/2);
    ofDisableAlphaBlending();
    ofPopStyle();   // recall the pushed style
}

RectangleVisual::RectangleVisual(ofPoint pos, float width, float height,bool centred): 
    Visual(pos,width,height,centred) 
{
    if(centred)
    {
        m_position.x = m_position.x - m_width/2;
        m_position.y = m_position.y - m_height/2;
    }
}

void RectangleVisual::draw() const
{
    ofPushStyle();  // push the current style for use later
    ofEnableAlphaBlending();
    ofSetColor(m_color);
    ofFill();
    ofRect(m_position, m_width,m_height);
    ofDisableAlphaBlending();
    ofPopStyle();   // recall the pushed style
}


SoundVisual::SoundVisual(const SoundObject& sound, ofPoint pos, float width, float height, bool centred):
    Visual(pos,width,height),
    m_sound(sound)
{
    if(centred)
    {
        m_position.x = m_position.x - m_width/2;
        m_position.y = m_position.y - m_height/2;
    }
}

void SoundVisual::draw() const
{
    if(!&m_sound)
    {
        return;
    }
    
    const float* energy = m_sound.getEnergy();
    
    ofPushStyle();  // push the current style for use later
    ofEnableAlphaBlending();
    ofSetColor(m_color);
    ofFill();
    ofRect(m_position,m_width*energy[0],m_height/3);
    ofRect(m_position.x, m_position.y + m_height/3,m_width*energy[0],m_height/3);
    ofDisableAlphaBlending();
    ofPopStyle();   // recall the pushed style
}


