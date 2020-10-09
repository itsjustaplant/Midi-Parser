//
// Created by Alperen on 3.10.2020.
//

#include "../include/midi_file.h"

void MidiFile::SetSize(std::ifstream* midi_file) {
    int begin, end;
    begin = (*midi_file).tellg();
    (*midi_file).seekg(0, std::ios::end);
    end   = (*midi_file).tellg();
    (*midi_file).seekg(0, std::ios::beg);
    this -> size_ = end - begin;
}

MidiFile::MidiFile(const std::string& path, std::ifstream* file) {

    //Allocate header_chunk_ here to avoid free empty memory block if the midi file is not valid
    this -> header_chunk_ = new char[HEADER_CHUNK_SIZE];
    this -> temp_track_chunk_ = new char[TRACK_CHUNK_SIZE];

    if(path.size() >= 50){
        std::cerr << "File name cannot be longer than 50 characters" << std::endl;
    } else{
        if(!file){
            std::cerr << "File not found" << std::endl;
        } else{
            this -> file_name_ = path;
            this -> SetSize(file);
            file -> read(this -> header_chunk_, HEADER_CHUNK_SIZE);
            file -> read(this -> temp_track_chunk_ , TRACK_CHUNK_SIZE);
        }
    }
}
MidiFile::~MidiFile() {
    if(this -> validity_){
        for (int i = 0; i < this->track_count_; ++i) {
            delete this -> tracks_[i].data_;
        }
        delete[] this -> tracks_;
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
    this -> tracks_ = new Track[this -> track_count_];

    for (int i = 0; i < this -> track_count_; ++i) {
        std::string temp_type = "";
        std::string temp_length = "";
        std::string temp_data = "";
        for (int j = 0; j < 4; ++j) {
            temp_type.append(std::bitset<8>(this -> temp_track_chunk_[j]).to_string());
        }

        for (int k = 4; k < 8; ++k) {
            temp_length.append(std::bitset<8>(this -> temp_track_chunk_[k]).to_string());
        }
        this -> tracks_[i].length_ = std::stoi(temp_length, nullptr, 2);

        //Sets position the beginning of the TRACK_CHUNK section
        this -> tracks_[i].data_ = new char[this -> tracks_[i].length_];
        midi_file -> read(this -> tracks_[i].data_, this -> tracks_[i].length_);

/*
        for (int m = 0; m < this -> tracks_[i].length; ++m) {
            temp_data.append(std::bitset<8>(this -> tracks_[i].data[m]).to_string());
        }
*/
        midi_file->read(this -> temp_track_chunk_, TRACK_CHUNK_SIZE);
        this -> tracks_[i].ReadTrackData();
    }

    //Initializes to struct to hold every track chunk in a structure
    //This will help us to read track chunks with one method

    //temporary is destroyed here
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
        this -> track_count_     = std::stoi(temp_track   , nullptr, 2);

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
    delete[] this -> header_chunk_;
}
void MidiFile::PrintMetaData() const {
    //std::cout << this->file_name_ << ":" << " Standard MIDI data (format " << this->format_ << ") using " << this -> track_count_ << " at " << this->division_<< std::endl;
    //cout << "\033[1;31mbold red text\033[0m\n";
    std::cout << "\033[33mname:       \033[0m" << this -> file_name_        << std::endl;
    std::cout << "\033[33mformat:     \033[0m" << this -> format_           << std::endl;
    std::cout << "\033[33mtracks:     \033[0m" << this -> track_count_      << std::endl;
    std::cout << "\033[33mresolution  \033[0m" << this -> division_         << std::endl;
    std::cout << "\033[33msize:       \033[0m" << this -> size_ << " bytes" << std::endl;
    for (int i = 0; i < this -> track_count_; ++i) {
        std::cout << "----------Track" << i+1 << "----------" << std::endl;
        //I know that the whole code is messy
        //Nothing good happens after this comment actually
        //I thought i couldn't more f*ck this up
        //But yeah, congrats to me, i did

        //A lot of if else
        //Soon they will be merged in to a method called PleaseStop()
        if(this -> tracks_[i].event_check_[0] == 1){
            std::cout <<"\033[33mtext event:       \033[0m" <<this -> tracks_[i].text_event_ << std::endl;
        } if(this -> tracks_[i].event_check_[2]==1){
            std::cout <<"\033[33mcopyright:       \033[0m" <<this -> tracks_[i].copyright_ << std::endl;
        } if(this -> tracks_[i].event_check_[3]==1){
            std::cout <<"\033[33mtrack name:       \033[0m" <<this -> tracks_[i].track_name_ << std::endl;
        } if(this -> tracks_[i].event_check_[4]==1){
            std::cout <<"\033[33minstrument name:  \033[0m" <<this -> tracks_[i].instrument_name_ << std::endl;
        } if(this -> tracks_[i].event_check_[5]==1){
            std::cout <<"\033[33mtrack lyric:       \033[0m" <<this -> tracks_[i].lyric_ << std::endl;
        } if(this -> tracks_[i].event_check_[6]==1){
            std::cout <<"\033[33mtrack marker:       \033[0m" <<this -> tracks_[i].marker_ << std::endl;
        } if(this -> tracks_[i].event_check_[7]==1){
            std::cout <<"\033[33mtrack cue:       \033[0m" <<this -> tracks_[i].cue_point_ << std::endl;
        }
    }
}




