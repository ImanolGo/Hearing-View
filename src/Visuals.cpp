//
//  Visuals.cpp
//  HearingView
//
//  Created by Imanolgo on 7/8/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "SoundObject.h"
#include "Visuals.h"

TextVisual::~TextVisual()
{
    delete m_font;
    m_font = NULL;
    
}

void TextVisual::setText(std::string text, int fontSize, bool centred)
{
    m_text = text;
    m_font = new ofTrueTypeFont();
    m_font->loadFont("fonts/frabk.ttf",fontSize);
    
    if(centred)
    {
        ofRectangle box = m_font->getStringBoundingBox(m_text, m_position.x, m_position.y);
        m_position.x = m_position.x - box.width/2;
        m_position.y = m_position.y - box.height/2;
        
    }
    
}

void TextVisual::draw() const
{
    ofPushStyle();  // push the current style for use later
    ofEnableAlphaBlending();
    ofSetColor(m_color);
    if (m_font) 
    {
        m_font->drawString(m_text,m_position.x,m_position.y);
    }
    ofDisableAlphaBlending();
    ofPopStyle();   // recall the pushed style
}

ImageVisual::ImageVisual(ofPoint pos, float width, float height): 
    Visual(pos, width, height), 
    m_image(NULL) 
{
     m_image = new ofImage();
     m_image->allocate(m_width,m_height,OF_IMAGE_COLOR);
}

ImageVisual::~ImageVisual()
{
    delete m_image;
    m_image = NULL;
    
}
void ImageVisual::setImage(std::string path)
{
    m_color = ofColor(255,255,255);
    m_image->loadImage(path);
    m_image->resize(m_width,m_height);
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


SoundVisual::SoundVisual(const SoundObject& sound, ofPoint pos, float width, float height):
    Visual(pos,width,height),
    m_sound(sound)
{
    
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


