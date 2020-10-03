//
// Created by Alperen on 3.10.2020.
//

#include "../include/midi_file.h"
MidiFile::MidiFile(const std::string& path) {

    std::ifstream midi_file(path, std::ios::in | std::ios::binary);
    this -> header_chunk_= new char[HEADER_CHUNK_SIZE];
    memset(this -> header_chunk_, 0, HEADER_CHUNK_SIZE);
    if(path.size() >= 50){
        std::cerr << "File name cannot be longer than 50 characters" << std::endl;
    } else{
        if(!midi_file){
            std::cerr << "File not found" << std::endl;
        } else{
            std::cout << "exist" << std::endl;
            this -> file_name_ = path;
            midi_file.read(this -> header_chunk_,HEADER_CHUNK_SIZE);
        }
    }
}

MidiFile::~MidiFile() {
    free(this -> header_chunk_);
}

void MidiFile::CheckValidity(){
    std::string MThd_binary = "";
    for (int i = 0; i < CHUNK_TYPE_SIZE; ++i) {
        MThd_binary.append(std::bitset<8>(MThd[i]).to_string());
    }
    
    this->validity_ = ((this -> chunk_type_) == MThd_binary) ? 1 : 0;
}
void MidiFile::ReadHeaderChunk() {

    std::string temp_length;
    std::string temp_format;
    std::string temp_track;
    std::string temp_division;


    for (int i = 0; i < 4; ++i) {
        this -> chunk_type_.append(std::bitset<8>(this -> header_chunk_[i]).to_string());
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
        this -> length_   = std::stoi(temp_length  ,nullptr,2);
        this -> format_   = std::stoi(temp_format  ,nullptr,2);
        this -> tracks_   = std::stoi(temp_track   ,nullptr,2);
        this -> division_ = std::stoi(temp_division,nullptr,2);
    } else{
        std::cerr << "Not a valid MIDI file" << std::endl;
        exit(0);
    }
}

void MidiFile::PrintInfo() const {
    std::cout << this->file_name_ << ":" << " Standard MIDI data (format " << this->format_ << ") using " << this -> tracks_ << " at " << this->division_<< std::endl;
}

