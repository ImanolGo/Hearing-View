//
//  Visuals.cpp
//  HearingView
//
//  Created by Imanolgo on 7/8/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "Visuals.h"


void TextVisual::setText(std::string text)
{
    m_text = text;
    m_font = new ofTrueTypeFont();
    m_font->loadFont("fonts/frabk.ttf",20);
    m_color = ofColor(0,0,0);
    
}

void TextVisual::draw()
{
    ofSetColor(m_color);
    if (m_font) 
    {
        m_font->drawString(m_text,m_position.x,m_position.y);
    }
}

void ImageVisual::setImage(std::string path)
{
    m_color = ofColor(255,255,255);
    m_image = new ofImage();
    m_image->loadImage(path);
}

void ImageVisual::draw()
{
    ofSetColor(m_color);
    if (m_image) 
    {
        m_image->draw(m_position.x,m_position.y);
    }
    
}


void CircleVisual::draw()
{
    ofSetColor(m_color);
    ofCircle(m_position.x,m_position.y,m_width,m_height);
}
