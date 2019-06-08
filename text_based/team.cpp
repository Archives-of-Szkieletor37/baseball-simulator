#include "team.h"

#include <iostream>
#include <math.h>

#include "database_player_name.h"
#include "game.h"

Team::Team() {

  for (int i = 0; i < NUM_OF_PLAYERS_ON_THE_BENCH; ++i) {
    Players[i] = Player();
  }
  for (int i = 0; i < 9; i++) {
    currentHittersOrder[i] = Players[i];
  }

  classOfThisTeam = HIGHSCHOOL;
  nameOfThisTeam.Name = "ほげほげ";
  nameOfThisTeam.Suffix = "高校";
}

Team::~Team() {
}

void Team::printTeamName() {
  std::cout << nameOfThisTeam.Name << nameOfThisTeam.Suffix;
}

void Team::printHittersCurrentlyAppeared() {
  for (int i = 0; i < 9; i++) {
    std::cout << i + 1 << " ";
    currentHittersOrder[i].printPlayerName();
    std::cout << std::endl;
  }
}
