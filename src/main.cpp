
#include "../include/midi_file.h"
using namespace std;
int main() {
    MidiFile midi_file("../midi_files/teddybear.mid");
    midi_file.ReadHeaderChunk();
    midi_file.PrintInfo();
    return 0;
}
