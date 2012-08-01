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


//========================== class Visual ==============================
//============================================================================
/** \class Visual Visuals.h
 *	\brief Base class for all visuals
 *	\details Gives basic functionalities for all objects to be rendered
 */

class Visual
{
public:
    
    //! Constructor
    Visual(ofPoint pos, float width, float height): m_position(pos), m_width(1.0), m_height(1.0), m_alpha(1.0) {}
    
    //! Destructor
    virtual ~Visual() {}
    
	//! Draws the visual
	virtual void draw() const = 0;
    
    //! Changes the alpha channel.
	void setAlpha(double alpha) { m_alpha = alpha;}
    
	//! gets the alpha channel.
	const double& getAlpha() const { return m_alpha;}
    
    //! Sets the color of the visual
    void setColor(const ofColor& color) {m_color = color;}
    
protected:
    
    ofPoint         m_position;		///< defines the position of the visual
	double			m_alpha;		///< current alpha value of the visual
	double			m_width;		///< the width of the visual
	double			m_height;		///< the height of the visual
    ofColor         m_color;       ///< color of the visual	
    
};


//========================== class TextVisual ==============================
//============================================================================
/** \class TextVisual Visuals.h
 *	\brief Represents a text visual
 *	\details The class uses the OF class ofTrueTypeFont to draw the text
 */

class TextVisual: public Visual
{
public:
    
    //! Constructor
    TextVisual(ofPoint pos, float width, float height): Visual(pos, width, height), m_font(NULL) {}
    
    //! Destructor
    virtual ~TextVisual();
    
	//! Draws the text visual
	virtual void draw() const;
    
    //! Sets the text to be drawn
    void setText(std::string text,int fontSize);
    
private:
    
    ofTrueTypeFont*  m_font;		///< pointer to the ofTrueTypeFont class
    std::string      m_text;        ///< text to be rendered
    
};



//========================== class ImageVisual ==============================
//============================================================================
/** \class ImageVisual ImageVisual.h
 *	\brief Represents an image visual
 *	\details The class uses the OF class ofImage to draw the image
 */

class ImageVisual: public Visual
{
public:
    
    //! Constructor
    ImageVisual(ofPoint pos, float width, float height);
    
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
/** \class CircleVisual CircleVisual.h
 *	\brief Represents an circle visual
 *	\details The class uses the OF class ofCircle to draw a circle
 */


class CircleVisual: public Visual
{
public:
    
    //! Constructor
    CircleVisual(ofPoint pos, float width, float height): Visual(pos,width,height) {}
    
    //! Destructor
    virtual ~CircleVisual(){}
    
	//! Draws the text visual
	virtual void draw() const;
    
};

#endif
