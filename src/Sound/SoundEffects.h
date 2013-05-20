/*==============================================================================
 Imanolgo on 6/27/12.
 ==============================================================================*/
/*! \file SoundEffects.h
 * \authors Imanol Gómez
 * \copyright{2012}
 *///============================================================================


#ifndef __SOUND_EFFECT_H__
#define __SOUND_EFFECT_H__

#include <vector>

#include "SoundManager.h"


typedef enum EasingFunction {
	LINEAR,
	EXPONENTIAL,
	QUADRATIC,
	CUBIC,
	SINUSOIDAL,
	QUARTIC,
	QUINTIC,
	CIRCULAR
};

typedef enum EasingType {
	EASE_IN,
	EASE_OUT,
	EASE_IN_OUT
};

//==============================================================================
/** \class SoundEffect SoundEffects.h
 *	\brief Base class for all sound effects.
 *	\details Provides basic member attributes which are in common for all 
 *           sound effects.
 */
//==============================================================================

class SoundEffect
{
public:
    
	//! Constructor
	SoundEffect(SoundObject& sound, EasingFunction function = LINEAR, EasingType type = EASE_IN);
    
	//! Destructor
	virtual ~SoundEffect(){}
    
	//! Updates the elapsed time and sound effect parameters
	virtual void update(double dt) = 0;
    
	//! Starts the sound effect
	virtual void start(double startTime=0);
    
	//! Stops the sound effect
	virtual void stop();
    
	//! Returns the sprite this animation is associated with
	const SoundObject& getSound() { return m_sound; }
    
    
	//! Returns the current state of the animation	
	bool isActive() const { return m_isActive; } 
    
	//! Returns the start time of the animation
	//double getStartTime() const { return m_startTime; }
    
	//! Returns the elapsed time before the start of the animation
	//double getElapsedTimeToStart() const { return m_elaspedTimeToStart; }
    
	//! Set the elapsed time before the start of the animation
	void setElapsedTimeToStart(double time) { m_elaspedTimeToStart = time; }
    
    
protected:
    
	//! Returns the update value from the selected function.
	//! t: current time, from: start value, to: end value, duration: the total animation time
	double function(double t, double from, double to, double duration) const;
    
protected:
    
	SoundObject&            m_sound;                ///< defines a const reference to SoundObject
    
    bool					m_isActive;				///< determines whether an animation is currently updated or not
	double					m_animationTime;		///< duration of the animation in ms
	double					m_elapsedTime;			///< elapsed time since the last update
	EasingFunction			m_function;				///< saves what kind of easing function do you want to use
	EasingType				m_type;					///< saves what type of easing you want
	double					m_startTime;			///< start time of the animation
	double					m_elaspedTimeToStart;	///< elapsed time before the start of the animation
    
};





//==============================================================================
/** \class FadeSound SoundEffects.h
 *	\brief Fade effect class for sounds.
 *	\details Provides basic member attributes and methods
 *			 to provide sounds fading.
 */
//==============================================================================

class FadeSound: public SoundEffect
{
public:
    
	//! Constructor
	FadeSound(SoundObject& sound, EasingFunction function = LINEAR, EasingType type = EASE_IN);
    
    
    //========================= Fade Interface ================================
    
	//! updates the fade sound if active
	virtual void update(double dt);
    
	//! starts the current fade effect
	virtual void start(double startTime=0);
    
	//! stops the current fade effect
	virtual void stop();

    
	//==============================================================================
    
    //! Sets the final volume and the duration of the animation
	virtual void setParameters(double endVolume, double animationTime);
    
	//! Sets the starting and final volume and the duration of the animation
	virtual void setParameters(double startVolume,double endVolume, double animationTime);
    
protected:
    
    float	m_volume;             ///< current volumen 
	double	m_startVolume;		///< start volume value
	double	m_endVolume;		///< end volume value
    
};

#endif