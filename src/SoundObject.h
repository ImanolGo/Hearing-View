/*==============================================================================
 Imanolgo on 08/07/12.
 ==============================================================================*/
/*! \file SoundObject.h
 * \authors Imanol Gómez
 * \copyright{2012}
 *///============================================================================


#ifndef __SOUND_OBJECT_H__
#define __SOUND_OBJECT_H__

#include <string>

#include "ofMain.h"

//========================== class SoundObject ==============================
//============================================================================
/** \class SoundObject SoundObject.h
 *	\brief Class representing a sound object
 *	\details It wrapst the OF class ofSoundPlayer
 */

class SoundObject
{
public:
    
    //! Constructor
    SoundObject(std::string name);
    //! Destructor
    virtual ~SoundObject();
    
    //! loads an audio file
    void loadSound(std::string path) {m_soundPlayer->loadSound(path);}
    
    //! unload an audio file
    void unloadSound() {m_soundPlayer->unloadSound();}
    
    //! sets the volume of a sample
    void setVolume(float volume);
    
    //! get the volume of a sample
    const float getVolume() {return m_volume;}
    
    //! get the volume of a sample
    const std::string& getName() const {return m_name;}
    
    //! set loop
    void setLoop(bool bLoop) {m_soundPlayer->setLoop(bLoop);}
    
    //! play sound
    const void play() const {m_soundPlayer->play();}
    
    //! stop sound
    const void stop() const {m_soundPlayer->stop();}
    
    //! returns if the sound is playing
    bool isPlaying() {return m_soundPlayer->getIsPlaying();}
    
private:
    
    ofSoundPlayer*  m_soundPlayer; ///< the oFSoundPlayer class
    float           m_volume;      ///< it saves the volume
    std::string     m_name;        ///< sound identifier
    
};


#endif
