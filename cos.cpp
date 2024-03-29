#include <assert.h>
#include <exception>
#include <algorithm>
#include <functional>
#include <iostream>
#include <fstream>

#include "cos.h"

using std::bad_exception;
using std::ifstream;
using std::ofstream;

using namespace std;

void Cos::add_cos(const Product& p) {
	cos_produse.push_back(p);
}

void Cos::empty_cos() {
	cos_produse.clear();
}

const vector <Product> Cos::get_produse_cos() {
	return cos_produse;
}

void Cos::save_cart(const string& filename){
	ofstream fout(filename);
	if (!fout.is_open()) {
		throw bad_exception();
	}

	for (auto& p : get_produse_cos()) {
		fout << p.get_name() << ' ' << p.get_type() << ' ' << p.get_price() << ' ' << p.get_producer() << std::endl;
	}

	fout.close();
}

void test_add_cos() {
	Cos cos;
	Product p("ciocolata", "aliment", 5, "Kinder");
	cos.add_cos(p);
	assert(cos.get_produse_cos()[0].get_name() == "ciocolata");
	assert(cos.get_produse_cos()[0].get_type() == "aliment");
	assert(cos.get_produse_cos()[0].get_price() == 5);
	assert(cos.get_produse_cos()[0].get_producer() == "Kinder");
}

void test_del_cos() {
	Cos cos;
	Product p("ciocolata", "aliment", 5, "Kinder");
	cos.add_cos(p);
	assert(cos.get_produse_cos()[0].get_name() == "ciocolata");
	assert(cos.get_produse_cos()[0].get_type() == "aliment");
	assert(cos.get_produse_cos()[0].get_price() == 5);
	assert(cos.get_produse_cos()[0].get_producer() == "Kinder");

	Product p2("c", "a", 5, "k");
	cos.add_cos(p2);

	cos.empty_cos();
	assert(cos.get_produse_cos().size() == 0);
}

