//Command OK;
#ifndef COMMAND_H
#define COMMAND_H
#include <istream>
#include <ostream>
#include <fstream>
#include "Enums.h"
class Command{
    //text, seed, scriptfile1, scriptfiel2, startlevel,
    std::ostream &out;
public:
//    enum type{move, level, rand, file, restart, setBlock, restart, seed, specialAction};
    enum type{left, right, down, clockwise, counterclockwise, drop,
            levelup, leveldown, 
            norandom, random, 
            sequence, restart,
            blind, heavy, force, quit,
            I, J, L, O, S, T, Z};
    Command(std::ostream& out): out{out}{}
private:
    type getSubCommand(const std::string subCmd);

public:
    static BlockType getBlockType(const char t);
    static BlockType getBlockType(const type t);
    static int getNumber(std::string temp, std::ostream& out);
    void getCommand(std::string cmd, Command::type &c, int& times);
};

#endif 
