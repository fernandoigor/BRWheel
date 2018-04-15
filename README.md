# BRWheel
#### Firmware BRWheel to Arduino Leonardo
 - Developing from the AI-Wave version ESP_WHEEL_0.3
 - Joystick FFB Wheel for replace Logitech G27 (maybe dead? :disappointed:)

> Master branch
> Current version: 0.5

```sh
 - 500 Hz update rate (USB & FFB)
 - 2-Channels encoder and auto calibration side-by-side
 - Inputs Shift-register (Used in G27 - 74HC165)
 - Reading average of the pedals (Filter)
```
 
 ##### Schematic
 ![pinout](https://github.com/fernandoigor/BRWheel/blob/master/BRWarduinoSchema.png)
 
> Alpha test branch
> Current version: 0.8

```sh
 - FFB (Added periodic effect type), working rFactor2
 - Turn (16bits), throttle,brake and clutch (8bits) and 32 Buttons (but 20 working with G27)
 - Configuration profile with HID (v2)
```