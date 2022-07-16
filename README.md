# 2bit PXLR Studio
![2bit PXLR Studio Logo](assets/2bitpxlr.png "Mitsubishi M64282FP artificial retina")

**2bit PXLR Studio** is a custom ROM ("firmware") for the Game Boy Camera targeted on accessing the full potential of the original Game Boy Camera's sensor, as well as giving photographers more control.   
It is meant to be used with [HDR's flashable Game Boy Camera PCB](https://github.com/HDR/Gameboy-Camera-Flashcart).   
For convenience there's also a [itch.io page](https://herrzatacke.itch.io/2bit-pxlr-studio).  
You can also tag your images with [#2bitpxlr](https://www.instagram.com/explore/tags/2bitpxlr/) or use the hashtag [#2bitpxlr](https://twitter.com/search?q=2bitpxlr) on Twitter.  

## Current features:
+ Most settings of the camera's sensor are already configurable
+ Images can be saved, deleted and printed
+ Sensor settings are being saved across restarts. To reset hold `start`+`select` on boot

# Feedback
**Remember: I can only improve things I know about!!**  
If you have actually used this ROM any type of feedback is very much appreciated. Please provide any feedback [via the issues](https://github.com/HerrZatacke/custom-camera-rom/issues).  
Feedback includes but is not restricted to things like:
+ "I'd like to have feature XX"
+ "I've used the following combination of parameters which work really well/bad"
+ "When I set param XX, I'd also like param YY to change"

# User Manual
The Mitsubishi M64282FP artificial retina is a one of the first mass produced CMOS light sensor. This kind of sensor is known for its good behavior in low light conditions and low power consumption. Basically each pixel of the sensor converts the quantity of photons received during an exposure time into a voltage. The sensor is able to perform some basic arithmetics on the voltage values before transfering them to a analog output (inversion, offsetting, 2D operations, multiplication, etc.). This sensor contains 128*128 pixels but only 123 lines returns image information as the first 5 lines are just composed of masked pixels uses to calibrate the dark response. The sensor documentation is notorious for being unreadable and some informations are deduced from the much better documentation of the Mitsubishi M64283FP sensor which is an upgrade.

The rom addresses the sensor in two ways:
- In **Assisted Mode**, the 2bit PXLR Studio rom mimics the behavior of the Game Boy Camera, it modifies only the **Exposure time, gain and output reference voltage. All other parameters used are fixed**
- In **Manual Mode**, the 2bit PXLR Studio rom allows modifying all the parameters (or registers) of the sensor. This could lead to unexpected results as certain parameters configuration are not expected to give a clear image.

# Effect of parameters
- The **exposure time** is the time each pixel of the sensor will receive photons and convert the integral photon quantity to voltage. The longer the exposure time, the higher the output voltage, the higher the signal to noise ratio, but the higher the motion blur. Sensor can saturate for too long exposure time/too high flux of photons. This sensor allows exposure time from 16 µseconds to 1.044 seconds. Exposure times below 256 µseconds lead to strong vertical artifacts. Using varying exposure time creates vertical (low exposure times) and horizontal (high exposure times) artifacts which are intrinsic to the sensor. The total voltage range between dark and saturated sensor is about 2 volts.
- The **gain** is a multiplier applied between the quantity of photons received and the output voltage. To make an analogy with film camera, gain is similar to the ISOs of the sensor. However calculating the real corresponding ISOs for each gain value is out of reach with the current documentation of the sensor. Like film cameras, high gains (ISOs) and low exposure times gives noisy images, low gains (ISOs) and high exposure times gives smooth images. The gain used in the Game Boy camera rom varies very little compared to what the sensor is able to in Manual Mode.
- The **Output reference voltage** is a fine bias applied to the output pin. It allows increasing the sensor dynamic. Basically this voltage should exactly compensate the voltage reading of dark pixels so that the sensor output is 0 volts in total darkness. 
- The **Voltage reference** or **Output node bias voltage** is a crude voltage bias applied to the output. It is not modified by the Game Boy Camera. It typically allows to have a match between the min/max output voltage and the min/max input voltage allowed by the external ADC converter used with the sensor. The M64282FP is able to automatically set the the voltage reading of dark pixels at the **Voltage reference** via the register Z.


# Building / Setup
This project has been created with [GBDK 2020](https://github.com/gbdk-2020/gbdk-2020).  
This project requires an environment variable `GBDK_FOLDER="..."` pointing to the folder of GBDK  
E.g. on wsl for windows add `export GBDK_FOLDER="/mnt/c/path_to_gbdk"` to your `.bashrc`

# Credits
Thanks to the following people for direct and indirect help with this project:
* [Toxa](https://github.com/untoxa) for a lot of help while refactoring, and for the GBDK in general. 
* [@rembrandx](https://www.instagram.com/rembrandx/) for the Logo/Splashcreen 
* [Raphaël Boichot](https://github.com/Raphael-Boichot/) for the in-depth analysis of the [Game Boy Camera's RAM structure](https://funtography.online/wiki/Cartridge_RAM)
* [AntonioND](https://github.com/AntonioND) for the outstanding [Documentation regarding the camera's sensor](https://github.com/AntonioND/gbcam-rev-engineer) / [PDF](https://github.com/AntonioND/gbcam-rev-engineer/blob/master/doc/gb_camera_doc_v1_1_1.pdf)
* [reini1305](https://github.com/reini1305) for the [print function](https://github.com/HerrZatacke/custom-camera-rom/commit/5976b47e6b6d577c954e2b678affa9925824f5b5) and general help with some C concepts
* [Alex (insidegadgets)](https://github.com/insidegadgets) for figuring out the flickering issue and more
* [All the folks from Game Boy Gamera Club Discord](https://discord.gg/C7WFJHG) for their support and ideas

# Other resources
- Mitsubishi [Sensor Datasheet](https://pdf1.alldatasheet.com/datasheet-pdf/view/146598/MITSUBISHI/M64282FP.html)

# Contributing
_This project is very much a work in progress._  
Join the [Game Boy Gamera Club Discord](https://discord.gg/C7WFJHG) for discussions in detail. And feel free to check and add to [this project's issues](https://github.com/HerrZatacke/custom-camera-rom/issues)

# License
This project is released under the [MIT License](LICENSE)
