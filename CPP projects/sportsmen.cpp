#include <iostream>
#include <vector>
#include <list>

using namespace std;

int main(){
	const int MAX_ATHLETES = 100'000;
	int q;
	cin >> q;

	list<int> ls;
	vector<list<int>::iterator> athlete_pos(MAX_ATHLETES + 1, ls.end());

	for (int i = 0; i < q; ++i) {
		int sp_num, j;
		cin >> sp_num >> j;
		athlete_pos[sp_num] = ls.insert(athlete_pos[j], sp_num);
	}
	for(auto& l : ls){
		cout << l << '\n';
	}

	return 0;
}