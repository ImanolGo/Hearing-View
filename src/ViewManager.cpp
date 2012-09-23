//
//  ViewManager.cpp
//  HearingView
//
//  Created by Imanolgo on 05/07/12.
//

#include "ofMain.h"
#include "Visuals.h"
#include "ViewManager.h"



ViewManager::ViewManager()
{
	// intentionally left empty
}

ViewManager::~ViewManager()
{
    
	VisualList::iterator it = m_visuals.begin();
	while(!m_visuals.empty()) {
		const Visual* visual = it->second;
		it = m_visuals.erase(it);
		delete visual;
		visual = NULL;
	}
    
	m_visuals.clear();
}


void ViewManager::setup()
{
     std::cout<< "StateManager-> initialized "<<std::endl;
}


void ViewManager::draw() const
{
    for(VisualList::const_reverse_iterator it = m_visuals.rbegin(); it != m_visuals.rend(); it++) {	
		glPushMatrix();
		it->second->draw();
		glPopMatrix();
	}
}

void ViewManager::addVisual(const Visual& visual,int zOrder)
{
	m_visuals.push_back(Overlay(zOrder,&visual));
	m_visuals.sort();
}

void ViewManager::removeVisual(const Visual& visual)
{
	for(VisualList::iterator it = m_visuals.begin(); it != m_visuals.end(); ) {
		if(it->second == &visual) {
			it = m_visuals.erase(it);
		}
		else {
			++it;
		}
	}
}