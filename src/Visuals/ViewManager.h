/*==============================================================================
 Imanolgo on 6/27/12.
 ==============================================================================*/
/*! \file ViewManager.h
 * \authors Imanol Gómez
 * \copyright{2012}
 *///============================================================================


#ifndef __VIEW_MANAGER_H__
#define __VIEW_MANAGER_H__

#include <vector>
#include <map>
#include <string>

class Visual;
class DateManager;

//========================== class ViewManager ==============================
//============================================================================
/** \class ViewManager ViewManager.h
 *	\brief Class managing the visualization of the application
 *	\details it uses the events to make visuals and transitions
 */

class ViewManager
{
public:
    
    //! Constructor
    ViewManager();
    
    //! Destructor
    ~ViewManager();
    
    //! Setups the logic
    void setup();
    
    //! renders all the graphics
    void draw();
    
    //! updates the date manager
    void update(double dt);
    
    //! Adds a visual as an overlay with the specified z-ordering.
	//! \details The scene is responsible for deleting overlay objects.
	void addVisual(const Visual& visual,  int zOrder = 0);
    
	//! Removes a visual to the list of elements that are rendered
	//! \details The scene is no longer responsible for deleting this visual object.
	void removeVisual(const Visual& visual);
    
    //! Deletes a visual to the list of elements
	//! \details The scene is responsible for deleting this visual object.
	void deleteVisual(const Visual& visual);
    
    //! fades an specific visual
    void  fadeVisual(Visual& visual, float alpha, float fadeTime);

    
    
    //==========================================================================
    
private:
    
    typedef std::pair<int,const Visual*>	Overlay;		///< pair<zOrder,Visual*> defines an overlay elemet
	typedef std::list<Overlay>				VisualList;     ///< list of overlay elements
    
    VisualList		m_visuals;	///< list of all visuals that are rendered each frame
    
    ofTrueTypeFont  m_frameRateFont;    ///< font displaying the frame rate 
    char            m_fpsStr[255];      ///<  framerate text
    DateManager*	  m_dateManager;	///< pointer to the date manager
    
};


#endif