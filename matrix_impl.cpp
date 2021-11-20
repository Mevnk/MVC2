#include "Calc.h"
Matrix::Matrix(int row, int col) { 
	A.resize(row, std::vector<double>(col)); 
	if (row == col) sq_size = row;
	size = std::make_pair(row, col);
	lower.resize(row, std::vector<double>(col));
	upper.resize(row, std::vector<double>(col));
}
Matrix::Matrix(int inp_size) {
	A.resize(inp_size, std::vector<double>(inp_size));
	sq_size = inp_size;
	size = std::make_pair(inp_size, inp_size);
	lower.resize(inp_size, std::vector<double>(inp_size));
	upper.resize(inp_size, std::vector<double>(inp_size));
}
Matrix::Matrix(const std::string& f_name) {
	std::ifstream file;
	double buf;
	int row, col;
	file.open(f_name + ".txt");
	file >> row >> col;
	if (row == col) sq_size = row;
	size = std::make_pair(row, col);
	std::cout << f_name << std::endl;
	A.resize(row, std::vector<double>(col));
	lower.resize(row, std::vector<double>(col));
	upper.resize(row, std::vector<double>(col));
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) { file >> A[i][j]; }
	}
}
void Matrix::f_open() {
	std::string fopen;
	std::string path = "./saves/matrix/";
	for (const auto& entry : std::filesystem::directory_iterator(path))
		std::cout << entry.path().filename() << std::endl;
	std::cin >> fopen;
	Matrix a(path + fopen);
	*this = a;
}
void Matrix::save_matrix() {
	char save_response;
	std::cout << "Do you want to save the matrix? (y/n)" << std::endl;
	std::cin >> save_response;
	if (save_response == 'y') {
		std::string matrix_name;
		std::cout << "Name the matrix: " << std::endl;
		std::cin >> matrix_name;
		std::ofstream file("./saves/matrix/"+matrix_name + ".txt");
		file << size.first << " " << size.second << std::endl;
		for (int i = 0; i < size.first; i++) {
			for (int j = 0; j < size.second; j++) { file << A[i][j] << " "; }
		}
		return;
	}
	return;
}
Matrix::Matrix() {
	size={ 0, 0 };
}
bool Matrix::check_range(int row, int col) {
	if (row >= size.first || col >= size.second) return false;
	return true;
}
bool Matrix::check_square() {
	if (size.first == size.second) return true;
	return false;
}
void Matrix::set_elem(int row, int col, double val) {
	if (!check_range(row, col)) { std::cout << "Index out of range " << row << " " << col << std::endl; return; }
	A[row][col] = val;
}
double Matrix::get_elem(int row, int col) {
	if (!check_range(row, col)) { std::cout << "Index out of range " << row << " " << col << std::endl; return NULL; }
	return A[row][col];
}
void Matrix::print() {
	for (int i = 0; i < size.first; i++) {
		for (int j = 0; j < size.second; j++) { std::cout << std::setw(4) << A[i][j] << " "; }
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
void Matrix::print_lu() {
	std::cout << "Upper: " << std::endl;
	for (int i = 0; i < size.first; i++) {
		for (int j = 0; j < size.second; j++) { std::cout << upper[i][j] << " "; }
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << "Lower: " << std::endl;
	for (int i = 0; i < size.first; i++) {
		for (int j = 0; j < size.second; j++) { std::cout << lower[i][j] << " "; }
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
std::pair<int, int> Matrix::get_size() { return size; }
void Matrix::sum(Matrix& a, Matrix& b, int sign) {
	a.print();
	b.print();
	for (int i = 0; i < size.first; i++) {
		for (int j = 0; j < size.second; j++) { A[i][j] = a.A[i][j] + sign * b.A[i][j]; }
	}
}
void Matrix::scal_mult(double scal_val, Matrix& a) {
	for (int i = 0; i < size.first; i++) {
		for (int j = 0; j < size.second; j++) { A[i][j] = scal_val * a.A[i][j]; }
	}
}
void Matrix::scal_div(double scal_val, Matrix& a) {
	for (int i = 0; i < size.first; i++) {
		for (int j = 0; j < size.second; j++) { A[i][j] = a.A[i][j] / scal_val ; }
	}
}
void Matrix::matrix_mult(Matrix& a, Matrix& b) {
	for (int i = 0; i < a.size.first; i++) {
		for (int j = 0; j < b.size.second; j++) {
			for (int k = 0; k < b.size.second; k++) {
				A[i][j] += a.A[i][k] * b.A[k][j];
			}
		}
	}
}
Matrix& Matrix::operator=(Matrix& a) {
	A.resize(a.size.first, std::vector<double>(a.size.second));
	lower.resize(a.size.first, std::vector<double>(a.size.second));
	upper.resize(a.size.first, std::vector<double>(a.size.second));
	size = a.get_size();
	for (int i = 0; i < size.first; i++) {
		for (int j = 0; j < size.second; j++) { A[i][j]=a.A[i][j]; }
	}
	return *this;
}
void Matrix::clear() {
	for (int i = 0; i < size.first; i++) {
		for (int j = 0; j < size.second; j++) { A[i][j] = 0; }
	}
}
void Matrix::identity() { for (int i = 0; i < size.first; i++) { A[i][i] == 1; } }
void Matrix::pow(Matrix& a, int pow) {
	Matrix buf(sq_size);
	buf = a;
	for (int i = 1; i < pow; i++) {
		this->clear();
		this->matrix_mult(buf, a);
		buf = *this;
	}
}
void Matrix::transpoition(Matrix& a) {
	for (int i = 0; i < a.size.first; i++) {
		for (int j = 0; j < a.size.second; j++) {
			A[j][i] = a.A[i][j];
		}
	}
}
void Matrix::lu_decompos() {
	for (int i = 0; i < size.first; i++) {
		for (int k = i; k < size.first; k++) {
			int sum = 0;
			for (int j = 0; j < i; j++)
				sum += (lower[i][j] * upper[j][k]);
			upper[i][k] = A[i][k] - sum;
		}
		for (int k = i; k < size.first; k++) {
			if (i == k) lower[i][i] = 1;
			else {
				int sum = 0;
				for (int j = 0; j < i; j++) sum += (lower[k][j] * upper[j][i]);
				lower[k][i] = (A[k][i] - sum) / upper[i][i];
			}
		}
	}
}
double Matrix::det() {
	if (sq_size == 2) { return A[0][0] * A[1][1] - A[0][1] * A[1][0]; }
	lu_decompos();
	double prod{ 1 };
	for (int i = 0; i < sq_size; i++) { prod *= upper[i][i]; }
	return prod;
}
vector Matrix::gauss(Matrix A) {
	int n = A.size.first;
	for (int i = 0; i < n; i++) {
		double max_el = abs(A.A[i][i]);
		int maxRow = i;
		for (int k = i + 1; k < n; k++) {
			if (abs(A.A[k][i]) > max_el) {
				max_el = abs(A.A[k][i]);
				maxRow = k;
			}
		}
		for (int k = i; k < n + 1; k++) {
			double tmp = A.A[maxRow][k];
			A.A[maxRow][k] = A.A[i][k];
			A.A[i][k] = tmp;
		}
		for (int k = i + 1; k < n; k++) {
			double c = -A.A[k][i] / A.A[i][i];
			for (int j = i; j < n + 1; j++) {
				if (i == j) {
					A.A[k][j] = 0;
				}
				else {
					A.A[k][j] += c * A.A[i][j];
				}
			}
		}
	}
	vector x(n);
	for (int i = n - 1; i >= 0; i--) {
		x[i] = A.A[i][n] / A.A[i][i];
		for (int k = i - 1; k >= 0; k--) {
			A.A[k][n] -= A.A[k][i] * x[i];
		}
	}
	return x;
}
void Matrix::inverse(Matrix& a) {
	Matrix system(a.sq_size, a.sq_size + 1);
	vector identity(a.sq_size);
	vector inverse_col(a.sq_size);
	for (int i = 0; i < a.size.first; i++) {
		for (int j = 0; j < a.size.first; j++) { system.A[i][j] = a.A[i][j]; }
	}
	for (int i = 0; i < a.size.first; i++) {
		identity[i] = 1;
		for (int j = 0; j < a.size.first; j++) {
			system.A[j][sq_size] = identity[j];
		}
		inverse_col = gauss(system);
		identity[i] = 0;
		A[i] = inverse_col;
	}
}
int Matrix::rank() {
	lu_decompos();
	int rank = size.first;
	double sum{ 0 };
	for (int i = size.first - 1; i >= 0; i--) {
		sum = std::accumulate(upper[i].begin(), upper[i].end(), 0);
		if (sum == 0) { rank--; }
	}
	return rank;
}
