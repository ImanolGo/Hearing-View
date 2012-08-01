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
class Event;
class TimedEvent;

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

    //! updates the event manager
    void update(double dt);
    
    //! sets an event
    void setEvent(Event event); //Intentionally make a copy of teh event
    
    //! sets a timed event
    void setTimedEvent(const std::string& name, double delay);

   //! triggers a certain timed event
   void triggerTimedEvent(TimedEvent& timeEvent);
   
   //! removes a certain timed event
   void removeTimedEvent(TimedEvent& timeEvent);

   //! removes all timed events from the list
   void removeAllTimedEvents();
    
    
private:
    
    //! interface with the GUI events
    void guiEvent(ofxUIEventArgs &e);
    
private:

	typedef std::vector<TimedEvent*>	TimedEventList; //< list of time events to be triggered
    
    StateManager*	  m_stateManager;	///< pointer to the state manager
    ofxUICanvas*      m_gui;            ///< pointer to the gui
    TimedEventList	m_timeEvents;       ///< list of the current time events
    
};




#endif
