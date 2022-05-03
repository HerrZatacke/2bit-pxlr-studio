# Custom Camera ROM
This project has been created with [GBDK 2020](https://github.com/gbdk-2020/gbdk-2020).  
It provides a custom ROM for [HDR's flashable Game Boy Camera](https://github.com/HDR/Gameboy-Camera-Flashcart) targeted on accessing the full potential of the sensor, as well as giving photographers more control.  

## Current features:
+ Most settings of the camera's sensor are already configurable:
  + Sensor gain
  + Exposure time
  + Dithering matrices
  + All edge enhancement settings
  + Output node bias voltage
  + Zero point calibration
  + Output reference voltage offset
+ Raw image data can be saved to the same positions where the original ROM stores it's data.

## Missing features:
- A name (and a logo) for this project [(suggestions welcome)](#1)
- Displaying images
- Sorting/deleting images
- Thumbnail generation
- Setting new saved images to visible
- Better UI in general
- Saving "EXIF-like" information with an image (possibly in the comment area for an image)
- Different modes for taking images:
  - Automatic exposure
  - Presets for separate light-levels (daylight, inside, night, etc...)
  - Re-using settings (from "EXIF-like" info)
  - suggestions welcome
- Printing images
- Storing settings persistently in the RAM (using momory-areas which do not get deleted by a reset of a parallel original ROM)
- Using beep-tones to transfer an image without any additional hardware. [Decoder by Raphaël Boichot](https://github.com/Raphael-Boichot/custom-camera-rom-beep-tone-converter)
- Currently this project has no makefile (just a [compile.bat](compile.bat))
- Panorama helper (allowing more than the original four images)

# Contributing
_This project is very much a work in progress._  
Join the [Game Boy Gamera Club Discord](https://discord.gg/C7WFJHG) for discussions in detail. And feel free to check and add to [this project's issues](https://github.com/HerrZatacke/custom-camera-rom/issues)  

# Feedback
**Remember: I can only improve things I know about!!**  
If you have actually used this ROM any type of feedback is very much appreciated. This includes but is not restricted to things like:
+ "I'd like to have feature XX"
+ "I've used the following combination of parameters which work really well/bad"
+ "When I set param XX, I'd also like param YY to change"


# Research and related projects
- [Documentation regarding the sensor by AntonioND](https://github.com/AntonioND/gbcam-rev-engineer) [PDF](https://github.com/AntonioND/gbcam-rev-engineer/blob/master/doc/gb_camera_doc_v1_1_1.pdf)
- [References regarding the Game Boy Camera's sensor](https://github.com/Raphael-Boichot/Play-with-the-Game-Boy-Camera-Mitsubishi-M64282FP-sensor)
- Mitsubishi [Sensor Datasheet](https://pdf1.alldatasheet.com/datasheet-pdf/view/146598/MITSUBISHI/M64282FP.html)
- I also received a lot of help and ideas from the [Game Boy Gamera Club Discord](https://discord.gg/C7WFJHG)

# License
This project is released under the [MIT License](LICENSE)
