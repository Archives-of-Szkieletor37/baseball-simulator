#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>

using Flag = bool;

struct PlayerName {
  int firstName; //index of database
  int lastName; //index of database
};

enum leftOrRight {
  LEFT,
  RIGHT,
  SWITCH, //両打ち
};

class Player {
  private:
    PlayerName thisPlayerName; 
    leftOrRight Bats; //右打ち左打ち両打ち
    leftOrRight Throws; //右投げ左投げ

  public:
    Player();
    ~Player();

    void printPlayerName();

};

#endif
