//
// Created by Alperen on 3.10.2020.
//
#include <iostream>
#include <fstream>

#ifndef MIDI_PARSER_MIDI_FILE_H
#define MIDI_PARSER_MIDI_FILE_H

#define HEADER_CHUNK_SIZE 14
#define CHUNK_TYPE_SIZE   4

const static std::string MThd = "MThd";

class MidiFile{
public:
  /*-------Class Data Members--------*/
    char* header_chunk_;
    std::string chunk_type_;
    std::string file_name_;
    unsigned int validity_:1;
    int   unsigned length_;            //32 bit
    short unsigned int format_;        //16 bit
    short unsigned int tracks_;        //16 bit
    short unsigned int division_;      //16 bit

    /*-------Class Function Members--------*/

    /**
     * @brief Constructor method, take path as parameter to initialize object with name
     *        Checks file if it exist
     *        Builds the header_chunk_ -> dynamic
     * @param path
     */
    explicit MidiFile(const std::string& path);

    /**
     * @brief Destructor method
     *        Destroys object and frees header_chunk_
     */
    ~MidiFile();

    /**
     * @brief   First builds chunk_type -> MThk  0x4d546864
     *          Calls CheckValidity to validate it is a standard midi file
     *          Then  builds object by assigning the values to it's members
     */
    void ReadHeaderChunk();

    /**
     * @brief Checks validity of file by comparing it's chunk_type_ with MThk 0x4d546864
     */
    void CheckValidity();

    /**
     * @brief Prints info about the file works as toString() method
     *        It prints info of the midi file in order of "file" command
     */
    void PrintInfo() const;
};
#endif //MIDI_PARSER_MIDI_FILE_H
