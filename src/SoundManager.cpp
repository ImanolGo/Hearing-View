//
//  SoundManager.cpp
//  HearingView
//
//  Created by Imanolgo on 6/24/12.
//

#include "ofMain.h"

#include "SoundManager.h"
#include "SoundObject.h"
#include "AppManager.h"
#include "EventManager.h"
#include "Event.h"
#include "SoundEffects.h"

    
SoundManager::SoundManager(): m_tube(NULL), m_isSamplerPlaying(false), m_currentSample(NULL),
    m_season("Summer"), m_weatherConditions("Day_Dry")
{
}


SoundManager::~SoundManager()
{
    
    for (SamplesMap::iterator it=m_samples.begin() ; it != m_samples.end(); it++ )
    {
        delete it->second;
        it->second = NULL;
    }
    

    m_samples.clear(); 
    
    if(m_tube)
    {
        delete m_tube;
        m_tube = NULL;
    }
    
}


void SoundManager::setup()
{
    m_tube = new SoundObject("tube");
    m_tube->loadSound("sounds/tube.wav");
    m_tube->setVolume(0.0);
    m_tube->setLoop(true);
    m_tube->play();
    this->loadSamples();
    
}

void SoundManager::loadSamples()
{
    //some path, may be absolute or relative to bin/data
    
    std::string samplesPath = "sounds/" + m_season + "/" + m_weatherConditions;
    
    if(m_currentSample)
    {
        m_currentSample->stop();
        m_currentSample = NULL;
    }
    
    for (SamplesMap::iterator it=m_samples.begin() ; it != m_samples.end(); it++ )
    {
        delete it->second;
        it->second = NULL;
    }
    
    m_samples.clear();
    m_sampleNames.clear();
    
    ofDirectory dir(samplesPath);
    //only show wav and aiff files
    dir.allowExt("wav");
    dir.allowExt("aiff");
    dir.allowExt("aif");
    //populate the directory object
    dir.listDir();
    
    //go through and print out all the paths
    for(int i = 0; i < dir.numFiles(); i++)
    {
        std::cout << dir.getPath(i) << std::endl;
        std::string sampleName = this->getSampleName(dir.getPath(i));
        SoundObject* sample = new SoundObject(sampleName);
        sample->loadSound(dir.getPath(i));
        m_samples[sampleName] = sample;
    }
    
}

void SoundManager::setVolume(const std::string& sampleName, float volume)
{
    if (m_samples.find(sampleName)!=m_samples.end()) 
    {
        m_samples[sampleName]->setVolume(volume);
    }
        
}

std::string SoundManager::getSampleName(const std::string& path)
{
    std::vector<std::string> strs = ofSplitString(path, "/");
    
    return strs.back();
}


void SoundManager::playSamples()
{
    m_sampleNames.clear();
    
    for (SamplesMap::iterator it=m_samples.begin() ; it != m_samples.end(); it++ )
    {
        m_sampleNames.push_back(it->first);
    }

    this->playRandomSample();
}

void SoundManager::playRandomSample()
{
    if(m_sampleNames.empty())
    {
        this->stopSamples();
        AppManager::getInstance().getEventManager().setEvent(Event("End")); 
        m_currentSample = NULL;
        return;
    }
        
    int ind = ofRandom(m_sampleNames.size());
    std::string sampleName = m_sampleNames[ind];
    m_currentSample = m_samples[sampleName];
    m_currentSample->play();
    m_sampleNames.erase(m_sampleNames.begin()+ind);
}

void SoundManager::stopSamples()
{
    m_sampleNames.clear();
    m_currentSample->stop();
    m_currentSample = NULL;
    
}


//--------------------------------------------------------------
void SoundManager::update(double dt)
{
    ofSoundUpdate();
    
    if(m_currentSample)
    {
        if(!m_currentSample->isPlaying())
        {
            this->playRandomSample();
        }
    
    }
}

//void SoundManager::guiEvent(ofxUIEventArgs &e)
//{
//    string name = e.widget->getName(); 
//	int kind = e.widget->getKind(); 
//	cout << "got event from: " << name << endl; 
//    
//    if(name == "Winter" || name == "Summer" || name == "Spring" || name == "Autumn")
//	{
//        m_season = name;
//        this->loadSamples();
//        ofxUIToggle * toggle = (ofxUIToggle *) AppManager::getInstance().getGUI().getWidget("EndSampler");
//    
//	}
//    
//    else if(name == "Day_Dry" || name == "Night_Dry" || name == "Day_Rain" || name == "Night_Rain")
//	{
//        m_weatherConditions = name;
//        this->loadSamples();
//        ofxUIToggle * toggle = (ofxUIToggle *) AppManager::getInstance().getGUI().getWidget("EndSampler");
//        toggle->setValue(true); 
//	}
//    
//}


void  SoundManager::fadeTube(float volume, float fadeTime)
{
    if(!m_tube)
    {
        return;
    }
    
    float currentVolume = m_tube->getVolume();
    FadeExp* fadeExp = new FadeExp(*m_tube);
    fadeExp->setParameters(currentVolume, volume, fadeTime);
    fadeExp->start();
    
}

void  SoundManager::fadeSample(float volume, float fadeTime)
{
    if(!m_currentSample)
    {
        return; 
    }
    
    float currentVolume = m_currentSample->getVolume();
    FadeExp* fadeExp = new FadeExp(*m_currentSample);
    fadeExp->setParameters(currentVolume, volume, fadeTime);
    fadeExp->start();
    
}






