#include "profile.h"
#include "test_runner.h"

#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class ReadingManager {
public:
  ReadingManager() : user_page(MAX_USER_COUNT_, -1), pages(MAX_PAGES, 0) {}

  void Read(int user_id, int page_count) {
    if(user_page[user_id] == -1){
      user_page[user_id] = page_count;
      ++pages[page_count];
      ++count_users;
    } else {
      --pages[user_page[user_id]];
      user_page[user_id] = page_count;
      ++pages[page_count];
    }
  }

  double Cheer(int user_id) const {
    if(user_page[user_id] == -1){
      return 0;
    }
    int users_pages = 0;
    for(int i = 0; i < user_page[user_id]; ++i){
      users_pages += pages[i];
    }
    return users_pages == count_users - 1 ? 1 : (count_users == pages[user_page[user_id]] ? 0 : users_pages * 1.0 / (count_users - 1));
  }

private:
  static const int MAX_USER_COUNT_ = 100'001;
  static const int MAX_PAGES = 1001;

  int count_users = 0;
  vector<int> user_page;    // Пользователь - страницы
  vector<int> pages;        // Кол-во пользователей, прочитавших n-ое количество страниц

};

void TestRead() {
    ReadingManager manager;

    ASSERT_EQUAL(0, manager.Cheer(5));
    manager.Read(1, 10);
    ASSERT_EQUAL(1, manager.Cheer(1));
    manager.Read(2, 5);
    manager.Read(3, 7);
    ASSERT_EQUAL(0, manager.Cheer(2));
    ASSERT_EQUAL(0.5, manager.Cheer(3));
    manager.Read(3, 10);
    ASSERT_EQUAL(0.5, manager.Cheer(3));
    manager.Read(3, 11);
    ASSERT_EQUAL(1, manager.Cheer(3));
    ASSERT_EQUAL(0.5, manager.Cheer(1));
    manager.Read(2, 11);
    ASSERT_EQUAL(0.5, manager.Cheer(3));
    ASSERT_EQUAL(0.5, manager.Cheer(2));
    manager.Read(2, 12);
    ASSERT_EQUAL(0.5, manager.Cheer(3));
    ASSERT_EQUAL(1, manager.Cheer(2));
    manager.Read(1, 13);
    manager.Read(2, 13);
    manager.Read(3, 13);
    ASSERT_EQUAL(0, manager.Cheer(1));
    ASSERT_EQUAL(0, manager.Cheer(2));
    ASSERT_EQUAL(0, manager.Cheer(3));
    manager.Read(4, 14);
    ASSERT_EQUAL(1, manager.Cheer(4));
}

void TestBasicCases() {
    ReadingManager manager;
    manager.Read(1, 10);
    manager.Read(2, 20);
    manager.Read(3, 30);
    ASSERT_EQUAL(manager.Cheer(1), 0);
    ASSERT_EQUAL(manager.Cheer(2), 0.5);
    ASSERT_EQUAL(manager.Cheer(3), 1);
}
 
 
void AddingZeroPages() {
    ReadingManager manager;
    manager.Read(1, 10);
    manager.Read(2, 20);
    manager.Read(3, 30);
    manager.Read(4, 0);
    manager.Read(5, 0);
    manager.Read(6, 0);
    ASSERT_EQUAL(manager.Cheer(1), 0.6);
    ASSERT_EQUAL(manager.Cheer(2), 0.8);
    ASSERT_EQUAL(manager.Cheer(3), 1);
    ASSERT_EQUAL(manager.Cheer(4), 0);
    ASSERT_EQUAL(manager.Cheer(5), 0);
    ASSERT_EQUAL(manager.Cheer(6), 0);
}
 
 
void Competitors() {
    ReadingManager manager;
    manager.Read(1, 10);
    manager.Read(2, 10);
    manager.Read(3, 10);
    manager.Read(4, 5);
    manager.Read(5, 15);
    manager.Read(6, 15);
    ASSERT_EQUAL(manager.Cheer(1), 0.2);
    ASSERT_EQUAL(manager.Cheer(2), 0.2);
    ASSERT_EQUAL(manager.Cheer(3), 0.2);
    ASSERT_EQUAL(manager.Cheer(4), 0);
    ASSERT_EQUAL(manager.Cheer(5), 0.8);
    ASSERT_EQUAL(manager.Cheer(6), 0.8);
}
 
 
void ReadMultipleTimes() {
    ReadingManager manager;
    manager.Read(1, 10);
    manager.Read(2, 10);
    manager.Read(3, 10);
    manager.Read(4, 5);
    manager.Read(5, 15);
    manager.Read(6, 15);
    manager.Read(1, 20);
    manager.Read(2, 20);
    manager.Read(3, 30);
    manager.Read(4, 30);
    manager.Read(5, 16);
    manager.Read(6, 17);
    ASSERT_EQUAL(manager.Cheer(1), 0.4);
    ASSERT_EQUAL(manager.Cheer(2), 0.4);
    ASSERT_EQUAL(manager.Cheer(3), 0.8);
    ASSERT_EQUAL(manager.Cheer(4), 0.8);
    ASSERT_EQUAL(manager.Cheer(5), 0);
    ASSERT_EQUAL(manager.Cheer(6), 0.2);
}
 
 
void BigValues() {
    ReadingManager manager;
    manager.Read(1, 10);
    manager.Read(1, 20);
    manager.Read(99999, 999);
    manager.Read(99999, 1000);
    manager.Read(100000, 999);
    manager.Read(100000, 1000);
 
    ASSERT_EQUAL(manager.Cheer(1), 0);
    ASSERT_EQUAL(manager.Cheer(2), 0);
    ASSERT_EQUAL(manager.Cheer(99999), 0.5);
    ASSERT_EQUAL(manager.Cheer(100000), 0.5);
}

void RunUnitTests(){
    TestRunner tr;
    RUN_TEST(tr, TestRead);
    RUN_TEST(tr, TestBasicCases);
    RUN_TEST(tr, AddingZeroPages);
    RUN_TEST(tr, Competitors);
    RUN_TEST(tr, ReadMultipleTimes);
    RUN_TEST(tr, BigValues);
   
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  RunUnitTests();

  ReadingManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int user_id;
    cin >> user_id;

    if (query_type == "READ") {
      int page_count;
      cin >> page_count;
      manager.Read(user_id, page_count);
    } else if (query_type == "CHEER") {
      cout << setprecision(6) << manager.Cheer(user_id) << "\n";
    }
  }

  return 0;
}