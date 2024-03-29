#include <assert.h>
#include <iostream>
#include "srv_store.h"
#include <string>
#include <vector>
#include <ostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <map>

using namespace std;

using std::vector;
using std::ostream;
using std::string;
using std::map;


const vector <Product> Service::get_produse_srv() {
	return repo.get_produse_repo();
}

bool cmp_producator_type(const Product& p1, const Product& p2) {
	if (p1.get_producer() != p2.get_producer())
		return p1.get_producer() < p2.get_producer();
	else
		return p1.get_type() < p2.get_type();
}

bool cmp_name(const Product& p1, const Product& p2) {
	return p1.get_name() < p2.get_name();
}

bool cmp_price(const Product& p1, const Product& p2) {
	return p1.get_price() < p2.get_price();
}

void Service::add_srv (const string& name, const string& type, const int& price, const string& producer){
	Product p = Product(name, type, price, producer);
	validate_product(p);
	repo.add_repo(p);
	//AddUndoAction* add_action = new AddUndoAction(repo, p);
	undo.add_child(new AddUndoAction(repo, p));
	//delete add_action;
}

void Service::validate_product(const Product& p) {
	vector <string> err;

	vector <Product> produse = get_produse_srv();
	vector <Product>::iterator f = std::find_if(produse.begin(), produse.end(), [=](const Product& produs) {
		return p.get_name() == produs.get_name();
		});
	
	if (f != produse.end()) {
		err.push_back("Acest produs exista deja!\n");
		throw ProductValidatorException(err);
	}
}

void Service::validate_existing_product(const string& name) {
	vector <string> err;

	vector <Product> produse = get_produse_srv();
	vector <Product>::iterator f = std::find_if(produse.begin(), produse.end(), [=](const Product& produs) {
		return name == produs.get_name();
		});

	if (f == produse.end()) {
		err.push_back("Acest produs nu exista!\n");
		throw ProductValidatorException(err);
	}
}


void Service::del_srv(const string& name) {
	validate_existing_product(name);
	Product p = search_srv(name);
	repo.del_repo(name);
	//RemoveUndoAction* rm_action = new RemoveUndoAction(repo, p);
	undo.add_child(new RemoveUndoAction(repo, p));
	//delete rm_action;
}

void Service::modify_srv(const string& name, const string& type, const int& price, const string& producer) {
	validate_existing_product(name);
	Product p = Product(name, type, price, producer);
	repo.modify_repo(name, type, price, producer);
	//ModUndoAction* mod_action = new ModUndoAction(repo, p);
	undo.add_child(new ModUndoAction(repo, p));
	//delete mod_action;
}

Product Service::search_srv(const string& name) {
	validate_existing_product(name);
	return repo.search_repo(name);
}

map <int, Product> Service::filter_srv(const int& choice, const string& filtru, const int& pret) {
	vector <Product> produse = get_produse_srv();
	std::map <int, Product> map_ret;
	int i = 0;
	switch (choice) {
	case 1://dupa pret
		//std::copy_if(produse.begin(), produse.end(), back_inserter(ret_list),
		//	[pret](const Product& m) {
		//		return m.get_price() == pret;
		//	});
		for (auto p : produse) {
			if (p.get_price() == pret) {
				map_ret.insert(pair<int, Product>(i, p));
				i++;
			}
		}
		break;

	case 2://dupa tip
		for (auto p : produse) {
			if (p.get_type() == filtru) {
				map_ret.insert(pair<int, Product>(i, p));
				i++;
			}
		}
		break;

	case 3://dupa producator
		for (auto p : produse) {
			if (p.get_producer() == filtru) {
				map_ret.insert(pair<int, Product>(i, p));
				i++;
			}
		}
		break;

	}
	return map_ret;
}

vector <Product> Service::sort_srv(const int& choice) {
	vector <Product> list = get_produse_srv();
	switch (choice) {
	case 1://dupa nume
		sort(list.begin(), list.end(), cmp_name);
		break;

	case 2://dupa pret
		sort(list.begin(), list.end(), cmp_price);
		break;
	}
	return list;
}

vector <Product> Service::sort2_srv() {
	vector <Product> list = get_produse_srv();
	sort(list.begin(), list.end(), cmp_producator_type);
	return list;
}

ostream& operator<<(ostream& out, const ProductValidatorException& ex) {
	for (const auto& msg : ex.msgs) {
		out << msg << '\n';
	}
	return out;
}

void Service::add_cos_srv(const string& name) {
	validate_existing_product(name);
	Product p = repo.search_repo(name);
	cos.add_cos(p);
}

void Service::add_random_cos_srv(int n) {
	vector <Product> list = get_produse_srv();
		// amestecam vectorul
		while (n > 0) {
			shuffle(list.begin(), list.end(), std::default_random_engine(std::random_device{}()));
			cos.add_cos(list.back());
			n--;
		}
}

void Service::empty_cos_srv() {
	cos.empty_cos();
}

const vector <Product> Service::get_produse_cos_srv() {
	return cos.get_produse_cos();
}

//void Service::load_from_file_srv() {
//	repo.load_from_file_repo();
//}

//void Service::save_to_file_srv() {
//	repo.save_to_file_repo();
//}

void Service::save_cart_srv(const string& filename) {
	cos.save_cart(filename);
}

void Service::do_undo_srv() {
	undo.do_undo();
}

void test_add_srv() {
	FileRepository repo{"test.txt"};
	repo.emptyRepo();
	Cos cos;
	Service srv{ repo, cos};
	repo.emptyRepo();
	srv.add_srv("ciocolata", "aliment", 5, "Kinder");
	assert(srv.get_produse_srv()[0].get_name() == "ciocolata");
	assert(srv.get_produse_srv()[0].get_type() == "aliment");
	assert(srv.get_produse_srv()[0].get_price() == 5);
	assert(srv.get_produse_srv()[0].get_producer() == "Kinder");
	srv.add_cos_srv("ciocolata");
	assert(srv.get_produse_cos_srv()[0].get_name() == "ciocolata");
	assert(srv.get_produse_cos_srv()[0].get_type() == "aliment");
	assert(srv.get_produse_cos_srv()[0].get_price() == 5);
	assert(srv.get_produse_cos_srv()[0].get_producer() == "Kinder");
	srv.do_undo_srv();
}

void test_add_cos_srv() {
	FileRepository repo{ "test.txt" };
	repo.emptyRepo();
	Cos cos;
	Service srv{ repo, cos };
	srv.add_srv("ciocolata", "aliment", 5, "Kinder");
	assert(srv.get_produse_srv()[0].get_name() == "ciocolata");
	assert(srv.get_produse_srv()[0].get_type() == "aliment");
	assert(srv.get_produse_srv()[0].get_price() == 5);
	assert(srv.get_produse_srv()[0].get_producer() == "Kinder");
	srv.add_cos_srv("ciocolata");
	assert(srv.get_produse_cos_srv()[0].get_name() == "ciocolata");
	assert(srv.get_produse_cos_srv()[0].get_type() == "aliment");
	assert(srv.get_produse_cos_srv()[0].get_price() == 5);
	assert(srv.get_produse_cos_srv()[0].get_producer() == "Kinder");
	srv.save_cart_srv("test.txt");
}

void test_add_random_cos_srv() {
	FileRepository repo{ "test.txt" };	Cos cos;
	repo.emptyRepo();
	Service srv{ repo, cos };
	srv.add_srv("ciocolata", "aliment", 5, "Kinder");
	assert(srv.get_produse_srv()[0].get_name() == "ciocolata");
	assert(srv.get_produse_srv()[0].get_type() == "aliment");
	assert(srv.get_produse_srv()[0].get_price() == 5);
	assert(srv.get_produse_srv()[0].get_producer() == "Kinder");
	srv.add_random_cos_srv(1);
	assert(srv.get_produse_cos_srv()[0].get_name() == "ciocolata");
	assert(srv.get_produse_cos_srv()[0].get_type() == "aliment");
	assert(srv.get_produse_cos_srv()[0].get_price() == 5);
	assert(srv.get_produse_cos_srv()[0].get_producer() == "Kinder");
}

void test_validate_product() {
	FileRepository repo{ "test.txt" };	Cos cos;
	repo.emptyRepo();
	Service srv{ repo, cos }; 
	srv.add_srv("ciocolata", "aliment", 5, "Kinder");
	Product produs = Product("ciocolata", "aliment", 5, "Kinder");
	try {
		srv.validate_product(produs);
		assert(false);
	}
	catch (ProductValidatorException ex) {
		assert(true);
	}

	try {
		srv.validate_existing_product("portocala");
		assert(false);
	}
	catch (ProductValidatorException ex) {
		assert(true);
	}
}

void test_del_srv() {
	FileRepository repo{ "test.txt" };	Cos cos;
	repo.emptyRepo();
	Service srv{ repo, cos };
	repo.emptyRepo();
	srv.add_srv("ciocolata", "aliment", 5, "Kinder");
	assert(srv.get_produse_srv()[0].get_name() == "ciocolata");
	assert(srv.get_produse_srv()[0].get_type() == "aliment");
	assert(srv.get_produse_srv()[0].get_price() == 5);
	assert(srv.get_produse_srv()[0].get_producer() == "Kinder");

	srv.add_srv("c", "a", 5, "K");
	assert(srv.get_produse_srv()[1].get_name() == "c");
	assert(srv.get_produse_srv()[1].get_type() == "a");
	assert(srv.get_produse_srv()[1].get_price() == 5);
	assert(srv.get_produse_srv()[1].get_producer() == "K");

	srv.del_srv("ciocolata");
	assert(srv.get_produse_srv()[0].get_name() == "c");
	assert(srv.get_produse_srv()[0].get_type() == "a");
	assert(srv.get_produse_srv()[0].get_price() == 5);
	assert(srv.get_produse_srv()[0].get_producer() == "K");
	srv.do_undo_srv();
}

void test_empty_cos_srv() {
	FileRepository repo{ "test.txt" };	Cos cos;
	repo.emptyRepo();
	Service srv{ repo, cos };

	srv.add_srv("ciocolata", "aliment", 5, "Kinder");
	assert(srv.get_produse_srv()[0].get_name() == "ciocolata");
	assert(srv.get_produse_srv()[0].get_type() == "aliment");
	assert(srv.get_produse_srv()[0].get_price() == 5);
	assert(srv.get_produse_srv()[0].get_producer() == "Kinder");

	srv.add_srv("c", "a", 5, "K");
	assert(srv.get_produse_srv()[1].get_name() == "c");
	assert(srv.get_produse_srv()[1].get_type() == "a");
	assert(srv.get_produse_srv()[1].get_price() == 5);
	assert(srv.get_produse_srv()[1].get_producer() == "K");

	srv.add_cos_srv("ciocolata");
	srv.add_cos_srv("c");
	srv.empty_cos_srv();
	assert(srv.get_produse_cos_srv().size() == 0);
}

void test_modify_srv() {
	FileRepository repo{ "test.txt" };	Cos cos;
	repo.emptyRepo();
	Service srv{ repo, cos };
	srv.add_srv("ciocolata", "aliment", 5, "Kinder");
	assert(srv.get_produse_srv()[0].get_name() == "ciocolata");
	assert(srv.get_produse_srv()[0].get_type() == "aliment");
	assert(srv.get_produse_srv()[0].get_price() == 5);
	assert(srv.get_produse_srv()[0].get_producer() == "Kinder");

	srv.add_srv("c", "a", 5, "K");
	assert(srv.get_produse_srv()[1].get_name() == "c");
	assert(srv.get_produse_srv()[1].get_type() == "a");
	assert(srv.get_produse_srv()[1].get_price() == 5);
	assert(srv.get_produse_srv()[1].get_producer() == "K");

	srv.modify_srv("ciocolata", "ALIMENT", 55, "KINDER");
	assert(srv.get_produse_srv()[0].get_name() == "ciocolata");
	assert(srv.get_produse_srv()[0].get_type() == "ALIMENT");
	assert(srv.get_produse_srv()[0].get_price() == 55);
	assert(srv.get_produse_srv()[0].get_producer() == "KINDER");
	srv.do_undo_srv();
}

void test_search_srv() {
	FileRepository repo{ "test.txt" };	Cos cos;
	repo.emptyRepo();
	Service srv{ repo, cos };
	srv.add_srv("ciocolata", "aliment", 5, "Kinder");
	assert(srv.get_produse_srv()[0].get_name() == "ciocolata");
	assert(srv.get_produse_srv()[0].get_type() == "aliment");
	assert(srv.get_produse_srv()[0].get_price() == 5);
	assert(srv.get_produse_srv()[0].get_producer() == "Kinder");

	srv.add_srv("c", "a", 5, "K");
	assert(srv.get_produse_srv()[1].get_name() == "c");
	assert(srv.get_produse_srv()[1].get_type() == "a");
	assert(srv.get_produse_srv()[1].get_price() == 5);
	assert(srv.get_produse_srv()[1].get_producer() == "K");

	Product p3 = srv.search_srv("ciocolata");
	assert(p3.get_name() == "ciocolata");
	assert(p3.get_type() == "aliment");
	assert(p3.get_price() == 5);
	assert(p3.get_producer() == "Kinder");
}

void test_filter_srv() {
	FileRepository repo{ "test.txt" };	Cos cos;
	repo.emptyRepo();
	Service srv{ repo, cos };
	srv.add_srv("ciocolata", "aliment", 9, "K");
	srv.add_srv("ciocolat", "bautura", 9, "Ki");
	srv.add_srv("ciocola", "aliment", 5, "Kin");
	srv.add_srv("ciocol", "aliment", 5, "Kind");
	srv.add_srv("cioco", "bautura", 9, "Kinde");
	srv.add_srv("cioc", "aliment", 5, "Kinder");

	map <int, Product> list = srv.filter_srv(1, "\0", 5);

	assert(list[0].get_name() == "ciocola");
	assert(list[0].get_type() == "aliment");
	assert(list[0].get_price() == 5);
	assert(list[0].get_producer() == "Kin");

	assert(list[1].get_name() == "ciocol");
	assert(list[1].get_type() == "aliment");
	assert(list[1].get_price() == 5);
	assert(list[1].get_producer() == "Kind");

	assert(list[2].get_name() == "cioc");
	assert(list[2].get_type() == "aliment");
	assert(list[2].get_price() == 5);
	assert(list[2].get_producer() == "Kinder");

	list = srv.filter_srv(2, "bautura", 0);

	assert(list[0].get_name() == "ciocolat");
	assert(list[0].get_type() == "bautura");
	assert(list[0].get_price() == 9);
	assert(list[0].get_producer() == "Ki");

	assert(list[1].get_name() == "cioco");
	assert(list[1].get_type() == "bautura");
	assert(list[1].get_price() == 9);
	assert(list[1].get_producer() == "Kinde");

	list = srv.filter_srv(3, "Kind", 0);

	assert(list[0].get_name() == "ciocol");
	assert(list[0].get_type() == "aliment");
	assert(list[0].get_price() == 5);
	assert(list[0].get_producer() == "Kind");
}

void test_sort_srv() {
	FileRepository repo{ "test.txt" };	Cos cos;
	repo.emptyRepo();
	Service srv{ repo, cos };

	srv.add_srv("e", "b", 5, "e");
	srv.add_srv("b", "e", 2, "b");
	srv.add_srv("c", "d", 3, "c");
	srv.add_srv("f", "a", 6, "f");
	srv.add_srv("a", "f", 1, "a");
	srv.add_srv("d", "c", 4, "d");

	vector <Product> list = srv.sort_srv(1);

	assert(list[0].get_name() == "a");
	assert(list[0].get_type() == "f");
	assert(list[0].get_price() == 1);
	assert(list[0].get_producer() == "a");

	assert(list[1].get_name() == "b");
	assert(list[1].get_type() == "e");
	assert(list[1].get_price() == 2);
	assert(list[1].get_producer() == "b");

	assert(list[2].get_name() == "c");
	assert(list[2].get_type() == "d");
	assert(list[2].get_price() == 3);
	assert(list[2].get_producer() == "c");

	assert(list[3].get_name() == "d");
	assert(list[3].get_type() == "c");
	assert(list[3].get_price() == 4);
	assert(list[3].get_producer() == "d");

	assert(list[4].get_name() == "e");
	assert(list[4].get_type() == "b");
	assert(list[4].get_price() == 5);
	assert(list[4].get_producer() == "e");

	assert(list[5].get_name() == "f");
	assert(list[5].get_type() == "a");
	assert(list[5].get_price() == 6);
	assert(list[5].get_producer() == "f");

	list = srv.sort_srv(2);

	assert(list[0].get_name() == "a");
	assert(list[0].get_type() == "f");
	assert(list[0].get_price() == 1);
	assert(list[0].get_producer() == "a");

	assert(list[1].get_name() == "b");
	assert(list[1].get_type() == "e");
	assert(list[1].get_price() == 2);
	assert(list[1].get_producer() == "b");

	assert(list[2].get_name() == "c");
	assert(list[2].get_type() == "d");
	assert(list[2].get_price() == 3);
	assert(list[2].get_producer() == "c");

	assert(list[3].get_name() == "d");
	assert(list[3].get_type() == "c");
	assert(list[3].get_price() == 4);
	assert(list[3].get_producer() == "d");

	assert(list[4].get_name() == "e");
	assert(list[4].get_type() == "b");
	assert(list[4].get_price() == 5);
	assert(list[4].get_producer() == "e");

	assert(list[5].get_name() == "f");
	assert(list[5].get_type() == "a");
	assert(list[5].get_price() == 6);
	assert(list[5].get_producer() == "f");
}

void test_sort2_srv() {
	FileRepository repo{ "test.txt" };	Cos cos;
	repo.emptyRepo();
	Service srv{ repo, cos };

	srv.add_srv("d", "a", 4, "c");
	srv.add_srv("b", "b", 2, "a");
	srv.add_srv("c", "b", 3, "c");
	srv.add_srv("f", "b", 6, "e");
	srv.add_srv("e", "a", 5, "e");
	srv.add_srv("a", "a", 1, "a");

	vector <Product> list = srv.sort2_srv();

	assert(list[0].get_name() == "a");
	assert(list[0].get_type() == "a");
	assert(list[0].get_price() == 1);
	assert(list[0].get_producer() == "a");

	assert(list[1].get_name() == "b");
	assert(list[1].get_type() == "b");
	assert(list[1].get_price() == 2);
	assert(list[1].get_producer() == "a");

	assert(list[2].get_name() == "d");
	assert(list[2].get_type() == "a");
	assert(list[2].get_price() == 4);
	assert(list[2].get_producer() == "c");

	assert(list[3].get_name() == "c");
	assert(list[3].get_type() == "b");
	assert(list[3].get_price() == 3);
	assert(list[3].get_producer() == "c");

	assert(list[4].get_name() == "e");
	assert(list[4].get_type() == "a");
	assert(list[4].get_price() == 5);
	assert(list[4].get_producer() == "e");

	assert(list[5].get_name() == "f");
	assert(list[5].get_type() == "b");
	assert(list[5].get_price() == 6);
	assert(list[5].get_producer() == "e");

}