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
    
    //! updates the graphics
    void update(double dt);
    
    //! renders all the graphics
    void draw();
    
    //==========================================================================
    
private:
    
    
};


#endif