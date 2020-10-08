#include "../include/midi_file.h"
using namespace std;
#define USAGE  \
    "Usage: midi_parser path\n" \
    "            path: path of the input file " \

int main(int argc, char* argv[]) {

    if(argc == 2){
        std::ifstream file(argv[1], std::ios::in | std::ios::binary);
        auto* midi_file = new MidiFile(argv[1], &file );
        midi_file -> ReadHeaderChunk();
        midi_file -> ReadTrackChunk(&file);

        string command;
        cout << ">> ";
        cin >> command;
        while(command != "exit"){
            if(command == "info"){
                midi_file->PrintMetaData();
            } else if(command == "usage"){
                cout <<"\033[34m" << USAGE << "\033[0m" << endl;
            } else{
                cout << "No command" << endl;
            }
            cout << ">> ";
            cin >> command;
        }

        delete midi_file;
    } else{
        cout << USAGE << endl;
    }
    return 0;
}
