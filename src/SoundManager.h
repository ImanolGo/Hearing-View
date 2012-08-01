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

class SoundObject;

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