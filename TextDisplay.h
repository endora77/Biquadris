#ifndef BIQUADRIS_TEXTDISPLAY_H
#define BIQUADRIS_TEXTDISPLAY_H
#include <string>
#include <iostream>
#include <vector>
#include "Display.h"

class TextDisplay : public Display {
    std::vector<std::vector<char>> theDisplay;
    const int row;
    const int column;
    std::ostream &out;
public:
    // Constructor
    TextDisplay(int row = 15, int column = 11);
    // init(string name) is a helper function to initialize textdisplay of the board(level, score, next)
    void init(std::string name) override;
    // fillBlind() fills the column 3-9, and row 3-12 with "?" until the player drops a block
    void fillBlind() override;
    // fillBlock() fills the Block with it's corresponding letter (i.e. j for JBlock)
    void fillBlock() override;
    // fillTopInfo() displays the information on the top 3 rows (i.e. level, score, and and a line)
    void fillTopInfo() override;
    // fillNextBlock() displays the next Block shape in the bottom 3 rows of the board
    void fillNextBlock() override;
    // notify() prints the display in text format
    void notify() override;
};


#endif //BIQUADRIS_TEXTDISPLAY_H
