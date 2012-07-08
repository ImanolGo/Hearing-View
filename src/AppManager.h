/*==============================================================================
 Imanolgo on 6/26/12.
 ==============================================================================*/
/*! \file AppManager.h
 * \authors Imanol Gómez
 * \copyright{2012}
 *///============================================================================


#ifndef __APP_MANAGER_H__
#define __APP_MANAGER_H__

#include <vector>
#include <map>
#include <string>


class ofxUICanvas;
class StateManager;
class ViewManager;
class SoundManager;
class DateManager;
class WeatherManager;
class SoundEffectsManager;
class VisualEffectsManager;

//========================== class AppManager ==============================
//============================================================================
/** \class AppManager AppManager.h
 *	\brief Class managing the whole application
 *	\details it setups all the different managers used for the application
 */

class AppManager
{
public:
    
    //! Constructor
    AppManager();
    
    //! Destructor
    ~AppManager();
    
    //! Returns the singleton instance.
    static AppManager& getInstance();
    
    //! Compares two transition objects
    void setup();
    
    //! updates the logic
    void update(double dt);

    //! calls the view manager to draw
    void draw();
    
    //! Returns the gui
    ofxUICanvas& getGUI() { return *m_gui; }
    
    //! Returns the soundEffectsManager
    SoundEffectsManager& getSoundEffectsManager() { return *m_soundEffectsManager; }
    
    //! Returns the soundEffectsManager
    VisualEffectsManager& getVisualEffectsManager() { return *m_visualEffectsManager; }
    
    //! Returns  a reference to the sound manager
    SoundManager& getSoundManager() const { return *m_soundManager; }
    
    //! Returns  a reference to the weather manager
    WeatherManager& getWeatherManager() const { return *m_weatherManager; }
    
    //! Returns  a reference to the date manager
    DateManager& getDateManager() const { return *m_dateManager; }

    
    //==========================================================================
    
private:
    
    //! Prevent copy constructor being generated.
    AppManager(const AppManager&);
    
    //! Prevent operator= being generated.
    const AppManager& operator=(const AppManager&);

    //!  Setups the GUI
    void setupGUI();
    
    static AppManager*      m_instance;             ///< singleton instance
    
    ofxUICanvas*            m_gui;                  ///< the gui and event manager
    StateManager*           m_stateManager;         ///< the state machine under the logic
    ViewManager*            m_viewManager;          ///< manages and renders all visuals
    SoundManager*           m_soundManager;         ///< manages and plays all sounds
    WeatherManager*         m_weatherManager;       ///< manages the weather conditions
    DateManager*            m_dateManager;          ///< manages the date and the seasons
    SoundEffectsManager*    m_soundEffectsManager;  ///< manages all the sound effects
    VisualEffectsManager*   m_visualEffectsManager; ///< manages all the visual effects
    
};

//==========================================================================

#endif

