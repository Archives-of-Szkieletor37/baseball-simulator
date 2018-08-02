
using Ability = int*;
using Name = char*;
using Flag = bool;

class ABILITY{
  private:
    static int ability_value_zero[100];
  public:
    Ability generate_ability(int);

};

Ability ABILITY::generate_ability(int ability_value) {
  if(ability_value > 100 || ability_value < 0) {
    // 例外
  }
  Ability ability;
  ability = ability_value_zero + ability_value;
  return ability;
};
  
class PLAYER : public ABILITY{
  public:
  struct player {
    Name firstname;
    Flag flag_pitcher;
    struct batter_ability *BA_ability;
    struct pitcher_ability *PI_ability;
  };
  
  struct batter_ability {
    /* 打者としての能力
     * パワー
     * ミート-> Abilityという型を作り、1から100までの数値しか取らないように限定したい
     */
    Ability Power;
    Ability Meet;
  };

  struct pitcher_ability {
    /* 投手としての能力
     * 最高球速
     * コントロール
     */
    Ability max_ball_speed;
    Ability control;
  };
};

class batter : public PLAYER{
};

class pitcher : public PLAYER{
};

int main() {

  /* 打者の情報を受け取る
   *
   * 投手の情報を受け取る
   *
   * 対戦する
   *
   * 結果を出力する
   */
}
  
