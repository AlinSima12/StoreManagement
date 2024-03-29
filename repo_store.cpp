#include <assert.h>
#include <exception>
#include <algorithm>
#include <functional>
#include <fstream>

#include "repo_store.h"

using std::bad_exception;
using std::ifstream;
using std::ofstream;

using namespace std;

void Repository::add_repo(const Product& p) {
	produse.push_back(p);
}

void Repository::del_repo(const string& name) {
	vector <Product>::iterator f = remove_if(produse.begin(), produse.end(),
		[=](const Product& p) {
			return p.get_name() == name;
		});
	produse.erase(f);
}

void Repository::modify_repo(const string& name, const string& type, const int& price, const string& producer) {
	vector <Product>::iterator f = find_if(produse.begin(), produse.end(), 
		[=](Product p) {
			return p.get_name() == name;
		});

	(*f).set_type(type);
	(*f).set_price(price);
	(*f).set_producer(producer);
}	

const vector <Product> Repository::get_produse_repo(){
	return produse;
}

Product Repository::search_repo(const string& name) {
	vector <Product>::iterator f = find_if(produse.begin(), produse.end(),
		[=](Product p) {
			return p.get_name() == name;
		});
	if (f == produse.end())
		throw bad_exception();
	else
		return (*f);
}


void FileRepository::load_from_file_repo() {
	ifstream fin(filename);
	Repository::emptyRepo();
	if (!fin.is_open()) {
		throw bad_exception();
	}

	while (!fin.eof()) {
		string name;
		fin >> name;

		// daca gasim linii goale
		if (fin.eof())
			break;
		string type;
		fin >> type;
		
		int price;
		fin >> price;
		
		string producer;
		fin >> producer;
		

		Product p(name, type, price, producer);
		Repository::add_repo(p);
	}

	fin.close();
}

void FileRepository::save_to_file_repo() {
	ofstream fout(filename);
	if (!fout.is_open()) {
		throw bad_exception();
	}

	for (auto& p : Repository::get_produse_repo()) {
		fout << p.get_name() << ' ' << p.get_type() << ' ' << p.get_price() << ' ' << p.get_producer() << std::endl;
	}

	fout.close();
}

ostream& operator<<(ostream& out, const RepoException& ex) {
		out << ex.msgs;
	return out;
}

void test_add_repo(){
	FileRepository repo{ "test.txt" }; repo;
	Product p("ciocolata", "aliment", 5, "Kinder");
	repo.add_repo(p);
	assert(repo.get_produse_repo()[0].get_name() == "ciocolata");
	assert(repo.get_produse_repo()[0].get_type() == "aliment");
	assert(repo.get_produse_repo()[0].get_price() == 5);
	assert(repo.get_produse_repo()[0].get_producer() == "Kinder");
}

void test_del_repo() {
	FileRepository repo{ "test.txt" };	Product p("ciocolata", "aliment", 5, "Kinder");
	repo.add_repo(p);
	assert(repo.get_produse_repo()[0].get_name() == "ciocolata");
	assert(repo.get_produse_repo()[0].get_type() == "aliment");
	assert(repo.get_produse_repo()[0].get_price() == 5);
	assert(repo.get_produse_repo()[0].get_producer() == "Kinder");

	Product p2("c", "a", 5, "k");
	repo.add_repo(p2);

	repo.del_repo("ciocolata");
	assert(repo.get_produse_repo()[0].get_name() == "c");
	assert(repo.get_produse_repo()[0].get_type() == "a");
	assert(repo.get_produse_repo()[0].get_price() == 5);
	assert(repo.get_produse_repo()[0].get_producer() == "k");
	assert(repo.get_produse_repo().size() == 1);
}

void test_modify_repo() {
	FileRepository repo{ "test.txt" };
	Product p("ciocolata", "aliment", 5, "Kinder");
	repo.add_repo(p);
	assert(repo.get_produse_repo()[0].get_name() == "ciocolata");
	assert(repo.get_produse_repo()[0].get_type() == "aliment");
	assert(repo.get_produse_repo()[0].get_price() == 5);
	assert(repo.get_produse_repo()[0].get_producer() == "Kinder");

	Product p2("c", "a", 5, "k");
	repo.add_repo(p2);

	repo.modify_repo("ciocolata", "ALIMENT", 55, "KINDER");
	assert(repo.get_produse_repo()[0].get_name() == "ciocolata");
	assert(repo.get_produse_repo()[0].get_type() == "ALIMENT");
	assert(repo.get_produse_repo()[0].get_price() == 55);
	assert(repo.get_produse_repo()[0].get_producer() == "KINDER");

}

void test_search_repo() {
	FileRepository repo{ "test.txt" };	Product p("ciocolata", "aliment", 5, "Kinder");
	repo.add_repo(p);
	assert(repo.get_produse_repo()[0].get_name() == "ciocolata");
	assert(repo.get_produse_repo()[0].get_type() == "aliment");
	assert(repo.get_produse_repo()[0].get_price() == 5);
	assert(repo.get_produse_repo()[0].get_producer() == "Kinder");
	
	Product p2("c", "a", 5, "k");
	repo.add_repo(p2);

	Product p3("c", "a", 5, "k");

	p3 = repo.search_repo("ciocolata");
	assert(p3.get_name() == "ciocolata");
	assert(p3.get_type() == "aliment");
	assert(p3.get_price() == 5);
	assert(p3.get_producer() == "Kinder");

	try {
		repo.search_repo("nu-i");
		//assert(false);
	}
	catch(bad_exception){
		assert(true);
	}

}

