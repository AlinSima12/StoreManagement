#pragma once
#include <ostream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "repo_store.h"
#include "produs.h"
#include "cos.h"
#include "undo.h"

using std::vector;
//using std::ostream;
using std::map;

class Service {

private:
	RepoAbstract& repo;
	Cos cos;
	ComplexUndoAction undo;

public:
	/// <summary>
	/// Initializeaza service
	/// </summary>
	/// <param name="my_repo"></param>
	Service(RepoAbstract& my_repo, Cos my_cos) : repo{ my_repo }, cos{ my_cos } {}

	/// <summary>
	/// Returneasa o lista de produse
	/// </summary>
	/// <returns></returns>
	const vector <Product> get_produse_srv();

	const vector <Product> get_produse_cos_srv();

	/// <summary>
	/// Adauga un produs la lista
	/// </summary>
	/// <param name="name">numele produsului</param>
	/// <param name="type">tipul produsului</param>
	/// <param name="price">pretul produsului</param>
	/// <param name="producer">producatorul produsului</param>
	void add_srv(const string &name, const string &type, const int &price, const string &producer);
	
	void add_cos_srv(const string& name);

	void add_random_cos_srv(int n);

	void validate_product(const Product& p);

	void validate_existing_product(const string& p);

	/// <summary>
	/// Sterge un produs din lista
	/// </summary>
	/// <param name="name"></param>
	void del_srv(const string& name);

	void empty_cos_srv();

	/// <summary>
	/// Modifica datele studentului
	/// </summary>
	/// <param name="name">numele produsului</param>
	/// <param name="type">tipul produsului</param>
	/// <param name="price">pretul produsului</param>
	/// <param name="producer">producatorul produsului</param>
	void modify_srv(const string& name, const string& type, const int& price, const string& producer);
	
	Product search_srv(const string& name);

	map <int, Product> filter_srv(const int& choice, const string& filtru, const int& pret);

	vector <Product> sort_srv(const int& choice);

	vector <Product> sort2_srv();

	//void load_from_file_srv();

	//void save_to_file_srv();

	void save_cart_srv(const string& filename);
	
	void do_undo_srv();
};


void test_add_srv();
void test_del_srv();
void test_modify_srv();
void test_search_srv();
void test_filter_srv();
void test_sort_srv();
void test_sort2_srv();
void test_validate_product();
void test_add_cos_srv();
void test_empty_cos_srv();
void test_add_random_cos_srv();

class ProductValidatorException {
	vector<string> msgs;
public:
	ProductValidatorException(const vector<string>& errors) : msgs{ errors } {}

	friend ostream& operator<<(ostream& out, const ProductValidatorException& ex);
};

ostream& operator<<(ostream& out, const ProductValidatorException& ex);