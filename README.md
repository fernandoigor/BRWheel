# BRWheel

#### Firmware BRWheel to Arduino Leonardo
 - Developing from the AI-Wave version ESP_WHEEL_0.3
 - Joystick FFB Wheel for replace Logitech G27 (maybe dead? :disappointed:)


 ##### **Check branch "*alfatest* ", it is most updated**
 ![#f03c15](https://placehold.it/15/f03c15/000000?text=+)![#f03c15](https://placehold.it/15/f03c15/000000?text=+)![#f03c15](https://placehold.it/15/f03c15/000000?text=+)![#f03c15](https://placehold.it/15/f03c15/000000?text=+)![#f03c15](https://placehold.it/15/f03c15/000000?text=+)![#f03c15](https://placehold.it/15/f03c15/000000?text=+)![#f03c15](https://placehold.it/15/f03c15/000000?text=+)![#f03c15](https://placehold.it/15/f03c15/000000?text=+)![#f03c15](https://placehold.it/15/f03c15/000000?text=+)![#f03c15](https://placehold.it/15/f03c15/000000?text=+)![#f03c15](https://placehold.it/15/f03c15/000000?text=+)![#f03c15](https://placehold.it/15/f03c15/000000?text=+)![#f03c15](https://placehold.it/15/f03c15/000000?text=+)![#f03c15](https://placehold.it/15/f03c15/000000?text=+)![#f03c15](https://placehold.it/15/f03c15/000000?text=+)![#f03c15](https://placehold.it/15/f03c15/000000?text=+)![#f03c15](https://placehold.it/15/f03c15/000000?text=+)![#f03c15](https://placehold.it/15/f03c15/000000?text=+)![#f03c15](https://placehold.it/15/f03c15/000000?text=+)![#f03c15](https://placehold.it/15/f03c15/000000?text=+)![#f03c15](https://placehold.it/15/f03c15/000000?text=+)![#f03c15](https://placehold.it/15/f03c15/000000?text=+)![#f03c15](https://placehold.it/15/f03c15/000000?text=+)![#f03c15](https://placehold.it/15/f03c15/000000?text=+)

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
 - Configuration profile with HID (v2) check BRWHeel-Profile
```

### Recommendations & Problems
__________________
#####  - Install the **Arduino Software** in the same project folder.
* To facilitate any updating of the core files with the project repository
```sh
/git-directory/arduino-1.0.5/[arduino.exe | *.dll | hardware/ | libraries/ ]
/git-directory/arduino-1.0.5/(project)[ hardware/ | libraries/ ]
/git-directory/brWheel/(project)[ * ]
```

___________________
##### - Visual Studio & Visual Micro
* I use Visual Studio Community 2017, is free and good.
* Visual Micro installed on the VS extensions panel.
* It better reports errors.

___________________
##### - If you use the standard Arduino IDE
* Erros like
```sh
error: stray '\' in program
error: stray '#' in program
```
IDE creates strange characters (i don't know why), but fix deleting or overwriting the lines.