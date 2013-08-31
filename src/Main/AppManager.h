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


class EventManager;
class GuiManager;
class StateManager;
class ViewManager;
class SoundManager;
class DateManager;
class WeatherManager;
class SoundEffectsManager;
class VisualEffectsManager;
class WeatherStationManager;
class SensorManager;

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
    
    //! Returns the event manager
    EventManager& getEventManager() { return *m_eventManager; }
    
    //! Returns the gui manager
    GuiManager& getGuiManager() { return *m_guiManager; }
    
    //! Returns the soundEffectsManager
    SoundEffectsManager& getSoundEffectsManager() { return *m_soundEffectsManager; }
    
    //! Returns the soundEffectsManager
    VisualEffectsManager& getVisualEffectsManager() { return *m_visualEffectsManager; }
    
    //! Returns the view manager
    ViewManager& getViewManager() { return *m_viewManager; }
    
    //! Returns  a reference to the StateManager
    StateManager& getStateManager() const { return *m_stateManager; }
    
    //! Returns  a reference to the sound manager
    SoundManager& getSoundManager() const { return *m_soundManager; }
    
    //! Returns  a reference to the weather manager
    WeatherManager& getWeatherManager() const { return *m_weatherManager; }
    
    //! Returns  a reference to the sensor manager
    SensorManager& getSensorManager() const { return *m_sensorManager; }
    
    //! Returns  a reference to the weather station manager
    WeatherStationManager& getWeatherStationManager() const { return *m_weatherStationManager; }
    
    //! Returns  a reference to the date manager
    DateManager& getDateManager() const { return *m_dateManager; }

    
    //==========================================================================
    
private:
    
    //! Prevent copy constructor being generated.
    AppManager(const AppManager&);
    
    //! Prevent operator= being generated.
    const AppManager& operator=(const AppManager&);

    static AppManager*      m_instance;             ///< singleton instance
    
    EventManager*           m_eventManager;         ///< manages all the events
    GuiManager*             m_guiManager;           ///< manages the GUI
    StateManager*           m_stateManager;         ///< the state machine under the logic
    ViewManager*            m_viewManager;          ///< manages and renders all visuals
    SoundManager*           m_soundManager;         ///< manages and plays all sounds
    WeatherManager*         m_weatherManager;       ///< manages the weather conditions
    WeatherStationManager*  m_weatherStationManager;   ///< manages the serial communication with the weather station
    SensorManager*          m_sensorManager;        ///< manages the serial communication with the Arduino and the sensor
    DateManager*            m_dateManager;          ///< manages the date and the seasons
    SoundEffectsManager*    m_soundEffectsManager;  ///< manages all the sound effects
    VisualEffectsManager*   m_visualEffectsManager; ///< manages all the visual effects
    
};

//==========================================================================

#endif

