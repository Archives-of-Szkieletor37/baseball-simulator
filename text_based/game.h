#ifndef _GAME_H_
#define _GAME_H_

#include <array>

#include "team.h"

enum ResultAtASingleBall {
  STRIKE,
  BALL,
  HIT, // ヒットではなく、"バットに当たってフェアゾーンに飛んだこと"
  FOUL,
  BUNT,
};

enum ResultAtBat {
  SINGLE,
  DOUBLE, // 二塁打
  TRIPLE, // 三塁打
  HOMERUN,
  WALK, // 四球
  HITBYPITCH, // 死球
  STRIKEOUT,
  GROUNDOUT, // ゴロアウト
  FLYOUT // フライアウト
};

enum InningTopOrBottom {
  TOP, //表
  BOTTOM, //裏
};

enum GameStatus {
  ONGOING,
  END,
};

struct Bases {
  std::array<bool, 3> bases;
};

constexpr int FIRST_BASE = 0;
constexpr int SECOND_BASE = 1;
constexpr int THIRD_BASE = 2;

struct Count {
  int Strike;
  int Ball;
};

class Game {
  private:
    Team Team1,Team2;
    std::array<Team, 2> teams;
    std::pair<int, InningTopOrBottom> currentInningNumber;
    std::array<int, 2> score;
    int teamIdOfOffence;
    int outs;
    Count currentCountOfAtBat;
    std::array<int, 2> numberOfCurrentAtBat; // 現在打席の打順
    Bases currentStatusOfBases;
    GameStatus gameStatus; //true->試合中、false->終了

  public:
    Game();
    ~Game();
    void printScore();
    std::array<int,2> startGame();

  private:
    void startInning();
    void applyTheResultAtBat(ResultAtBat);
    void succeedOuts();
    void changeStatusOfBases(ResultAtBat);
    void updateScoreByTheResultAtBut(ResultAtBat);
    void updateScore(int);
    void succeedInning();
    ResultAtBat startAtBat();
    void succeedCurrentAtBat();
};

#endif
