#pragma once

#include <stdexcept>
#include <array>
using namespace std;

template <typename T, size_t N>
class StackVector {
public:
   explicit StackVector(size_t a_size = 0) : size(a_size) {
      if(size > N){
         throw invalid_argument("error size");
      }
   }

   T& operator[](size_t index){
      return data[index];
   }

   const T& operator[](size_t index) const {
      return data[index];
   }

   typename array<T, N>::iterator begin(){
      return data;
   }

   typename array<T, N>::iterator end(){
      return data + size;
   }

   typename array<T, N>::const_iterator begin() const {
      return data;
   }

   typename array<T, N>::const_iterator end() const {
      return data + size;
   }

   size_t Size() const {
      return size;
   }

   size_t Capacity() const {
      return N;
   }

   void PushBack(const T& value){
      if(size == N){
         throw overflow_error("error push_back");
      } else {
         data[size++] = value;
      }
   }

   T PopBack(){
      if(size){
         return data[--size];
      } else {
         throw underflow_error("error pop_back");
      }
   }

private:
   size_t size;
   T data[N];
};

