//
// Created by Alperen on 7.10.2020.
//

#ifndef MIDI_PARSER_TRACK_H
#define MIDI_PARSER_TRACK_H
#define DELTA_TIME_SIZE     8 // it is fixed to 1 byte for now
#include <iostream>
#include <sstream>
//<Track Chunk> = <chunk type><length><MTrk event>+
//
//The syntax of an MTrk event is very simple:
//
//<MTrk event> = <delta-time><event>
class Track{
public:
    //These variables will be initialized in ReadTrackChunk()
    int unsigned length_;
    char* data_;

    //These variables will be initialized in ReadTrackData()
    std::string delta_time_;
    std::string event_;

    //These variables will be initialized in ClassifyMetaEvent()
    std::string track_name_;

    Track()=default;
    void ReadTrackData();
    void ClassifyMetaEvent();
    std::string static BinToString(std::string* str);
};



#endif //MIDI_PARSER_TRACK_H
