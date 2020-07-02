#include "test_runner.h"
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

template<typename T>
class Table {
public:
   Table(size_t a, size_t b) { Resize(a, b); }

   const vector<T>& operator[](const size_t& a) const {
      return table[a];
   }

   vector<T>& operator[](const size_t& a) {
      return table[a];
   }

   void Resize(const size_t& a, const size_t& b) {
      rows = a;
      columns = b;
      table.resize(a);
      for(auto& t : table){
         t.resize(b);
      }
   }

   pair<size_t, size_t> Size() const {
      return make_pair(table.size(), (table.empty() ? 0 : table[0].size()));
   }

private:
   size_t rows, columns;
   vector<vector<T>> table;
};

void TestTable() {
   Table<int> t(1, 1);
   ASSERT_EQUAL(t.Size().first, 1u);
   ASSERT_EQUAL(t.Size().second, 1u);
   t[0][0] = 42;
   ASSERT_EQUAL(t[0][0], 42);
   t.Resize(3, 4);
   ASSERT_EQUAL(t.Size().first, 3u);
   ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
   TestRunner tr;
   RUN_TEST(tr, TestTable);
   return 0;
}
