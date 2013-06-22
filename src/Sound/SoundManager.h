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
class Event;
class DateManager;
class StateManager;
class WeatherStationManager;
class SoundVisual;
class TextVisual;

//========================== class SoundManager ==============================
//============================================================================
/** \class SoundManager SoundManager.h
 *	\brief Class managing the sound of the application
 *	\details it uses the events to make visuals and transitions
 */

class SoundManager
{
     static const int MAX_NUM_SAMPLES;  //defines the maximum number of normal samples to be played
    
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
    
    //! Initializes all the parameters
    void start();
    
    //! plays the next sample according to the logic
    void playNextSample(float volume);
    
    //! stops the current sample
    void stopSamples();
    
    //! fades the tube sound from it current volume level to a specific level
    void  fadeTube(float volume, float fadeTime);
    
    //! fades the tube sound from as specific volume level  a specific level
    void  fadeTube(float fromVolume, float toVolume, float fadeTime);
    
    //! fades the current sample to a specific level
    void  fadeSample(float volume,float fadeTime);
    
    //! fades the sample from as specific volume level  a specific level
    void  fadeSample(float fromVolume, float toVolume, float fadeTime);
    
     //! Returns the tube's sound object volume
    float getTubeVolume() const;
    
    //! resets the sample list
    void resetSamples();
    
    //! handles the events
    void handleEvent(const Event& event);
       
private:
    
    //! plays a random sample
    void playRandomSample();
    
    //! plays one of the expert samples
    void playExpertSample();
    
    //! interface with the GUI events
    void guiEvent(ofxUIEventArgs &e);
    
    //! loads the samples into the list
    void loadSamples();
    
    //! returns if a given sample can be played or not
    bool fitsPlayConditions(const SoundObject& sample);
    
    //! sets the sample list to be played
    bool setCurrentSamples(std::string sampleListName);
    
    //! returns the sample name given its path
    std::string getSampleName(const std::string& path);
    
    
private:
    
    typedef std::vector <SoundObject*>   SamplesList;            ///< defines a list of SoundObjects
    typedef std::map <std::string, SamplesList>   SamplesMap;   ///< defines a map of SamplesList sorted by the category name
    
    SoundObject*           m_tube;                  ///< tube sound
    SamplesMap             m_samples;               ///< list of the sounds to be play
    SamplesList            m_currentSampleList;     ///< current sample list to be played
    SoundObject*           m_currentSample;         ///< current playback sample
    bool                   m_playExpert;            ///< defines if the expert sample will be played
    int                    m_numPlayedSamples;      ///< stores the number of samples played
    
    float                  m_masterSampleVolume;    ///< stores the master sample volume
    double                 m_sampleTimer;           ///< the amount of time to wait until playing a sample
    double                 m_elapsedTime;           ///< the elapsed time waiting to play a sample
    
    std::string            m_season;                ///< saves the current season
    std::string            m_category;              ///< saves the current sample category
        
    DateManager*                m_dateManager;              ///< pointer to the date manager
    StateManager*               m_stateManager;         ///< pointer to the state manager
    WeatherStationManager*      m_weatherStationManager; ///< pointer to the weather station manager
    SoundVisual*                m_soundVisual;              ///< visualization of th ecurrent sound level
    
    TextVisual*       m_sampleName;                ///< text visual from the current sample name being played
    TextVisual*       m_sampleElapsedTimeText;     ///< text visual from the current sample elapsed time
    TextVisual*       m_sampleRemainTimeText;      ///< text visual from the current sample remaining time
    
    float             m_W;              ///< wind speed threshold value used to exlcude samples with this letter
    float             m_T;              ///< temperature threshold value used to exlcude samples with this letter
    float             m_R;              ///< wetness threshold value used to exlcude samples with this letter
    float             m_S;              ///< insolation threshold value used to exlcude samples with this letter
    
};


#endif