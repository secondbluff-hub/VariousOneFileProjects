#include <iostream>
#include <stdexcept>
#include <exception>
#include <vector>

using namespace std;

class Matrix{
public:
	Matrix(){
		num_rows = 0;
		num_cols = 0;
	}

	Matrix(int rows, int cols){
		if(rows < 0 || cols < 0){
			throw out_of_range("");
		} else {
			num_rows = rows;
			num_cols = cols;
			matrix.assign(rows, vector<int>(cols));
		}
	}

	void Reset(int new_rows, int new_cols){
		if(new_rows < 0 || new_cols < 0){
			throw out_of_range("");
		} else {
			num_rows = new_rows;
			num_cols = new_cols;
			matrix.assign(new_rows, vector<int>(new_cols));
		}
	}

	int At(int row, int col) const {
		if(row >= num_rows || row < 0 || col >= num_cols || col < 0){
			throw out_of_range("");
		}
		return matrix[row][col];
	}

	int& At(int row, int col){
		if(row >= num_rows || row < 0 || col >= num_cols || col < 0){
			throw out_of_range("");
		}
		return matrix[row][col];
	}

	int GetNumRows() const {
		return num_rows;
	}

	int GetNumColumns() const {
		return num_cols;
	}

private:
	int num_rows, num_cols;
	vector<vector<int>> matrix;
};

istream& operator>>(istream& stream, Matrix& mx){
	int rows, cols;
	stream >> rows >> cols;
	Matrix result(rows, cols);
	for(int i = 0; i < rows; ++i){
		for(int j = 0; j < cols; ++j){
			stream >> result.At(i, j);
		}
	}
	mx = result;
	return stream;
}

ostream& operator<<(ostream& stream, const Matrix& mx){
	stream << mx.GetNumRows() << ' ' << mx.GetNumColumns() << endl;
	for(int i = 0; i < mx.GetNumRows(); ++i){
		for(int j = 0; j < mx.GetNumColumns(); ++j){
			stream << mx.At(i, j) << ' ';
		}
		stream << endl;
	}
	return stream;
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs){

	if((lhs.GetNumRows() == rhs.GetNumRows() && lhs.GetNumColumns() == rhs.GetNumColumns())
												|| ((lhs.GetNumRows() == 0 || lhs.GetNumColumns() == 0) 
														&& (rhs.GetNumRows() == 0 || rhs.GetNumColumns() == 0))){
		const int rows = lhs.GetNumRows(), cols = lhs.GetNumColumns();
		Matrix result(rows, cols);

		for(int i = 0; i < rows; ++i){
			for(int j = 0; j < cols; ++j){
				result.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
			}
		}

		return result;

	} else {
		throw invalid_argument("");
	}
}

bool operator==(const Matrix& lhs, const Matrix& rhs){
	if((lhs.GetNumRows() == rhs.GetNumRows() && lhs.GetNumColumns() == rhs.GetNumColumns())
												|| ((lhs.GetNumRows() == 0 || lhs.GetNumColumns() == 0) 
														&& (rhs.GetNumRows() == 0 || rhs.GetNumColumns() == 0))){
		const int rows = lhs.GetNumRows(), cols = lhs.GetNumColumns();
		for(int i = 0; i < rows; ++i){
			for(int j = 0; j < cols; ++j){
				if(lhs.At(i, j) != rhs.At(i, j)){
					return false;
				}
			}
		}
		return true;
	} else {
		return false;
	}
}

int main() {
	try{

	   Matrix one;
	   Matrix two;

	   cin >> one >> two;

	   cout << (one==two) << endl;

	   cout << one + two << endl;

	} catch(exception& ex){
		cout << ex.what() << endl;
	}
   return 0;
}