#include <string>
#include <iostream>
#include "GraphicsDisplay.h"

using namespace std;


// row includes the height of the board + the reserved 3 rows
GraphicsDisplay::GraphicsDisplay(int row, int column): row{row + 3}, column{column}, cellSize{20} {
    // std::vector<int> temp(n, DefualtColour);
    // theDisplay.assign(n, temp);

    // Initialize the board
    for (int i = 0; i < row; i += 1) {
        vector<int> r;
        for (int j = 0; j < (2 * column + 6); j += 1) {
            r.emplace_back(Xwindow::White);
        }
        theDisplay.emplace_back(r);
    }
    // Initialize the next Block section
    for (int i = 0; i < 2; i += 1) {
        vector<int> r;
        for (int j = 0; j < (2 * column + 6); j += 1) {
            r.emplace_back(Xwindow::White);
        }
        theNextBlock.emplace_back(r);
    }

    xw = make_unique<Xwindow>(20 * (2 * column + 8), 20 * (row + 10));
    xw->drawRectangle(0, 0, 560, 460, Xwindow::White);
    // Display the top two rows (Level, Score)
    xw->drawString(20, 20, "Level:", Xwindow::Black);
    xw->drawString(220, 20, "0", Xwindow::Black);
    xw->drawString(340, 20, "Level:", Xwindow::Black);
    xw->drawString(540, 20, "0", Xwindow::Black);
    
    xw->drawString(20, 40, "Score:", Xwindow::Black);
    xw->drawString(220, 40, "0", Xwindow::Black);
    xw->drawString(340, 40, "Score:", Xwindow::Black);
    xw->drawString(540, 40, "0", Xwindow::Black);

    // Display the two lines
    xw->drawLine(20, 50, 220, 50);
    xw->drawLine(400, 50, 620, 50);
    xw->drawLine(20, 430, 40, 430);
    xw->drawLine(400, 430, 620, 430);
    // Display Next Block section
    xw->drawString(20, 430, "Next:", Xwindow::Black);
    xw->drawString(400, 430, "Next:", Xwindow::Black);
}

// fillBlind() fills the column 3-9, row 3-12 with Brown
void GraphicsDisplay::fillBlind(int x, int y, int width, int height, int colour) {
    // Check if one or more players has blind effect
    for (int i = 0; i < 2; i += 1) {
        if (game->players[i].restriction == Restriction::blind) {
            // Access row 3-12 (row index needs to increase by 3 since there are 3 reserved rows)
            for (int j = 5; j < 17; j += 1) { // TBD??????
                // Access column 3-9
                for (int k = (2 + i * 17); k < (9 + i * 17); k += 1) {
                    theDisplay[j][k] = Xwindow::Black; // Set as black for now
                }
            }
        }
    }
}

// fillBlock() fills the Block with it's corresponding colour
void GraphicsDisplay::fillBlock() {
    // Access each player
    for (int i = 0; i < 2; i += 1) {
        // Access each row
        for (int j = 0; j < game->players[i].board->gridH; j += 1) {
            // Access each column
            for (int k = 0; k < game->player[i].board->gridW; k += 1) {
                if (game->players[i].board->grid[i][j]) {
                    BlockType type = game->players[i].board->grid[i][j]->getType();
                    switch(type) {
                        case BlockType::IBlock: {
                            theDisplay[j][k + i * 17] = Xwindow::Blue;
                            break;
                        }
                        case BlockType::JBlock: {
                            theDisplay[j][k + i * 17] = Xwindow::Red;
                            break;
                        }
                        case BlockType::LBlock: {
                            theDisplay[j][k + i * 17] = Xwindow::Yellow;
                            break;
                        }
                        case BlockType::OBlock: {
                            theDisplay[j][k + i * 17] = Xwindow::Orange;
                            break;
                        }
                        case BlockType::SBlock: {
                            theDisplay[j][k + i * 17] = Xwindow::Green;
                            break;
                        }
                        case BlockType::ZBlock: {
                            theDisplay[j][k + i * 17] = Xwindow::Cyan;
                            break;
                        }
                        case BlockType::TBlock: {
                            theDisplay[j][k + i * 17] = Xwindow::Magenta;
                            break;
                        }
                        case BlockType::StarBlock: {
                            theDisplay[j][k + i * 17] = Xwindow::Brown;
                        }
                    }
                }
            }
        }
    }
}


// fillNextBlock() displays the next Block shape in the bottom rows of the board
void GraphicsDisplay::fillNextBlock() {
    // Reset each next block 
    for (int i = 0; i < 2; i += 1) {
        for (int j = 0; j < 28; j += 1) {
            theNextBlock[i][j] = Xwindow::White;
        }
    }

    for (int i = 0; i < 2; i += 1) {
        if (game->players[current_player].playing) continue;
        BlockType type = game->players[i].nextType;
        switch(type) {
            case BlockType::IBlock: {
                theNextBlock[1][0 + i * 17] = Xwindow::Blue;
                theNextBlock[1][1 + i * 17] = Xwindow::Blue;
                theNextBlock[1][2 + i * 17] = Xwindow::Blue;
                theNextBlock[1][3 + i * 17] = Xwindow::Blue;
            }
            case BlockType::JBlock: {
                theNextBlock[0][0 + i * 17] = Xwindow::Red;
                theNextBlock[1][0 + i * 17] = Xwindow::Red;
                theNextBlock[1][1 + i * 17] = Xwindow::Red;
                theNextBlock[1][2 + i * 17] = Xwindow::Red;
            }
            case BlockType::LBlock: {
                theNextBlock[0][2 + i * 17] = Xwindow::Yellow;
                theNextBlock[1][0 + i * 17] = Xwindow::Yellow;
                theNextBlock[1][1 + i * 17] = Xwindow::Yellow;
                theNextBlock[1][2 + i * 17] = Xwindow::Yellow;
            }
            case BlockType::OBlock: {
                theNextBlock[0][0 + i * 17] = Xwindow::Orange;
                theNextBlock[0][1 + i * 17] = Xwindow::Orange;
                theNextBlock[1][0 + i * 17] = Xwindow::Orange;
                theNextBlock[1][1 + i * 17] = Xwindow::Orange;
            }
            case BlockType::SBlock: {
                theNextBlock[0][1 + i * 17] = Xwindow::Green;
                theNextBlock[0][2 + i * 17] = Xwindow::Green;
                theNextBlock[1][0 + i * 17] = Xwindow::Green;
                theNextBlock[1][1 + i * 17] = Xwindow::Green;
            }
            case BlockType::ZBlock: {
                theNextBlock[0][0 + i * 17] = Xwindow::Cyan;
                theNextBlock[0][1 + i * 17] = Xwindow::Cyan;
                theNextBlock[1][1 + i * 17] = Xwindow::Cyan;
                theNextBlock[1][2 + i * 17] = Xwindow::Cyan;
            }
            case BlockType::TBlock: {
                theNextBlock[0][0 + i * 17] = Xwindow::Magenta;
                theNextBlock[0][1 + i * 17] = Xwindow::Magenta;
                theNextBlock[0][2 + i * 17] = Xwindow::Magenta;
                theNextBlock[1][1 + i * 17] = Xwindow::Magenta;
            }
        }
    }
        
}


// notify() notifies the GraphicsDisplay if a board changes
void GraphicsDisplay::notify(){
    fillBlock();
    fillNextBlock();
    fillBlind();
    // Update Level and Score
    for (int i = 0; i < 2; i += 1) {
        int level = game->players[i].currentLevel;
        int score = game->players[i].getScore();
        xw->drawString(20, 200 + i * 340, static_cast<string>(level), Xwindow::Black);
        xw->drawString(40, 200 + i * 340, static_cast<string>(score), Xwindow::Black);
    }
    // Display the board
    // Access rows
    for (int i = 0; i < row; i += 1) {
        // Access columns
        for (int j = 0; j < 2 * column + 6; j += 1) {
            xw->fillRectangle(j * cellSize + 20, (i + 4) * cellSize, cellSize, cellSize, theDisplay[i][j]);
        }
    }
    // Display the next Block
    // Access rows
    for (int i = 0; i < 2; i += 1) {
        // Access columns
        for (int j = 0; j < 2 * column + 6; j += 1) {
            xw->fillRectangle(j * cellSize + 20, i * cellSize, cellSize, cellSize, theNextBlock[i][j]);
        }
    }
}