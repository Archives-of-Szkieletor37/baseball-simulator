#ifndef _TEAM_H_
#define _TEAM_H_

#include <string>
#include <array>

#include "player.h"
#include "database_player_name.h"
/*
 * ベンチ入りメンバーを実装する。
 * ベンチメンバーは可変だけど今回は25人にしておく。
 * チームのクラスを作る。
 * メンバ->チーム名、選手
 */
constexpr int NUM_OF_PLAYERS_ON_THE_BENCH = 25;

struct TeamName {
  std::string Name;
  std::string Suffix;
};

enum TeamClass {
  HIGHSCHOOL,
  COLLEGE,
  NPB,
};

class Team {
  private:
    TeamClass classOfThisTeam; 
    TeamName nameOfThisTeam;
    std::array<Player, NUM_OF_PLAYERS_ON_THE_BENCH> Players;
    std::array<Player, 9> currentHittersOrder; //出場中

  public:
    Team();
    ~Team();

    void printTeamName();
    void printHittersCurrentlyAppeared();
};

#endif
