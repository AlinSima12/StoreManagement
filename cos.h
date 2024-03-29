#pragma once
#include <vector>

#include "produs.h"

using std::vector;

class Cos {

private:
	//vector <Product> produse;
	vector <Product> cos_produse;

public:
	//Repository() = default;

	//Repository(const Repository& r) = delete;

	/// <summary>
	/// Adauga produsul in lista
	/// </summary>
	/// <param name="p">produsul care se adauga</param>
	void add_cos(const Product& p);

	/// <summary>
	/// Sterge produsul cu numele dat
	/// </summary>
	/// <param name="name">numele produsului de sters>/param>
	void empty_cos();

	/// <summary>
	/// Modifica datele unui produs
	/// </summary>
	/// <param name="name">numele produsului</param>
	/// <param name="type">tipul produsului</param>
	/// <param name="price">pretul produsului</param>
	/// <param name="producer">producatorul produsului</param>
	const vector <Product> get_produse_cos();

	void save_cart(const string& filename);

};


void test_add_cos();
void test_del_cos();