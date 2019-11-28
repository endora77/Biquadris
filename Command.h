#ifndef COMMAND_H
#define COMMAND_H
#include <istream>
#include <ostream>
class Command{
    //text, seed, scriptfile1, scriptfiel2, startlevel,
public:
//    enum type{move, level, rand, file, restart, setBlock, restart, seed, specialAction};
    enum type{left, right, down, clockwise, counterclockwise, drop,
            levelup, leveldown, 
            norandom, random, 
            sequence, restart,
            blind, heavy, force, quit,
            I, J, L, O, S, T, Z};

private:
    void seperateCommand(const std::string cmd, std::string& subCmd, int& times){
        times = stoi(cmd);
        std::string firstChar;
        for (const char& c : cmd){
            if(c < 48 || c > 57){
                firstChar = c;
                break;
            }
        }
        subCmd = cmd.substr(cmd.find(firstChar));
    }

    type getSubCommand(const std::string subCmd){
        if ( subCmd == "lef" ) { 
            return type::left;
        } else if ((subCmd == "ri") || (subCmd == "rig") || (subCmd == "righ")) {
            return type::right;
        } else if ((subCmd == "do") || (subCmd == "dow")) {
            return type::down;
        } else if ((subCmd == "cl") || (subCmd == "clo") || (subCmd == "cloc") || (subCmd == "clock") || (subCmd == "clockw") ||
            (subCmd == "clockwi") || (subCmd == "clockwis")) {
            return type::clockwise;
        } else if ((subCmd == "co") || (subCmd == "cou") || (subCmd == "coun") || (subCmd == "count") || (subCmd == "counte") ||
            (subCmd == "counter") || (subCmd == "counterc") || (subCmd == "countercl") || (subCmd == "counterclo") ||
            (subCmd == "countercloc") || (subCmd == "counterclock") || (subCmd == "counterclockw") || (subCmd == "counterclockwi") ||
            (subCmd == "counterclockwis")) {
            return type::counterclockwise;
        }else if ((subCmd == "dr") || (subCmd == "dro")) {
            return type::drop;
        } else if (subCmd == "levelu") {
            return type::levelup;
        } else if ((subCmd == "leveld") || (subCmd == "leveldo") || (subCmd == "leveldow")) {
            return type::leveldown;
        } else if ((subCmd == "n") || (subCmd == "no") || (subCmd == "nor") || (subCmd == "nora") || (subCmd == "noran") ||
            (subCmd == "norand") || (subCmd == "norando")) {
            return type::norandom;
        } else if ((subCmd == "ra") || (subCmd == "ran") || (subCmd == "rand") || (subCmd == "rando")) {
            return type::random;
        } else if ((subCmd == "s") || (subCmd == "se") || (subCmd == "seq") || (subCmd == "sequ") || (subCmd == "seque") ||
            (subCmd == "sequen") || (subCmd == "sequenc")) {
            return type::sequence;
        } else if ((subCmd == "re") || (subCmd == "res") || (subCmd == "rest") || (subCmd == "resta") || (subCmd == "restar")) {
            return type::restart;
        }
        std::string temp = "blind";
        int f = temp.find(subCmd); 
        if(!f) return type::blind;
        std::string temp = "heavy";
        int f = temp.find(subCmd); 
        if(!f) return type::heavy;
        std::string temp = "force";
        int f = temp.find(subCmd); 
        if(!f) return type::force;
        std::string temp = "quit";
        int f = temp.find(subCmd); 
        if(!f) return type::quit;
        if(subCmd.length() == 1){
            switch(subCmd[0]){
                case 'i': return I;
                case 'j': return J;
                case 'l': return L;
                case 'o': return O;
                case 's': return S;
                case 't': return T;
                case 'z': return Z;
            }
        }
        throw "Not a valid command";
    }

public:
    static BlockType getBlockType(const char t){
            switch(t){
                case 'i': return BlockType::IBlock;
                case 'j': return BlockType::JBlock;
                case 'l': return BlockType::LBlock;
                case 'o': return BlockType::OBlock;
                case 's': return BlockType::SBlock;
                case 't': return BlockType::TBlock;
                case 'z': return BlockType::ZBlock;
            }
            throw "Not a valid Block type";
    }
    static BlockType getBlockType(const type t){
            switch(t){
                case I: return BlockType::IBlock;
                case J: return BlockType::JBlock;
                case L: return BlockType::LBlock;
                case O: return BlockType::OBlock;
                case S: return BlockType::SBlock;
                case T: return BlockType::TBlock;
                case Z: return BlockType::ZBlock;
            }
            throw "Not a valid Block type";
    }
    void getCommand(std::istream& in, type &c, int& times){
        while(true){
            try{
                std::string cmd;
                std::string subCmd;
                int times;
                in >>cmd;
                seperateCommand(cmd, subCmd, times);
                type c = getSubCommand(subCmd);
            }catch(const char* m){
                std::cout << m << std::endl;
                continue;
            }
            break;
        }
    }
};

#endif