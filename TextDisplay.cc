#include "TextDisplay.h"
using namespace std;
// Constructor
TextDisplay::TextDisplay(Game* game, int row, int column) : row{row + 10}, column{column}, out{std::cout}, Display{game} {
    // Display the first two rows (Level, score)
    init("Level:");
    init("Score:");
    // Display the dashes
    init("dashes");
    // Initialize the board
    for (int i = 0; i < row + 3; i += 1) {
        init("empty");
    }
    // Display the dashes
    init("dashes");
    // Display the Next
    init("Next:");
    init("empty");
    init("empty");
}

// Helper function to initialize boards for two players
void TextDisplay::init(string type) {
    vector<char> r;
    int size = (int)type.length();
    if (type == "Next:") {
        // Set up for Player 1
        for (int i = 0; i < size; i += 1) {
            r.emplace_back(type[i]);
        }
        // Print middle empty space
        for (int i = 0; i < 12; i += 1) {
            r.emplace_back(' ');
        }
        // Set up for Player 2
        for (int i = 0; i < size; i += 1) {
            r.emplace_back(type[i]);
        }
        for (int i = 0; i < 6; i += 1) {
            r.emplace_back(' ');
        }
    } else if (type == "dashes") {
        // Set up for Player 1
        for (int i = 0; i < column; i += 1) {
            r.emplace_back('-');
        }
        // Print middle empty space
        for (int i = 0; i < 6; i += 1) {
            r.emplace_back(' ');
        }
        // Set up for Player 2
        for (int i = 0; i < column; i += 1) {
            r.emplace_back('-');
        }
    } else if (type == "empty") {
        // Set up for Player 1
        for (int i = 0; i < (2 * column + 6); i += 1) {
            r.emplace_back(' ');
        }
    } else { // type is "Level:" or "Score:"
        // Set up for Player 1
        for (int i = 0; i < size; i += 1) {
            r.emplace_back(type[i]);
        }
        for (int j = 0; j < 4; j += 1) {
            r.emplace_back(' ');
        }
        r.emplace_back('0');
        // Print middle empty space
        for (int i = 0; i < 6; i += 1) {
            r.emplace_back(' ');
        }
        // Set up for Player 2
        for (int i = 0; i < size; i += 1) {
            r.emplace_back(type[i]);
        }
        for (int j = 0; j < 4; j += 1) {
            r.emplace_back(' ');
        }
        r.emplace_back('0');
    }
    theDisplay.emplace_back(r);
}


// fillBlind() fills the column 3-9, and row 3-12 with "?" until the player drops a block
void TextDisplay::fillBlind() {
    // Check if one or more players has blind effect
    for (int i = 0; i < 2; i += 1) {
        if (game->players[i].restriction == Restriction::blind) {
            for (int j = 3 + (i * 11) + (i * 6); j < 12 + (i * 11) + (i * 6); j += 1) {
                for (int k = 3; k < 9; k += 1) {
                    theDisplay[j][k] = '?';
                }
            }
        }
    }
}


// fillBlock() fills the Block with the corresponding letter (i.e. j for JBlock)
void TextDisplay::fillBlock() {
    // Access players
    for (int i = 0; i < 2; i += 1) {
        // Access each row
        for (int j = 0; j < game->players[i].board->gridH; j += 1) {
            // Access each column
            for (int k = 0; k < game->players[i].board->gridW; k += 1) {
                if(!game->players[i].board->grid[j][k])theDisplay[j + 3][k + i * 17] = ' ';
                else{
                    BlockType type = game->players[i].board->grid[j][k]->getType();
                    if (type == BlockType::IBlock) {
                        theDisplay[j + 3][k + i * 17] = 'I';
                    }
                    if (type == BlockType::JBlock) {
                        theDisplay[j + 3][k + i * 17] = 'J';
                    }
                    if (type == BlockType::LBlock) {
                        theDisplay[j + 3][k + i * 17] = 'L';
                    }
                    if (type == BlockType::OBlock) {
                        theDisplay[j + 3][k + i * 17] = 'O';
                    }
                    if (type == BlockType::SBlock) {
                        theDisplay[j + 3][k + i * 17] = 'S';
                    }
                    if (type == BlockType::ZBlock) {
                        theDisplay[j + 3][k + i * 17] = 'Z';
                    }
                    if (type == BlockType::TBlock) {
                        theDisplay[j + 3][k + i * 17] = 'T';
                    }
                    if (type == BlockType::StarBlock) {
                        theDisplay[j + 3][k + i * 17] = '*';
                    }
                }
            }
        }
    }
}


// fillTopInfo() displays the information on the top 3 rows (i.e. level, score, and and a line)
void TextDisplay::fillTopInfo() {
    for (int i = 0; i < 2; i += 1) {
        int level = game->players[i].currentLevel;
        int score = game->players[i].getScore();
        theDisplay[0][10 + i * 17] = static_cast<char>(level + 48);
        if (score < 10) {
            theDisplay[1][10 + i * 17] = static_cast<char>(score + 48);
        } else {
            theDisplay[1][9 + i * 17] = static_cast<char>(score / 10 + 48);
            theDisplay[1][10 + i * 17] = static_cast<char>(score % 10 + 48);
        }
    }
}



// fillNextBlock() displays the next Block shape in the bottom rows of the board
void TextDisplay::fillNextBlock() {
    for (int i = row - 2; i < row; i += 1) {
        for (int j = 0; j < 28; j += 1) {
            theDisplay[i][j] = ' ';
        }
    }
    for (int i = 0; i < 2; i += 1) {
        if(!game->players[i].playing) continue;
        BlockType type = game->players[i].nextType;
        if (type == BlockType::IBlock) {
            theDisplay[row - 1][0 + i * 17] = 'I';
            theDisplay[row - 1][1 + i * 17] = 'I';
            theDisplay[row - 1][2 + i * 17] = 'I';
            theDisplay[row - 1][3 + i * 17] = 'I';
        }
        if (type == BlockType::JBlock) {
            theDisplay[row - 2][0 + i * 17] = 'J';
            theDisplay[row - 1][0 + i * 17] = 'J';
            theDisplay[row - 1][1 + i * 17] = 'J';
            theDisplay[row - 1][2 + i * 17] = 'J';
        }
        if (type == BlockType::LBlock) {
            theDisplay[row - 2][2 + i * 17] = 'L';
            theDisplay[row - 1][0 + i * 17] = 'L';
            theDisplay[row - 1][1 + i * 17] ='L';
            theDisplay[row - 1][2 + i * 17] ='L';
        }
        if (type == BlockType::OBlock) {
            theDisplay[row - 2][0 + i * 17] = 'O';
            theDisplay[row - 2][1 + i * 17] = 'O';
            theDisplay[row - 1][0 + i * 17] = 'O';
            theDisplay[row - 1][1 + i * 17] = 'O';
        }
        if (type == BlockType::SBlock) {
            theDisplay[row - 2][1 + i * 17] = 'S';
            theDisplay[row - 2][2 + i * 17] = 'S';
            theDisplay[row - 1][0 + i * 17] = 'S';
            theDisplay[row - 1][1 + i * 17] = 'S';
        }
        if (type == BlockType::ZBlock) {
            theDisplay[row + 8 - 10][0 + i * 17] = 'Z';
            theDisplay[row + 8 - 10][1 + i * 17] = 'Z';
            theDisplay[row + 9 - 10][1 + i * 17] = 'Z';
            theDisplay[row + 9 - 10][2 + i * 17] = 'Z';
        }
        if (type == BlockType::TBlock) {
            theDisplay[row + 8 - 10][0 + i * 17] = 'T';
            theDisplay[row + 8 - 10][1 + i * 17] = 'T';
            theDisplay[row + 8 - 10][2 + i * 17] = 'T';
            theDisplay[row + 9 - 10][1 + i * 17] = 'T';
        }
    }
}

void TextDisplay::notify() {
    fillTopInfo();
    fillBlind();
    fillBlock();
    fillNextBlock();
    print();
}

void TextDisplay::print(){
    out << endl;
    out << "*****************************************"<<endl;
    int columns = (int)(2*column + 6);
    for (int i = 0; i < row; i += 1) {
        for (int j = 0; j < columns; j += 1) {
            out << theDisplay[i][j];
        }
        out << endl;
    }
    out << "*****************************************"<<endl;
    out << endl;
}
