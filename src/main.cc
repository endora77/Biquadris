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

//Track the used arguments
bool used[9] = {false};

//Get the arguments
void getArguments(int argc, char* argv[], string& p1, string& p2, string& f1, string& f2, int& seed, int& startlevel, int& w, int& h, bool &text);
void getMoreArguments(istream &in, string& p1, string& p2, string& f1, string& f2, int& seed, int& startlevel, int& w, int& h, bool &text);

//Output direction
std::ostream &out = cout;

//Main function
int main(int argc, char *argv[]) {
    string f1, f2, p1 = "player1", p2 = "player2";
    bool text = false;
    int seed = 0;
    int startlevel = 0;
    int w = 11, h = 15;

    getArguments(argc, argv, p1, p2, f1, f2, seed, startlevel, w, h, text);
    //out << "p1, p2, seed, f1, f2, startlevel, h, w"<<endl;
    //out << p1<<" "<<p2<<" "<<seed<<" "<<f1<<" "<<f2<<" "<<startlevel<<" "<<h<<" "<<w<<endl;
    std::vector<unique_ptr<Observer>> displays;
    

    Game g{std::cin, out};
    displays.emplace_back(make_unique<TextDisplay>(&g, h, w));
    //Try to initlaize the game, if failed, tries to ask for more arguments
    while(true){
        if(!g.Init(p1, p2, seed, f1, f2, startlevel, std::move(displays), h, w)) break;
        else{
            out << "Please specify a new level or specify both sequence files(enter commands one at a time)" << endl;
            getMoreArguments(std::cin, p1, p2, f1, f2, seed, startlevel, w, h, text);
        }
    }
    out << "Successfully initialized the game."<<endl;
    g.run();
}

//If nessecary arguments are missing, have to take more arguments from terminal
//Comparing string with string
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
                        out << "Expecting one more word after "<<arg1<<", please enter again."<<endl;
                        out << endl;
                        return;
                    }
                    else{
                        switch(j){
                            case Tseed:{
                                string temp = arg2;
                                seed = Command::getNumber(temp, out);
                                break;
                            }
                            case Tstartlevel:{
                                string temp = arg2;
                                startlevel = Command::getNumber(temp, out);
                                break;
                            }
                            case Twidth:{
                                string temp = arg2;
                                w = Command::getNumber(temp, out);
                                break;
                            }
                            case Theight:{
                                string temp = arg2;
                                h = Command::getNumber(temp, out);
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

//Take the initizl arguments
//Compare char* argv[] with string
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
                      out << "Expecting one more word after "<<argv[i]<<endl;
                      exit(-1);
                  }
                  if( i < argc - 1){
                      i++;
                      switch(j){
                          case Tseed:{
                              string temp = argv[i];
                              seed = Command::getNumber(temp, out);
                              break;
                          }
                          case Tstartlevel:{
                              string temp = argv[i];
                              startlevel = Command::getNumber(temp, out);
                              break;
                          }
                          case Twidth:{
                              string temp = argv[i];
                              w = Command::getNumber(temp, out);
                              break;
                          }
                          case Theight:{
                              string temp = argv[i];
                              h = Command::getNumber(temp, out);
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
            out <<"Missing sequence files since it is starting at level 0" <<endl;
            exit(-1);
        }
    }
    if(startlevel > 4 || startlevel < 0){
        out << "startlevel is out of range." << std::endl;
        exit(-1);
    }
}
