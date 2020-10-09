//
// Created by Alperen on 8.10.2020.
//

#include "../include/track.h"
std::string Track::BinToString(std::string* str){
    std::stringstream  sstream(*str);
    std::string output;
    while (sstream.good()){
        std::bitset<8> bits;
        sstream >> bits;
        char ch = char(bits.to_ullong());
        output+= ch;
    }
    return output;
}
void Track::ReadTrackData() {

    for (int i = 0; i < 1; ++i) {
        this -> delta_time_.append((std::bitset<8>(this -> data_[i]).to_string()));
    }
    //Each event is longer than 2 bytes
    //To classify the even it only reads 2 bytes and checks the second byte
    for (int i = 2; i < 3; ++i) {
        this -> event_.append(std::bitset<8>(this -> data_[i]).to_string());
    }
    this -> ClassifyMetaEvent();
}
/*
 *
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

void Track::ClassifyMetaEvent() {
    int meta_event = std::stoi(this -> event_, nullptr, 2);
    if(meta_event == 0){
    } else if(meta_event >= 1 && meta_event <= 7){
        std::string temp_length;
        int temp_length_i;
        for (int i = 3; i < 4; ++i) {
            temp_length.append(std::bitset<8>(this -> data_[i]).to_string());
        }
        temp_length_i = std::stoi(temp_length, nullptr, 2);
        switch (meta_event) {
            case 1: {
                std::string temp_event;
                for (int i = 4; i < 4 + temp_length_i; ++i) {
                    temp_event.append(std::bitset<8>(this -> data_[i]).to_string());
                }
                this -> text_event_ = BinToString(&temp_event);
                this -> event_check_[1] = 1;
                break;
            }
            case 2: {
                std::string temp_copyright;
                for (int i = 4; i < 4 + temp_length_i; ++i) {
                    temp_copyright.append(std::bitset<8>(this -> data_[i]).to_string());
                }
                this -> copyright_ = BinToString(&temp_copyright);
                this -> event_check_[2] = 1;
                break;
            }
            case 3: {
                std::string temp_name;
                for (int i = 4; i < 4 + temp_length_i; ++i) {
                    temp_name.append(std::bitset<8>(this->data_[i]).to_string());
                }
                this->track_name_ = BinToString(&temp_name);
                this -> event_check_[3] = 1;
                break;
            }
            case 4:{
                std::string temp_instrument;
                for (int i = 4; i < 4 + temp_length_i; ++i) {
                    temp_instrument.append(std::bitset<8>(this -> data_[i]).to_string());
                }
                this -> instrument_name_ = BinToString(&temp_instrument);
                this -> event_check_[4] = 1;
            }
            case 5:{
                std::string temp_lyric;
                for (int i = 4; i < 4 + temp_length_i; ++i) {
                    temp_lyric.append(std::bitset<8>(this -> data_[i]).to_string());
                }
                this -> lyric_ = BinToString(&temp_lyric);
                this -> event_check_[5];
            }
            case 6:{
                std::string temp_marker;
                for (int i = 4; i < 4 + temp_length_i; ++i) {
                    temp_marker.append(std::bitset<8>(this -> data_[i]).to_string());
                }
                this -> marker_ = BinToString(&temp_marker);
                this -> event_check_[6] = 1;
            }
            case 7:{
                std::string temp_cue;
                for (int i = 4; i < 4 + temp_length_i; ++i) {
                    temp_cue.append(std::bitset<8>(this -> data_[i]).to_string());
                }
                this -> cue_point_ = BinToString(&temp_cue);
                this -> event_check_[7] = 1;
            }
        }
    }

}