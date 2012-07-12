/*==============================================================================
 Imanolgo on 08/05/12.
 ==============================================================================*/
/*! \file EventManager.h
 * \authors Imanol Gómez
 * \copyright{2012}
 *///============================================================================


#ifndef __EVENT_MANAGER_H__
#define __EVENT_MANAGER_H__

#include <vector>
#include <map>
#include <string>

class ofxUIEventArgs;
class ofxUICanvas;
class StateManager;

//========================== class EventManager ==============================
//============================================================================
/** \class EventManager EventManager.h
 *	\brief Manages the GUI and its events
 *	\details It creates the GUI and send its events to the StateManager
 */


class EventManager
{
public:
    
    //! Constructor
    EventManager();
    
    //! Destructor
    ~EventManager();
    
    //! Setups the state machine
    void setup();
    
    
private:
    
    //! interface with the GUI events
    void guiEvent(ofxUIEventArgs &e);
    
private:
    
    StateManager*	  m_stateManager;	///< pointer to the state manager
    ofxUICanvas*      m_gui;            ///< pointer to the gui
    
};




#endif