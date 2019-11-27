#include <string>
#include <iostream>
#include <fstream>
using namespace std;


int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;
  int times;
  string subCmd;
  string restCmd;

  try {
  while (true){
    cin >> cmd;
    // check if cmd has multiplier prefix and separate the prefix and the command
    for (int i = 0; i < cmd.length(); ++i){
      if ( isdigit(cmd[i]) ) {
	      subCmd += cmd[i];
      } else {
	      restCmd = cmd.substr(i);
      }
    }
    times = stoi(subCmd);
    
    // distinguish the abbreviation of command

    if ( subCmd == "lef" ) { 
      subCmd = "left";
    } else if ((subCmd == "ri") || (subCmd == "rig") || (subCmd == "righ")) {
      subCmd = "right";
    } else if ((subCmd == "do") || (subCmd == "dow")) {
      subCmd = "down";
    } else if ((subCmd == "cl") || (subCmd == "clo") || (subCmd == "cloc") || (subCmd == "clock") || (subCmd == "clockw") ||
		(subCmd == "clockwi") || (subCmd == "clockwis")) {
      subCmd = "clockwise";
    } else if ((subCmd == "co") || (subCmd == "cou") || (subCmd == "coun") || (subCmd == "count") || (subCmd == "counte") ||
		(subCmd == "counter") || (subCmd == "counterc") || (subCmd == "countercl") || (subCmd == "counterclo") ||
		(subCmd == "countercloc") || (subCmd == "counterclock") || (subCmd == "counterclockw") || (subCmd == "counterclockwi") ||
		(subCmd == "counterclockwis")) {
      subCmd = "counterclockwise";
    } else if ((subCmd == "dr") || (subCmd == "dro")) {
      subCmd = "drop";
    } else if (subCmd == "levelu") {
      subCmd = "levelup";
    } else if ((subCmd == "leveld") || (subCmd == "leveldo") || (subCmd == "leveldow")) {
      subCmd = "leveldown";
    } else if ((subCmd == "n") || (subCmd == "no") || (subCmd == "nor") || (subCmd == "nora") || (subCmd == "noran") ||
		(subCmd == "norand") || (subCmd == "norando")) {
      subCmd = "norandom";
    } else if ((subCmd == "ra") || (subCmd == "ran") || (subCmd == "rand") || (subCmd == "rando")) {
      subCmd = "random";
    } else if ((subCmd == "s") || (subCmd == "se") || (subCmd == "seq") || (subCmd == "sequ") || (subCmd == "seque") ||
		(subCmd == "sequen") || (subCmd == "sequenc")) {
      subCmd = "sequence";
    } else if ((subCmd == "re") || (subCmd == "res") || (subCmd == "rest") || (subCmd == "resta") || (subCmd == "restar")) {
      subCmd = "restart";
    }

    // run commands several times (it needed)
    for (int t = 0; t < times; ++t){
      
      if (cmd == "left"){

      } else if (cmd == "right"){

      } else if (cmd == "down"){

      } else if (cmd == "clockwise"){

      } else if (cmd == "counterclockwise"){

      } else if (cmd == "drop"){

      } else if (cmd == "levelup"){

      } else if (cmd == "leveldown"){

      } else if (cmd == "norandom"){
	      cin >> cmd;
	      // now cmd is the sequence file

	      break;                    // multiplier prefix has no effect on this command;
      } else if (cmd == "random"){
	
	      break;                    // multiplier prefix has no effect on this command;
      } else if (cmd == "sequence"){
	      cin >> cmd;
	      // now cmd is the sequence file of blocks
	      ifstream myCmds;
	      myCmds.open(cmd);
	      char c;
	      while (myCmds.get(c)){
	        if (c == 'I'){
	
	        } else if (c == 'J'){

          } else if (c == 'L'){

          } else if (c == 'O'){

          } else if (c == 'S'){

          } else if (c == 'Z'){

          } else if (c == 'T'){
	
	        }
        } 
	      myfile.close();
      } else if (cmd == "restart"){

        break; // multiplier prefix has no effect on this command;	
      } else if (cmd == "I"){
      
      } else if (cmd == "J"){

      } else if (cmd == "L"){

      } else if (cmd == "O"){

      } else if (cmd == "S"){

      } else if (cmd == "Z"){

      } else if (cmd == "T"){

      }
    }
  }
  }   
  catch (ios::failure &) {}  // Any I/O failure quits
}        
