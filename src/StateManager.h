/*==============================================================================
 Imanolgo on 7/5/12.
 ==============================================================================*/
/*! \file StateManager.h
 * \authors Imanol Gómez
 * \copyright{2012}
 *///============================================================================


#ifndef __STATE_MANAGER_H__
#define __STATE_MANAGER_H__

#include <vector>
#include <map>
#include <string>

class Event;

class StateMachine;
class ofxUIEventArgs;
class DateManager;

//========================== class StateManager ==============================
//============================================================================
/** \class StateManager StateManager.h
 *	\brief It creates and manages a certain state machine
 *	\details It would create a state machhine according to a certain logic
 */


class StateManager
{
public:
    
    //! Constructor
    StateManager();
    
    //! Destructor
    ~StateManager();
    
    //! Setups the state machine
    void setup();
    
    //! handles the events
    void handleEvent(const Event& event);
    
    
private:
    
    StateMachine*	  m_stateMachine;	///< pointer to the current state machine
    DateManager*      m_dateManager;    ///< pointer to the date manager
    
};




#endif