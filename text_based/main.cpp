#include <bits/stdc++.h>
#include "game.h"

/*Strike_or_Ball Result_of_a_Ball(int power, int meet, int maxspeed, int control) {
  if(power+meet > 4*(maxspeed+control)) 
  return HIT;
  else if(power+meet > maxspeed+control)
  return FOUL;
  else if(power+meet > std::max(maxspeed, control))
  return STRIKE;
  else
  return BALL;
  }*/

/*Result_at_Bat Eval_at_Bat(int power, int meet, int maxspeed, int control) {
  int count_strike = 0;
  int count_ball = 0;
  while(1) {
  switch(Result_of_a_Ball(power,meet,maxspeed,control)) {
  case STRIKE:
  count_strike++;
  case BALL:
  count_ball++;
  case FOUL:
  if(count_strike < 2)
  count_strike++;
  case HIT:
  break;
  }
  if(count_strike == 3) 
  return OUT;
  else if(count_ball == 4)
  return BASE_ON_BALLS;
  }
  }*/

/*struct Bases{
  bool First;
  bool Second;
  bool Third;
  };*/



int main() {

  GAME *new_game;

  srand((unsigned int)time(NULL));

  new_game = new GAME;

  std::pair<int,int> final_score;
  final_score = new_game->Start_Game();

  std::cout << "The final score is\n" << final_score.first << " - " << final_score.second << std::endl;

  delete new_game;

  return 0;
}


