#include "Calc.h"
Calc::Calc() {
	key_to_proceed = 'a';
	map.emplace(0, [this]() {main_menu(); });
	map.emplace(1, [this]() {matrix_ops(); });
	map.emplace(2, [this]() {vector_ops(); });
	map.emplace(11, [this]() {matrix_sum(); });
	map.emplace(12, [this]() {matrix_scal_mult('*'); });
	map.emplace(13, [this]() {matrix_scal_mult('/'); });
	map.emplace(14, [this]() {matrix_mult(); });
	map.emplace(15, [this]() {matrix_pow(); });
	map.emplace(16, [this]() {matrix_transpos(); });
	map.emplace(17, [this]() {determinant(); });
	map.emplace(18, [this]() {lu_decomposition(); });
	map.emplace(19, [this]() {matrix_inverse(); });
	map.emplace(20, [this]() {matrix_rank(); });
	map.emplace(21, [this]() {vector_sum(); });
	map.emplace(22, [this]() {vector_scal_mult('*'); });
	map.emplace(23, [this]() {cross_product(); });
	map.emplace(24, [this]() {dot_product(); });
	map.emplace(25, [this]() {vector_scal_mult('/'); });
	map.emplace(26, [this]() {vector_magnitude(); });
	map.emplace(27, [this]() {vector_angle(); });
	map.emplace(28, [this]() {vector_projection(); });
	map.emplace(29, [this]() {scal_proj(); });
}
void Calc::proceed() {
	std::cout << "Press any letter to proceed" << std::endl;
	std::cin >> key_to_proceed;
}
void Calc::main_menu() {
	system("cls");
	std::cout << "1 Matrix operations" << std::endl;
	std::cout << "2 Vector operations" << std::endl;
	std::cout << "3 Exit" << std::endl;
	std::cin >> response;
}
void Calc::matrix_ops() {
	system("cls");
	std::cout << "1 Sum/difference" << std::endl;
	std::cout << "2 Scalar multiplication" << std::endl;
	std::cout << "3 Scalar division" << std::endl;
	std::cout << "4 Matrix multiplication" << std::endl;
	std::cout << "5 Power of a matrix" << std::endl;
	std::cout << "6 Transposition of a matrix" << std::endl;
	std::cout << "7 Determinant of a matrix" << std::endl;
	std::cout << "8 LU decomposition" << std::endl;
	std::cout << "9 Inverse of a matrix" << std::endl;
	std::cout << "10 Rank of a matrix" << std::endl;
	std::cout << "0 Return" << std::endl;
	std::cout << "-1 Exit" << std::endl;
	std::cin >> response;
	system("cls");
	if (response > 0) response += 10;
}
void Calc::vector_ops() {
	system("cls");
	std::cout << "1 Sum/difference" << std::endl;
	std::cout << "2 Scalar multiplication" << std::endl;
	std::cout << "3 Cross product" << std::endl;
	std::cout << "4 Dot product" << std::endl;
	std::cout << "5 Scalar division" << std::endl;
	std::cout << "6 Magnitude" << std::endl;
	std::cout << "7 Angle" << std::endl;
	std::cout << "8 Vector projection" << std::endl;
	std::cout << "9 Scalar projection" << std::endl;
	std::cout << "0 Return" << std::endl;
	std::cout << "-1 Exit" << std::endl;
	std::cin >> response;
	system("cls");
	if (response > 0) response += 20;
}
void Calc::matrix_sum() {
	char sign;
	std::cout << "Choose the first matrix: " << std::endl;
	Matrix A;
	A.f_open();
	system("cls");
	A.print();
	proceed();
	system("cls");
	std::cout << "Choose the second matrix: " << std::endl;
	Matrix B;
	B.f_open();
	system("cls");
	B.print();
	proceed();
	system("cls");
	if (A.get_size().first == B.get_size().first && A.get_size().second == B.get_size().second) {
		std::cout << "Choose the sign (+/-): " << std::endl;
		std::cin >> sign;
		int sign_int;
		switch (sign) {
		case '+':
			sign_int = 1;
			break;
		case '-':
			sign_int = -1;
			break;
		default:
			sign_int = 1;
			break;
		}
		Matrix res(A.get_size().first, A.get_size().second);
		res.sum(A, B, sign_int);
		system("cls");
		res.print();
		res.save_matrix();
	}
	response = 0;
}
void Calc::matrix_scal_mult(const char sign) {
	Matrix A;
	double scal_val;
	std::cout << "Choose the matrix: " << std::endl;
	A.f_open();
	system("cls");
	A.print();
	proceed();
	system("cls");
	std::cout << "Enter the scalar value: " << std::endl;
	std::cin >> scal_val;
	system("cls");
	Matrix res(A.get_size().first, A.get_size().second);
	if (sign == '/') {
		if (sign == 0) { 
			std::cout << "Division by zero" << std::endl; 
			proceed();
			return; 
		}
		res.scal_div(scal_val, A);
	}
	else { res.scal_mult(scal_val, A); }
	res.print();
	res.save_matrix();
	response = 0;
}
void Calc::matrix_mult() {
	std::cout << "Choose the first matrix: " << std::endl;
	Matrix A;
	A.f_open();
	system("cls");
	A.print();
	proceed();
	system("cls");
	std::cout << "Choose the second matrix: " << std::endl;
	Matrix B;
	B.f_open();
	system("cls");
	B.print();
	proceed();
	system("cls");
	if (A.get_size().second != B.get_size().first) { 
		std::cout << "Incompatible sizes" << std::endl; 
		proceed();
		return; 
	}
	Matrix res(A.get_size().first, B.get_size().second);
	res.matrix_mult(A, B);
	res.print();
	res.save_matrix();
	response = 0;
}
void Calc::matrix_pow() {
	int power;
	Matrix A;
	std::cout << "Choose the matrix: " << std::endl;
	A.f_open();
	if (!A.check_square()) { std::cout << "Matrix not square" << std::endl; return; }
	system("cls");
	A.print();
	proceed();
	system("cls");
	std::cout << "Enter the power: " << std::endl;
	std::cin >> power;
	Matrix res(A.get_size().first);
	res.pow(A, power);
	res.print();
	res.save_matrix();
	response = 0;
}
void Calc::matrix_transpos() {
	std::cout << "Choose the matrix: " << std::endl;
	Matrix A;
	A.f_open();
	system("cls");
	A.print();
	proceed();
	system("cls");
	Matrix res(A.get_size().second, A.get_size().first);
	res.transpoition(A);
	res.print();
	res.save_matrix();
	response = 0;
}
void Calc::determinant() {
	std::cout << "Choose the matrix: " << std::endl;
	Matrix A;
	A.f_open();
	system("cls");
	if (!A.check_square()) { std::cout << "Matrix not square" << std::endl; return; }
	A.print();
	proceed();
	system("cls");
	std::cout << "Determinant: " << A.det() << std::endl;
	proceed();
	response = 0;
}
void Calc::lu_decomposition() {
	std::cout << "Choose the matrix: " << std::endl;
	Matrix A;
	A.f_open();
	system("cls");
	A.print();
	proceed();
	system("cls");
	A.lu_decompos();
	A.print_lu();
	proceed();
	response = 0;
}
void Calc::matrix_inverse() {
	std::cout << "Choose the matrix: " << std::endl;
	Matrix A;
	A.f_open();
	system("cls");
	if (!A.check_square()) { 
		std::cout << "Matrix not square" << std::endl; 
		proceed();
		return; 
	}
	if (A.det() == 0) {
		std::cout << "Zero determinant" << std::endl;
		proceed();
		return;
	}
	A.print();
	proceed();
	system("cls");
	Matrix res(A.get_size().first);
	res.inverse(A);
	res.print();
	res.save_matrix();
	response = 0;
}
void Calc::matrix_rank() {
	std::cout << "Choose the matrix: " << std::endl;
	Matrix A;
	A.f_open();
	system("cls");
	A.print();
	proceed();
	system("cls");
	std::cout << "Matrix rank: " << A.rank() << std::endl;
	proceed();
	response = 0;
}
void Calc::vector_sum() {
	char sign;
	std::cout << "Choose the first vector: " << std::endl;
	Vector A;
	A.f_open();
	system("cls");
	A.print();
	proceed();
	system("cls");
	std::cout << "Choose the second vector: " << std::endl;
	Vector B;
	B.f_open();
	system("cls");
	B.print();
	proceed();
	system("cls");
	if (A.get_size() == B.get_size()) {
		std::cout << "Choose the sign (+/-): " << std::endl;
		std::cin >> sign;
		int sign_int;
		switch (sign) {
		case '+':
			sign_int = 1;
			break;
		case '-':
			sign_int = -1;
			break;
		default:
			sign_int = 1;
			break;
		}
		Vector res(A.get_size());
		res.sum(A, B, sign_int);
		system("cls");
		res.print();
		res.save_vector();
	}
	response = 0;
}
void Calc::vector_scal_mult(char sign) {
	Vector A;
	double scal_val;
	std::cout << "Choose the vector: " << std::endl;
	A.f_open();
	system("cls");
	A.print();
	proceed();
	system("cls");
	std::cout << "Enter the scalar value: " << std::endl;
	std::cin >> scal_val;
	system("cls");
	Vector res(A.get_size());
	if (sign == '/') {
		if (sign == 0) {
			std::cout << "Division by zero" << std::endl;
			proceed();
			return;
		}
		res.scal_div(scal_val, A);
	}
	else { res.scal_mult(scal_val, A); }
	res.print();
	res.save_vector();
	response = 0;
}
void Calc::cross_product() {
	Vector A;
	std::cout << "Choose the first vector: " << std::endl;
	A.f_open();
	system("cls");
	A.print();
	proceed();
	system("cls");
	Vector B;
	std::cout << "Choose the second vector: " << std::endl;
	B.f_open();
	system("cls");
	B.print();
	proceed();
	system("cls");
	if (A.get_size() != B.get_size()) {
		std::cout << "Unequal sizes" << std::endl;
		proceed();
		return;
	}
	if (A.get_size() != 3 && A.get_size() != 7) {
		std::cout << "Vectors must be of size 3 or 7 to perform cross product" << std::endl;
		proceed();
		return;
	}
	Vector res(A.get_size());
	res.cross_product(A, B);
	res.print();
	res.save_vector();
	response = 0;
}
void Calc::dot_product() {
	Vector A;
	std::cout << "Choose the first vector: " << std::endl;
	A.f_open();
	system("cls");
	A.print();
	proceed();
	system("cls");
	Vector B;
	std::cout << "Choose the second vector: " << std::endl;
	B.f_open();
	system("cls");
	B.print();
	proceed();
	system("cls");
	if (A.get_size() != B.get_size()) {
		std::cout << "Unequal sizes" << std::endl;
		proceed();
		return;
	}
	Vector res(A.get_size());
	res.dot_prod(A, B);
	res.print();
	res.save_vector();
	response = 0;
}
void Calc::vector_magnitude() {
	Vector A;
	std::cout << "Choose the first vector: " << std::endl;
	A.f_open();
	system("cls");
	A.print();
	proceed();
	system("cls");
	std::cout << "Magnitude: " << A.magnitude() << std::endl;
	proceed();
	response = 0;
}
void Calc::vector_angle() {
	Vector A;
	std::cout << "Choose the first vector: " << std::endl;
	A.f_open();
	system("cls");
	A.print();
	proceed();
	system("cls");
	Vector B;
	std::cout << "Choose the second vector: " << std::endl;
	B.f_open();
	system("cls");
	B.print();
	proceed();
	system("cls");
	if (A.get_size() != B.get_size()) {
		std::cout << "Unequal sizes" << std::endl;
		proceed();
		return;
	}
	Vector res(A.get_size());
	std::cout << "Angle: " << res.angle(A, B) << std::endl;
	proceed();
	response = 0;
}
void Calc::vector_projection() {
	Vector A;
	std::cout << "Choose the vector: " << std::endl;
	A.f_open();
	system("cls");
	A.print();
	proceed();
	system("cls");
	Vector B;
	std::cout << "Choose the base vector: " << std::endl;
	B.f_open();
	system("cls");
	B.print();
	proceed();
	system("cls");
	if (A.get_size() != B.get_size()) {
		std::cout << "Unequal sizes" << std::endl;
		proceed();
		return;
	}
	Vector res(A.get_size());
	res.v_proj(A, B);
	res.print();
	res.save_vector();
	response = 0;
}
void Calc::scal_proj() {
	Vector A;
	std::cout << "Choose the vector: " << std::endl;
	A.f_open();
	system("cls");
	A.print();
	proceed();
	system("cls");
	Vector B;
	std::cout << "Choose the base vector: " << std::endl;
	B.f_open();
	system("cls");
	B.print();
	proceed();
	system("cls");
	if (A.get_size() != B.get_size()) {
		std::cout << "Unequal sizes" << std::endl;
		proceed();
		return;
	}
	std::cout << "Scalar projection : " << A.scal_proj(A, B) << std::endl;
	proceed();
	response = 0;
}
void Calc::run() {
	while (response != 3 && response != -1) {
		auto it = map.find(response);
		if (it != map.end()) {
			it->second();
		}
	}
}