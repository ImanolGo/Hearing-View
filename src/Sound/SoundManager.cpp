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
    m_sampleText(NULL),
    m_season("SUM"),
    m_category("DAY")
{
    //Intentionally left empty
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
    
    if (m_sampleText) {
        AppManager::getInstance().getViewManager().removeVisual(*m_sampleText);
        delete m_sampleText;
        m_sampleText = NULL;
    }
    
    if(m_tube)
    {
        delete m_tube;
        m_tube = NULL;

    }
}

void SoundManager::setup()
{
    m_dateManager = &AppManager::getInstance().getDateManager();
    
    m_tube = new SoundObject("tube");
    m_tube->loadSound("sounds/tube.wav");
    m_tube->setVolume(0.0f);
    m_tube->setLoop(true);
    m_tube->play();
    this->loadSamples();
    
    float margin = ofGetHeight()/70;
    float widthVolumes = (1-0.25)*(ofGetWidth() - 4*margin); 
    float heightVolumes = ofGetHeight()/3.0 - 4*margin;
    float x =  6*margin + widthVolumes/2 + widthVolumes/8;
    float y =  6*margin + heightVolumes + heightVolumes/4;
    
    m_soundVisual = new SoundVisual(*m_currentSample,ofPoint(500,1000),5,50);
    AppManager::getInstance().getViewManager().addVisual(*m_soundVisual);
    
    m_sampleText = new TextVisual(ofPoint(x,y),5,50);
    m_sampleText->setColor(ofColor(255,255,255));
    AppManager::getInstance().getViewManager().addVisual(*m_sampleText);
    
    std::cout<< m_dateManager->getTime() << "- SoundManager-> play tube "<<std::endl;
    std::cout<<  m_dateManager->getTime() << "- SoundManager-> initialized "<<std::endl;
    ofLogNotice() << m_dateManager->getTime() << "- SoundManager-> play tube ";
    ofLogNotice() << m_dateManager->getTime() << "- SoundManager-> initialized ";

}

void SoundManager::loadSamples()
{
    //some path, may be absolute or relative to bin/data
    int numSeasons = 4;
    int numCategories = 4;

    std::string seasons[4] = {"SUM","FAL","WIN","SPR"};
    std::string category[4] = {"DWN","DAY","DSK","EXP"};
    
    
    for (int i=0; i<numSeasons; i++) 
    {
        for (int j=0; j<numCategories; j++) 
        {
            std::string folderName = seasons[i] + "_" + category[j];
            std::string samplesPath = "sounds/" + folderName;
            std::cout<< m_dateManager->getTime()<<"- SoundManager-> loading samples from \""<<samplesPath<<"/\""<<std::endl;
            ofLogNotice()<< m_dateManager->getTime()<<"- SoundManager->loading samples from \""<<samplesPath<<"/\"";
            ofDirectory dir(samplesPath);
            //only show wav and aiff files
            dir.allowExt("wav");
            dir.allowExt("aiff");
            dir.allowExt("aif");
            //populate the directory object
            if(dir.listDir()==0)
            {
                std::cout <<m_dateManager->getTime()<<"- SoundManager-> No samples found in \""<< samplesPath <<"/\"" << std::endl;
                ofLogNotice() <<m_dateManager->getTime()<<"- SoundManager-> No samples found in \""<< samplesPath <<"/\"";
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
                std::cout <<m_dateManager->getTime()<<"- SoundManager-> loaded sample \""<< sampleName <<"/\"" << std::endl;
                ofLogNotice() <<m_dateManager->getTime()<<"- SoundManager-> loaded sample \""<< sampleName <<"/\"";
            }
            m_samples[folderName] = sampleList;
         }
    }
    
    m_currentSampleList = m_samples.begin()->second; // m_currentSampleList points to the first element map
    
}


float SoundManager::getTubeVolume() const
{
    if(m_tube){
        return m_tube->getVolume();
    }
    
    return 0.0f;
}

std::string SoundManager::getSampleName(const std::string& path)
{
    std::vector<std::string> strs = ofSplitString(path, "/");
    //strs = ofSplitString(strs.back(), ".");
    return strs.back();
}


void SoundManager::setCurrentSamples(std::string sampleListName)
{
    m_currentSampleList.clear();
    
    if(m_samples.find(sampleListName) == m_samples.end())
    {
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
    
    std::cout <<m_dateManager->getTime()<<"- SoundManager-> setSamples: playing samples from \""<< sampleListName <<"\"" << std::endl;
    ofLogNotice() <<m_dateManager->getTime()<<"- SoundManager-> setSamples: playing samples from \""<< sampleListName <<"\"" ;

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
        AppManager::getInstance().getViewManager().fadeVisual(*m_sampleText, 0, 3);
        AppManager::getInstance().getEventManager().setEvent(Event("END_SAMPLER"));
    }
    
    else
    {
        int ind = ofRandom(m_indexList.size());
        m_currentSample = m_currentSampleList[m_indexList[ind]];
        m_sampleText->setText("\"" + m_currentSample->getName() + "\"", 15);
        m_sampleText->setColor(ofColor(255,255,255,0));
        AppManager::getInstance().getViewManager().fadeVisual(*m_sampleText, 255, 3);
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

void  SoundManager::fadeTube(float volume, float fadeTime)
{
    if(!m_tube)
    {
        return;
    }
    
    AppManager::getInstance().getSoundEffectsManager().removeAllSoundEffects(*m_tube);
    FadeSound* fade = new FadeSound(*m_tube);
    fade->setParameters(volume, fadeTime);
    fade->start();

    std::cout <<m_dateManager->getTime()<<"- SoundManager-> fade tube to "<<volume<< " in "<< fadeTime<<"s"<<std::endl;
    //ofLogNotice() <<m_dateManager->getTime()<<"- SoundManager-> fade tube to "<<volume<< " in "<< fadeTime<<"s";
}

void  SoundManager::fadeTube(float fromVolume, float toVolume, float fadeTime)
{
    if(!m_tube)
    {
        return;
    }
    
    AppManager::getInstance().getSoundEffectsManager().removeAllSoundEffects(*m_tube);
    FadeSound* fade = new FadeSound(*m_tube);
    fade->setParameters(fromVolume, toVolume, fadeTime);
    fade->start();
    
    
    std::cout <<m_dateManager->getTime()<<"- SoundManager-> fade tube from" << fromVolume <<" to "<<toVolume<<  " in "<< fadeTime<<"s"<<std::endl;
    //ofLogNotice() <<m_dateManager->getTime()<<"- SoundManager-> fade tube from" << fromVolume << " to "<<toVolume<<  " in "<< fadeTime<<"s";
    
}


void  SoundManager::fadeSample(float volume, float fadeTime)
{
    if(!m_currentSample || !m_currentSample->isPlaying())
    {
        return; 
    }
    
    AppManager::getInstance().getViewManager().fadeVisual(*m_sampleText,volume*255, 3);
    AppManager::getInstance().getSoundEffectsManager().removeAllSoundEffects(*m_currentSample);
    
    FadeSound* fade = new FadeSound(*m_currentSample);
    fade->setParameters(volume, fadeTime);
    fade->start();
    
    std::cout <<m_dateManager->getTime()<<"- SoundManager-> sample tube to "<<volume<< " in "<< fadeTime<<"s"<<std::endl;
    //ofLogNotice() <<m_dateManager->getTime()<<"- SoundManager-> sample tube to "<<volume<< " in "<< fadeTime<<"s";
    
}

void  SoundManager::fadeSample(float fromVolume, float toVolume, float fadeTime)
{
    if(!m_currentSample || !m_currentSample->isPlaying())
    {
        return; 
    }
    
    AppManager::getInstance().getViewManager().fadeVisual(*m_sampleText, toVolume*255, 3);
    AppManager::getInstance().getSoundEffectsManager().removeAllSoundEffects(*m_currentSample);

    FadeSound* fade = new FadeSound(*m_currentSample);
    fade->setParameters(fromVolume, toVolume, fadeTime);
    fade->start();
    
    
    std::cout <<m_dateManager->getTime()<<"- SoundManager-> fade sample from" << fromVolume <<" to "<<toVolume<<  " in "<< fadeTime<<"s"<<std::endl;
    //ofLogNotice() <<m_dateManager->getTime()<<"- SoundManager-> fade sample from" << fromVolume << " to "<<toVolume<<  " in "<< fadeTime<<"s";}
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
    
    else if(name=="SENSOR")
    {
        if(event.getValue() == 0.0)
        {
            m_playSamples = false;
        }
    }
    
    else if(name=="WIN" || name=="SUM" ||name=="FAL" ||name=="SPR")
    {
        if(m_season!=name)
        {
            m_season = name;
            this->setCurrentSamples(m_season+ "_" + m_category);
        }
    }
    
    else if(name== "DAY" || name=="NIG" || name=="DSK" || name== "DWN")
    {
        if(m_category!=name)
        {
            m_category = name;
            this->setCurrentSamples(m_season+ "_" + m_category);
        }
        
    }

}






