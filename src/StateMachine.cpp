//
//  SateMachine.cpp
//  HearingView
//
//  Created by Imanolgo on 6/24/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "StateMachine.h"
#include "States.h"


StateMachine::StateMachine():m_currentState(NULL)
{
}

StateMachine::~StateMachine()
{
	for(unsigned int i = 0; i < m_transitions.size(); ++i) {
		delete m_transitions[i];
	}
	m_transitions.clear();
    
	for(StateMap::iterator it = m_states.begin(); it != m_states.end(); ++it) {
		delete it->second;
	}
	m_states.clear();
	m_currentState = NULL;
}

const State* StateMachine::getState(std::string name) const
{
	StateMap::const_iterator it = m_states.find(name);
	if(it == m_states.end()) {
		return NULL;
	}
	return it->second;
}

void StateMachine::addState(State* state)
{
	if(!getState(state->getName())) {
		m_states[state->getName()] = state;
	}
}

bool StateMachine::addTransition(const Transition* transition)
{
	if(transition == NULL) {
		return false;
	}
	// check if an equal transition already exists
	// ---------------------------------------------
	for(unsigned int i = 0; i < m_transitions.size(); ++i) {
		if(*m_transitions[i] == *transition) {
            std::cout << "Unable to add Transition because an equal transition already exists!" << std::endl;
			delete transition;
			return false;
		}
	}
	// add the new created transition to the transition list
	m_transitions.push_back(transition);
	return true;
}

void StateMachine::createTransition(std::string postState, std::string event)
{
	// check if a state with specified postState name exist
	const State* toState = getState(postState);
	if(!toState) {
		std::cout << "Unable to add Transition because there is no state with name " << postState << std::endl;
		return;
	}
    
    // add the transition 
    this->addTransition(new Transition(*toState, event));

}

void StateMachine::createTransition(std::string preState, std::string postState, std::string event)
{
	// check if states with specified names exist
	const State* fromState = getState(preState);
	const State* toState = getState(postState);
    
	if(!fromState) {
        std::cout<< "Unable to add Transition because there is no state with name " << preState << std::endl;

		return;
	}
	if(!toState) {
		std::cout << "Unable to add Transition because there is no state with name " << postState << std::endl;
		return;
	}
	// add the transition 
    this->addTransition(new Transition(*fromState, *toState, event));
	
}



void StateMachine::setCurrentState(std::string name)
{
	m_currentState = const_cast<State*>(getState(name));
	if(!m_currentState) {
        std::cout<<"Unable to set current state, there is no state with name "<< name << std::endl;
		return;
	}
	m_currentState->onEnter();
}

void StateMachine::switchStateTo(const State& newState)
{
	if(m_currentState) {
		m_currentState->onExit();
	}
	setCurrentState(newState.getName());
}

void StateMachine::handleEvent(const std::string& event) 
{
	for(unsigned int i = 0; i < m_transitions.size(); ++i) {
		if(m_transitions[i]->getEventType() == event) {
			// switch if there is a transition from the current state to a new state 
			// OR if there is a NO-PreState transition (all states are potential PreStates)
			if(m_transitions[i]->getPreState() == m_currentState || m_transitions[i]->getPreState() == NULL) {
				switchStateTo(*m_transitions[i]->getPostState());
				return;
			}
		}
	}
}

