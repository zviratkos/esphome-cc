# JS ESPHome custom components

### Components
- sencor_sacmt12 - Old air conditioner Sencor SAC MT12 IR remote control for climate entity in ESPHome
- touch_sensor - Capacitance sensor for measurement of water level using pair of simple copper tape
- gdey042z98 - Driver for LaskaKit GDEY042Z98 4.2 https://www.laskakit.cz/en/laskakit-espink-42-esp32-e-paper-pcb-antenna/

## gdey042z98

```
esp32:
  board: esp32-s3-devkitc-1          # upravte dle vaší desky
  framework:
    type: arduino

#external_components:

external_components:
  - source:
      type: git
      url: https://github.com/zviratkos/esphome-cc
      ref: main
    components: [gdey042z98]
```

### License MIT
