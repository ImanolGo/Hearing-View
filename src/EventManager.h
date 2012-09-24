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

class StateManager;
class SoundManager;
class DateManager;
class GuiManager;
class WeatherManager;
class Event;
class TimedEvent;
class Event;


//========================== class EventManager ==============================
//============================================================================
/** \class EventManager EventManager.h
 *	\brief Manages the events system
 *	\details It creates the interface to handle events
 */


class EventManager
{
public:
    
    //! Constructor
    EventManager();
    
    //! Destructor
    ~EventManager();
    
    //! Setups the event manager
    void setup();

    //! updates the event manager
    void update(double dt);
    
    //! sets an event
    void setEvent(Event event); //Intentionally make a copy of the event
    
    //! sets a timed event
    void setTimedEvent(const std::string& name, double delay);

   //! triggers a certain timed event
   void triggerTimedEvent(TimedEvent& timeEvent);
   
   //! removes a certain timed event
   void removeTimedEvent(TimedEvent& timeEvent);

   //! removes all timed events from the list
   void removeAllTimedEvents();
    
    
private:

	typedef std::vector<TimedEvent*>	TimedEventList; //< list of time events to be triggered
    
    StateManager*	  m_stateManager;	///< pointer to the state manager
    DateManager*	  m_dateManager;	///< pointer to the date manager
    WeatherManager*	  m_weatherManager;	///< pointer to the weather manager
    SoundManager*	  m_soundManager;	///< pointer to the sound manager
    GuiManager*       m_guiManager;     ///< pointer to the sound manager
    TimedEventList	m_timeEvents;       ///< list of the current time events
    
};




#endif
