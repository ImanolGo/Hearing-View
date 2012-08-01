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
		const Visual* visual = *it;
		it = m_visuals.erase(it);
		delete visual;
		visual = NULL;
	}
	m_visuals.clear();
    
}


void ViewManager::setup()
{
    
}


void ViewManager::draw() const
{
    for(VisualList::const_iterator it = m_visuals.begin(); it != m_visuals.end(); it++) {
			(*it)->draw();
	}
}

void ViewManager::addVisual(const Visual& visual)
{
	m_visuals.push_back(&visual);
}

void ViewManager::removeVisual(const Visual& visual)
{
	for(VisualList::iterator it = m_visuals.begin(); it != m_visuals.end(); ) {
		if(*it == &visual) {
			it = m_visuals.erase(it);
		}
		else {
			++it;
		}
	}
}