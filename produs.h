#pragma once
#include <string>
#include <iostream>

using std::string;
using std::cout;

class Product {
private:
	string name;
	string type;
	int price;
	string producer;

public:
	/// <summary>
	/// Nu creeaza un produs gol
	/// </summary>
	Product() = default;

	/// <summary>
	/// Creeaza un produs cu datele date
	/// </summary>
	/// <param name="nume">numele produsului</param>
	/// <param name="tip">tipul produsului</param>
	/// <param name="pret">pretul produsului</param>
	/// <param name="producator">producatorul produsului</param>
	Product(string nume, string tip, int pret, string producator) : name{ nume }, type{ tip }, price{ pret }, producer{ producator } {}

	/// <summary>
	/// Copiaza un produs
	/// </summary>
	/// <param name="p">produsul care se copiaza</param>
	Product(const Product& p): name {p.name}, type {p.type}, price{p.price}, producer{p.producer}{
	}
	

	string get_name() const{
		return this->name;
	}

	string get_type() const{
		return this->type;
	}

	int get_price()const noexcept{
		return this->price;
	}

	string get_producer() const{
		return this->producer;
	}

	void set_name(const string& nume) {
		this->name = nume;
	}

	void set_type(const string& tip) {
		this->type = tip;
	}

	void set_price(const int& pret) noexcept {
		this->price = pret;
	}

	void set_producer(const string& producator) {
		this->producer = producator;
	}
};

void test_get_and_set();