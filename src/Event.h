

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
    Event(const std::string& name, double value= 0.0): m_name(name), m_value(value) { }
    
    //! Compares two event types by their names
    bool operator==(const Event& rhs) const { return ((m_name == rhs.m_name) && (m_value == rhs.m_value)); }
    //! Compares two event types lexicographically by their names
    bool operator<(const Event& rhs) const { return (m_name.compare(rhs.m_name) < 0); }
    
    friend std::ostream& operator<<(std::ostream& stream, EventType type);

    //< Get Event name
    const std::string& getName() const { return m_name; }
    
    //! return the value
    const double&  getValue() const {return m_value;}
	
    
private:
    
    std::string	m_name;
    double		m_value;        //< the value of the event
    
};


//==============================================================================
/** \class TimedEvent Event.h
 *	\brief Event set after a delay time
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
    
	double		m_delay;        //< the time the event shoul be delayed
    double      m_elapsedTime;  //< the time since the event was created
};



#endif
