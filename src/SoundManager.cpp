//
//  SoundManager.cpp
//  HearingView
//
//  Created by Imanolgo on 6/24/12.
//

#include "ofMain.h"

#include "DateManager.h"
#include "SoundManager.h"
#include "SoundObject.h"
#include "AppManager.h"
#include "EventManager.h"
#include "Event.h"
#include "Visuals.h"
#include "ViewManager.h"
#include "SoundEffectsManager.h"
#include "SoundEffects.h"

    
SoundManager::SoundManager(): 
    m_tube(NULL), 
    m_playSamples(false), 
    m_currentSample(NULL),
    m_dateManager(NULL),
    m_soundVisual(NULL),
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
    
    if(m_soundVisual)
    {
        AppManager::getInstance().getViewManager().removeVisual(*m_soundVisual);
        delete m_soundVisual;
        m_soundVisual = NULL;
    }
   
    m_dateManager = NULL;
}

void SoundManager::setup()
{
    m_dateManager = &AppManager::getInstance().getDateManager();
    
    m_tube = new SoundObject("tube");
    m_tube->loadSound("sounds/tube.wav");
    m_tube->setVolume(0.0);
    m_tube->setLoop(true);
    m_tube->play();
    this->loadSamples();
    
    m_soundVisual = new SoundVisual(*m_currentSample,ofPoint(500,1000),5,50);
    AppManager::getInstance().getViewManager().addVisual(*m_soundVisual);
    
    std::cout<< m_dateManager->getTime() << "- SoundManager-> play tube "<<std::endl;
    std::cout<<  m_dateManager->getTime() << "- SoundManager-> initialized "<<std::endl;
    ofLogNotice() << m_dateManager->getTime() << "- SoundManager-> play tube ";
    ofLogNotice() << m_dateManager->getTime() << "- SoundManager-> initialized ";

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
                std::cout<< m_dateManager->getTime()<<"- SoundManager-> loadSamples: loading sampels from \""<<samplesPath<<"\"..."<<std::endl;
                ofLogNotice()<< m_dateManager->getTime()<<"- SoundManager-> loadSamples: loading sampels from \""<<samplesPath<<"\"...";
                ofDirectory dir(samplesPath);
                //only show wav and aiff files
                dir.allowExt("wav");
                dir.allowExt("aiff");
                dir.allowExt("aif");
                //populate the directory object
                if(dir.listDir()==0)
                {
                    std::cout <<m_dateManager->getTime()<<"- SoundManager-> loadSamples: No samples found in \""<< samplesPath <<"\"" << std::endl;
                    ofLogNotice() <<m_dateManager->getTime()<<"- SoundManager-> loadSamples: No samples found in \""<< samplesPath <<"\"";
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
                    std::cout <<m_dateManager->getTime()<<"- SoundManager-> loaded sample \""<< sampleName <<"\"" << std::endl;
                    ofLogNotice() <<m_dateManager->getTime()<<"- SoundManager-> loaded sample \""<< sampleName <<"\"";
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
        std::cout <<m_dateManager->getTime()<<"- SoundManager-> setSamples: no sample list with name \""<< sampleListName <<"\"" << std::endl;
        ofLogNotice() <<m_dateManager->getTime()<<"- SoundManager-> setSamples: no sample list with name \""<< sampleListName <<"\"" ;
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
    
    m_playSamples = true;
    this->playRandomSample();
}

void SoundManager::playRandomSample()
{
    if(m_indexList.empty())
    {
        m_playSamples = false;
        AppManager::getInstance().getEventManager().setEvent(Event("END_SAMPLER")); 
    }
    
    else
    {
        int ind = ofRandom(m_indexList.size());
        m_currentSample = m_currentSampleList[m_indexList[ind]];
        m_currentSample->play();
        m_indexList.erase(m_indexList.begin()+ind);
        std::cout <<m_dateManager->getTime()<<"- SoundManager-> play sample \""<< m_currentSample->getName() <<"\"" << std::endl;
        ofLogNotice() <<m_dateManager->getTime()<<"- SoundManager-> play sample \""<< m_currentSample->getName() <<"\"" ;
    }
    
}

void SoundManager::stopSamples()
{
    m_currentSample->stop();
    std::cout <<m_dateManager->getTime()<<"- SoundManager-> stop sample \""<< m_currentSample->getName() <<"\"" << std::endl;
    ofLogNotice() <<m_dateManager->getTime()<<"- SoundManager-> stop sample \""<< m_currentSample->getName() <<"\"";
}


//--------------------------------------------------------------
void SoundManager::update(double dt)
{
    ofSoundUpdate();
    
    if(!m_playSamples)
    {
        return;
    }
        
    if(!m_currentSample->isPlaying())
    {
        this->playRandomSample();
    }
    
}

void  SoundManager::fadeTube(float volume, float fadeTime, FadeType type)
{
    if(!m_tube)
    {
        return;
    }
    
    AppManager::getInstance().getSoundEffectsManager().removeAllSoundEffects(*m_tube);
    
    float currentVolume = m_tube->getVolume();
    switch(type)
    {
        case LINEAR:
        {
            FadeSoundLinear* fade = new FadeSoundLinear(*m_tube);
            fade->setParameters(currentVolume, volume, fadeTime);
            fade->start();
            break;
        }
        case EXPONENTIAL:
        {
            FadeSoundExp* fade = new FadeSoundExp(*m_tube);
            fade->setParameters(currentVolume, volume, fadeTime);
            fade->start();
            break;
        }
        case LOGARITHMIC:
        {
            FadeSoundLog* fade = new FadeSoundLog(*m_tube);
            fade->setParameters(currentVolume, volume, fadeTime);
            fade->start();
            break;
        }
        default:
        {
            FadeSoundLinear* fade = new FadeSoundLinear(*m_tube);
            fade->setParameters(currentVolume, volume, fadeTime);
            fade->start();
            break;
        }
    }
    
    std::cout <<m_dateManager->getTime()<<"- SoundManager-> fade tube to "<<volume<< " in "<< fadeTime<<"s"<<std::endl;
    ofLogNotice() <<m_dateManager->getTime()<<"- SoundManager-> fade tube to "<<volume<< " in "<< fadeTime<<"s";
}

void  SoundManager::fadeTube(float fromVolume, float toVolume, float fadeTime, FadeType type)
{
    if(!m_tube)
    {
        return;
    }
    
    AppManager::getInstance().getSoundEffectsManager().removeAllSoundEffects(*m_tube);
    
    switch(type)
    {
        case LINEAR:
        {
            FadeSoundLinear* fade = new FadeSoundLinear(*m_tube);
            fade->setParameters(fromVolume, toVolume, fadeTime);
            fade->start();
            break;
        }
        case EXPONENTIAL:
        {
            FadeSoundExp* fade = new FadeSoundExp(*m_tube);
            fade->setParameters(fromVolume, toVolume, fadeTime);
            fade->start();
            break;
        }
        case LOGARITHMIC:
        {
            FadeSoundLog* fade = new FadeSoundLog(*m_tube);
            fade->setParameters(fromVolume, toVolume, fadeTime);
            fade->start();
            break;
        }
        default:
        {
            FadeSoundLinear* fade = new FadeSoundLinear(*m_tube);
            fade->setParameters(fromVolume, toVolume, fadeTime);
            fade->start();
            break;
        }
    }
    
    std::cout <<m_dateManager->getTime()<<"- SoundManager-> fade tube from" << fromVolume <<" to "<<toVolume<<  " in "<< fadeTime<<"s"<<std::endl;
    ofLogNotice() <<m_dateManager->getTime()<<"- SoundManager-> fade tube from" << fromVolume << " to "<<toVolume<<  " in "<< fadeTime<<"s";
    
}


void  SoundManager::fadeSample(float volume, float fadeTime, FadeType type)
{
    if(!m_currentSample || !m_currentSample->isPlaying())
    {
        return; 
    }
    
    AppManager::getInstance().getSoundEffectsManager().removeAllSoundEffects(*m_currentSample);
    float currentVolume = m_currentSample->getVolume();
    
    switch(type)
    {
        case LINEAR:
        {
            FadeSoundLinear* fade = new FadeSoundLinear(*m_currentSample);
            fade->setParameters(currentVolume, volume, fadeTime);
            fade->start();
            break;
        }
        case EXPONENTIAL:
        {
            FadeSoundExp* fade = new FadeSoundExp(*m_currentSample);
            fade->setParameters(currentVolume, volume, fadeTime);
            fade->start();
            break;
        }
        case LOGARITHMIC:
        {
            FadeSoundLog* fade = new FadeSoundLog(*m_currentSample);
            fade->setParameters(currentVolume, volume, fadeTime);
            fade->start();
            break;
        }
        default:
        {
            FadeSoundLinear* fade = new FadeSoundLinear(*m_currentSample);
            fade->setParameters(currentVolume, volume, fadeTime);
            fade->start();
            break;
        }
    }

    
    std::cout <<m_dateManager->getTime()<<"- SoundManager-> sample tube to "<<volume<< " in "<< fadeTime<<"s"<<std::endl;
    ofLogNotice() <<m_dateManager->getTime()<<"- SoundManager-> sample tube to "<<volume<< " in "<< fadeTime<<"s";
    
}

void  SoundManager::fadeSample(float fromVolume, float toVolume, float fadeTime, FadeType type)
{
    if(!m_currentSample || !m_currentSample->isPlaying())
    {
        return; 
    }
    
    AppManager::getInstance().getSoundEffectsManager().removeAllSoundEffects(*m_currentSample);

    switch(type)
    {
        case LINEAR:
        {
            FadeSoundLinear* fade = new FadeSoundLinear(*m_currentSample);
            fade->setParameters(fromVolume, toVolume, fadeTime);
            fade->start();
            break;
        }
        case EXPONENTIAL:
        {
            FadeSoundExp* fade = new FadeSoundExp(*m_currentSample);
            fade->setParameters(fromVolume, toVolume, fadeTime);
            fade->start();
            break;
        }
        case LOGARITHMIC:
        {
            FadeSoundLog* fade = new FadeSoundLog(*m_currentSample);
            fade->setParameters(fromVolume, toVolume, fadeTime);
            fade->start();
            break;
        }
        default:
        {
            FadeSoundLinear* fade = new FadeSoundLinear(*m_currentSample);
            fade->setParameters(fromVolume, toVolume, fadeTime);
            fade->start();
            break;
        }
    }
    
    std::cout <<m_dateManager->getTime()<<"- SoundManager-> fade sample from" << fromVolume <<" to "<<toVolume<<  " in "<< fadeTime<<"s"<<std::endl;
    ofLogNotice() <<m_dateManager->getTime()<<"- SoundManager-> fade sample from" << fromVolume << " to "<<toVolume<<  " in "<< fadeTime<<"s";}

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
    
    else if(name=="SENSOR")
    {
        if(event.getValue() == 0.0)
        {
            m_playSamples = false;
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






