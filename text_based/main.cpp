#include <bits/stdc++.h>
#include "game.h"
#include "database_player_name.h"

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


