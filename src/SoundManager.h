/*==============================================================================
 Imanolgo on 6/27/12.
 ==============================================================================*/
/*! \file SoundManager.h
 * \authors Imanol Gómez
 * \copyright{2012}
 *///============================================================================


#ifndef __SOUND_MANAGER_H__
#define __SOUND_MANAGER_H__

#include <vector>
#include <map>
#include <string>

#include "ofMain.h"
#include "ofxUI.h"

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
    ~SoundObject();
    
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



//========================== class SoundManager ==============================
//============================================================================
/** \class SoundManager SoundManager.h
 *	\brief Class managing the sound of the application
 *	\details it uses the events to make visuals and transitions
 */

class SoundManager
{
public:
    
    //! Constructor
    SoundManager();
    
    //! Destructor
    ~SoundManager();
    
    //! Setups the sounds
    void setup();
    
    //! updates the sounds
    void update(double dt);
    
    //==========================================================================
    
    //! plays all samples randomly
    void playSamples();
    
    //! stop play samples
    void stopSamples();
    
    //! returns if the sound is playing
    bool isSamplerPlaying(){return m_isSamplerPlaying;}
    
    //! fades the tube sound to a specific level
    void  fadeTube(float volume, float fadeTime);
    
    //! fades the current sample to a specific level
    void  fadeSample(float volume,float fadeTime);
    
       
private:
    
    //! plays a random sample
    void playRandomSample();
    
    //! interface with the GUI events
    void guiEvent(ofxUIEventArgs &e);
    
    //! loads the samples into the list
    void loadSamples();
    
    //! sets the volume of a sample
    void setVolume(const std::string& sampleName, float volume);
    
    //! returns the sample name given its path
    std::string getSampleName(const std::string& path);

    
    
private:
    
    typedef std::map <std::string, SoundObject*>   SamplesMap;   ///< defines a map of SoundObjects sorted by its name
    
    SoundObject*                     m_tube;              ///< tube sound
    SamplesMap                       m_samples;           ///< list of the sounds to be play
    std::vector <std::string>        m_sampleNames;       ///< list of names of the samples to play
    SoundObject*                     m_currentSample;     ///< current playback sample
    bool                             m_isSamplerPlaying;  ///< it tells wether the sampler is finished or not
    
    std::string                      m_season;            ///< saves the current year's season
    std::string                      m_weatherConditions; ///< saves the current weather conditions
    
};


#endif