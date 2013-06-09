/*==============================================================================
 Imanolgo on 08/07/12.
 ==============================================================================*/
/*! \file Visuals.h
 * \authors Imanol Gómez
 * \copyright{2012}
 *///============================================================================


#ifndef __VISUALS_H__
#define __VISUALS_H__


#include <string>

#include "ofMain.h"
//#include "SoundObject.h"

class SoundObject;
class DateManager;

//=============================== class Visual ==============================
//===========================================================================
/** \class Visual Visuals.h
 *	\brief Base class for all visuals
 *	\details Gives basic functionalities for all objects to be rendered
 */

class Visual
{
public:
    
    //! Constructor
    Visual(ofPoint pos, float width, float height, bool centred = false);
    
    //! Destructor
    virtual ~Visual();
    
	//! Draws the visual
	virtual void draw() const = 0;
    
    //! Changes the alpha channel.
	void setAlpha(double alpha) { m_color.set(m_color.r,m_color.g,m_color.b,alpha);}
    
    //! Changes the alpha channel.
	double getAlpha() const{ return m_color.a;}
    
    //! Sets the color of the visual
    void setColor(const ofColor& color) {m_color = color;}
    
    
    
protected:
    
    ofPoint         m_position;		///< defines the position of the visual
	double			m_width;		///< the width of the visual
	double			m_height;		///< the height of the visual
    ofColor         m_color;        ///< color of the visual	
    bool            m_centred;      ///< sets of the position reference is the centre
    DateManager*    m_dateManager; ///< pointer to the date manager
    
};


//============================ class TextVisual ==============================
//============================================================================
/** \class TextVisual Visuals.h
 *	\brief Represents a text visual
 *	\details The class uses the OF class ofTrueTypeFont to draw the text
 */

class TextVisual: public Visual
{
public:
    
    //! Constructor
    TextVisual(ofPoint pos, float width, float height, bool centred = false): Visual(pos, width, height, centred), m_font(NULL) {}
    
    //! Destructor
    virtual ~TextVisual();
    
	//! Draws the text visual
	virtual void draw() const;
    
    //! Sets the text to be drawn
    void setText(std::string text, std::string fontName, int fontSize );
    
private:
    
    ofTrueTypeFont*  m_font;		///< pointer to the ofTrueTypeFont class
    std::string      m_text;        ///< text to be rendered
    ofRectangle      m_box;         ///< the box surrounding the text
    
};



//=========================== class ImageVisual ==============================
//============================================================================
/** \class ImageVisual Visual.h
 *	\brief Represents an image visual
 *	\details The class uses the OF class ofImage to draw the image
 */

class ImageVisual: public Visual
{
public:
    
    //! Constructor
    ImageVisual(ofPoint pos, float width, float height,bool centred = false);
    
    //! Destructor
    virtual ~ImageVisual();
    
	//! Draws the text visual
	virtual void draw() const;
    
    //! Sets the text to be drawn
    void setImage(std::string path);
    
    
private:
    
    ofImage*         m_image;		///< pointer to the ofImage class
    std::string      m_text;        ///< text to be rendered
    
};


//========================== class CircleVisual ==============================
//============================================================================
/** \class CircleVisual Visual.h
 *	\brief Represents an circle visual
 *	\details The class uses the OF class ofCircle to draw a circle
 */


class CircleVisual: public Visual
{
public:
    
    //! Constructor
    CircleVisual(ofPoint pos, float width, float height,bool centred = false);
    
    //! Destructor
    virtual ~CircleVisual(){}
    
	//! Draws the text visual
	virtual void draw() const;
    
};


//========================== class RectangleVisual ==============================
//============================================================================
/** \class RectangleVisual Visual.h
 *	\brief Represents an rectangle visual
 *	\details The class uses the OF class ofRectangle to draw a rectangle
 */


class RectangleVisual: public Visual
{
public:
    
    //! Constructor
    RectangleVisual(ofPoint pos, float width, float height,bool centred = false);
    
    //! Destructor
    virtual ~RectangleVisual(){}
    
	//! Draws the text visual
	virtual void draw() const;
    
};


//=========================== class SoundVisual ==============================
//============================================================================
/** \class SoundVisual Visual.h
 *	\brief Represents an sound visual
 *	\details Visualization of a playback sound 
 */


class SoundVisual: public Visual
{
public:
    
    //! Constructor
    SoundVisual(const SoundObject& sound, ofPoint pos, float width, float height, bool centred = false);    
    //! Destructor
    virtual ~SoundVisual(){}
    
	//! Draws the text visual
	virtual void draw() const;
    
    //! Sets the color
    void setColor(const ofColor& color){m_color= color;}
    
private:
    
    const SoundObject&  m_sound; ///< reference to the sound it visualizes
    ofColor             m_color; ///< color of the visual
    
};

#endif
