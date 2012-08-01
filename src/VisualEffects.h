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
	VisualEffect(Visual& visual);
    
	//! Destructor
	virtual ~VisualEffect(){}
    
	//! Updates the elapsed time and visual effect parameters
	virtual void update(double dt) = 0;
    
	//! Starts the visual effect
	virtual void start();
    
	//! Stops the visual effect
	virtual void stop();
    
	//! Returns the image this animation is associated with
	const Visual& getVisual() { return m_visual; }
    
protected:
    
	Visual&     m_visual;		///< defines a visual reference
	double		m_elapsedTime;	///< elapsed time
    bool        m_isActive;		///< determines whether a sound effect is currently updated or not
    
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
	FadeVisual(Visual& visual);
    
    
    //========================= Fade Interface ================================
    
	//! updates the fade visual if active
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




//
////==============================================================================
///** \class FadeOutAnimation Animatons.h
// *	\brief Fade out animation class for sprites.
// *	\details Provides basic member attributes and methods
// *			 to provide animations fading out.
// */
////==============================================================================
//
//class FadeOutAnimation: public Animation
//{
//public:
//    
//	//! Constructor
//	FadeOutAnimation(Sprite& sprite, Scene& scene);
//    
//    
//	//========================= Animation Interface ================================
//	
//	//! Renders the visual if visible
//	virtual void update(double dt);
//	//! stops the current animation
//	virtual void stop();
//    
//	//==============================================================================
//    
//	//! sets parameter of the animation
//	virtual void setParameters(float maxAlpha, float animationTime);
//    
//protected:
//    
//	float	m_alpha;			///< current alpha value
//	float	m_alphaMax;			///< maximum alpha value
//	float	m_animationTime;	///< duration of the animation in ms 
//    
//};
//
////==============================================================================
///** \class FadeInAnimation Animatons.h
// *	\brief Fade In animation class for sprites.
// *	\details Provides basic member attributes and methods
// *			 to provide animations fading in.
// */
////==============================================================================
//
//class FadeInAnimation: public Animation
//{
//public:
//    
//	//! Constructor
//	FadeInAnimation(Sprite& sprite, Scene& scene);
//    
//	//========================= Animation Interface ================================
//    
//	//! Renders the visual if visible
//	virtual void update(double dt);
//	//! stops the current animation
//	virtual void stop();
//    
//	//==============================================================================
//    
//	//! sets parameter of the animation
//	virtual void setParameters(float maxAlpha, float animationTime);
//    
//protected:
//    
//	float	m_alpha;			///< current alpha value
//	float	m_alphaMax;			///< maximum alpha value
//	float	m_animationTime;	///< duration of the animation in ms 
//    
//};
//
////==============================================================================
///** \class MovAnimation Animatons.h
// *	\brief Movement animation class for sprites.
// *	\details Provides basic member attributes and methods
// *			 to provide animations changing the position.
// */
////==============================================================================
//
//class MovAnimation: public Animation
//{
//public:
//    
//	//! Constructor
//	MovAnimation(Sprite& sprite, Scene& scene);
//    
//	//========================= Animation Interface ================================
//    
//	//! Renders the visual if visible
//	virtual void update(double dt);
//	//! stops the current animation
//	virtual void stop();
//    
//	//==============================================================================
//    
//	//! sets parameter of the animation
//	virtual void setParameters(const math::Vector2D& pos, float animationTime);
//    
//protected:
//    
//	math::Vector2D		m_initPos;			///< initial position of the moving sprite
//	math::Vector2D		m_finalPos;			///< final position of the moving sprite
//	float				m_fFinalPosRatio;	///< determines the spriteŽs current positions as a ratio of initial and final position
//	float				m_animationTime;	///< duration of the animation in ms 
//    
//};
//
////==============================================================================
///** \class BounceAnimation Animatons.h
// *	\brief Bounce animation class for sprite.
// *	\details Provides basic member attributes and methods
// *			 to provide bouncing animations.
// */
////==============================================================================
//
//class BounceAnimation: public Animation
//{
//public:
//    
//	//! Constructor
//	BounceAnimation(Sprite& sprite, Scene& scene);
//    
//	//========================= Animation Interface ================================
//    
//	//! Renders the visual if visible
//	virtual void update(double dt);
//	//! stops the current animation
//	virtual void stop();
//    
//	//==============================================================================
//    
//	virtual void setParameters(int numMaxBounces,float animationTime);
//    
//protected:
//    
//	int			m_numBounces;		///< counts the number of bounces occurred 
//	int			m_numMaxBounces;	///< determines the maximum number of bounces
//	bool		m_forward;			///< determines if the bouncing goes forwards or backwards
//	float		m_scaleFactor;		///< determines size factor of the visual
//	float		m_animationTime;	///< duration of the animation in ms 
//    
//};
//
////==============================================================================
///** \class FrameAnimation Animatons.h
// *	\brief Frame animation class for sprite.
// *	\details Provides basic member attributes and methods
// *			 to provide frame based animations.
// */
////==============================================================================
//
//class FrameAnimation: public Animation
//{
//public:
//    
//	//! Constructor
//	FrameAnimation(Sprite& sprite, Scene& scene):Animation(sprite, scene), m_animationTime(55){};
//	
//	//========================= Animation Interface ================================
//    
//	//! Renders the visual if visible
//	virtual void update(double dt);
//	//! stops the current animation
//	virtual void stop();
//    
//	//==============================================================================
//    
//	virtual void setParameters(float animationTime);
//    
//protected:
//    
//	float		m_animationTime;	///< duration of the animation in ms 
//    
//};
//


#endif