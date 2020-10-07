
#include "../include/midi_file.h"
using namespace std;
#define USAGE  \
    "Usage: midi_parser path\n" \
    "            path: path of the input file " \

int main(int argc, char* argv[]) {
    if(argc == 2){
        std::ifstream midi_file_f(argv[1], std::ios::in | std::ios::binary);
        MidiFile* midi_file = new MidiFile(argv[1], &midi_file_f );
        midi_file -> ReadHeaderChunk();

        string command;
        cout << ">> ";
        cin >> command;
        while(command != "exit"){
            if(command == "info"){
                midi_file->PrintMetaData();
            } else if(command == "usage"){
                cout << USAGE << endl;
            } else{
                cout << "No command" << endl;
            }
            cout << ">> ";
            cin >> command;
        }
        midi_file -> ReadTrackChunk(&midi_file_f);
        midi_file->ClearChunks();
        delete midi_file;
    } else{
        cout << USAGE << endl;
    }
    return 0;
}
