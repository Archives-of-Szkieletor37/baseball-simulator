#include <iostream>

#include "game.h"

int main() {

  Game newGame;

  srand((unsigned int)time(NULL));


  std::array<int, 2> finalScore;
  finalScore = newGame.startGame();

  std::cout << "The final score is\n"
            << finalScore[0] << " - " << finalScore[1] << std::endl;

  return 0;
}
