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
    void draw() const;
    
    //! Adds a visual to the list of elements that are rendered
	void addVisual(const Visual& visual);
    
	//! Removes a visual to the list of elements that are rendered
	void removeVisual(const Visual& visual);
    

    
    //==========================================================================
    
private:
    
    typedef std::list<const Visual*>		VisualList;		///< list for storing all visual
    
    VisualList		m_visuals;	///< list of all visuals that are rendered each frame
    
};


#endif