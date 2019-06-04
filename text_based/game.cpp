#include "game.h"
#include "team.h"

Game::Game() {
  Team1 = new Team;
  Team2 = new Team;
  Teams.first = Team1;
  Teams.second = Team2;
  currentInningNumber = std::pair<int, InningTopOrBottom>(1, TOP);
  Score = std::pair<int, int>(0, 0);
  numberOfCurrentAtBat = 1;
  gameStatus = ONGOING;
};

Game::~Game() {
  delete Team1;
  delete Team2;
};

std::pair<int, int> Game::startGame() {

  Teams.first->printTeamName();
  std::cout << " vs ";
  Teams.second->printTeamName();
  std::cout << std::endl;

  std::cout << "スターティングメンバーを紹介します" << std::endl;
  std::cout << "先攻:";
  Teams.first->printTeamName();
  std::cout << std::endl;
  Teams.first->printHittersCurrentlyAppeared();

  std::cout << "後攻:";
  Teams.second->printTeamName();
  std::cout << std::endl;
  Teams.second->printHittersCurrentlyAppeared();

  while (gameStatus != END) {

    std::cout << "The ";
    if (currentInningNumber.second == TOP)
      std::cout << "TOP";
    else
      std::cout << "BOTTOM";
    std::cout << " of the " << currentInningNumber.first << std::endl;

    inning = new Inning;
    inning->startInning(this);
    succeedInning();

    std::cout << "Change\n" << std::endl;

    delete inning;
  }
  return Score;
}

void Game::updateScore(int scoreToAdd) { //スコアを変える関数

  switch (currentInningNumber.second) {
  case TOP:                   //表なら
    Score.first += scoreToAdd; //先攻にプラスする
    break;
  case BOTTOM:                 //裏なら
    Score.second += scoreToAdd; //後攻にプラスする
    break;
  }
}

void Game::printScore() {

  std::cout << "Now score is " << Score.first << " - " << Score.second
            << std::endl;
}

void Game::succeedInning() {          //イニングを進める関数
  if (currentInningNumber.first == 9 // 9回で
      && (currentInningNumber.second == BOTTOM // 9回裏か
          || (currentInningNumber.second == TOP &&
              Score.first < Score.second))) { // 9回表終了で後攻がリードなら
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

void Game::succeedCurrentAtBat() { //打順を進める関数
  if (numberOfCurrentAtBat == 9)            // 9番なら
    numberOfCurrentAtBat = 1;               // 1番へ
  else
    numberOfCurrentAtBat++; //ひとつ進める
}

Inning::Inning() { //イニングの初期状態
  Outs = 0;
  for (int i = FIRST_BASE; i <= THIRD_BASE; i++)
    currentStatusofBases[i] = false;
  inningStatus = ONGOING;
}

Inning::~Inning(){};

void Inning::startInning(Game *game) {

  ResultAtBat resultAtBat;

  while (inningStatus != END) {
    currentAtBat = new AtBat;
    resultAtBat = currentAtBat->startAtBat(game, this);
    applyTheResultAtBat(resultAtBat, game);
    delete currentAtBat;
  }
}

void Inning::succeedOuts() {
  ++Outs;
  if (Outs == 3) {
    inningStatus = END; // 終了処理
  }
}

void Inning::applyTheResultAtBat(ResultAtBat resultAtBat, Game *game) {
  switch (resultAtBat) {
  case STRIKEOUT:
  case BATTED_BALL_OUT:
    succeedOuts();
    break;
  default:
    game->succeedCurrentAtBat();
    break;
  }
  updateScoreByTheResultAtBut(resultAtBat, game);
  changeStatusOfBases(resultAtBat);
  game->printScore();
  std::cout << currentStatusofBases[0] << " " << currentStatusofBases[1] << " "
            << currentStatusofBases[2] << std::endl;
}

void Inning::changeStatusOfBases(ResultAtBat resultAtBat) {
  int numberOfAdvanceOfBases;
  switch (resultAtBat) {
  case SINGLE_HIT:
    numberOfAdvanceOfBases = 1;
    std::cout << "Single Hit" << std::endl;
    break;
  case TWO_BASE_HIT:
    numberOfAdvanceOfBases = 2;
    std::cout << "Two-Base Hit" << std::endl;
    break;
  case THREE_BASE_HIT:
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
  case STRIKEOUT:
    std::cout << "StrikeOut" << std::endl;
    numberOfAdvanceOfBases = 0;
    break;
  case BATTED_BALL_OUT:
    std::cout << "Batted_Ball_Out" << std::endl;
    numberOfAdvanceOfBases = 0;
    break;
  }
  Bases nextStatusOfBases = {false, false, false};
  for (int i = FIRST_BASE; i <= THIRD_BASE;
       i++) { //既に塁上にいるランナーの処理
    if (i + numberOfAdvanceOfBases >= 3) { //本塁まで進む場合
      currentStatusofBases[i] = false;           //塁からいなくなる
      continue;
    } else if (currentStatusofBases[i] == true) //それ以外で、ランナーがいる場合は
      nextStatusOfBases[i + numberOfAdvanceOfBases] =
          currentStatusofBases[i]; // numberOfAdvanceOfBases だけ進む
  }
  if (numberOfAdvanceOfBases < 4     //打者の処理
      && numberOfAdvanceOfBases > 0) //ホームラン・アウト以外
    nextStatusOfBases[numberOfAdvanceOfBases - 1] = true;
  for (int i = FIRST_BASE; i <= THIRD_BASE; i++)
    this->currentStatusofBases[i] = nextStatusOfBases[i]; //配列コピー
}

void Inning::updateScoreByTheResultAtBut(ResultAtBat resultAtBat,
                                            Game *game) {

  int NumberOfRunnersPossibleToComeHomebase =
      0; //帰ってこられる最大のランナーの数
  int NumberOfRunnersComeHomebase = 0; //帰ってくるランナーの数
  switch (resultAtBat) {
  case SINGLE_HIT:
    NumberOfRunnersPossibleToComeHomebase = 1;
    break;
  case TWO_BASE_HIT:
    NumberOfRunnersPossibleToComeHomebase = 2;
    break;
  case THREE_BASE_HIT:
    NumberOfRunnersPossibleToComeHomebase = 3;
    break;
  case HOMERUN:
    NumberOfRunnersPossibleToComeHomebase = 3;
    game->updateScore(1);
    break;
  case WALK:
    NumberOfRunnersPossibleToComeHomebase = 1;
    break;
  case BATTED_BALL_OUT:
  case STRIKEOUT:
    NumberOfRunnersPossibleToComeHomebase = 0;
    break;
  }
  for (int i = 3; i > 3 - NumberOfRunnersPossibleToComeHomebase; i--) {
    if (currentStatusofBases[i - 1] == true)
      NumberOfRunnersComeHomebase++;
  }
  if (NumberOfRunnersComeHomebase > 0)
    game->updateScore(NumberOfRunnersComeHomebase);
}

AtBat::AtBat() { //打席の初期状態
  CurrentCountOfThisAtBat.Strike = 0;
  CurrentCountOfThisAtBat.Ball = 0;
}
AtBat::~AtBat(){};

ResultAtBat AtBat::startAtBat(Game *game, Inning *inning) {

  return ResultAtBat(rand() % 7);
}
