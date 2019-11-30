//Command OK;
#include "Command.h"
#include <string>
int Command::getNumber(std::string temp, std::ostream& out){
  int n = 0;
  try{
    n = stoi(temp);
  }catch(...){
    out << "Unable to convert " << temp <<" to a number" <<std::endl;
    exit(-1);
  }
  return n;
}

Command::type Command::getSubCommand(const std::string subCmd){
    std::string temp = "blind";
    int f = (int)temp.find(subCmd);
    if(!f) return type::blind;
    temp = "heavy"; f = (int)temp.find(subCmd);
    if(!f) return type::heavy;
    temp = "force"; f = (int)temp.find(subCmd);
    if(!f) return type::force;
    temp = "quit"; f = (int)temp.find(subCmd);
    if(!f) return type::quit;
    temp = "norandom"; f = (int)temp.find(subCmd);
    if(!f) return type::norandom;
    temp = "sequence"; f = (int)temp.find(subCmd);
    if(!f) return type::sequence;
    if(subCmd != "le" && subCmd != "level"){
        temp = "left"; f = (int)temp.find(subCmd);
        if(!f) return type::left;
        temp = "levelup"; f = (int)temp.find(subCmd);
        if(!f) return type::levelup;
        temp = "leveldown"; f = (int)temp.find(subCmd);
        if(!f) return type::leveldown;
    }
    if(subCmd != "r"){
        temp = "right"; f = (int)temp.find(subCmd);
        if(!f) return type::right;
        temp = "random"; f = (int)temp.find(subCmd);
        if(!f) return type::random;
        temp = "restart"; f = (int)temp.find(subCmd);
        if(!f) return type::restart;
    }
    if(subCmd != "d"){
        temp = "down"; f = (int)temp.find(subCmd);
        if(!f) return type::down;
        temp = "drop"; f = (int)temp.find(subCmd);
        if(!f) return type::drop;
    }
    if(subCmd != "c"){
        temp = "clockwise"; f = (int)temp.find(subCmd);
        if(!f) return type::clockwise;
        temp = "counterclockwise"; f = (int)temp.find(subCmd);
        if(!f) return type::counterclockwise;
    }
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

BlockType Command::getBlockType(const char t){
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

BlockType Command::getBlockType(const type t){
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

void Command::getCommand(std::string cmd, Command::type &c, int& times){
    while(true){
        try{
            std::string subCmd;
            times = stoi(cmd);
            getNumber(cmd, out);
            std::string firstChar;
            for (const char& c : cmd){
                if(c < 48 || c > 57){
                    firstChar = c;
                    break;
                }
            }
            subCmd = cmd.substr(cmd.find(firstChar));
            c = getSubCommand(subCmd);
            out << cmd << std::endl;
        }catch(const char* m){
            out << m << std::endl;
            continue;
        }
        break;
    }
}
