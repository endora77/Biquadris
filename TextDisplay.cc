#include "TextDisplay.h"
#include <vector>
#include <string>
#Include "Enums.h"

// Constructor
TextDisplay::TextDisplay() : row{row + 7}, column{row} {
    // Display the first two rows (Level, score)
    init("Level:");
    init("Score:");
    // Display the dashes
    vector<char> dashes;
    for (int i = 0; i < row; i += 1) {
        row.emplace_back('-');
    }
    theDisplay.emplace_back(dashes);
    // Initialize the board
    for (int i = 3; i < row; i += 1) {
        vector<char> row;
        for (int j = 0; j < column; j += 1) {
            row.emplace_back(' ');
        }
        theDisplay.emplace_back(row);
    }
    // Display the dashes
    theDisplay.emplace_back(dashes);
    // Display the Next
    init("Next:");
}

// Helper function to initialize level, score, and next
void TextDisplay::init(string name) {
    vector<char> row;
    int size = name.length();
    if (name == "Next:") {
        for (int i = 0; i < size; i += 1) {
            row.emplace_back(name[i]);
        }
    } else {
        for (int i = 0; i < size; i += 1) {
            row.emplace_back(name[i]);
        }
        for (int j = 0; j < 4; j += 1) {
            row.emplace_back(' ');
        }
        row.emplace_back('0');
    }
    theDisplay.emplace_back(row);
}


// fillBlind() fills the column 3-9, and row 3-12 with "?" until the player drops a block
void TextDisplay::fillBlind() {
    for (int i = 3, i < 12; i += 1) {
        for (int j = 3; j < 9; j += 1) {
            theDisplay[i][j] = '?';
        }
    }
}


// fillBlock() fills the Block with it's corresponding letter (i.e. j for JBlock)
void TextDisplay::fillBlock() {
    for (int i = 0; i < gridH; i += 1) {
        for (int j = 0; j < gridW; j += 1) {
            BlockType type = grid[i][j]->getType();
            if (type == BlockType::IBlock) {
                theDisplay[i + 3][j] = 'I';
            }
            if (type == BlockType::JBlock) {
                theDisplay[i + 3][j] = 'J';
            }
            if (type == BlockType::LBlock) {
                theDisplay[i + 3][j] = 'L';
            }
            if (type == BlockType::OBlock) {
                theDisplay[i + 3][j] = 'O';
            }
            if (type == BlockType::SBlock) {
                theDisplay[i + 3][j] = 'S';
            }
            if (type == BlockType::ZBlock) {
                theDisplay[i + 3][j] = 'Z';
            }
            if (type == BlockType::TBlock) {
                theDisplay[i + 3][j] = 'T';
            }
        }
    }
}


// fillTopInfo() displays the information on the top 3 rows (i.e. level, score, and and a line)
void TextDisplay::fillTopInfo() {
    int level = board->getLevel();
    int score = board->getScore();
    theDisplay[0][14] = static_cast<char>(level);
    if (score > 9) {
        theDisplay[1][13] = static_cast<char>(score / 10);
        theDisplay[1][14] = static_cast<char>(score % 10);
    }
}



// fillNextBlock() displays the next Block shape in the bottom rows of the board
void fillNextBlock() {
    BlockType type = board.getNextBlock();
    if (type == BlockType::IBlock) {
        theDisplay[row + 6][0] = 'I';
        theDisplay[row + 6][1] = 'I';
        theDisplay[row + 6][2] = 'I';
        theDisplay[row + 6][3] = 'I';
    }
    if (type == BlockType::JBlock) {
        theDisplay[row + 5][0] = 'J';
        theDisplay[row + 6][0] = 'J';
        theDisplay[row + 6][1] = 'J';
        theDisplay[row + 6][2] = 'J';
    }
    if (type == BlockType::LBlock) {
        theDisplay[row + 5][2] = 'L';
        theDisplay[row + 6][0] = 'L';
        theDisplay[row + 6][1] ='L';
        theDisplay[row + 6][2] ='L';
    }
    if (type == BlockType::OBlock) {
        theDisplay[row + 5][0] = 'O';
        theDisplay[row + 5][1] = 'O';
        theDisplay[row + 6][0] = 'O';
        theDisplay[row + 6][1] = 'O';
    }
    if (type == BlockType::SBlock) {
        theDisplay[row + 5][1] = 'S';
        theDisplay[row + 5][2] = 'S';
        theDisplay[row + 6][0] = 'S';
        theDisplay[row + 6][1] = 'S';
    }
    if (type == BlockType::ZBlock) {
        theDisplay[row + 5][0] = 'Z';
        theDisplay[row + 5][1] = 'Z';
        theDisplay[row + 6][1] = 'Z';
        theDisplay[row + 6][2] = 'Z';
    }
    if (type == BlockType::TBlock) {
        theDisplay[row + 5][0] = 'T';
        theDisplay[row + 5][1] = 'T';
        theDisplay[row + 5][2] = 'T';
        theDisplay[row + 6][1] = 'T';
    }
}

std::ostream &TextDisplay::operator<<(std::ostream &out, const TextDisplay &td) {
    int row = td.theDisplay.size();
    for (int i = 0; i < row; i += 1) {
        int column = td.theDisplay[i].size();
        for (int j = 0; j < column; j += 1) {
            out << td.theDisplay[i][j];
        }
        out << endl;
    }
    return out;
}
