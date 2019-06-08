#include "player.h"

#include <iostream>

#include "database_player_name.h"

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
