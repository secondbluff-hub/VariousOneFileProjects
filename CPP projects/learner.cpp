#include "profile.h"
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <iostream>

using namespace std;

class Learner {
 private:
  set<string> dict;

 public:
  int Learn(const vector<string>& words) {
    int newWords = dict.size();
    for(const auto& w : words){
      dict.insert(w);
    }
    return dict.size() - newWords;
  }

  vector<string> KnownWords() {
    return {dict.begin(), dict.end()};
  }
};

int main() {
  Learner learner;
  string line;
  while (getline(cin, line)) {
    vector<string> words;
    stringstream ss(line);
    string word;
    while (ss >> word) {
      words.push_back(word);
    }
    cout << learner.Learn(words) << "\n";
  }
  cout << "=== known words ===\n";
  for (auto word : learner.KnownWords()) {
    cout << word << "\n";
  }
}