//
//  ViewManager.cpp
//  HearingView
//
//  Created by Imanolgo on 05/07/12.
//

#include "ofMain.h"
#include "Visuals.h"
#include "VisualEffectsManager.h"
#include "VisualEffects.h"
#include "ViewManager.h"
#include "DateManager.h"
#include "AppManager.h"



ViewManager::ViewManager(): m_dateManager(NULL)
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
    
    m_dateManager= NULL;
}


void ViewManager::setup()
{
    
     m_dateManager = &AppManager::getInstance().getDateManager();
     m_frameRateFont.loadFont("fonts/frabk.ttf", 14, true, true);
     
     std::cout << m_dateManager->getTime() << "- ViewManager-> initialized "<<std::endl;
     ofLogNotice() <<  m_dateManager->getTime() << "- ViewManager-> initialized ";
}

void ViewManager::update(double dt)
{
    //sprintf(m_fpsStr, "%f fps", dt);
}

void ViewManager::draw()
{
    for(VisualList::const_reverse_iterator it = m_visuals.rbegin(); it != m_visuals.rend(); it++) {	
		glPushMatrix();
		it->second->draw();
		glPopMatrix();
	}

    //m_frameRateFont.drawString(m_fpsStr, ofGetWidth() - 200,50);
}

void ViewManager::addVisual(const Visual& visual,int zOrder)
{
	m_visuals.push_back(Overlay(zOrder,&visual));
	m_visuals.sort();
}

void ViewManager::removeVisual(const Visual& visual)
{
	for(VisualList::iterator it = m_visuals.begin(); it != m_visuals.end();) {
		if(it->second == &visual) {
			it = m_visuals.erase(it);
		}
		else {
			++it;
		}
	}
}

//! fades an specific visual
void  ViewManager::fadeVisual(Visual& visual, float alpha, float fadeTime,  FadeType type)
{
    for(VisualList::iterator it = m_visuals.begin(); it != m_visuals.end();it++ ) {
		if(it->second == &visual) {
			AppManager::getInstance().getVisualEffectsManager().removeAllVisualEffects(visual);
            switch(type)
            {
                case LINEAR:
                {
                    FadeVisualLinear* fade = new FadeVisualLinear(visual);
                    fade->setParameters(visual.getAlpha(), alpha, fadeTime);
                    fade->start();
                    break;
                }
                case EXPONENTIAL:
                {
                    FadeVisualExp* fade = new FadeVisualExp(visual);
                    fade->setParameters(visual.getAlpha(), alpha, fadeTime);
                    fade->start();
                    break;
                }
                case LOGARITHMIC:
                {
                    FadeVisualLog* fade = new FadeVisualLog(visual);
                    fade->setParameters(visual.getAlpha(), alpha, fadeTime);
                    fade->start();
                    break;
                }
                default:
                {
                    FadeVisualLinear* fade = new FadeVisualLinear(visual);
                    fade->setParameters(visual.getAlpha(), alpha, fadeTime);
                    fade->start();
                    break;
                }
            }
            
            std::cout << m_dateManager->getTime() << "- ViewManager-> fade visual to "<<alpha<< " alpha value in "<< fadeTime<<"s"<<std::endl;
            ofLogNotice() << m_dateManager->getTime() << "- ViewManager-> fade visual to "<<alpha<< " alpha value in "<< fadeTime<<"s";
            break;
		}
    }
}
