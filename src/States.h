
/*==============================================================================
 Imanolgo on 6/26/12.
 ==============================================================================*/
/*! \file States.h
 * \authors Imanol Gómez
 * \copyright{2012}
 *///============================================================================


#ifndef __STATES_H__
#define __STATES_H__

#include <vector>
#include <map>
#include <string>

class ofSoundPlayer;
class ofxUICanvas;

//========================== class State =======================================
//==============================================================================
/** \class State States.h
 *	\brief Represents a state of a finite state machine. 
 *	\details Each state state has a unique identifier (its name).
 */

class State
{
public:
    //! Constructor
    State(const std::string& name): m_name(name) {}
    //! Destructor
    virtual ~State() {}
    
    //! Do the state initialization stuff here
    virtual void initialize() {}
    //! Called when the state is entered
    virtual void onEnter() = 0;
    //! Called before the state is left
    virtual void onExit() = 0;
       
    //! Returns the unique identifier of this state
    const std::string& getName() const { return m_name; }
    
    
protected:
    
    std::string      m_name;  ///< unique identifier of this state
    
};


//========================== class IdleState =======================================
//==============================================================================
/** \class IdleState States.h
 *	\brief Represents a the idle state of a finite state machine. 
 *	\details It waits for the sensor to be active
 */

class IdleState: public State
{
public:
    //! Constructor
    IdleState(const std::string& name): State(name) {}
    //! Destructor
    virtual ~IdleState() {}
    
    //! Do the state initialization stuff here
    virtual void initialize() {}
    //! Called when the state is entered
    virtual void onEnter();
    //! Called before the state is left
    virtual void onExit();
    
};



//========================== class AmbienceState =======================================
//==============================================================================
/** \class AmbienceState States.h
 *	\brief Represents a the sound ambience state of a finite state machine. 
 *	\details It plays the ambience sound for a certain time.
 */

class AmbienceState: public State
{
public:
    //! Constructor
    AmbienceState(const std::string& name): State(name){}
    //! Destructor
    virtual ~AmbienceState() {}
    
    //! Do the state initialization stuff here
    virtual void initialize() {}
    //! Called when the state is entered
    virtual void onEnter();
    //! Called before the state is left
    virtual void onExit();
   
};



//========================== class SamplerState =======================================
//====================================================================================
/** \class SamplerState States.h
 *	\brief Represents a the sampler state of a finite state machine. 
 *	\details It plays randomly samples according to 
 */

class SamplerState: public State
{
public:
    //! Constructor 
    SamplerState(const std::string& name): State(name){}
    //! Destructor
    virtual ~SamplerState() {}
    
    //! Do the state initialization stuff here
    virtual void initialize() {}
    //! Called when the state is entered
    virtual void onEnter();
    //! Called before the state is left
    virtual void onExit();
   
};


#endif


