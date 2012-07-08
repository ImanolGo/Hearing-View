
/*==============================================================================
    Imanolgo on 6/24/12.
 ==============================================================================*/
/*! \file StateMachine.h
 * \authors Imanol Gómez
 * \copyright{2012}
 *///============================================================================


#ifndef __STATE_MACHINE_H__
#define __STATE_MACHINE_H__

#include <vector>
#include <map>
#include <string>

class State;

//========================== class Transition ==============================
//==========================================================================
/** \class Transition StateMachine.h
 *	\brief Represents the transition from one state to another when
 *	an event of the specified event type is fired.
 */

class Transition
{
public:
    
    //! Constructor
    Transition(const State& from, const State& to, const std::string& event): 
    m_preState(&from), m_postState(&to), m_eventType(event) {}
    
    //! Constructor NO-PreState transition (all states are potential PreStates)
    Transition(const State& to, const std::string& event): 
    m_preState(NULL), m_postState(&to), m_eventType(event) {}
    
    //! Destructor
    ~Transition() { m_preState = NULL; m_postState = NULL; }
    
    //! Compares two transition objects
    bool operator==(const Transition& rhs) const { return rhs.m_preState == this->m_preState && 
        rhs.m_postState == this->m_postState && rhs.m_eventType == this->m_eventType; }
    
    //! Returns the associated source state
    const State* getPreState() const { return m_preState; }
    //! Returns the associated target state
    const State* getPostState() const { return m_postState; }
    //! Returns the associated event type
    const std::string& getEventType() const { return m_eventType; }
    
    //==========================================================================
    
private:
    
    const State*	m_preState;	 ///< the source state
    const State*	m_postState; ///< the target state
    std::string		m_eventType; ///< if an event of type 'eventType' is fired and the state machine is  
    ///< currently in the 'preState' the current state is switched to 'postState'
};

//==========================================================================




//======================== class StateMachine ==================================
//==============================================================================
/** \class StateMachine StateMachine.h
 *	\brief Finite state machine for managing states and their transitions.
 */
class StateMachine
{
public:
    //! Constructor
    StateMachine();
    //! Destructor
    ~StateMachine();
    
    //=================== EventListener Interface ==========================
    
    //! Handles all transition events
    virtual void handleEvent(const std::string& event);
    
    //======================================================================
    
    //! Adds a new state if there is no state with the same name
    void addState(State* state);
    //! Sets the current state to the specified state (calls onEnter() for the new state).
    void setCurrentState(std::string name);
    //! Sets the current state to the specified state (calls onEnter() for the new state).
    State* getCurrentState() { return m_currentState; }
    //! Returns the state with the specified name or NULL if there is no such state
    const State* getState(std::string name) const;
    
    //! Adds a new transition with the specified parameters if there is no such transition
    void createTransition(std::string preState, std::string postState, std::string event);
    //! Adds a new NO-PreState transition (all states are potential PreStates)
    void createTransition(std::string postState, std::string event);
    
    
private:
    
    //! Returns true if the transition was successfully added
    bool addTransition(const Transition* transition);
    
    //! Switches the current state to the specified state (onExit() resp. onEnter() are called for the current and the new state).
    void switchStateTo(const State& newState);
    
	//==========================================================================
    
private:
    
    typedef std::map<std::string, State*>		StateMap;		  ///< map for storing states sorted by their names
    typedef std::vector<const Transition*>      TransitionVector; ///< vector for storing all transitions
    
    StateMap		  m_states;			///< a map of all added states sorted by there name
    TransitionVector  m_transitions;	///< list of all transitions
    State*			  m_currentState;	///< the currently active state
    
};

#endif