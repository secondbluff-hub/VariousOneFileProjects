#include <string>
#include <vector>
using namespace std;

#define NEWID(str) var_##str
#define NEWID1(str) NEWID(str)
#define UNIQ_ID NEWID1(__LINE__)

int main() {
  int UNIQ_ID = 0;
  string UNIQ_ID = "hello";
  vector<string> UNIQ_ID = {"hello", "world"};
  vector<int> UNIQ_ID = {1, 2, 3, 4};
}
