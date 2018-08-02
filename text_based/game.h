#ifndef _GAME_H_
#define _GAME_H_

#include <bits/stdc++.h>
#include "team.h"

enum Result_at_a_Single_ball{
  HIT,
  STRIKE, 
  FOUL,
  BALL,
};

enum Result_at_Bat{
  SINGLE_HIT,
  TWO_BASE_HIT,
  THREE_BASE_HIT,
  HOMERUN,
  WALK, //四球
  STRIKEOUT,
  BATTED_BALL_OUT, //スリーバント失敗
};

enum Inning_Top_or_Bottom{
  TOP, //表
  BOTTOM, //裏
};

enum Status_Ongoing_or_End{
  ONGOING,
  END,
};

typedef struct Bases_ {
  bool& operator[](int i) {return bases[i];}
  bool bases[3];
} Bases;

#define FIRST_BASE 0
#define SECOND_BASE 1
#define THIRD_BASE 2

struct Count {
  int Strike;
  int Ball;
};

class INNING;
class AT_BAT;

class GAME{
  private:
    TEAM *Team1,*Team2;
    std::pair<TEAM*, TEAM*> Teams;
    std::pair<int, Inning_Top_or_Bottom> Current_Inning_Number;
    std::pair<int,int> Score;
    int Current_At_Bat; // 現在打席の打順
    Status_Ongoing_or_End Game_Status; //true->試合中、false->終了
    INNING *inning;

  public:
    GAME();
    ~GAME();

    void Update_Score(int);
    void Print_Score();
    std::pair<int,int> Start_Game();
    void Succeed_Inning();
    void Succeed_Current_At_Bat();
};

class INNING{
  private:
    int Outs;
    Bases Bases_Status;
    Status_Ongoing_or_End Inning_Status;
    AT_BAT *at_bat;

  public:
    INNING();
    ~INNING();

    void Start_Inning(GAME*);
    void Succeed_Outs();
    void Apply_the_Result_at_Bat(Result_at_Bat, GAME*);

  private:
    void Change_Bases_Status(Result_at_Bat);
    void Add_Score_by_the_Result_at_Bat(Result_at_Bat, GAME*);
};

class AT_BAT{
  private:
    Count Count_at_Bat;
    //Result_at_Bat eval();

  public:
    AT_BAT();
    ~AT_BAT();

    Result_at_Bat Start_At_Bat(GAME*, INNING*);
};

#endif
