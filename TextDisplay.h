#ifndef BIQUADRIS_TEXTDISPLAY_H
#define BIQUADRIS_TEXTDISPLAY_H

#include <iostream>
#include <string>
#include <vector>

class TextDisplay {
    std::vector<std::vector<char>> td;
    const int row;
    const int column;
public:
    // Constructor
    TextDisplay(int row = 15, int column = 11);
    // init(string name) is a helper function to initialize textdisplay of the board(level, score, next)
    void init(string name);
    // fillBlind() fills the column 3-9, and row 3-12 with "?"
    // until the player drops a block
    void fillBlind();
    // fillBlock() fills the Block with it's corresponding letter (i.e. j for JBlock)
    void fillBlock();
    // fillTopInfo() displays the information on the top 3 rows (i.e. level, score, and and a line)
    void fillTopInfo();
    // fillNextBlock() displays the next Block shape in the bottom 3 rows of the board
    void fillNextBlock();

    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

std::ostream &operator<<(std::ostream &out, const TextDisplay &td);


#endif //BIQUADRIS_TEXTDISPLAY_H
