#include "game.h"

#include <iostream>
#include <array>

#include "team.h"

Game::Game() {
  Team team1;
  Team team2;
  teams[0] = team1;
  teams[1] = team2;
  currentInningNumber = std::pair<int, InningTopOrBottom>(1, TOP);
  score = {0, 0};
  numberOfCurrentAtBat = {1, 1};
  gameStatus = ONGOING;
};

Game::~Game() {
};

std::array<int, 2> Game::startGame() {

  teams[0].printTeamName();
  std::cout << " vs ";
  teams[1].printTeamName();
  std::cout << std::endl;

  std::cout << "スターティングメンバーを紹介します" << std::endl;
  std::cout << "先攻:";
  teams[0].printTeamName();
  std::cout << std::endl;
  teams[0].printHittersCurrentlyAppeared();

  std::cout << "後攻:";
  teams[1].printTeamName();
  std::cout << std::endl;
  teams[1].printHittersCurrentlyAppeared();

  while (gameStatus != END) {

    std::cout << "The ";
    if (currentInningNumber.second == TOP)
      std::cout << "TOP";
    else
      std::cout << "BOTTOM";
    std::cout << " of the " << currentInningNumber.first << std::endl;

    startInning();
    succeedInning();

    std::cout << "Change\n" << std::endl;

  }
  return score;
}

void Game::printScore() {

  std::cout << "Now score is " << score[0] << " - " << score[1]
            << std::endl;
}

void Game::updateScore(int scoreToAdd) { //スコアを変える関数

  switch (currentInningNumber.second) {
  case TOP:                   //表なら
    score[0] += scoreToAdd; //先攻にプラスする
    break;
  case BOTTOM:                 //裏なら
    score[1] += scoreToAdd; //後攻にプラスする
    break;
  default:
    break;
  }
}

void Game::startInning() {

  outs = 0;
  ResultAtBat resultAtBat;
  teamIdOfOffence = (currentInningNumber.second == TOP) ? 0 : 1;

  while (outs != 3) {
    resultAtBat = startAtBat();
    applyTheResultAtBat(resultAtBat);
  }
}

void Game::succeedOuts() {
  ++outs;
}

void Game::applyTheResultAtBat(ResultAtBat resultAtBat) {
  switch (resultAtBat) {
  case STRIKEOUT:
  case GROUNDOUT:
  case FLYOUT:
    succeedOuts();
    [[gnu::fallthrough]];
  default:
    succeedCurrentAtBat();
    break;
  }
  updateScoreByTheResultAtBut(resultAtBat);
  changeStatusOfBases(resultAtBat);
  printScore();
  std::cout << currentStatusofBases.bases[0] << " " << currentStatusofBases.bases[1] << " "
            << currentStatusofBases.bases[2] << std::endl;
}

void Game::succeedCurrentAtBat() {

 if (numberOfCurrentAtBat[teamIdOfOffence] == 9)            // 9番なら
    numberOfCurrentAtBat[teamIdOfOffence] = 1;               // 1番へ
  else
    ++numberOfCurrentAtBat[teamIdOfOffence];
}

void Game::changeStatusOfBases(ResultAtBat resultAtBat) {
  int numberOfAdvanceOfBases;
  switch (resultAtBat) {
  case SINGLE:
    numberOfAdvanceOfBases = 1;
    std::cout << "Single Hit" << std::endl;
    break;
  case DOUBLE:
    numberOfAdvanceOfBases = 2;
    std::cout << "Two-Base Hit" << std::endl;
    break;
  case TRIPLE:
    std::cout << "Three-Base Hit" << std::endl;
    numberOfAdvanceOfBases = 3;
    break;
  case HOMERUN:
    std::cout << "HOMERUN!" << std::endl;
    numberOfAdvanceOfBases = 4;
    break;
  case WALK:
    std::cout
        << "Walk"
        << std::endl; // 四球のときのランナーの進み方に特殊な処理が必要(未実装）
    numberOfAdvanceOfBases = 1;
    break;
  case HITBYPITCH:
    std::cout << "Hit By Pitch" << std::endl;
    numberOfAdvanceOfBases = 1;
    break;
  case STRIKEOUT:
    std::cout << "StrikeOut" << std::endl;
    numberOfAdvanceOfBases = 0;
    break;
  case GROUNDOUT:
    std::cout << "GroundOut" << std::endl;
    numberOfAdvanceOfBases = 0;
    break;
  case FLYOUT:
    std::cout << "FlyOut" << std::endl;
    numberOfAdvanceOfBases = 0;
    break;
  default:
    break;

  }
  Bases nextStatusOfBases = {false, false, false};
  for (int i = FIRST_BASE; i <= THIRD_BASE;
       i++) { //既に塁上にいるランナーの処理
    if (i + numberOfAdvanceOfBases >= 3) { //本塁まで進む場合
      currentStatusofBases.bases[i] = false;           //塁からいなくなる
      continue;
    } else if (currentStatusofBases.bases[i] == true) //それ以外で、ランナーがいる場合は
      nextStatusOfBases.bases[i + numberOfAdvanceOfBases] =
          currentStatusofBases.bases[i]; // numberOfAdvanceOfBases だけ進む
  }
  if (numberOfAdvanceOfBases < 4     //打者の処理
      && numberOfAdvanceOfBases > 0) //ホームラン・アウト以外
    nextStatusOfBases.bases[numberOfAdvanceOfBases - 1] = true;
  for (int i = FIRST_BASE; i <= THIRD_BASE; i++)
    this->currentStatusofBases.bases[i] = nextStatusOfBases.bases[i]; //配列コピー
}

void Game::updateScoreByTheResultAtBut(ResultAtBat resultAtBat) {

  int NumberOfRunnersPossibleToComeHomebase =
      0; //帰ってこられる最大のランナーの数
  int NumberOfRunnersComeHomebase = 0; //帰ってくるランナーの数
  switch (resultAtBat) {
  case SINGLE:
    NumberOfRunnersPossibleToComeHomebase = 1;
    break;
  case DOUBLE:
    NumberOfRunnersPossibleToComeHomebase = 2;
    break;
  case TRIPLE:
    NumberOfRunnersPossibleToComeHomebase = 3;
    break;
  case HOMERUN:
    NumberOfRunnersPossibleToComeHomebase = 3;
    updateScore(1);
    break;
  case WALK:
  case HITBYPITCH:
    NumberOfRunnersPossibleToComeHomebase = 1;
    break;
  case STRIKEOUT:
  case GROUNDOUT:
  case FLYOUT:
    NumberOfRunnersPossibleToComeHomebase = 0;
    break;
  }
  for (int i = 3; i > 3 - NumberOfRunnersPossibleToComeHomebase; i--) {
    if (currentStatusofBases.bases[i - 1] == true)
      NumberOfRunnersComeHomebase++;
  }
  if (NumberOfRunnersComeHomebase > 0)
    updateScore(NumberOfRunnersComeHomebase);
}

ResultAtBat Game::startAtBat() {

  currentCountOfAtBat.Strike = 0;
  currentCountOfAtBat.Ball = 0;

  std::array<double, 9> probabilities = {
    0.2, // HIT
    0.2, // DOUBLE
    0.2, // TRIPLE
    0.2, // HOMERUN
    0.2, // WALK
    0.2, // HITBYPITCH
    0.2, // STRIKEOUT
    0.2, // GROUNDOUT
    0.2, // FLYOUT
  };

  return ResultAtBat(rand() % 9);
}

void Game::succeedInning() {          //イニングを進める関数
  if (currentInningNumber.first == 9 // 9回で
      && (currentInningNumber.second == BOTTOM // 9回裏か
          || (currentInningNumber.second == TOP &&
              score[0] < score[1]))) { // 9回表終了で後攻がリードなら
    gameStatus = END;                        // ゲーム終了処理
  } else {
    switch (currentInningNumber.second) {
    case TOP:                                // 表なら
      currentInningNumber.second = BOTTOM; //裏にする
      break;
    case BOTTOM:                          // 裏なら
      currentInningNumber.first++;      //回をひとつ進める
      currentInningNumber.second = TOP; //回を表にする
      break;
    }
  }
}

