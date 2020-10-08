//
// Created by Alperen on 7.10.2020.
//

#ifndef MIDI_PARSER_TRACK_H
#define MIDI_PARSER_TRACK_H


class Track{
public:
    int unsigned length;
    char* data;
    Track()=default;
    void ReadTrackData();
};



#endif //MIDI_PARSER_TRACK_H
