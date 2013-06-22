//
//  SoundManager.cpp
//  HearingView
//
//  Created by Imanolgo on 6/24/12.
//

#include "ofMain.h"

#include "DateManager.h"
#include "SoundManager.h"
#include "StateManager.h"
#include "WeatherStationManager.h"
#include "SoundObject.h"
#include "AppManager.h"
#include "EventManager.h"
#include "Event.h"
#include "Visuals.h"
#include "ViewManager.h"
#include "SoundEffectsManager.h"
#include "VisualEffectsManager.h"
#include "SoundEffects.h"

const int SoundManager::MAX_NUM_SAMPLES = 5;
    
SoundManager::SoundManager(): 
    m_tube(NULL), 
    m_playExpert(false),
    m_currentSample(NULL),
    m_dateManager(NULL),
    m_soundVisual(NULL),
    m_sampleName(NULL),
    m_numPlayedSamples(0),
    m_season(" "),
    m_category(" "),
    m_W(50),m_T(0),m_R(0.5),m_S(500),
    m_masterSampleVolume(0.0f),
    m_sampleTimer(0.0),
    m_elapsedTime(0.0)
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
    
    if (m_sampleName) {
        AppManager::getInstance().getVisualEffectsManager().removeAllVisualEffects(*m_sampleName);
        AppManager::getInstance().getViewManager().removeVisual(*m_sampleName);
        delete m_sampleName;
        m_sampleName = NULL;
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
    m_stateManager = &AppManager::getInstance().getStateManager();
    m_weatherStationManager = &AppManager::getInstance().getWeatherStationManager();
    m_playExpert = false;
    
    m_tube = new SoundObject("tube");
    m_tube->loadSound("sounds/tube.wav");
    m_tube->setVolume(0.0f);
    m_tube->setLoop(true);
    //m_tube->play();
    this->loadSamples();
    
    float margin = ofGetHeight()/70;
    float widthGUI = ofGetWidth()- 4*margin; 
    float heightGUI = ofGetHeight()/3.0 - 4*margin;
    float w = widthGUI/4 - 2*margin;
    float h = heightGUI - 4*margin;
    float x = 10*margin + 3*w;
    float y = 4*margin + heightGUI*0.5 + heightGUI;

    m_soundVisual = new SoundVisual(*m_currentSample,ofPoint(500,1000),5,50);
    AppManager::getInstance().getViewManager().addVisual(*m_soundVisual);
    
    m_sampleName = new TextVisual(ofPoint(x,y),w,h);
    m_sampleName->setColor(ofColor(255,255,255));
    AppManager::getInstance().getViewManager().addVisual(*m_sampleName);
    
    std::cout<< m_dateManager->getTime() << "- SoundManager-> play tube "<<std::endl;
    std::cout<<  m_dateManager->getTime() << "- SoundManager-> initialized "<<std::endl;
    ofLogNotice() << m_dateManager->getTime() << "- SoundManager-> play tube ";
    ofLogNotice() << m_dateManager->getTime() << "- SoundManager-> initialized ";

}

void SoundManager::start()
{
    m_tube->setVolume(0.0f);
}

void SoundManager::loadSamples()
{
    //some path, may be absolute or relative to bin/data
    int numSeasons = 4;
    int numCategories = 5;

    std::string seasons[4] = {"SUM","FAL","WIN","SPR"};
    std::string category[5] = {"DWN","DAY","DSK","EXP","NIG"};
    
    
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


bool SoundManager::setCurrentSamples(std::string sampleListName)
{
    m_numPlayedSamples = 0;
    m_currentSampleList.clear();
    
    if(m_samples.find(sampleListName) == m_samples.end())
    {
        std::cout <<m_dateManager->getTime()<<"- SoundManager-> setSamples: no sample list with name \""<< sampleListName <<"\"" << std::endl;
        ofLogNotice() <<m_dateManager->getTime()<<"- SoundManager-> setSamples: no sample list with name \""<< sampleListName <<"\"" ;
        return false;
    }
    
    
    //m_currentSampleList = m_samples[sampleListName];
    m_currentSampleList = m_samples.find(sampleListName)->second;
    
    std::cout <<m_dateManager->getTime()<<"- SoundManager-> setSamples: playing samples from \""<< sampleListName <<"\"" << std::endl;
    ofLogNotice() <<m_dateManager->getTime()<<"- SoundManager-> setSamples: playing samples from \""<< sampleListName <<"\"" ;

    return true;
}

bool SoundManager::fitsPlayConditions(const SoundObject& sample)
{
    string conditions = ofSplitString(sample.getName(), "_").back();
   
    if(ofIsStringInString(conditions, "W"))
    {
        if (m_weatherStationManager->getWindSpeed() >= m_W) {
            return false;
        }
    }
    
    if(ofIsStringInString(conditions, "R"))
    {
        if (m_weatherStationManager->getWetness() >= m_R) {
            return false;
        }
    }
    
    if(ofIsStringInString(conditions, "T"))
    {
        if (m_weatherStationManager->getTemperature() <= m_T) {
            return false;
        }
    }

    if(ofIsStringInString(conditions, "S"))
    {
        if (m_weatherStationManager->getInsolation() <= m_S) {
            return false;
        }
    }
    
    return true;
}

void SoundManager::playNextSample(float volume)
{
    m_masterSampleVolume = volume;
    
    if (m_playExpert) {
        this->playExpertSample();
        return;
    }
    else 
    {
        this->playRandomSample();
        return;
    }

    
}

void SoundManager::playExpertSample()
{
    string sampleListName = m_season + "_EXP";
    
    if(!this->setCurrentSamples(sampleListName)){
        std::cout <<m_dateManager->getTime()<<"- SoundManager-> No expert expert samples in " << sampleListName << std::endl;
        AppManager::getInstance().getEventManager().setTimedEvent("END_ALL_SAMPLES", m_stateManager->m_t5);
    }
    
    int n = 0;
    int i = rand()%m_currentSampleList.size();
    while (n<m_currentSampleList.size()) {
        if (fitsPlayConditions(*m_currentSampleList[i])) {
            m_currentSample = m_currentSampleList[i];
            
            m_currentSample->play();
            AppManager::getInstance().getEventManager().setEvent(Event("SAMPLE VOLUME", m_masterSampleVolume));
            std::string sampleText = "Expert Sample:\n" +m_currentSample->getName();
            m_sampleName->setText(sampleText,"Klavika-BoldItalic.otf", 10);
            m_sampleName->setColor(ofColor(255,255,255,255));
            
            std::cout <<m_dateManager->getTime()<<"- SoundManager-> play expert sample \""<< m_currentSample->getName() <<"\"" << std::endl;
            ofLogNotice() <<m_dateManager->getTime()<<"- SoundManager-> play expert sample  \""<< m_currentSample->getName() <<"\"" ;
            return;
        }
        else{
            std::cout <<m_dateManager->getTime()<<"- SoundManager-> playExpertSample: sample \""<< m_currentSampleList[i]->getName() <<"\" excluded" << std::endl;
            ofLogNotice() <<m_dateManager->getTime()<<"- SoundManager-> playExpertSample: samples \""<< m_currentSampleList[i]->getName() <<"\" excluded" ;
        }
            
        i = (i+1)%m_currentSampleList.size();
        n++;
    }
    
    this->resetSamples();
    AppManager::getInstance().getEventManager().setTimedEvent("END_ALL_SAMPLES", m_stateManager->m_t5);
}

void SoundManager::playRandomSample()
{
    int n = 0;
    if(m_currentSampleList.empty()){
         std::cout <<m_dateManager->getTime()<<"- SoundManager-> Random samples list empty. Next sample expert " << std::endl;
        m_playExpert = true;
        this->playExpertSample();
        return;
    }
    
    if(m_numPlayedSamples >= MAX_NUM_SAMPLES){
        m_playExpert = true;
        this->playExpertSample();
        return;
    }
    int i = rand()%m_currentSampleList.size();
    while (n<m_currentSampleList.size()) {
        if (fitsPlayConditions(*m_currentSampleList[i])) {
            std::cout << n << std::endl;
            m_currentSample = m_currentSampleList[i];
            m_currentSampleList.erase(m_currentSampleList.begin()+i);
            m_numPlayedSamples++;
            
            m_currentSample->play();
            AppManager::getInstance().getEventManager().setEvent(Event("SAMPLE VOLUME", m_masterSampleVolume));
            std::string sampleText = "Random Sample " + ofToString(m_numPlayedSamples) + ":\n" +m_currentSample->getName();
            m_sampleName->setText(sampleText,"Klavika-BoldItalic.otf", 10);
            m_sampleName->setColor(ofColor(255,255,255,255));

            std::cout <<m_dateManager->getTime()<<"- SoundManager-> play random sample " << m_numPlayedSamples << " \""<< m_currentSample->getName() <<"\"" << std::endl;
            ofLogNotice() <<m_dateManager->getTime()<<"- SoundManager-> play random sample " << m_numPlayedSamples << " \""<< m_currentSample->getName() <<"\"" ;
    
            return;
        }
        else{
            std::cout <<m_dateManager->getTime()<<"- SoundManager-> playRandomSample: sample \""<< m_currentSampleList[i]->getName() <<"\" excluded" << std::endl;
            ofLogNotice() <<m_dateManager->getTime()<<"- SoundManager-> playRandomSample: samples \""<< m_currentSampleList[i]->getName() <<"\" excluded" ;
        }
        i = (i+1)%m_currentSampleList.size();
        
        n++;
    }
    
    m_playExpert = true;
    this->playExpertSample();
}

void SoundManager::stopSamples()
{
    m_currentSample->stop();
    std::cout <<m_dateManager->getTime()<<"- SoundManager-> stop sample \""<< m_currentSample->getName() <<"\"" << std::endl;
    ofLogNotice() <<m_dateManager->getTime()<<"- SoundManager-> stop sample \""<< m_currentSample->getName() <<"\"";
}

void SoundManager::resetSamples()
{
    AppManager::getInstance().getVisualEffectsManager().removeAllVisualEffects(*m_sampleName);
    AppManager::getInstance().getViewManager().fadeVisual(*m_sampleName,0.0, 2);
    
    m_currentSample = NULL;
    m_playExpert = false;
    this->setCurrentSamples(m_season+ "_" + m_category);
    std::cout <<m_dateManager->getTime()<<"- SoundManager-> resetSamples: "<< m_season+ "_" + m_category<< std::endl;
    ofLogNotice() <<m_dateManager->getTime()<<"- SoundManager-> resetSamples: "<< m_season+ "_" + m_category ;
    
     std::cout <<m_dateManager->getTime()<<"- SoundManager-> playing samples from " << m_season << "_" << m_category << std::endl;
    
}


//--------------------------------------------------------------
void SoundManager::update(double dt)
{
    ofSoundUpdate();
    
    if(!m_currentSample)
    {
        return;
    }
    
    
    if(!m_currentSample->isPlaying())
    {
        if (m_playExpert) {
            this->resetSamples();
            AppManager::getInstance().getEventManager().setTimedEvent("END_ALL_SAMPLES", m_stateManager->m_t5);
        }
        
        else{
            AppManager::getInstance().getVisualEffectsManager().removeAllVisualEffects(*m_sampleName);
            AppManager::getInstance().getViewManager().fadeVisual(*m_sampleName, 0, m_stateManager->m_t5);
            AppManager::getInstance().getEventManager().setTimedEvent("END_SAMPLE", m_stateManager->m_t5);
            m_currentSample = NULL;
        }
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

     std::cout <<m_dateManager->getTime()<<"- SoundManager-> fade tube from " << m_tube->getVolume() <<" to "<<volume<<  " in "<< fadeTime<<"s"<<std::endl;
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
    
    
    std::cout <<m_dateManager->getTime()<<"- SoundManager-> fade tube from " << fromVolume <<" to "<<toVolume<<  " in "<< fadeTime<<"s"<<std::endl;
    //ofLogNotice() <<m_dateManager->getTime()<<"- SoundManager-> fade tube from" << fromVolume << " to "<<toVolume<<  " in "<< fadeTime<<"s";
    
}


void  SoundManager::fadeSample(float volume, float fadeTime)
{
    if(!m_currentSample || !m_currentSample->isPlaying())
    {
        return; 
    }
    
    float alpha = 255;
    if (volume == 0.0f) {
        alpha = 0.0f;
    }
    AppManager::getInstance().getVisualEffectsManager().removeAllVisualEffects(*m_sampleName);
    AppManager::getInstance().getViewManager().fadeVisual(*m_sampleName,alpha, fadeTime);
    
    
    AppManager::getInstance().getSoundEffectsManager().removeAllSoundEffects(*m_currentSample);
    FadeSound* fade = new FadeSound(*m_currentSample);
    fade->setParameters(volume, fadeTime);
    fade->start();
    
    std::cout <<m_dateManager->getTime()<<"- SoundManager-> fade tube from " << m_currentSample->getVolume() <<" to "<<volume<<  " in "<< fadeTime<<"s"<<std::endl;
   
    //ofLogNotice() <<m_dateManager->getTime()<<"- SoundManager-> sample tube to "<<volume<< " in "<< fadeTime<<"s";
    
}

void  SoundManager::fadeSample(float fromVolume, float toVolume, float fadeTime)
{
    if(!m_currentSample || !m_currentSample->isPlaying())
    {
        return; 
    }
    
    float alpha = 255;
    if (toVolume == 0.0f) {
        alpha = 0.0f;
    }
    AppManager::getInstance().getVisualEffectsManager().removeAllVisualEffects(*m_sampleName);
    AppManager::getInstance().getViewManager().fadeVisual(*m_sampleName,alpha, fadeTime);

    AppManager::getInstance().getSoundEffectsManager().removeAllSoundEffects(*m_currentSample);
    FadeSound* fade = new FadeSound(*m_currentSample);
    fade->setParameters(fromVolume, toVolume, fadeTime);
    fade->start();
    
    
    std::cout <<m_dateManager->getTime()<<"- SoundManager-> fade sample from " << fromVolume <<" to "<<toVolume<<  " in "<< fadeTime<<"s"<<std::endl;
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
            m_masterSampleVolume = m_currentSample->getVolume();
        }
    }
    
    
    else if(name=="WIN" || name=="SUM" ||name=="FAL" ||name=="SPR")
    {
        if(m_season!=name)
        {
            m_season = name;
            this->resetSamples();
        }
    }
    
    else if(name== "DAY" || name=="NIG" || name=="DSK" || name== "DWN")
    {
        if(m_category!=name)
        {
            m_category = name;
            this->resetSamples();
        }
        
    }
    
    else if(name=="W (Km/h)"){
        m_W = (float) event.getValue();
        std::cout <<m_dateManager->getTime()<<"- SoundManager-> W = " << m_W <<" Km/h "<<std::endl;
        ofLogNotice() <<m_dateManager->getTime()<<"- SoundManager-> W = " << m_W <<" Km/h ";
    }
    else if(name=="T (°C)"){
        m_T= (float) event.getValue();
        std::cout <<m_dateManager->getTime()<<"- SoundManager-> T = " << m_T <<" °C"<<std::endl;
        ofLogNotice() <<m_dateManager->getTime()<<"- SoundManager-> T = " << m_T <<" °C ";
    }
    else if(name=="R (.)"){
        m_R = (float) event.getValue();
        std::cout <<m_dateManager->getTime()<<"- SoundManager-> R = " << m_R <<" "<<std::endl;
        ofLogNotice() <<m_dateManager->getTime()<<"- SoundManager-> R = " << m_R <<" ";
    }
    else if(name=="S (W/m2)"){
        m_S = (float) event.getValue();
        std::cout <<m_dateManager->getTime()<<"- SoundManager-> S = " << m_S <<" W/m2"<<std::endl;
        ofLogNotice() <<m_dateManager->getTime()<<"- SoundManager-> S = " << m_S <<" W/m2";
    }

}






