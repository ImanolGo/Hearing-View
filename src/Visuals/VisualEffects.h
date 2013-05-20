/*==============================================================================
 Imanolgo on 6/27/12.
 ==============================================================================*/
/*! \file VisualEffect.h
 * \authors Imanol Gómez
 * \copyright{2012}
 *///============================================================================


#ifndef __VISUAL_EFFECT_H__
#define __VISUAL_EFFECT_H__

#include <vector>

#include "ofMain.h"

class Visual;

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
/** \class VisualEffect VisualEffect.h
 *	\brief Base class for all the visual effects.
 *	\details Provides basic member attributes which are in common for all 
 *           visual effects.
 */
//==============================================================================

class VisualEffect
{
public:
    
	//! Constructor
	VisualEffect(Visual& visual, EasingFunction function = LINEAR, EasingType type = EASE_IN);
    
	//! Destructor
	virtual ~VisualEffect(){}
    
	//! Updates the elapsed time and visual effect parameters
	virtual void update(double dt) = 0;
    
	//! Starts the visual effect
	virtual void start(double startTime = 0.0);
    
	//! Stops the visual effect
	virtual void stop();
    
	//! Returns the image this animation is associated with
	const Visual& getVisual() { return m_visual; }
    
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
    
	Visual&     m_visual;		///< defines a visual reference
	bool					m_isActive;				///< determines whether an animation is currently updated or not
	double					m_animationTime;		///< duration of the animation in ms
	double					m_elapsedTime;			///< elapsed time since the last update
	EasingFunction			m_function;				///< saves what kind of easing function do you want to use
	EasingType				m_type;					///< saves what type of easing you want
	double					m_startTime;			///< start time of the animation
	double					m_elaspedTimeToStart;	///< elapsed time before the start of the animation
    
};


//==============================================================================
/** \class FadeVisual VisualEffects.h
 *	\brief Fade effect class for visuals.
 *	\details Provides basic member attributes and methods
 *			 to provide visuals fading.
 */
//==============================================================================

class FadeVisual: public VisualEffect
{
public:
    
	//! Constructor
	FadeVisual(Visual& visual, EasingFunction function = LINEAR, EasingType type = EASE_IN);
    
    
    //========================= Fade Interface ================================
    
	//! updates the fade visual if active
	virtual void update(double dt);
    
	//! starts the current fade effect
	virtual void start(double startTime = 0.0);
    
	//! stops the current fade effect
	virtual void stop();
    
    
    //==============================================================================
    
    //! Sets the final alpha value and the duration of the animation
	virtual void setParameters(double endAlpha, double animationTime);
    
	//! Sets the starting and final alpha value and the duration of the animation
	virtual void setParameters(double startAlpha,double endAlpha, double animationTime);

    
protected:
    
    float	m_alpha;            ///< current alpha value 
	double	m_startAlpha;		///< start alpha value
	double	m_endAlpha;         ///< end alpha value

    
};

#endif