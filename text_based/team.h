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
constexpr int NUM_OF_PLAYERS_ON_THE_BENCH = 25;

using Flag = bool;

struct PlayerName{
  int firstName; //index of database
  int lastName; //index of database
};

struct TeamName{
  std::string Name;
  std::string Suffix;
};

enum leftOrRight {
  LEFT,
  RIGHT,
  SWITCH, //両打ち
};

enum TeamClass {
  Highschool,
  College,
  Npb,
};

class Player;
class Team{
  private:
    TeamClass classOfThisTeam; 
    TeamName nameOfThisTeam;
    Player* Players[NUM_OF_PLAYERS_ON_THE_BENCH];
    Player* currentHittersOrder[9]; //出場中

  public:
    Team();
    ~Team();

    void printTeamName();
    void printHittersCurrentlyAppeared();
};

class Player{
  private:
    Team* theirTeam;
    PlayerName thisPlayerName; 
    leftOrRight Bats; //右打ち左打ち両打ち
    leftOrRight Throws; //右投げ左投げ

  public:
    Player();
    ~Player();

    void printPlayerName();
    
};


#endif
