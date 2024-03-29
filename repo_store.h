#pragma once
#include <vector>
#include <map>
#include <random>

#include "my_list.h"
#include "produs.h"

using std::vector;
using std::pair;
using std::ostream;

class RepoException {
public:
	string msgs;

	RepoException(string errors) : msgs{ errors } {}

	friend ostream& operator<<(ostream& out, const RepoException& ex);
};

ostream& operator<<(ostream& out, const RepoException& ex);

class RepoAbstract {
public:
	//RepoAbstract() = default;
	virtual ~RepoAbstract() {};

	virtual void add_repo(const Product& p) = 0;

	virtual void del_repo(const string& name) = 0;

	virtual void modify_repo(const string& name, const string& type, const int& price, const string& producer) = 0;

	virtual const vector <Product> get_produse_repo() = 0;

	virtual Product search_repo(const string& name) = 0;
};

class Repository : public RepoAbstract{
	 
protected:
	//vector <Product> produse;
	vector <Product> produse;

public:
	Repository() = default;

	//Repository(const Repository& r) = delete;

	/// <summary>
	/// Adauga produsul in lista
	/// </summary>
	/// <param name="p">produsul care se adauga</param>
	void add_repo(const Product& p);

	/// <summary>
	/// Sterge produsul cu numele dat
	/// </summary>
	/// <param name="name">numele produsului de sters>/param>
	void del_repo(const string& name);

	/// <summary>
	/// Modifica datele unui produs
	/// </summary>
	/// <param name="name">numele produsului</param>
	/// <param name="type">tipul produsului</param>
	/// <param name="price">pretul produsului</param>
	/// <param name="producer">producatorul produsului</param>
	void modify_repo(const string& name, const string& type, const int& price, const string& producer);

	const vector <Product> get_produse_repo();

	Product search_repo(const string& name);

	void emptyRepo() {
		this->produse.clear();
	}
};

class RepositoryLab : public RepoAbstract {

protected:
	//vector <Product> produse;
	std::map <string, Product> produse;
	double prob;
public:

	RepositoryLab(double _r) :prob{ _r } {};

	/// <summary>
	/// Adauga produsul in lista
	/// </summary>
	/// <param name="p">produsul care se adauga</param>
	
	double get_prob() {
		return prob;
	}
	
	void add_repo(const Product& p) {
		double lower_bound = 0;
		double upper_bound = 1;
		std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
		std::default_random_engine re;
		double a_random_double = unif(re);

		if (a_random_double < get_prob()) {
			throw RepoException("Probabilitate " + std::to_string(a_random_double) + " sub cea data");
		}
		produse.insert(pair<string, Product>(p.get_name(), p));
	};

	/// <summary>
	/// Sterge produsul cu numele dat
	/// </summary>
	/// <param name="name">numele produsului de sters>/param>
	void del_repo(const string& name) {
		double lower_bound = 0;
		double upper_bound = 1;
		std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
		std::default_random_engine re;
		double a_random_double = unif(re);

		if (a_random_double < get_prob()) {
			throw RepoException("Probabilitate " + std::to_string(a_random_double) + " sub cea data");
		}
		produse.erase(name);
	}

	/// <summary>
	/// Modifica datele unui produs
	/// </summary>
	/// <param name="name">numele produsului</param>
	/// <param name="type">tipul produsului</param>
	/// <param name="price">pretul produsului</param>
	/// <param name="producer">producatorul produsului</param>
	void modify_repo(const string& name, const string& type, const int& price, const string& producer) {
		double lower_bound = 0;
		double upper_bound = 1;
		std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
		std::default_random_engine re;
		double a_random_double = unif(re);

		if (a_random_double < get_prob()) {
			throw RepoException("Probabilitate " + std::to_string(a_random_double) + " sub cea data");
		}
		produse[name].set_price(price);
			produse[name].set_producer(producer);
			produse[name].set_type(type);
	}

	const vector <Product> get_produse_repo() {
		vector <Product> products;
		for (auto const& x : produse) {
			products.push_back(x.second);
		}
		return products;
	}

	Product search_repo(const string& name) {
		return produse[name];
	}

	void emptyRepo() {
		this->produse.clear();
	}

};

class FileRepository : public Repository {
private:
	//vector <Product> produse;

	string filename;

public:
	void add_repo(const Product& p) {
		produse.push_back(p);
		save_to_file_repo();
	}

	void del_repo(const string& name) {
		vector <Product>::iterator f = remove_if(produse.begin(), produse.end(),
			[=](const Product& p) {
				return p.get_name() == name;
			});
		produse.erase(f);
		save_to_file_repo();
	}

	void modify_repo(const string& name, const string& type, const int& price, const string& producer) {
		vector <Product>::iterator f = find_if(produse.begin(), produse.end(),
			[=](Product p) {
				return p.get_name() == name;
			});

		(*f).set_type(type);
		(*f).set_price(price);
		(*f).set_producer(producer);
		save_to_file_repo();
	}

	const vector <Product> get_produse_repo() {
		load_from_file_repo();
		//save_to_file_repo();
		return produse;
	}
	void save_to_file_repo();

	void load_from_file_repo();

	FileRepository(string fisier) : Repository(), filename{fisier}{}

	void emptyRepo() {
		this->produse.clear();
		save_to_file_repo();
	}
};

void test_add_repo();
void test_del_repo();
void test_modify_repo();
void test_search_repo();