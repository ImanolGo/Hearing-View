/*==============================================================================
 Imanolgo on 23/09/12.
 ==============================================================================*/
/*! \file GuiManager.h
 * \authors Imanol Gómez
 * \copyright{2012}
 *///============================================================================


#ifndef __GUI_MANAGER_H__
#define __GUI_MANAGER_H__

class ofxUIEventArgs;
class ofxUICanvas;
class EventManager;
class Event;
class DateManager;

//========================== class GuiManager ==============================
//============================================================================
/** \class GuiManager GuiManager.h
 *	\brief Manages the GUI and its events
 *	\details It creates the GUI and sends its events to the EventManager
 */


class GuiManager
{
public:
    
    //! Constructor
    GuiManager();
    
    //! Destructor
    ~GuiManager();
    
    //! Setups the GUI
    void setup();
    
    //! updates the GUI 
    void update(double dt);
    
    //! handles the events adjusting the gui values
    void handleEvent(const Event& event);
    
private:
    
    //! interface with the GUI events
    void guiEvent(ofxUIEventArgs &e);
    
private:
    
    EventManager*	  m_eventManager;	///< pointer to the event manager
    ofxUICanvas*      m_gui;            ///< pointer to the gui
    DateManager*          m_dateManager;        ///< pointer to the date manager
    
};

#endif

