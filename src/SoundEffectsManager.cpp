//
//  SoundEffectsManager.cpp
//  HearingView
//
//  Created by Imanolgo on 6/24/12.
//

#include "SoundEffectsManager.h"
#include "SoundEffects.h"

SoundEffectsManager::SoundEffectsManager()
{
	// intentionally left empty
}


SoundEffectsManager::~SoundEffectsManager()
{
	for ( unsigned int i = 0; i < m_soundEffects.size(); i++ ) {
        delete m_soundEffects[i];
    }
	m_soundEffects.clear();
}


void SoundEffectsManager::update(double dt)
{
	for ( unsigned int i = 0; i < m_soundEffects.size(); i++ ) {
		m_soundEffects[i]->update(dt);
    }
}

void SoundEffectsManager::addSoundEffect(SoundEffect& soundEffect) 
{
	for(SoundEffectVector::iterator it = m_soundEffects.begin(); it != m_soundEffects.end();) {
		if(*it == &soundEffect) {
			return;
		}		
	}
	m_soundEffects.push_back(&soundEffect);
}

void SoundEffectsManager::removeSoundEffect(SoundEffect& soundEffect) 
{
	for(SoundEffectVector::iterator it = m_soundEffects.begin(); it != m_soundEffects.end();) {
		if(*it == &soundEffect) {
			delete *it; 
			it = m_soundEffects.erase(it);
		}		
	}
}

void SoundEffectsManager::removeAllSoundEffects(const SoundObject& sound) 
{
	for(SoundEffectVector::iterator it = m_soundEffects.begin(); it != m_soundEffects.end();) {
		if(&(*it)->getSound() == &sound) {
			delete * it; 
			it = m_soundEffects.erase(it);	
		}
		else {
			++it;
		}		
	}
}





