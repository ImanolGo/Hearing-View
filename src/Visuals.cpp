//
//  Visuals.cpp
//  HearingView
//
//  Created by Imanolgo on 7/8/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "Visuals.h"

TextVisual::~TextVisual()
{
    delete m_font;
    m_font = NULL;
    
}

void TextVisual::setText(std::string text, int fontSize)
{
    m_text = text;
    m_font = new ofTrueTypeFont();
    m_font->loadFont("fonts/frabk.ttf",fontSize);
    
}

void TextVisual::draw() const
{
    ofEnableAlphaBlending();
    ofSetColor(m_color);
    if (m_font) 
    {
        m_font->drawString(m_text,m_position.x,m_position.y);
    }
    ofDisableAlphaBlending();
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
}

void ImageVisual::draw() const
{
    ofEnableAlphaBlending();
    ofSetColor(m_color);
    if (m_image) 
    {
        m_image->draw(m_position.x,m_position.y);
    }
    ofDisableAlphaBlending();
    
}


void CircleVisual::draw() const
{
    ofEnableAlphaBlending();
    ofSetColor(m_color);
    ofEllipse(m_position,m_width,m_height);
    ofDisableAlphaBlending();
}
