#ifndef BIQUADRIS_GRAPHICSDISPLAY_H
#define BIQUADRIS_GRAPHICSDISPLAY_H
#include "Display.h"
#include "Window.h"
#include "Enums.h"
#include <string>
#include <iostream>

class GraphicsDisplay: public Display {
    // The display of the board
    std::vector<std::vector<int>> theDisplay;
    // The display of the Next Block section
    std::vector<std::vector<int>> theNextBlock;
    const int row;
    const int column;
    const int cellHeight;//The size of the board
    const int cellWidth;//The size of a single cell

    Xwindow *xw;

public:
    // Constructor
    GraphicsDisplay(int row = 15, int column = 11);
    // init(string name) is a helper function to initialize the graphicsdisplay of the board
    // init(std::string type) override;
    // fillBlind() fills the column 3-9, and row 3-12 with "?" until the player drops a block
    void fillBlind() override;
    // fillBlock() fills the Block with it's corresponding letter (i.e. j for JBlock)
    void fillBlock(int x, int y, int width, int height, int colour) override;
    // fillNextBlock() displays the next Block shape in the bottom 3 rows of the board
    void fillNextBlock() override;
    //notify() notifies the GraphicsDisplay if the board changes
    void notify() override;

};


#endif