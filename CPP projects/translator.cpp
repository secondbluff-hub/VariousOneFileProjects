#include "test_runner.h"
#include <string>
#include <algorithm>
#include <string_view>
#include <map>
#include <deque>
#include <list>

using namespace std;

class Translator {
public:
   void Add(string_view source, string_view target){
      auto it1 = find(strs.begin(), strs.end(), source);
      if(it1 == strs.end()){
         strs.push_back(string(source));
         it1 = (strs.end() - 1);
      }

      auto it2 = find(strs.begin(), strs.end(), target);
      if(it2 == strs.end()){
         strs.push_back(string(target));
         it2 = (strs.end() - 1);
      }
      words1[*it1] = *it2;
      words2[*it2] = *it1;
   }

   string_view TranslateForward(string_view source) const {
      if(words1.find(source) == words1.end()){
         return "";
      } else {
         return words1.at(source);
      }
   }
   
   string_view TranslateBackward(string_view target) const {
      if(words2.find(target) == words2.end()){
         return "";
      } else {
         return words2.at(target);
      }
   }

private:
   deque<string> strs;
   map<string_view, string_view> words1;
   map<string_view, string_view> words2;
};

void TestSimple() {
   Translator translator;
   translator.Add(string("okno"), string("window"));
   translator.Add(string("stol"), string("table"));
   translator.Add(string("stol"), string("tablo"));

   ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
   ASSERT_EQUAL(translator.TranslateForward("stol"), "tablo");
   ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
   ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
   TestRunner tr;
   RUN_TEST(tr, TestSimple);
   return 0;
}
