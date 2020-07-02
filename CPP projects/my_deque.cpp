#include <iostream>
#include <string>
#include <vector>
#include <exception>
using namespace std;


template<typename T>
class Deque {
public:
	Deque() = default;

	bool Empty() const {
		return front.empty() && back.empty();
	}

	size_t Size() const {
		return front.size() + back.size();
	}

	T& operator[](const size_t index) {
		if(index >= front.size()){
			return back[index - front.size()];
		}
			return front[front.size() - 1 - index];
	}

	const T& operator[](const size_t index) const {
		if(index >= front.size()){
			return back[index - front.size()];
		} else {
			return front[front.size() - 1 - index];
		}
	}

	T& At(const size_t& index) {
		if(index >= front.size() + back.size()){
			throw out_of_range("Out of range!");
		}else if(index >= front.size()){
			return back.at(index - front.size());
		} else {
			return front.at(front.size() - 1 - index);
		}
	}

	const T& At(const size_t& index) const {
		if(index >= front.size() + back.size()){
			throw out_of_range("Out of range!");
		}else if(index >= front.size()){
			return back.at(index - front.size());
		} else {
			return front.at(front.size() - 1 - index);
		}
	}

	const T& Front() const {
		if(front.empty()){
			return back.front();
		} else {
			return front.back();
		}
	}

	T& Front() {
		if(front.empty()){
			return back[0];
		} else {
			return front[front.size() - 1];
		}
	}

	const T& Back() const {
		if(back.empty()){
			return front.front();
		} else {
			return back.back();
		}
	}

	T& Back() {
		if(back.empty()){
			return front[0];
		} else {
			return back[back.size() - 1];
		}
	}

	void PushFront(const T& a) {
		front.push_back(a);
	}

	void PushBack(const T& a) {
		back.push_back(a);
	}

private:
	vector<T> front, back;
};


int main() {
	Deque<int> d;
	for(auto a : {1, 2, 3, 4, 5, 6, 7, 8, 9, 4}){ // 9 7 5 3 1 2 4 6 8 4

		if(a%2 == 1){
			d.PushFront(a);
		} else {
			d.PushBack(a);
		}

		for(int i = 0; i < d.Size(); ++i){
			cout << d.At(i) << ' ';
		}
		cout << endl;
	}

	for(int i = 0; i < d.Size(); ++i){
		cout << d[i] << ' ';
	}
	return 0;
}