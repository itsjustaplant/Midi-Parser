##MIDI meta data extractor

Simple midi meta data extractor without any library
***

### Build
* Fork it, clone it
```
mkdir build && cd build
cmake ..
make
```
### To do
* Midi events classifying must be improved
* Leaks are fixed but several test cases must be implemented

### Issues
* ClassifyMetaEvent() method only classifies meta events with delta_time_ = 0x00
* Code must be refactored

### Resources
* http://www.music.mcgill.ca/~ich/classes/mumt306/StandardMIDIfileformat.html
* https://www.personal.kent.edu/~sbirch/Music_Production/MP-II/MIDI/midi_file_format.htm

 