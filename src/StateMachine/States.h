
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

#include "ofMain.h"

class ofSoundPlayer;
class ofxUICanvas;
class ImageVisual;
class TextVisual;
class DateManager;
class StateManager;

//========================== class State =======================================
//==============================================================================
/** \class State States.h
 *	\brief Represents a state of a finite state machine. 
 *	\details Each state state has a unique identifier (its name).
 */

class State
{
public:
    
    static const double FADE_TIME;  //defines the fade time between states
    
    //! Constructor
    State(const std::string& name,const ofPoint& pos);
    //! Destructor
    virtual ~State();
    
    //! Do the state initialization stuff here
    virtual void initialize();
    //! Called when the state is entered
    virtual void onEnter() = 0;
    //! Called before the state is left
    virtual void onExit() = 0;
       
    //! Returns the unique identifier of this state
    const std::string& getName() const { return m_name; }
    
    
protected:
    
    std::string      m_name;  ///< unique identifier of this state
    ofPoint          m_pos;   ///< position of the State
    ImageVisual*     m_circleState; ///< circle representing the state
    TextVisual*      m_textState; ///< text representing the state
    DateManager*     m_dateManager; ///< pointer to the date manager
    StateManager*    m_stateManager; ///< pointer to the state manager
    
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
    IdleState(const std::string& name,const ofPoint& pos): State(name,pos) {}
    //! Destructor
    virtual ~IdleState() {}
    //! Do the state initialization stuff here
    //virtual void initialize();
    //! Called when the state is entered
    virtual void onEnter();
    //! Called before the state is left
    virtual void onExit();
 
};


//========================== class SensorOffTransitionState =======================================
//==============================================================================
/** \class SensorOffTransitionState States.h
 *	\brief Represents a sensor off transition state of a finite state machine. 
 *	\details It comes whenever the sensor is inactivated and transits to the idle state
 */

class SensorOffTransitionState: public State
{
public:
    //! Constructor
    SensorOffTransitionState(const std::string& name,const ofPoint& pos): State(name,pos) {}
    //! Destructor
    virtual ~SensorOffTransitionState() {}
    //! Do the state initialization stuff here
    //virtual void initialize();
    //! Called when the state is entered
    virtual void onEnter();
    //! Called before the state is left
    virtual void onExit();
    
};

//========================== class TubeOffTransitionState =======================================
//==============================================================================
/** \class TubeOffTransitionState States.h
 *	\brief Represents a tube off transition state of a finite state machine.
 *	\details It comes whenever the tube is inactivated and transits to the sampler state
 */

class TubeOffTransitionState: public State
{
public:
    //! Constructor
    TubeOffTransitionState(const std::string& name,const ofPoint& pos): State(name,pos) {}
    //! Destructor
    virtual ~TubeOffTransitionState() {}
    //! Do the state initialization stuff here
    //virtual void initialize();
    //! Called when the state is entered
    virtual void onEnter();
    //! Called before the state is left
    virtual void onExit();
    
};




//========================== class TubeState ====================================
//==============================================================================
/** \class TubeState States.h
 *	\brief Represents a the sound ambience state of a finite state machine. 
 *	\details It plays the ambience sound for a certain time, after the sensor has been triggered
 *           or the samples ended.
 */

class TubeState: public State
{
public:
    //! Constructor
    TubeState(const std::string& name,const ofPoint& pos): State(name,pos){}
    //! Destructor
    virtual ~TubeState() {}
    //! Do the state initialization stuff here
    //virtual void initialize();
    //! Called when the state is entered
    virtual void onEnter();
    //! Called before the state is left
    virtual void onExit();
   
};


//========================== class ShortTubeState ====================================
//==============================================================================
/** \class ShortTubeState States.h
 *	\brief Represents a the sound ambience state of a finite state machine. 
 *	\details It plays the ambience sound for a certain time, for a short period of time 
 *           bewtween samples.
 */

class ShortTubeState: public State
{
public:
    //! Constructor
    ShortTubeState(const std::string& name,const ofPoint& pos): State(name,pos){}
    //! Destructor
    virtual ~ShortTubeState() {}
    //! Do the state initialization stuff here
    //virtual void initialize();
    //! Called when the state is entered
    virtual void onEnter();
    //! Called before the state is left
    virtual void onExit();
    
};


//========================== class SamplerState =======================================
//====================================================================================
/** \class SamplerState States.h
 *	\brief Represents a the sampler state of a finite state machine. 
 *	\details It plays randomly samples according to date, time of the day and weather conditions
 */

class SamplerState: public State
{
public:
    //! Constructor 
    SamplerState(const std::string& name,const ofPoint& pos): State(name,pos){}
    //! Destructor
    virtual ~SamplerState() {}
    //! Do the state initialization stuff here
    //virtual void initialize();
    //! Called when the state is entered
    virtual void onEnter();
    //! Called before the state is left
    virtual void onExit();
   
};


#endif


