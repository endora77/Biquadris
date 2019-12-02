#include <string>
#include <iostream>
#include "GraphicsDisplay.h"

using namespace std;


// row includes the height of the board + the reserved 3 rows
GraphicsDisplay::GraphicsDisplay(int row, int column): row{row + 3}, column{column}, cellHeight{20}, cellWidth{20} {
    // std::vector<int> temp(n, DefualtColour);
    // theDisplay.assign(n, temp);

    // Initialize the board
    for (int i = 0; i < row; i += 1) {
        vector<int> r;
        for (int j = 0; j < (2 * column + 6); j += 1) {
            r.emplace_back(Colour::White);
        }
        theDisplay.emplace_back(r);
    }
    // Initialize the next Block section
    for (int i = 0; i < 2; i += 1) {
        vector<int> r;
        for (int j = 0; j < (2 * column + 6); j += 1) {
            r.emplace_back(Colour::White);
        }
        theNextBlock.emplace_back(r);
    }

    xw = make_unique<Xwindow>(20 * (2 * column + 6), 20 * (row + 7));
    xw->drawRectangle(0, 0, 560, 460, Colour::White);
    // Display the top two rows (Level, Score)
    xw->drawString(20, 20, "Level:", Colour::Black);
    xw->drawString(20, 220, "0", Colour::Black);
    xw->drawString(20, 340, "Level:", Colour::Black);
    xw->drawString(20, 540, "0", Colour::Black);
    
    xw->drawString(40, 20, "Score:", Colour::Black);
    xw->drawString(40, 200, "0", Colour::Black);
    xw->drawString(40, 340, "Score:", Colour::Black);
    xw->drawString(40, 540, "0", Colour::Black);

    xw->drawLine(45, 0, 40, 560);
    xw->drawLine(400, 0, 400, 560);
    // Display Next Block section
    xw->drawString(420, 0, "Next:", Colour::Black);
    xw->drawString(420, 340, "Next:", Colour::Black);
}

// fillBlind() fills the column 3-9, row 3-12 with Brown
void GraphicsDisplay::fillBlind(int x, int y, int width, int height, int colour) {
    // Check if one or more players has blind effect
    for (int i = 0; i < 2; i += 1) {
        if (game->players[i].restriction == Restriction::blind) {
            // Access row 3-12 (row index needs to increase by 3 since there are 3 reserved rows)
            for (int j = 5; j < 17; j += 1) {
                // Access column 3-9
                for (int k = (2 + i * 17); k < (9 + i * 17); k += 1) {
                    theDisplay[j][k] = Colour::Brown;
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
                            theDisplay[j][k + i * 17] = Colour::Blue;
                            break;
                        }
                        case BlockType::JBlock: {
                            theDisplay[j][k + i * 17] = Colour::Red;
                            break;
                        }
                        case BlockType::LBlock: {
                            theDisplay[j][k + i * 17] = Colour::Yellow;
                            break;
                        }
                        case BlockType::OBlock: {
                            theDisplay[j][k + i * 17] = Colour::Orange;
                            break;
                        }
                        case BlockType::SBlock: {
                            theDisplay[j][k + i * 17] = Colour::Green;
                            break;
                        }
                        case BlockType::ZBlock: {
                            theDisplay[j][k + i * 17] = Colour::Cyan;
                            break;
                        }
                        case BlockType::TBlock: {
                            theDisplay[j][k + i * 17] = Colour::Magneta;
                            break;
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
            theNextBlock[i][j] = Colour::White;
        }
    }

    for (int i = 0; i < 2; i += 1) {
        if (game->players[current_player].playing) continue;
        BlockType type = game->players[i].nextType;
        switch(type) {
            case BlockType::IBlock: {
                theNextBlock[1][0 + i * 17] = Colour::Blue;
                theNextBlock[1][1 + i * 17] = Colour::Blue;
                theNextBlock[1][2 + i * 17] = Colour::Blue;
                theNextBlock[1][3 + i * 17] = Colour::Blue;
            }
            case BlockType::JBlock: {
                theNextBlock[0][0 + i * 17] = Colour::Red;
                theNextBlock[1][0 + i * 17] = Colour::Red;
                theNextBlock[1][1 + i * 17] = Colour::Red;
                theNextBlock[1][2 + i * 17] = Colour::Red;
            }
            case BlockType::LBlock: {
                theNextBlock[0][2 + i * 17] = Colour::Yellow;
                theNextBlock[1][0 + i * 17] = Colour::Yellow;
                theNextBlock[1][1 + i * 17] = Colour::Yellow;
                theNextBlock[1][2 + i * 17] = Colour::Yellow;
            }
            case BlockType::OBlock: {
                theNextBlock[0][0 + i * 17] = Colour::Purple;
                theNextBlock[0][1 + i * 17] = Colour::Purple;
                theNextBlock[1][0 + i * 17] = Colour::Purple;
                theNextBlock[1][1 + i * 17] = Colour::Purple;
            }
            case BlockType::SBlock: {
                theNextBlock[0][1 + i * 17] = Colour::Green;
                theNextBlock[0][2 + i * 17] = Colour::Green;
                theNextBlock[1][0 + i * 17] = Colour::Green;
                theNextBlock[1][1 + i * 17] = Colour::Green;
            }
            case BlockType::ZBlock: {
                theNextBlock[0][0 + i * 17] = Colour::White;
                theNextBlock[0][1 + i * 17] = Colour::White;
                theNextBlock[1][1 + i * 17] = Colour::White;
                theNextBlock[1][2 + i * 17] = Colour::White;
            }
            case BlockType::TBlock: {
                theNextBlock[0][0 + i * 17] = Colour::Brown;
                theNextBlock[0][1 + i * 17] = Colour::Brown;
                theNextBlock[0][2 + i * 17] = Colour::Brown;
                theNextBlock[1][1 + i * 17] = Colour::Brown;
            }
        }
    }
        
}


// notify() notifies the GraphicsDisplay if a board changes
void GraphicsDisplay::notify(){
    fillBlind();
    fillBlock();
    fillNextBlock();
    // Update Level and Score
    for (int i = 0; i < 2; i += 1) {
        int level = game->players[i].currentLevel;
        int score = game->players[i].getScore();
        xw->drawString(20, 200 + i * 340, static_cast<string>(level), Colour::Black);
        xw->drawString(40, 200 + i * 340, static_cast<string>(score), Colour::Black);
    }
    // Display the board
    for (int i = 0; i < row + 3; i += 1) {
        for (int j = 0; j < 2 * column + 6; j += 1) {
            xw->fillRectangle(j * cellWidth + 40, i * cellHeight, cellWidth, cellHeight, theDisplay[i][j]);
        }
    }
    // Display the next Block
    for (int i = 0; i < 2; i += 1) {
        for (int j = 0; j < 2 * column + 6; j += 1) {
            xw->fillRectangle(j * cellWidth + 420, i * cellHeight, cellWidth, cellHeight, theNextBlock[i][j]);
        }
    }
}