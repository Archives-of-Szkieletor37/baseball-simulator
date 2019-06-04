#include <iostream>

#include "database_player_name.h"
#include "game.h"

int main() {

  Game *newGame;

  srand((unsigned int)time(NULL));

  newGame = new Game;

  std::pair<int, int> finalScore;
  finalScore = newGame->startGame();

  std::cout << "The final score is\n"
            << finalScore.first << " - " << finalScore.second << std::endl;

  delete newGame;

  return 0;
}
