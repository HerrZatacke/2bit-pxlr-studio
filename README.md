# 2bit PXLR Studio
![2bit PXLR Studio Logo](assets/2bitpxlr.png "2bit PXLR Studio")

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
