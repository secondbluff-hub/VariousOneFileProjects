#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>

using namespace std;

template <class T>
class ObjectPool {
public:
  T* Allocate(){
    T* result;
    if(free.empty()){
      result = new T;
    } else {
      result = free.front();
      free.pop();
    }
    vid.insert(result);
    return result;
  }

  T* TryAllocate(){
    if(free.empty()){
      return nullptr;
    } else {
      T* result = free.front();
      vid.insert(result);
      free.pop();
      return result;
    }
  }

  void Deallocate(T* object){
    if(vid.count(object)){
      free.push(object);
      vid.erase(object);
    } else {
      throw invalid_argument("Error!");
    }
  }

  ~ObjectPool(){
    while(!free.empty()){
      delete free.front();
      free.pop();
    }
    for(const auto& i : vid){
      delete i;
    }
  }

private:
  queue<T*> free;
  set<T*> vid;
};

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}
