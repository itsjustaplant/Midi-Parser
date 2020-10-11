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

void Track::SetText() {
    size_t found = this -> temp_data.find("1111111100000001");
    if (found != std::string::npos && found % 8 == 0){
        int position = (int)found / 8;
        std::string temp_length;
        std::string temp_text;
        for (int i = position + 2; i < position + 3; ++i) {
            temp_length.append(std::bitset<8>(this -> data_[i]).to_string());
        }
        int temp_length_i = std::stoi(temp_length, nullptr, 2);
        for (int i = position + 3; i < position + 3 + temp_length_i; ++i) {
            temp_text.append(std::bitset<8>(this -> data_[i]).to_string());
        }
        this -> text_event_ = BinToString(&temp_text);
        this -> event_check_[0] = 1;
    }
}

void Track::SetCopyright() {
    size_t found = this -> temp_data.find("1111111100000010");

    if (found != std::string::npos && found % 8 == 0){
        int position = (int)found / 8;
        std::string temp_length;
        std::string temp_text;
        for (int i = position + 2; i < position + 3; ++i) {
            temp_length.append(std::bitset<8>(this -> data_[i]).to_string());
        }
        int temp_length_i = std::stoi(temp_length, nullptr, 2);
        for (int i = position + 3; i < position + 3 + temp_length_i; ++i) {
            temp_text.append(std::bitset<8>(this -> data_[i]).to_string());
        }
        this -> copyright_ = BinToString(&temp_text);
        this -> event_check_[1] = 1;
    }
}

void Track::SetTrackName() {
    size_t found = this -> temp_data.find("1111111100000011");
    if (found != std::string::npos && found % 8 == 0){
        int position = (int)found / 8;
        std::string temp_length;
        std::string temp_text;
        for (int i = position + 2; i < position + 3; ++i) {
            temp_length.append(std::bitset<8>(this -> data_[i]).to_string());
        }
        int temp_length_i = std::stoi(temp_length, nullptr, 2);
        for (int i = position + 3; i < position + 3 + temp_length_i; ++i) {
            temp_text.append(std::bitset<8>(this -> data_[i]).to_string());
        }
        this -> track_name_ = BinToString(&temp_text);
        this -> event_check_[2] = 1;
    }
}

void Track::SetInstrumentName() {
    size_t found = this -> temp_data.find("1111111100000100");
    if (found != std::string::npos && found % 8 == 0){
        int position = (int)found / 8;
        std::string temp_length;
        std::string temp_text;
        for (int i = position + 2; i < position + 3; ++i) {
            temp_length.append(std::bitset<8>(this -> data_[i]).to_string());
        }
        int temp_length_i = std::stoi(temp_length, nullptr, 2);
        for (int i = position + 3; i < position + 3 + temp_length_i; ++i) {
            temp_text.append(std::bitset<8>(this -> data_[i]).to_string());
        }
        this -> instrument_name_ = BinToString(&temp_text);
        this -> event_check_[3] = 1;
    }
}

void Track::SetLyric() {
    size_t found = this -> temp_data.find("1111111100000101");
    if (found != std::string::npos && found % 8 == 0){
        int position = (int)found / 8;
        std::string temp_length;
        std::string temp_text;
        for (int i = position + 2; i < position + 3; ++i) {
            temp_length.append(std::bitset<8>(this -> data_[i]).to_string());
        }
        int temp_length_i = std::stoi(temp_length, nullptr, 2);
        for (int i = position + 3; i < position + 3 + temp_length_i; ++i) {
            temp_text.append(std::bitset<8>(this -> data_[i]).to_string());
        }
        this -> lyric_ = BinToString(&temp_text);
        this -> event_check_[4] = 1;
    }
}

void Track::SetMarker() {
    size_t found = this -> temp_data.find("1111111100000110");
    if (found != std::string::npos && found % 8 == 0){
        int position = (int)found / 8;
        std::string temp_length;
        std::string temp_text;
        for (int i = position + 2; i < position + 3; ++i) {
            temp_length.append(std::bitset<8>(this -> data_[i]).to_string());
        }
        int temp_length_i = std::stoi(temp_length, nullptr, 2);
        for (int i = position + 3; i < position + 3 + temp_length_i; ++i) {
            temp_text.append(std::bitset<8>(this -> data_[i]).to_string());
        }
        this -> marker_ = BinToString(&temp_text);
        this -> event_check_[5] = 1;
    }
}

void Track::SetCuePoint() {
    size_t found = this -> temp_data.find("1111111100000111");
    if (found != std::string::npos && found % 8 == 0){
        int position = (int)found / 8;
        std::string temp_length;
        std::string temp_text;
        for (int i = position + 2; i < position + 3; ++i) {
            temp_length.append(std::bitset<8>(this -> data_[i]).to_string());
        }
        int temp_length_i = std::stoi(temp_length, nullptr, 2);
        for (int i = position + 3; i < position + 3 + temp_length_i; ++i) {
            temp_text.append(std::bitset<8>(this -> data_[i]).to_string());
        }
        this -> cue_point_ = BinToString(&temp_text);
        this -> event_check_[6] = 1;
    }
}
void Track::ReadTrackData() {

    for (int i = 0; i < this->length_; ++i) {
        this->temp_data.append(std::bitset<8>(this->data_[i]).to_string());
    }
    this -> SetText();
    this -> SetCopyright();
    this -> SetTrackName();
    this -> SetInstrumentName();
    this -> SetLyric();
    this -> SetMarker();
    this -> SetCuePoint();
}