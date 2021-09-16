//Command OK;
#ifndef COMMAND_H
#define COMMAND_H
#include <istream>
#include <ostream>
#include <fstream>
#include "Enums.h"
class Command{
    //Output string for errors
    std::ostream &out;
public:
    //All types of command
    enum type{left, right, down, clockwise, counterclockwise, drop,
        levelup, leveldown,
        norandom, random,
        sequence, restart,
        blind, heavy, force, noeffect, quit,
        I, J, L, O, S, T, Z};
private:
    //Seperate the command string into number and letters
    type getSubCommand(const std::string subCmd);

public:
    //Constructor
    Command(std::ostream& out): out{out}{}
    
    //Get a command
    bool getCommand(std::string cmd, Command::type &c, int& times, bool printCommand);
    
    //Get a number
    static int getNumber(std::string temp, std::ostream& out);
    
    //Convert information into enum BlockType
    static BlockType getBlockType(const char t);
    static BlockType getBlockType(const type t);
};

#endif 
