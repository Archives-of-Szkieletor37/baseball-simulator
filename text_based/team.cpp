#include "team.h"

#include <math.h>

#include "database_player_name.h"
#include "game.h"

Team::Team() {

  for (int i = 0; i < NUM_OF_PLAYERS_ON_THE_BENCH; i++) {
    Players[i] = new Player;
  }
  for (int i = 0; i < 9; i++) {
    currentHittersOrder[i] = Players[i];
  }

  classOfThisTeam = Highschool;
  nameOfThisTeam.Name = "ほげほげ";
  nameOfThisTeam.Suffix = "高校";
}

Team::~Team() {
  for (int i = 0; i < NUM_OF_PLAYERS_ON_THE_BENCH; i++) {
    delete Players[i];
  }
}

void Team::printTeamName() {
  std::cout << nameOfThisTeam.Name << nameOfThisTeam.Suffix;
}

void Team::printHittersCurrentlyAppeared() {
  for (int i = 0; i < 9; i++) {
    std::cout << i + 1 << " ";
    currentHittersOrder[i]->printPlayerName();
    std::cout << std::endl;
  }
}

Player::Player() {
  thisPlayerName.firstName = rand() % 2022 + 1; // database[0]がダミーのため
  thisPlayerName.lastName = rand() % 433 + 1;   //同上
  Bats = leftOrRight(rand() % 3);
  Throws = leftOrRight(rand() % 2); //両投げはなし
}

Player::~Player(){};

void Player::printPlayerName() {

  std::cout << getLastNameFromDB(thisPlayerName.lastName).first;
  std::cout << " ";
  std::cout << getFirstNameFromDB(thisPlayerName.firstName).first;
  // std::cout << .first << " " <<
  // DATABASE_Player_NAME::get_firstname(thisPlayerName.firstName).first;
}
