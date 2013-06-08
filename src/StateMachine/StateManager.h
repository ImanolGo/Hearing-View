/*==============================================================================
 Imanolgo on 7/5/13.
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
    
    //! Starts the state machine
    void start();
    
    //! handles the events
    void handleEvent(const Event& event);

public:
    
    float m_t1; ///< time(s) fade in tube to normal running
    float m_t2; ///< time(s) fade in tube to higher level running
    float m_t3; ///< time(s) the tube plays before fade out
    float m_t4; ///< time(s) fade out tube 
    float m_t5; ///< pause time(s) between sample and tube
    float m_t6; ///< pause time(s) tube between samples
    float m_t7; ///< time(s) fade out sample or tube when sitter leaves cube
    
    float m_V1; ///< basic tube volume(%)
    float m_V2; ///< basic sample volume(%)
    float m_V3; ///< high level tube volume(%)
    
    
private:
    
    StateMachine*	  m_stateMachine;	///< pointer to the current state machine
    DateManager*      m_dateManager;    ///< pointer to the date manager
    
};




#endif