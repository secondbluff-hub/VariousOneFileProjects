#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool Tester(vector<int>& example){
	for(int i = 1; i <= 9; ++i){
		if(find(example.begin(), example.end(), i) != example.end() || example.at(example.size()-1) == i){
			example.erase(find(example.begin(), example.end(), i), find(example.begin(), example.end(), i) + 1);
		}
		else {
			return false;
		}
	}
	if(!example.empty()){
		return false;
	}
	return true;
}

bool validSolution(unsigned int board[9][9]){

	vector<int> example;

	for(int i = 0; i < 9; ++i){
		for(auto n : board[i]){
			example.push_back(n);
		}
		if(!Tester(example)){
			return false;
		}
	}

	for(int i = 0; i < 9; ++i){
		for(int j = 0; j < 9; ++j){
			example.push_back(board[j][i]);
		}
		if(!Tester(example)){
			return false;
		}
	}

	for(int jk = 0; jk < 9; jk += 3){
		for(int ik = 0; ik < 9; ik += 3){
			for(int i = 0+ik; i < 3+ik; ++i){
				for(int j = 0+jk; j < 3+jk; ++j){
					example.push_back(board[i][j]);
				}
			}
			if(!Tester(example)){
				return false;
			}
		}
	}

   return true;
}

int main(){
unsigned int example[9][9] = {{5, 3, 4, 6, 7, 8, 9, 1, 2}, 
                             {6, 7, 2, 1, 9, 5, 3, 4, 8},
                             {1, 9, 8, 3, 4, 2, 5, 6, 7},
                             {8, 5, 9, 7, 6, 1, 4, 2, 3},
                             {4, 2, 6, 8, 5, 3, 7, 9, 1},
                             {7, 1, 3, 9, 2, 4, 8, 5, 6},
                             {9, 6, 1, 5, 3, 7, 2, 8, 4},
                             {2, 8, 7, 4, 1, 9, 6, 3, 5},
                             {3, 4, 5, 2, 8, 6, 1, 7, 9}}; 
   cout << validSolution(example);
	return 0;
}