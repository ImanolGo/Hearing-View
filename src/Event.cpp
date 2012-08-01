//
//  Event.cpp
//  HearingView
//
//  Created by Imanolgo on 7/9/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "Event.h"
#include "AppManager.h"
#include "EventManager.h"

void TimedEvent::update(double dt)
{
    m_elapsedTime = m_elapsedTime + dt;
    if (m_elapsedTime>= m_delay) {
        AppManager::getInstance().getEventManager().triggerTimedEvent(*this);
    }
}
