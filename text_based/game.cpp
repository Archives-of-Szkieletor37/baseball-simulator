#include "game.h"
#include "team.h"

GAME::GAME() {
  Team1 = new TEAM;
  Team2 = new TEAM;
  Teams.first = Team1;
  Teams.second = Team2;
  Current_Inning_Number = std::pair<int, Inning_Top_or_Bottom>(1, TOP);
  Score = std::pair<int,int>(0,0);
  Current_At_Bat = 1;
  Game_Status = ONGOING;
};

GAME::~GAME(){
  delete Team1;
  delete Team2;
};

std::pair<int,int> GAME::Start_Game() {

  Teams.first->Print_Team_Name();
  std::cout << " vs "; 
  Teams.second->Print_Team_Name();
  std::cout << std::endl;

  std::cout << "スターティングメンバーを紹介します" << std::endl;
  std::cout << "先攻:";
  Teams.first->Print_Team_Name();
  std::cout << std::endl;
  Teams.first->Print_Current_Players_on_the_Ground();

  std::cout << "後攻:";
  Teams.second->Print_Team_Name();
  std::cout << std::endl;
  Teams.second->Print_Current_Players_on_the_Ground();

  while(Game_Status != END) {

    std::cout << "The ";
    if(Current_Inning_Number.second == TOP)
      std::cout << "TOP";
    else
      std::cout << "BOTTOM";
    std::cout << " of the " << Current_Inning_Number.first << std::endl;

    inning = new INNING;
    inning->Start_Inning(this);
    Succeed_Inning();

    std::cout << "Change\n" << std::endl;

    delete inning;
  }
  return Score;
}

void GAME::Update_Score(int add_score) { //スコアを変える関数

  switch(Current_Inning_Number.second) {
    case TOP: //表なら
      Score.first += add_score; //先攻にプラスする
      break;
    case BOTTOM: //裏なら
      Score.second += add_score; //後攻にプラスする
      break;
  }
}

void GAME::Print_Score() {

  std::cout << "Now score is " << Score.first << " - " << Score.second << std::endl;
}

void GAME::Succeed_Inning() { //イニングを進める関数
  if(Current_Inning_Number.first == 9 // 9回で 
      && (Current_Inning_Number.second == BOTTOM //9回裏か
	|| 
	(Current_Inning_Number.second == TOP && Score.first < Score.second))) { //9回表終了で後攻がリードなら
    Game_Status = END;// ゲーム終了処理
  }
  else {
    switch(Current_Inning_Number.second) {
      case TOP: // 表なら
	Current_Inning_Number.second = BOTTOM; //裏にする
	break;
      case BOTTOM: // 裏なら
	Current_Inning_Number.first++; //回をひとつ進める
	Current_Inning_Number.second = TOP; //回を表にする
	break;
    }
  }
}

void GAME::Succeed_Current_At_Bat() { //打順を進める関数
  if(Current_At_Bat == 9) //9番なら
    Current_At_Bat = 1; //1番へ
  else
    Current_At_Bat++; //ひとつ進める
}

INNING::INNING() { //イニングの初期状態
  Outs = 0;
  for(int i=FIRST_BASE; i<=THIRD_BASE; i++)
    Bases_Status[i] = false;
  Inning_Status = ONGOING;
}

INNING::~INNING(){
};

void INNING::Start_Inning(GAME *game) {

  Result_at_Bat result_at_bat;

  while(Inning_Status != END){
    at_bat = new AT_BAT;
    result_at_bat = at_bat->Start_At_Bat(game, this);
    Apply_the_Result_at_Bat(result_at_bat, game); 
    delete at_bat;
  }
}

void INNING::Succeed_Outs() {
  ++Outs;
  if(Outs == 3) {
    Inning_Status = END;// 終了処理
  }
}

void INNING::Apply_the_Result_at_Bat(Result_at_Bat result_at_bat, GAME *game) {
  switch(result_at_bat) {
    case STRIKEOUT:
    case BATTED_BALL_OUT:
      Succeed_Outs();
      break;
    default:
      game->Succeed_Current_At_Bat();
      break;
  }
  Add_Score_by_the_Result_at_Bat(result_at_bat, game);
  Change_Bases_Status(result_at_bat);
  game->Print_Score();
  std::cout << Bases_Status[0] << " " << Bases_Status[1] << " " << Bases_Status[2] << std::endl;
}

void INNING::Change_Bases_Status(Result_at_Bat result_at_bat) {
  int num_of_succeed_bases;
  switch(result_at_bat) {
    case SINGLE_HIT:
      num_of_succeed_bases = 1;
      std::cout << "Single Hit" << std::endl;
      break;
    case TWO_BASE_HIT:
      num_of_succeed_bases = 2;
      std::cout << "Two-Base Hit" << std::endl;
      break;
    case THREE_BASE_HIT:
      std::cout << "Three-Base Hit" << std::endl;
      num_of_succeed_bases = 3;
      break;
    case HOMERUN:
      std::cout << "HOMERUN!" << std::endl;
      num_of_succeed_bases = 4;
      break;
    case WALK:
      std::cout << "Walk" << std::endl; // 四球のときのランナーの進み方に特殊な処理が必要(未実装）
      num_of_succeed_bases = 1;
      break;
    case STRIKEOUT:
      std::cout << "StrikeOut" << std::endl;
      num_of_succeed_bases = 0;
      break;
    case BATTED_BALL_OUT:
      std::cout << "Batted_Ball_Out" << std::endl;
      num_of_succeed_bases = 0;
      break;
  }
  Bases New_Bases_Status = {false,false,false};
  for(int i=FIRST_BASE; i<=THIRD_BASE; i++) { //既に塁上にいるランナーの処理
    if(i + num_of_succeed_bases >= 3) {//本塁まで進む場合 
      Bases_Status[i] = false; //塁からいなくなる 
      continue;
    }
    else if(Bases_Status[i] == true)//それ以外で、ランナーがいる場合は
      New_Bases_Status[i + num_of_succeed_bases] = Bases_Status[i];// num_of_succeed_bases だけ進む
  }
  if(num_of_succeed_bases < 4 //打者の処理
      && num_of_succeed_bases > 0) //ホームラン・アウト以外
    New_Bases_Status[num_of_succeed_bases-1] = true; 
  for(int i=FIRST_BASE; i<=THIRD_BASE; i++)
    this->Bases_Status[i] = New_Bases_Status[i]; //配列コピー
}

void INNING::Add_Score_by_the_Result_at_Bat(Result_at_Bat result_at_bat, GAME *game) {
  
  int possible_base_runner_can_come_home_from=0; //帰ってこられる最大のランナーの数
  int num_of_runners_come_home=0; //帰ってくるランナーの数
  switch(result_at_bat) {
    case SINGLE_HIT:
      possible_base_runner_can_come_home_from=1;
      break;
    case TWO_BASE_HIT:
      possible_base_runner_can_come_home_from=2;
      break;
    case THREE_BASE_HIT:
      possible_base_runner_can_come_home_from=3;
      break;
    case HOMERUN:
      possible_base_runner_can_come_home_from=3;
      game->Update_Score(1);
      break;
    case WALK:
      possible_base_runner_can_come_home_from=1;
      break;
    case BATTED_BALL_OUT:
    case STRIKEOUT:
      possible_base_runner_can_come_home_from=0;
      break;
  }
  for(int i=3; i>3-possible_base_runner_can_come_home_from; i--) {
    if(Bases_Status[i-1] == true)
      num_of_runners_come_home++;
  }
  if(num_of_runners_come_home > 0)
    game->Update_Score(num_of_runners_come_home);
}


AT_BAT::AT_BAT() { //打席の初期状態
  Count_at_Bat.Strike = 0;
  Count_at_Bat.Ball = 0;
}
AT_BAT::~AT_BAT(){
};

Result_at_Bat AT_BAT::Start_At_Bat(GAME *game, INNING *inning) {

  return Result_at_Bat(rand() % 7);

}
