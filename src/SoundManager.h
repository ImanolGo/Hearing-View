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
    
    //! set to the current season and the corresponding sample list 
    void setSeason(const std::string& season);
    
     //! set to the current weather conditions and the corresponding sample list 
    void setConditions(const std::string& conditions);
    
       
private:
    
    //! plays a random sample
    void playRandomSample();
    
    //! interface with the GUI events
    void guiEvent(ofxUIEventArgs &e);
    
    //! loads the samples into the list
    void loadSamples();
    
    //! sets the sample list to be played
    void setCurrentSamples(std::string sampleListName);
    
    //! returns the sample name given its path
    std::string getSampleName(const std::string& path);
    
    
private:
    
    typedef std::vector <SoundObject*>   SamplesList;            ///< defines a list of SoundObjects
    typedef std::map <std::string, SamplesList>   SamplesMap;   ///< defines a map of SamplesList sorted by the category name
    
    SoundObject*                     m_tube;              ///< tube sound
    SamplesMap                       m_samples;           ///< list of the sounds to be play
    SamplesList                      m_currentSampleList; ///< current sample list to be played
    SoundObject*                     m_currentSample;     ///< current playback sample
    bool                             m_isSamplerPlaying;  ///< it tells wether the sampler is finished or not
    
    std::string                      m_season;            ///< saves the current season
    std::string                      m_conditions;        ///< saves the current weather conditions
    std::vector<int>                 m_indexList;         ////< list with the current sample list indexes
    
};


#endif