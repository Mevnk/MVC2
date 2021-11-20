#include "Calc.h"
Vector::Vector(const std::string& f_name) {
	std::ifstream file;
	file.open(f_name + ".txt");
	file >> size;
	V.resize(size);
	for (int i = 0; i < size; i++) { file >> V[i]; }
}
Vector::Vector(int inp_size) {
	size = inp_size;
	V.resize(size);
}
Vector::Vector() {
	size = 0;
}
void Vector::f_open() {
	std::string fopen;
	std::string path = "./saves/vector/";
	for (const auto& entry : std::filesystem::directory_iterator(path))
		std::cout << entry.path().filename() << std::endl;
	std::cin >> fopen;
	Vector a(path + fopen);
	*this = a;
}
void Vector::save_vector() {
	char save_response;
	std::cout << "Do you want to save the vector? (y/n)" << std::endl;
	std::cin >> save_response;
	if (save_response == 'y') {
		std::string vector_name;
		std::cout << "Name the vector: " << std::endl;
		std::cin >> vector_name;
		std::ofstream file("./saves/vector/" + vector_name + ".txt");
		file << size << std::endl;
		for (int i = 0; i < size; i++) { file << V[i] << " "; }
		return;
	}
	return;
}
void Vector::print() {
	for (int i = 0; i < size; i++) { std::cout << V[i] << " "; }
	std::cout << std::endl;
}
int Vector::get_size() { return size; }
bool Vector::check_eq_size(Vector& a, Vector& b) {
	if (a.size == b.size) return true;
	return false;
}
void Vector::sum(Vector& a, Vector& b, int sign) {
	if (sign != 1 && sign != -1) return; 
	if (!check_eq_size(a, b)) return;
	for (int i = 0; i < size; i++) { V[i] = a.V[i] + sign * b.V[i]; }
}
void Vector::scal_mult(double scal_val, Vector& a) {
	for (int i = 0; i < size; i++) { V[i] = a.V[i] * scal_val; }
}
void Vector::scal_div(double scal_val, Vector& a) {
	for (int i = 0; i < size; i++) { V[i] = a.V[i] / scal_val; }
}
void Vector::cross_product(Vector& a, Vector& b) {
	if (!check_eq_size(a, b)) return;
	if (a.size != 3 && a.size != 7) return;
	V[0] = a.V[1] * b.V[2] - a.V[2] * b.V[1];
	V[1] = -(a.V[0] * b.V[2] - a.V[2] * b.V[0]);
	V[2] = a.V[0] * b.V[1] - a.V[1] * b.V[0];
}
double Vector::dot_prod(Vector& a, Vector& b) {
	double sum{ 0 };
	for (int i = 0; i < size; i++) { sum += a.V[i] * b.V[i]; }
	return sum;
}
double Vector::magnitude() {
	double sum_of_sq{ 0 };
	for (int i = 0; i < size; i++) { sum_of_sq += std::pow(V[i], 2); }
	return std::sqrt(sum_of_sq);
}
double Vector::angle(Vector& a, Vector& b) {
	double dot = a.V[0] * b.V[0] + a.V[1] * b.V[1];
	double det = a.V[0] * b.V[1] - a.V[1] * b.V[0];
	double angle = std::atan2(det, dot);
	return angle;
}
void Vector::v_proj(Vector& a, Vector& base) {
	double base_mag = base.magnitude();
	double dot=dot_prod(a, base);
	double temp1 = dot / pow(base_mag, 2);
	std::cout << base_mag << std::endl;
	this->scal_mult(temp1, base);
}
double Vector::scal_proj(Vector& a, Vector& base) { return dot_prod(base, a) / base.magnitude(); }