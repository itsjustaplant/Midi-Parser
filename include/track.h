//
// Created by Alperen on 7.10.2020.
//

#ifndef MIDI_PARSER_TRACK_H
#define MIDI_PARSER_TRACK_H

#include <iostream>
#include <sstream>

//<Track Chunk> = <chunk type><length><MTrk event>+
//
//The syntax of an MTrk event is very simple:
//
//<MTrk event> = <delta-time><event>

/*
header -> type -> len,01,02,03,04,05 -> len,text,etc
FF 00 02 Sequence Number
FF 01 len text Text Event
FF 02 len text Copyright Notice
FF 03 len text Sequence/Track Name
FF 04 len text Instrument Name
FF 05 len text Lyric
FF 06 len text Marker
FF 07 len text Cue Point
FF 20 01 cc MIDI Channel Prefix
FF 2F 00 End of Track
FF 51 03 tttttt Set Tempo (in microseconds per MIDI quarter-note)
FF 54 05 hr mn se fr ff SMPTE Offset
FF 58 04 nn dd cc bb Time Signature */
class Track{
public:
    int event_check_[7] = {0,0,0,0,0,0,0};

    //These variables will be initialized in ReadTrackChunk()
    int unsigned length_;
    char* data_;
    std::string temp_data;

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
     * @brief Takes string of binary array and convert it's to ASCII text
     *        It is used for converting binary copyright, lyric, track name etc. to string
     * @param str
     * @return It returns std::string
     */
    std::string static BinToString(std::string* str);
    /*------- There lies a spaghetti, pls don't scroll down-------- */
    /**
     * @brief Seeks for FF XX if it finds, it initializes this -> XX and checks the event_check[X]
     *                        else does nothing
     */
    void SetText();
    void SetCopyright();
    void SetTrackName();
    void SetInstrumentName();
    void SetLyric();
    void SetMarker();
    void SetCuePoint();
};



#endif //MIDI_PARSER_TRACK_H
