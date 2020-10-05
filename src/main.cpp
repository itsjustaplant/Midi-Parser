
#include "../include/midi_file.h"
using namespace std;
#define USAGE  \
    "Usage: midi_parser path\n" \
    "            path: path of the input file " \

int main(int argc, char* argv[]) {
    if(argc == 2){
        MidiFile midi_file(argv[1]);
        midi_file.ReadHeaderChunk();

        string command;
        cout << ">> ";
        cin >> command;
        while(command != "exit"){
            if(command == "info"){
                midi_file.PrintInfo();
            } else if(command == "usage"){
                cout << USAGE << endl;
            } else{
                cout << "No command" << endl;
            }
            cout << ">> ";
            cin >> command;
        }
    } else{
        cout << USAGE << endl;
    }
    return 0;
}
