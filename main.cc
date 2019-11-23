#include <string>
#include <iostream>
#include <fstream>
using namespace std;


int main(int argc, char *argv[]) {
  string cmd;
  int times;
  string subCmd;
  string restCmd;

  while (true){
    cin >> cmd;
    int times = 0;
    for (int i = 0; i < cmd.length; ++i){
      if ( isdigit(cmd[i]) ) {
	subCmd += cmd[i];
      } else {
	restCmd = cmd.substr(i);
	for ( int i = 0; i < 
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
    } else if (cmd == "random"){

    } else if (cmd == "sequence"){
	cin >> cmd;
	// now cmd is the file containing a sequence of cmds
	ofstream myCmds;
	myCmds.open(cmd);
	
	myfile.close();
    } else if (cmd == "")
