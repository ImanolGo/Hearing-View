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
#include "SoundEffectsManager.h"
#include "SoundEffects.h"

    
SoundManager::SoundManager(): 
    m_tube(NULL), 
    m_isSamplerPlaying(false), 
    m_currentSample(NULL),
    m_season("Summer"),
    m_conditions("Dry"),
    m_dayTime("Day")
{
}


SoundManager::~SoundManager()
{
    
    for (SamplesMap::iterator it=m_samples.begin() ; it != m_samples.end(); it++ )
    {
        SamplesList sampleList = it->second;
        for (SamplesList::iterator it2=sampleList.begin() ; it2 != sampleList.end(); it2++ )
        {
            delete *it2;
            *it2 = NULL;
        }
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
    std::cout<< "SoundManager-> play tube "<<std::endl;
    std::cout<< "SoundManager-> initialized "<<std::endl;

}

void SoundManager::loadSamples()
{
    //some path, may be absolute or relative to bin/data

    std::string seasons[4] = {"Summer","Autumn","Winter","Spring"};
    std::string conditions[2] = {"Dry","Rain"};
    std::string dayTime[2] = {"Day","Night"};
    
    
    for (int i=0; i<4; i++) 
    {
        for (int j=0; j<2; j++) 
        {
            for (int k=0; k<2; k++) 
            {
                std::string samplesPath = "sounds/" + seasons[i] + "/" + dayTime[j] +"/" + conditions[k];
                std::cout<< "SoundManager-> loadSamples: loading sampels from \""<<samplesPath<<"\"..."<<std::endl;
                ofDirectory dir(samplesPath);
                //only show wav and aiff files
                dir.allowExt("wav");
                dir.allowExt("aiff");
                dir.allowExt("aif");
                //populate the directory object
                if(dir.listDir()==0)
                {
                    std::cout <<"SoundManager-> loadSamples: No samples found in \""<< samplesPath <<"\"" << std::endl;
                    break;
                }
                
                SamplesList sampleList;
                //go through and print out all the paths
                for(int n = 0; n < dir.numFiles(); n++)
                {
                    std::string sampleName = this->getSampleName(dir.getPath(n));
                    SoundObject* sample = new SoundObject(sampleName);
                    sample->loadSound(dir.getPath(n));
                    sampleList.push_back(sample);
                    std::cout <<"SoundManager-> loaded sample \""<< sampleName <<"\"" << std::endl;
                }
                m_samples[seasons[i] + "/" + dayTime[j] +"/" + conditions[k]] = sampleList;
            }
         }
    }
    
    m_currentSampleList = m_samples.begin()->second; // m_currentSampleList points to the first element map
    
}


std::string SoundManager::getSampleName(const std::string& path)
{
    std::vector<std::string> strs = ofSplitString(path, "/");
    
    return strs.back();
}


void SoundManager::setCurrentSamples(std::string sampleListName)
{
    if(m_samples.find(sampleListName) == m_samples.end())
    {
        //if there are no samples with this name, the m_currentSampleList remains at it was
        std::cout <<"SoundManager-> setSamples: no sample list with name \""<< sampleListName <<"\"" << std::endl;
        return;
    }
    
    m_currentSampleList = m_samples[sampleListName];
    
    m_indexList.clear();
    for(int i = 0; i < m_currentSampleList.size(); i++ )
    {
        m_indexList.push_back(i);
    }


}

void SoundManager::playSamples()
{
    m_indexList.clear();
    for(int i = 0; i < m_currentSampleList.size(); i++ )
    {
        m_indexList.push_back(i);
    }
    
    this->playRandomSample();
}

void SoundManager::playRandomSample()
{
    if(m_indexList.empty())
    {
        m_currentSample = NULL;
        AppManager::getInstance().getEventManager().setEvent(Event("END_SAMPLER")); 
    }
    
    else
    {
        int ind = ofRandom(m_indexList.size());
        m_currentSample = m_currentSampleList[m_indexList[ind]];
        m_currentSample->play();
        m_indexList.erase(m_indexList.begin()+ind);
        std::cout <<"SoundManager-> play sample \""<< m_currentSample->getName() <<"\"" << std::endl;
    }
    
}

void SoundManager::stopSamples()
{
    m_currentSample->stop();
    std::cout <<"SoundManager-> stop sample \""<< m_currentSample->getName() <<"\"" << std::endl;
}


//--------------------------------------------------------------
void SoundManager::update(double dt)
{
    ofSoundUpdate();
    
    if(!m_currentSample)
    {
        return;
    }
        
    if(m_currentSample->isPlaying())
    {
        this->playRandomSample();
    }
    
}

void  SoundManager::fadeTube(float volume, float fadeTime)
{
    if(!m_tube)
    {
        return;
    }
    
    AppManager::getInstance().getSoundEffectsManager().removeAllSoundEffects(*m_tube);
    
    float currentVolume = m_tube->getVolume();
    FadeSoundExp* fadeExp = new FadeSoundExp(*m_tube);
    fadeExp->setParameters(currentVolume, volume, fadeTime);
    fadeExp->start();
    std::cout<< "SoundManager-> fade tube to "<<volume<< " in "<< fadeTime<<"s"<<std::endl;
    
}

void  SoundManager::fadeSample(float volume, float fadeTime)
{
    if(!m_currentSample || !m_currentSample->isPlaying())
    {
        return; 
    }
    
    AppManager::getInstance().getSoundEffectsManager().removeAllSoundEffects(*m_currentSample);
    
    std::cout<< "SoundManager-> fade sample \""<< m_currentSample->getName() << "\" to "<<volume<< " in "<< fadeTime<<"s"<<std::endl;
    float currentVolume = m_currentSample->getVolume();
    FadeSoundExp* fadeExp = new FadeSoundExp(*m_currentSample);
    fadeExp->setParameters(currentVolume, volume, fadeTime);
    fadeExp->start();
    
}

void SoundManager::handleEvent(const Event& event)
{
    std::string name = event.getName();
    
    if(name=="TUBE VOLUME")
    {
        m_tube->setVolume((float) event.getValue());
    }
    
    else if(name=="SAMPLE VOLUME")
    {
        if(m_currentSample && m_currentSample->isPlaying())
        {
            m_currentSample->setVolume((float) event.getValue());
        }
    }
    
    else if(name=="Winter" || name=="Summer" ||name=="Autumn" ||name=="Spring")
    {
        if(m_season!=name)
        {
            m_season = name;
            this->setCurrentSamples(m_season+"/"+ m_dayTime+"/"+ m_conditions);
        }
    }
    
    else if(name== "Day" || name=="Night" )
    {
        if(m_dayTime!=name)
        {
            m_dayTime = name;
            this->setCurrentSamples(m_season+"/"+ m_dayTime+"/"+ m_conditions);
        }
        
    }
    
    else if(name== "Dry" || name=="Rain" )
    {
        if(m_conditions!=name)
        {
            m_conditions = name;
            this->setCurrentSamples(m_season+"/"+ m_dayTime+"/"+ m_conditions);
        }
        
    }


}






