

#ifndef __EVENT_H__
#define __EVENT_H__

#include <ostream>
#include <string>

//======================== class EventType =====================================
//==============================================================================
/** \class Event Event.h
 *	\brief ...
 */

class Event{
    
public:
    
    //! Constructor
    Event(const std::string& name): m_name(name) { }
    
    //! Compares two event types by their names
    bool operator==(const Event& rhs) const { return m_name == rhs.m_name; }
    //! Compares two event types lexicographically by their names
    bool operator<(const Event& rhs) const { return (m_name.compare(rhs.m_name) < 0); }
    
    friend std::ostream& operator<<(std::ostream& stream, EventType type);

    //< Get Event name
    const std::string& getName() const { return m_name; }
    
    
    
private:
    
    std::string	m_name;
    
};


//==============================================================================
/** \class TimedEvent Event.h
 *	\brief Base class for all events.
 */
//==============================================================================

class TimedEvent: public Event {
    
public:
    
	//! Constructor
	//! @param type the type of event
	//! @param delay delay in milliseconds
	TimedEvent(const std::string& name, double delay): Event(name), m_delay(delay),m_elapsedTime(0.0) {}
    
	//! Destructor
	virtual ~TimedEvent() {}
    
    //! updates event
    void update(double dt);

    
private:
    
	double		m_delay;        //< the that the event shoul be delayed
    double      m_elapsedTime;  //< the time since the event was created
};

#endif
