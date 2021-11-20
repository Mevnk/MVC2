#pragma once
#include <vector>;
#include <iostream>
#include <string>
#include <fstream>
#include <numeric>
#include <map>
#include <functional>
#include <filesystem>
#include <iomanip>
using matrix = std::vector<std::vector<double>>;
using vector = std::vector<double>;
class Calc {
protected:
	int response = 0;
private:
	std::map<int, std::function<void()>> map;
	char key_to_proceed;
	void proceed();
public:
	Calc();
	void main_menu();
	void matrix_ops();
	void vector_ops();
	void matrix_sum();
	void matrix_scal_mult(const char sign);
	void matrix_mult();
	void matrix_pow();
	void matrix_transpos();
	void determinant();
	void lu_decomposition();
	void matrix_inverse();
	void matrix_rank();
	void vector_sum();
	void vector_scal_mult(char sign);
	void cross_product();
	void dot_product();
	void vector_magnitude();
	void vector_angle();
	void vector_projection();
	void scal_proj();
	void run();
};
class Matrix : public Calc {
private:
	matrix A;
	matrix lower;
	matrix upper;
	std::pair<int, int> size;
	int sq_size = 0;
	void clear();
	void identity();
	Matrix& operator=(Matrix& a);
public:
	void f_open();
	void save_matrix();
	Matrix(int row, int col);
	Matrix(const std::string& f_name);
	Matrix(int size);
	Matrix();
	bool check_range(int row, int col);
	bool check_square();
	void print();
	void print_lu();
	std::pair<int, int> get_size();
	void sum(Matrix& a, Matrix& b, int sign);
	void scal_mult(double scal_val, Matrix& a);
	void scal_div(double scal_val, Matrix& a);
	void matrix_mult(Matrix& a, Matrix& b);
	void pow(Matrix& a, int pow);
	void transpoition(Matrix& a);
	double det();
	void lu_decompos();
	vector gauss(Matrix A);
	void inverse(Matrix& a);
	int rank();
};
class Vector {
private:
	vector V;
	int size;
public:
	void f_open();
	void save_vector();
	Vector(const std::string& f_name);
	Vector(int inp_size);
	Vector();
	void print();
	int get_size();
	bool check_eq_size(Vector& a, Vector& b);
	void sum(Vector& a, Vector& b, int sign);
	void scal_mult(double scal_val, Vector& a);
	void cross_product(Vector& a, Vector& b);
	double dot_prod(Vector& a, Vector& b);
	void scal_div(double scal_val, Vector& a);
	double magnitude();
	double angle(Vector& a, Vector& b);
	void v_proj(Vector& a, Vector& base);
	double scal_proj(Vector& a, Vector& base);
};

