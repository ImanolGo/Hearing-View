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
	SoundEffect(SoundObject& sound);
    
	//! Destructor
	virtual ~SoundEffect(){}
    
	//! Updates the elapsed time and sound effect parameters
	virtual void update(double dt) = 0;
    
	//! Starts the sound effect
	virtual void start();
    
	//! Stops the sound effect
	virtual void stop();
    
	//! Returns the sprite this animation is associated with
	const SoundObject& getSound() { return m_sound; }
    
protected:
    
	SoundObject&		m_sound;		///< defines a const reference to SoundObject
	double              m_elapsedTime;	///< elapsed time (s)
    bool                m_isActive;		///< determines whether a sound effect is currently updated or not
    
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
	FadeSound(SoundObject& sound);
    
    
    //========================= Fade Interface ================================
    
	//! updates the fade sound if active
	virtual void update(double dt) = 0;
    
	//! starts the current fade effect
	virtual void start();
    
	//! stops the current fade effect
	virtual void stop();

    
	//==============================================================================
    
	//! sets parameter of the animation
	virtual void setParameters(float from, float to, float fadeTime);
    
protected:
    
    float	m_elapsedTime;			///< elapsed time (ms)
    float	m_fadeTime;             ///< fade duration (ms)
	float	m_from;                 ///< initial value
    float	m_to;                   ///< final value
    
};



//==============================================================================
/** \class FadeSoundLinear SoundEffects.h
 *	\brief Fades a sound linearly.
 *
 */
//==============================================================================

class FadeSoundLinear: public FadeSound
{
public:
    
	//! Constructor
	FadeSoundLinear(SoundObject& sound);
    
    
    //========================= Fade Interface ================================
    
	//! updates the linear fade if active
	virtual void update(double dt);
    
};



//==============================================================================
/** \class FadeSoundLog SoundEffects.h
 *	\brief Fades a sound logaritmically.
 *
 */
//==============================================================================

class FadeSoundLog: public FadeSound
{
public:
    
	//! Constructor
	FadeSoundLog(SoundObject& sound);
    
    
    //========================= Fade Interface ================================
    
	//! updates the logaritmic fade if active
	virtual void update(double dt);
    
};

//==============================================================================
/** \class FadeSoundExp SoundEffects.h
 *	\brief Fades a sound exponentially.
 *
 */
//==============================================================================

class FadeSoundExp: public FadeSound
{
public:
    
	//! Constructor
	FadeSoundExp(SoundObject& sound);
    
    
    //========================= Fade Interface ================================
    
	//! updates the exponential fade if active
	virtual void update(double dt);
    
};



#endif