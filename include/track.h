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
    int event_check_[8] = {0,0,0,0,0,0,0,0};
    //These variables will be initialized in ReadTrackChunk()
    int unsigned length_;
    char* data_;

    //These variables will be initialized in ReadTrackData()
    std::string delta_time_;
    std::string event_;

    //These variables will be initialized in ClassifyMetaEvent()
    std::string text_event_;
    std::string copyright_;
    std::string track_name_;
    std::string instrument_name_;
    std::string lyric_;
    std::string marker_;
    std::string cue_point_;

    Track()=default;

    /**
     * @brief Reads track data and writes delta_time_ and event_
     */
    void ReadTrackData();

    /**
     * @brief Classify the meta event by checking the 3rd and 4th byte of meta event
     */
    void ClassifyMetaEvent();

    /**
     * @brief Takes string of binary array and convert it's to ASCII text
     *        It is used for converting binary copyright, lyric, track name etc. to string
     * @param str
     * @return It returns std::string
     */
    std::string static BinToString(std::string* str);
};



#endif //MIDI_PARSER_TRACK_H
