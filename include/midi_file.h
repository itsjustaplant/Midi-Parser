/**
 * @author just a plant
 *
 */
#include <iostream>
#include <fstream>

#ifndef MIDI_PARSER_MIDI_FILE_H
#define MIDI_PARSER_MIDI_FILE_H

#define HEADER_CHUNK_SIZE  14
#define TRACK_CHUNK_SIZE    8
#define CHUNK_TYPE_SIZE     4

const static std::string MThd = "MThd";

class MidiFile{
public:
  /*-------Class Data Members--------*/
    char* header_chunk_;
    char* track_chunk_;
    char* temp_track_chunk_;

    std::string header_chunk_type_;
    std::string file_name_;
    unsigned int validity_:1;
    int   unsigned header_length_;      //32 bit
    int   unsigned track_length_;       //32 bit
    int   unsigned size_;              //32 bit
    short unsigned int format_;        //16 bit
    short unsigned int tracks_;        //16 bit
    short unsigned int division_;      //16 bit
    int frames_:7;
    int ticks_ :8;

    /*-------Class Function Members--------*/

    /**
     * @brief Constructor method, take path as parameter to initialize object with name
     *        Checks file if it exist
     *        Builds the header_chunk_ -> dynamic
     * @param path
     */
    explicit MidiFile(const std::string& path, std::ifstream* midi_file);

    /**
     * @brief Destructor method
     *        Destroys object and frees header_chunk_
     */
    ~MidiFile()=default;

    /**
     * @brief   First builds header_chunk_type -> MThk  0x4d546864
     *          Calls CheckValidity to validate it is a standard midi file
     *          Then  builds object by assigning the values to it's members
     */
    void ReadHeaderChunk();

    /**
     * @brief Checks validity of file by comparing it's header_chunk_type_ with MThk 0x4d546864
     */
    void CheckValidity();

    /**
     * @brief Prints info about the file works as toString() method
     *        It prints info of the midi file in order of "file" command
     */
    void PrintMetaData() const;

    /**
     * @brief Finds the size of the file by reading the file::end and file::beg
     *        and initializes the class member "size" to it
     * @param midi_file
     */
    void SetSize(std::ifstream* midi_file);

    /**
     * @brief Clears the header chunk to not cause any memory leak
     *        This method can be moved into destructor method
     */
    void ClearChunks() const;

    /**
     * @brief Reads track chunk and initializes track_chunk_
     * @attention   this method only reads first track chunk of midi file
     *              for further development this method must be generalized
     * @param midi_file
     */
    void ReadTrackChunk(std::ifstream* midi_file);

};
#endif //MIDI_PARSER_MIDI_FILE_H
