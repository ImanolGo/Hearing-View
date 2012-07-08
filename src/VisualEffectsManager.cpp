//
//  VisualEffectsManager.cpp
//  HearingView
//
//  Created by Imanolgo on 6/24/12.
//


#include "VisualEffectsManager.h"
#include "VisualEffects.h"

VisualEffectsManager::VisualEffectsManager()
{
	// intentionally left empty
}


VisualEffectsManager::~VisualEffectsManager()
{
	for ( unsigned int i = 0; i < m_visualEffects.size(); i++ ) {
        delete m_visualEffects[i];
    }
	m_visualEffects.clear();
}


void VisualEffectsManager::update(double dt)
{
	for ( unsigned int i = 0; i < m_visualEffects.size(); i++ ) {
		m_visualEffects[i]->update(dt);
    }
}

void VisualEffectsManager::addVisualEffect(VisualEffect& visualEffect) 
{
	for(VisualEffectVector::iterator it = m_visualEffects.begin(); it != m_visualEffects.end();) {
		if(*it == &visualEffect) {
			return;
		}		
	}
	m_visualEffects.push_back(&visualEffect);
}

void VisualEffectsManager::removeVisualEffect(VisualEffect& visualEffect) 
{
	for(VisualEffectVector::iterator it = m_visualEffects.begin(); it != m_visualEffects.end();) {
		if(*it == &visualEffect) {
			delete *it; 
			it = m_visualEffects.erase(it);
		}		
	}
}

void VisualEffectsManager::removeAllVisualEffects(const ofImage& image) 
{
	for(VisualEffectVector::iterator it = m_visualEffects.begin(); it != m_visualEffects.end();) {
		if(&(*it)->getImage() == &image) {
			delete * it; 
			it = m_visualEffects.erase(it);	
		}
		else {
			++it;
		}		
	}
}





