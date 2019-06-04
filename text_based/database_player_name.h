#ifndef _DATABASE_PLAYER_NAME_H_
#define _DATABASE_PLAYER_NAME_H_

#include <string>
#include <vector>

using kanji = std::string;
using hiragana = std::string;

extern const std::vector<std::pair<kanji,hiragana>> DATABASE_LASTNAME;
extern const std::vector<std::pair<kanji,hiragana>> DATABASE_FIRSTNAME;

extern std::pair<kanji,hiragana> getFirstNameFromDB(int);
extern std::pair<kanji,hiragana> getLastNameFromDB(int);

#endif
