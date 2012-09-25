/*==============================================================================
 Imanolgo on 6/27/12.
 ==============================================================================*/
/*! \file SoundEffectsManager.h
 * \authors Imanol Gómez
 * \copyright{2012}
 *///============================================================================


#ifndef __SOUND_EFFECTS_MANAGER_H__
#define __SOUND_EFFECTS_MANAGER_H__

#include <vector>

class SoundEffect;
class SoundObject;

//========================== class SoundEffectsManager ==============================
//============================================================================
/** \class SoundEffectsManager SoundEffectsManager.h
 *	\brief Manages arbitrary sound effects.
 *	\details Manages all different sound effects.
 *   The sound effects are organized in fadeIn, fadeOut ...
 */
//==============================================================================

class SoundEffectsManager
{
public:
    
    //! Constructor
    SoundEffectsManager();
    
    //! Destructor
    ~SoundEffectsManager();
    
    //! Updates all the sound effects
	void update(double dt);
    
	//! Adds a certain sound effect
	void addSoundEffect(SoundEffect& soundEffect);
    
	//! Removes a certain sound effect
	void removeSoundEffect(SoundEffect& soundEffect);
    
	//! Removes all sound effects for the specified sound 
	void removeAllSoundEffects(const SoundObject& sound);    
    
    //==========================================================================
    
    
private:
    
    
    typedef std::vector<SoundEffect*>		SoundEffectVector;
    
	SoundEffectVector	m_soundEffects; ///< Vector of all sound effects
    
    
};


#endif