# BananaPlayer Firmware

## File Structure
```
src/
├── input/
│   ├── input.c
│   ├── input.h
│   ├── input_esp32.c
│   ├── input_simulator.c
│   ├── encoder.c
│   ├── mt6701.c
│   └── buttons.c
│
├── navigation/
│   ├── navigation.c
│   └── navigation.h
│
├── system/
│   ├── system.c
│   ├── system.h
│   ├── inactivity.c
│   ├── power.c
│   └── device_lock.c
│
├── player/
│   ├── player.c
│   ├── player.h
│   ├── playback.c
│   ├── volume.c
│   └── scrubbing.c
│
└── ui/
    ├── ui.c
    ├── ui_menu.c
    ├── ui_home.c
    ├── ui_music.c
    └── ui_settings.c
```

#### Responsibilities

|Component|Responsibility|
|---|---|
|Input|Detects physical and simulated inputs|
|Navigation|Translates inputs into UI navigation actions|
|System|Handles locking, power, sleep, WiFi, and device-wide operations|
|Player|Handles music playback, volume, seeking, and tracks|
|UI|Displays menus, screens, animations, and other interface elements|

### 1.1 Input Events
```
INPUT_KNOB_ROTATE_CW
INPUT_KNOB_ROTATE_CCW
INPUT_KNOB_PRESS
INPUT_KNOB_HOLD
INPUT_KNOB_FORCE_PRESS

INPUT_MIDDLE_BTN
INPUT_LEFT_BTN
INPUT_RIGHT_BTN
INPUT_LOCK_BTN
```
### 1.2 Navigation Actions
```
typedef enum {
    NAV_UP,
    NAV_DOWN,
    NAV_ENTER,
    NAV_BACK,
    NAV_OPEN_CONTROL_CENTER
} nav_action_t;
```

Example:

- Encoder Push (Magnitude) → `NAV_ENTER`
    
- Encoder Long Push → `NAV_BACK`
    
- Encoder Firm Push → `NAV_CONTROL_CENTER`
    
- Keyboard Escape → `NAV_BACK`
    
- Encoder clockwise → `NAV_DOWN`
    
- Encoder counterclockwise → `NAV_UP`
    

### 1.3 Player Actions
```
typedef enum {
    PLAYER_TOGGLE_PLAYBACK,
    PLAYER_PLAY,
    PLAYER_PAUSE,

    PLAYER_NEXT_TRACK,
    PLAYER_PREVIOUS_TRACK,

    PLAYER_VOLUME_UP,
    PLAYER_VOLUME_DOWN,

    PLAYER_ENTER_SCRUB,
    PLAYER_COMMIT_SCRUB
} player_action_t;
```

### 1.4 System Actions

System actions can be triggered by buttons, timers, menus, or other system components.
```
typedef enum {
    SYSTEM_LOCK,
    SYSTEM_UNLOCK,

    SYSTEM_DISPLAY_ON,
    SYSTEM_DISPLAY_OFF,

    SYSTEM_LIGHT_SLEEP,
    SYSTEM_DEEP_SLEEP,
    SYSTEM_WAKE,

    SYSTEM_WIFI_ENABLE,
    SYSTEM_WIFI_DISABLE,

    SYSTEM_RESTART
} system_action_t;
```

Example implementation:
```
system_execute(SYSTEM_LOCK);
```

The same action can be triggered by multiple sources:

| Trigger              | Action        |
| -------------------- | ------------- |
| Physical lock button | `SYSTEM_LOCK` |
| Inactivity timer     | `SYSTEM_LOCK` |
| Control Center       | `SYSTEM_LOCK` |
