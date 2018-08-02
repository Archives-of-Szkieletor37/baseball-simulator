#include "game.h"
#include "team.h"
#include "database_player_name.h"
#include <math.h>

TEAM::TEAM() {

  for(int i=0; i<NUM_OF_PLAYERS_ON_THE_BENCH; i++) {
   Players[i] = new PLAYER;
  }
  for(int i=0; i<9; i++) {
    Current_Players_on_the_Ground[i] = Players[i];
  }

  Team_Class = Highschool;
  Team_Name.Name = "ほげほげ";
  Team_Name.Suffix = "高校";
}

TEAM::~TEAM() {
  for(int i=0; i<NUM_OF_PLAYERS_ON_THE_BENCH; i++) {
    delete Players[i];
  }
}

void TEAM::Print_Team_Name() {
  std::cout << Team_Name.Name << Team_Name.Suffix;
}

void TEAM::Print_Current_Players_on_the_Ground() {
  for(int i=0; i<9; i++) {
    std::cout << i+1 << " ";
    Current_Players_on_the_Ground[i]->Print_Player_Name();
    std::cout << std::endl;
  }
}

PLAYER::PLAYER() {
    Player_Name.First_Name = rand()%2022+1;//database[0]がダミーのため
    Player_Name.Last_Name = rand()%433+1; //同上
    Bats = Left_or_Right(rand()%3);
    Throws = Left_or_Right(rand()%2); //両投げはなし
}

PLAYER::~PLAYER() {
};

void PLAYER::Print_Player_Name() {

  std::cout << get_lastname_fromdb(Player_Name.Last_Name).first;
  std::cout << " ";
  std::cout << get_firstname_fromdb(Player_Name.First_Name).first;
 //std::cout << .first << " " << DATABASE_PLAYER_NAME::get_firstname(Player_Name.First_Name).first;
}

