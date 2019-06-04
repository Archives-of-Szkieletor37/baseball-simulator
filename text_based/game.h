#ifndef _GAME_H_
#define _GAME_H_

#include <bits/stdc++.h>
#include "team.h"

enum ResultAtASingleBall{
  HIT,
  STRIKE, 
  FOUL,
  BALL,
};

enum ResultAtBat{
  SINGLE_HIT,
  TWO_BASE_HIT,
  THREE_BASE_HIT,
  HOMERUN,
  WALK, //四球
  STRIKEOUT,
  BATTED_BALL_OUT, //スリーバント失敗
};

enum InningTopOrBottom{
  TOP, //表
  BOTTOM, //裏
};

enum GameStatus{
  ONGOING,
  END,
};

struct Bases {
  bool& operator[](int i) {return bases[i];}
  bool bases[3];
};

constexpr int FIRST_BASE = 0;
constexpr int SECOND_BASE = 1;
constexpr int THIRD_BASE = 2;

struct Count {
  int Strike;
  int Ball;
};

class Inning;
class AtBat;

class Game{
  private:
    Team *Team1,*Team2;
    std::pair<Team*, Team*> Teams;
    std::pair<int, InningTopOrBottom> currentInningNumber;
    std::pair<int,int> Score;
    int numberOfCurrentAtBat; // 現在打席の打順
    GameStatus gameStatus; //true->試合中、false->終了
    Inning *inning;

  public:
    Game();
    ~Game();

    void updateScore(int);
    void printScore();
    std::pair<int,int> startGame();
    void succeedInning();
    void succeedCurrentAtBat();
};

class Inning{
  private:
    int Outs;
    Bases currentStatusofBases;
    GameStatus inningStatus;
    AtBat *currentAtBat;

  public:
    Inning();
    ~Inning();

    void startInning(Game*);
    void succeedOuts();
    void applyTheResultAtBat(ResultAtBat, Game*);

  private:
    void changeStatusOfBases(ResultAtBat);
    void updateScoreByTheResultAtBut(ResultAtBat, Game*);
};

class AtBat{
  private:
    Count CurrentCountOfThisAtBat;
    //ResultAtBat eval();

  public:
    AtBat();
    ~AtBat();

    ResultAtBat startAtBat(Game*, Inning*);
};

#endif
