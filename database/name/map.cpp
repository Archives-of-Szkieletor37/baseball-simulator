#include <bits/stdc++.h>
using namespace std;

int main() {

  string kanji,hiragana;
  map<pair<string,string>,int> mp;
  for(int i=0; i<10000; i++) {
    cin >> kanji >> hiragana;
    mp[pair<string,string>(kanji,hiragana)]++;
  }

  cout << "{";
  cout << "{\"保毛\", \"ほげ\"}\n";
  for(map<pair<string,string>, int>::iterator i = mp.begin(); i != mp.end(); i++) {
    cout << "{\"" << i->first.first << "\", \"" << i->first.second << "\"},"; 
  }
  cout << "\n}";
  return 0;
}
    
    
