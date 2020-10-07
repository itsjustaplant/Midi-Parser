//
// Created by Alperen on 3.10.2020.
//

#include "../include/midi_file.h"
void MidiFile::ClearChunks() const {
    delete[] this -> header_chunk_;
    delete[] this -> track_chunk_;
}
void MidiFile::SetSize(std::ifstream* midi_file) {
    int begin, end;
    begin = (*midi_file).tellg();
    (*midi_file).seekg(0, std::ios::end);
    end   = (*midi_file).tellg();
    (*midi_file).seekg(0, std::ios::beg);
    this -> size_ = end - begin;
}

MidiFile::MidiFile(const std::string& path, std::ifstream* midi_file) {

    //Allocate header_chunk_ here to avoid free empty memory block if the midi file is not valid
    this -> header_chunk_ = new char[HEADER_CHUNK_SIZE];
    this -> temp_track_chunk_ = new char[TRACK_CHUNK_SIZE];

    if(path.size() >= 50){
        std::cerr << "File name cannot be longer than 50 characters" << std::endl;
    } else{
        if(!midi_file){
            std::cerr << "File not found" << std::endl;
        } else{
            this -> file_name_ = path;
            this -> SetSize(midi_file);
            midi_file -> read(this -> header_chunk_, HEADER_CHUNK_SIZE);
            midi_file -> read(this -> temp_track_chunk_ , TRACK_CHUNK_SIZE);
        }
    }
}
void MidiFile::CheckValidity(){
    std::string MThd_binary;
    for (int i = 0; i < CHUNK_TYPE_SIZE; ++i) {
        MThd_binary.append(std::bitset<8>(MThd[i]).to_string());
    }

    this->validity_ = ((this -> header_chunk_type_) == MThd_binary) ? 1 : 0;
}
void MidiFile::ReadTrackChunk(std::ifstream* midi_file) {
    std::string temp_type;
    std::string temp_length;
    std::string temp_data;

    for (int i = 0; i < 4; ++i) {
        temp_type.append(std::bitset<8>(this -> temp_track_chunk_[i]).to_string());
    }
    for (int i = 4; i < 8; ++i) {
        temp_length.append(std::bitset<8>(this -> temp_track_chunk_[i]).to_string());
    }
    this -> track_length_ = std::stoi(temp_length, nullptr, 2);
    //Sets position the beginning of the TRACK_CHUNK section
    midi_file->seekg(14, std::ios::beg);
    this -> track_chunk_  = new char[TRACK_CHUNK_SIZE + this -> track_length_];

    midi_file -> read(this -> track_chunk_, TRACK_CHUNK_SIZE + this -> track_length_);
    for (int i = 8; i < 8 + track_length_; ++i) {
        temp_data.append(std::bitset<8>(this -> track_chunk_[i]).to_string());
    }

    delete[] this -> temp_track_chunk_;
    midi_file->close();
}

void MidiFile::ReadHeaderChunk() {

    std::string temp_length;
    std::string temp_format;
    std::string temp_track;
    std::string temp_division;
    std::string temp_frame = "0000000";
    std::string temp_tick;

    for (int i = 0; i < 4; ++i) {
        this -> header_chunk_type_.append(std::bitset<8>(this -> header_chunk_[i]).to_string());
    }

    //Call CheckValidity to validate the midi file
    this -> CheckValidity();

    if(this -> validity_){
        for (int i = 4; i < 8; ++i) {
            temp_length.append(std::bitset<8>(this -> header_chunk_[i]).to_string());
        }
        for (int i = 8; i < 10; ++i) {
            temp_format.append(std::bitset<8>(this -> header_chunk_[i]).to_string());
        }
        for (int i = 10; i < 12; ++i) {
            temp_track.append(std::bitset<8>(this -> header_chunk_[i]).to_string());
        }
        for (int i = 12; i < 14; ++i) {
            temp_division.append(std::bitset<8>(this -> header_chunk_[i]).to_string());
        }

        this -> header_length_   = std::stoi(temp_length  ,nullptr,2);
        this -> format_          = std::stoi(temp_format  ,nullptr,2);
        this -> tracks_          = std::stoi(temp_track   ,nullptr,2);

        if(temp_division[15] == '0'){
            this -> division_    = std::stoi(temp_division, nullptr, 2);
        } else{
            for (int i = 14; i > 7; --i) {
                temp_frame[i-8] = temp_division[i];
            }
            for (int i = 7; i >= 0; --i){
                temp_tick[i] = temp_division[i];
            }
            this -> frames_ = std::stoi(temp_frame, nullptr, 2);
            this -> ticks_  = std::stoi(temp_tick,  nullptr, 2);
        }

    } else{
        std::cerr << "Not a valid MIDI file" << std::endl;
        exit(0);
    }
}
void MidiFile::PrintMetaData() const {
    //std::cout << this->file_name_ << ":" << " Standard MIDI data (format " << this->format_ << ") using " << this -> tracks_ << " at " << this->division_<< std::endl;
    std::cout << "name:       " << this -> file_name_       << std::endl;
    std::cout << "format:     " << this -> format_          << std::endl;
    std::cout << "tracks:     " << this -> tracks_          << std::endl;
    std::cout << "resolution  ";
    (this -> frames_ !=0) ? (std::cout << this -> frames_):(std::cout << this -> division_);
    std:: cout << std::endl;
    std::cout << "size:       " << this -> size_ << " bytes" << std::endl;
}



