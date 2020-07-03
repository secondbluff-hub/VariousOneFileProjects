#pragma once

#include <cstdlib>
#include <algorithm>

template <typename T>
class SimpleVector {
public:
   SimpleVector() = default;

   explicit SimpleVector(size_t size){
      data = new T[size];
      _end = data + size;
      this->size = size;
      cap = size;
   }

   ~SimpleVector(){
      delete[] data;
   }

   T& operator[](size_t index){
      return data[index];
   }

   const T& operator[](size_t index) const {
      return data[index];
   }

   T* begin(){
      return data;
   }

   T* end(){
      return _end;
   }

   const T* begin() const {
      return data;
   }

   const T* end() const {
      return _end;
   }

   size_t Size() const {
      return size;
   }

   size_t Capacity() const {
      return cap;
   }

   void PushBack(const T& value){
      if(Capacity()){
         if(Size() == Capacity()){
            cap *= 2;
            T* cpy = new T[cap];
            std::copy(data, _end, cpy);
            delete[] data;
            data = cpy;
            _end = data + cap;
         }
         data[size] = value;
         ++size;
         _end = data + size;
      } else {
         data = new T[1];
         data[0] = value;
         _end = data + 1;
         cap = 1;
         size = 1;
      }
   }

private:
   T* data = nullptr;
   T* _end = nullptr;
   size_t cap = 0;
   size_t size = 0;
};
