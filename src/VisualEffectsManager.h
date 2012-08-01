/*==============================================================================
 Imanolgo on 6/27/12.
 ==============================================================================*/
/*! \file VisualEffectsManager.h
 * \authors Imanol Gómez
 * \copyright{2012}
 *///============================================================================


#ifndef __VISUAL_EFFECTS_MANAGER_H__
#define __VISUAL_EFFECTS_MANAGER_H__

#include <vector>

class VisualEffect;
class Visual;


//========================== class VisualEffectsManager ==============================
//============================================================================
/** \class VisualEffectsManager VisualEffectsManager.h
 *	\brief Manages arbitrary visual effects.
 *	\details Manages all different image effects.
 *   The animations are organized in fadeIn, fadeOut, move and bouncing effects.
 */
//==============================================================================

class VisualEffectsManager
{
public:
    
    //! Constructor
    VisualEffectsManager();
    
    //! Destructor
    ~VisualEffectsManager();
    
    //! Updates all the visual effects
	void update(double dt);
    
	//! Adds a certain visual effect
	void addVisualEffect(VisualEffect& visualEffect);
    
	//! Removes a certain visual effect
	void removeVisualEffect(VisualEffect& visualEffect);
    
	//! Removes all visual effects for the specified image
	void removeAllVisualEffects(const Visual& visual);    
    
    //==========================================================================
    
private:
    
    
    typedef std::vector<VisualEffect*>		VisualEffectVector;
    
	VisualEffectVector	m_visualEffects; ///< Vector of all visual effects
    
    
};


#endif