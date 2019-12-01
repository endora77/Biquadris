//Game could be used unmodified
#include <string>
#include <iostream>
#include <fstream>
#include "Game.h"
#include "TextDisplay.h"

using namespace std;
//Arguments settings
enum argType{Ttext, Tseed, Tscript1, Tscript2, Tstartlevel, Tplayer1, Tplayer2, Twidth, Theight};
const std::string arguments[] = {"-text", "-seed", "-scriptfile1", "-scriptfile2", "-startlevel", "-player1", "-player2", "-width", "-height"};
const int numArgs = 9;

bool used[9] = {false};
//Get the arguments
void getArguments(int argc, char* argv[], string& p1, string& p2, string& f1, string& f2, int& seed, int& startlevel, int& w, int& h, bool &text);
void getMoreArguments(istream &in, string& p1, string& p2, string& f1, string& f2, int& seed, int& startlevel, int& w, int& h, bool &text);
//run main
int main(int argc, char *argv[]) {
    string f1, f2, p1 = "player1", p2 = "player2";
    bool text = false;
    int seed = 0;
    int startlevel = 0;
    int w = 11, h = 15;

    getArguments(argc, argv, p1, p2, f1, f2, seed, startlevel, w, h, text);
    cout << "p1, p2, seed, f1, f2, startlevel, h, w"<<endl;
    cout << p1<<" "<<p2<<" "<<seed<<" "<<f1<<" "<<f2<<" "<<startlevel<<" "<<h<<" "<<w<<endl;
    std::vector<unique_ptr<Observer>> displays;
    

    Game g{std::cin, std::cout};
    displays.emplace_back(make_unique<TextDisplay>(&g, h, w));
    while(true){
        if(!g.Init(p1, p2, seed, f1, f2, startlevel, std::move(displays), h, w)) break;
        else{
            std::cout << "Please specify a new level or specify both sequence files(enter one command at a time)" << endl;
            getMoreArguments(std::cin, p1, p2, f1, f2, seed, startlevel, w, h, text);
        }
    }

    cout << "Successfully initialized the game."<<endl;
    g.run();
}

void getMoreArguments(istream &in, string& p1, string& p2, string& f1, string& f2, int& seed, int& startlevel, int& w, int& h, bool &text){
    string arg1;
    string arg2;
    if(in >> arg1){
        for(int j = 0; j < numArgs; j ++){
            if(arguments[j].compare(arg1) == 0){
                used[j] = true;
                if(j == Ttext){
                    text = true;
                    break;
                }
                else{
                    if(!(in >> arg2)){
                        cout << "Expecting one more word after "<<arg1<<", please enter again."<<endl;
                        cout << endl;
                        return;
                    }
                    else{
                        switch(j){
                            case Tseed:{
                                string temp = arg2;
                                seed = Command::getNumber(temp, std::cout);
                                break;
                            }
                            case Tstartlevel:{
                                string temp = arg2;
                                startlevel = Command::getNumber(temp, std::cout);
                                break;
                            }
                            case Twidth:{
                                string temp = arg2;
                                w = Command::getNumber(temp, std::cout);
                                break;
                            }
                            case Theight:{
                                string temp = arg2;
                                h = Command::getNumber(temp, std::cout);
                                break;
                            }
                            case Tplayer1:{
                                p1 = arg2;
                                break;
                            }
                            case Tplayer2:{
                                p2 = arg2;
                                break;
                            }
                            case Tscript1:{
                                f1 = arg2;
                                break;
                            }
                            default:{
                                f2 = arg2;
                                break;
                            }
                        }
                    }
                    break;
                }
            }
        }
    }
}
void getArguments(int argc, char* argv[], string& p1, string& p2, string& f1, string& f2, int& seed, int& startlevel, int& w, int& h, bool &text){
  for(int i = 1; i < argc; i++){
      for(int j = 0; j < numArgs; j ++){
          if(arguments[j].compare(argv[i]) == 0){
              used[j] = true;
              if(j == Ttext){
                  text = true;
                  break;
              }
              else{
                  if(i >= argc - 1){
                      cout << "Expecting one more word after "<<argv[i]<<endl;
                      exit(-1);
                  }
                  if( i < argc - 1){
                      i++;
                      switch(j){
                          case Tseed:{
                              string temp = argv[i];
                              seed = Command::getNumber(temp, std::cout);
                              break;
                          }
                          case Tstartlevel:{
                              string temp = argv[i];
                              startlevel = Command::getNumber(temp, std::cout);
                              break;
                          }
                          case Twidth:{
                              string temp = argv[i];
                              w = Command::getNumber(temp, std::cout);
                              break;
                          }
                          case Theight:{
                              string temp = argv[i];
                              h = Command::getNumber(temp, std::cout);
                              break;
                          }
                          case Tplayer1:{
                              p1 = argv[i];
                              break;
                          }
                          case Tplayer2:{
                              p2 = argv[i];
                              break;
                          }
                          case Tscript1:{
                              f1 = argv[i];
                              break;
                          }
                          default:{
                              f2 = argv[i];
                              break;
                          }
                      }
                  }
              }
          }
      }
  }
    if(startlevel == 0){
        if(!f1.size() || !f2.size()){
            cout <<"Missing sequence files since it is starting at level 0" <<endl;
            exit(-1);
        }
    }
    if(startlevel > 4 || startlevel < 0){
        cout << "startlevel is out of range." << std::endl;
        exit(-1);
    }
}



// int main(int argc, char *argv[]) {
//   cin.exceptions(ios::eofbit|ios::failbit);
//   string cmd;
//   int times;
//   string subCmd;
//   string restCmd;

//   try {
//   while (true){
//     cin >> cmd;
//     // check if cmd has multiplier prefix and separate the prefix and the command
//     for (int i = 0; i < cmd.length(); ++i){
//       if ( isdigit(cmd[i]) ) {
// 	      subCmd += cmd[i];
//       } else {
// 	      restCmd = cmd.substr(i);
//       }
//     }
//     times = stoi(subCmd);
    
//     // distinguish the abbreviation of command

//     if ( subCmd == "lef" ) { 
//       subCmd = "left";
//     } else if ((subCmd == "ri") || (subCmd == "rig") || (subCmd == "righ")) {
//       subCmd = "right";
//     } else if ((subCmd == "do") || (subCmd == "dow")) {
//       subCmd = "down";
//     } else if ((subCmd == "cl") || (subCmd == "clo") || (subCmd == "cloc") || (subCmd == "clock") || (subCmd == "clockw") ||
// 		(subCmd == "clockwi") || (subCmd == "clockwis")) {
//       subCmd = "clockwise";
//     } else if ((subCmd == "co") || (subCmd == "cou") || (subCmd == "coun") || (subCmd == "count") || (subCmd == "counte") ||
// 		(subCmd == "counter") || (subCmd == "counterc") || (subCmd == "countercl") || (subCmd == "counterclo") ||
// 		(subCmd == "countercloc") || (subCmd == "counterclock") || (subCmd == "counterclockw") || (subCmd == "counterclockwi")) ||
// 		(subCmd == "counterclockwis") {
//       subCmd = "counterclockwise";
//     } else if ((subCmd == "dr") || (subCmd == "dro")) {
//       subCmd = "drop";
//     } else if (subCmd == "levelu") {
//       subCmd = "levelup";
//     } else if ((subCmd == "leveld") || (subCmd == "leveldo") || (subCmd == "leveldow")) {
//       subCmd = "leveldown";
//     } else if ((subCmd == "n") || (subCmd == "no") || (subCmd == "nor") || (subCmd == "nora") || (subCmd == "noran") ||
// 		(subCmd == "norand") || (subCmd == "norando")) {
//       subCmd = "norandom";
//     } else if ((subCmd == "ra") || (subCmd == "ran") || (subCmd == "rand") || (subCmd == "rando")) {
//       subCmd = "random";
//     } else if ((subCmd == "s") || (subCmd == "se") || (subCmd == "seq") || (subCmd == "sequ") || (subCmd == "seque") ||
// 		(subCmd == "sequen") || (subCmd == "sequenc")) {
//       subCmd = "sequence";
//     } else if ((subCmd == "re") || (subCmd == "res") || (subCmd == "rest") || (subCmd == "resta") || (subCmd == "restar")) {
//       subCmd = "restart";
//     }

//     // run commands several times (it needed)
//     for (int t = 0; t < times; ++t){
      
//       if (cmd == "left"){

//       } else if (cmd == "right"){

//       } else if (cmd == "down"){

//       } else if (cmd == "clockwise"){

//       } else if (cmd == "counterclockwise"){

//       } else if (cmd == "drop"){

//       } else if (cmd == "levelup"){

//       } else if (cmd == "leveldown"){

//       } else if (cmd == "norandom"){
// 	      cin >> cmd;
// 	      // now cmd is the sequence file

// 	      break;                    // multiplier prefix has no effect on this command;
//       } else if (cmd == "random"){
	
// 	      break;                    // multiplier prefix has no effect on this command;
//       } else if (cmd == "sequence"){
// 	      cin >> cmd;
// 	      // now cmd is the sequence file of blocks
// 	      ifstream myCmds;
// 	      myCmds.open(cmd);
// 	      char c;
// 	      while (myCmds.get(c)){
// 	        if (c == 'I'){
	
// 	        } else if (c == 'J'){

//           } else if (c == 'L'){

//           } else if (c == 'O'){

//           } else if (c == 'S'){

//           } else if (c == 'Z'){

//           } else if (c == 'T'){
	
// 	        }
//         } 
// 	      myfile.close();
//       } else if (cmd == "restart"){

//         break; // multiplier prefix has no effect on this command;	
//       } else if (cmd == "I"){
      
//       } else if (cmd == "J"){

//       } else if (cmd == "L"){

//       } else if (cmd == "O"){

//       } else if (cmd == "S"){

//       } else if (cmd == "Z"){

//       } else if (cmd == "T"){

//       }
//     }
//   }
//   }   
//   catch (ios::failure &) {}  // Any I/O failure quits
// }        
