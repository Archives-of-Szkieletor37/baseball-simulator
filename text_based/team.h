#ifndef _TEAM_H_
#define _TEAM_H_
#include <string>
#include "database_player_name.h"
/*
 * ベンチ入りメンバーを実装する。
 * ベンチメンバーは可変だけど今回は25人にしておく。
 * チームのクラスを作る。
 * メンバ->チーム名、選手
 * 選手のクラスを作る。
 * メンバ->名前、右打ち左打ち両打ち、右投げ左投げ
 */
#define NUM_OF_PLAYERS_ON_THE_BENCH 25

using Flag = bool;

typedef struct PLAYER_Name{
  int First_Name; //index of database
  int Last_Name; //index of database
}PLAYER_Name;

typedef struct TEAM_Name{
  std::string Name;
  std::string Suffix;
}TEAM_Name;

enum Left_or_Right {
  LEFT,
  RIGHT,
  SWITCH, //両打ち
};

enum TEAM_Class {
  Highschool,
  College,
  Npb,
};

class PLAYER;
class TEAM{
  private:
    TEAM_Class Team_Class; 
    TEAM_Name Team_Name;
    PLAYER* Players[NUM_OF_PLAYERS_ON_THE_BENCH];
    PLAYER* Current_Players_on_the_Ground[9]; //出場中

  public:
    TEAM();
    ~TEAM();

    void Print_Team_Name();
    void Print_Current_Players_on_the_Ground();
};

class PLAYER{
  private:
    TEAM* Team;
    PLAYER_Name Player_Name; 
    Left_or_Right Bats; //右打ち左打ち両打ち
    Left_or_Right Throws; //右投げ左投げ

  public:
    PLAYER();
    ~PLAYER();

    void Print_Player_Name();
    
};


#endif
