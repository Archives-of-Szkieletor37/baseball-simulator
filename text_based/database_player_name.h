#ifndef _DATABASE_PLAYER_NAME_H_
#define _DATABASE_PLAYER_NAME_H_

#include <string>
#include <vector>

using kanji = std::string;
using hiragana = std::string;

extern const std::vector<std::pair<kanji,hiragana>> database_lastname;
extern const std::vector<std::pair<kanji,hiragana>> database_firstname;

extern std::pair<kanji,hiragana> get_firstname_fromdb(int);
extern std::pair<kanji,hiragana> get_lastname_fromdb(int);

#endif
