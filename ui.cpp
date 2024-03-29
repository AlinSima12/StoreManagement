#include <iostream>
#include "ui.h"
#include <string>
#include <map>

using std::cin;
using std::cout;
using std::string;
using std::vector;

void Ui::add_ui() {
	string name, type, producer;
	int price;

	cout << "Introduceti numele produsului: \n";
	cin >> name;
	cout << "Introduceti tipul produsului: \n";
	cin >>  type;
	cout << "Introduceti pretul produsului: \n";
	cin >> price;
	cout << "Introduceti producatorul produsului: \n";
	cin >> producer;

	srv.add_srv(name, type, price, producer);
}

void Ui::add_cart_ui() {
	string name;

	cout << "Introduceti numele produsului: \n";
	cin >> name;
	srv.add_cos_srv(name);
}

void Ui::add_random_cart_ui() {
	int n;

	cout << "Introduceti numarul de produse: \n";
	cin >> n;
	srv.add_random_cos_srv(n);
}

void Ui::del_ui() {
	string name;
	cout << "Introduceti numele produsului: ";
	cin >> name;
	srv.del_srv(name);
}

void Ui::empty_cart_ui() {
	srv.empty_cos_srv();
}

void Ui::modify_ui() {
	string name, type, producer;
	int price;

	cout << "Introduceti numele produsului: \n";
	cin >> name;
	cout << "Introduceti tipul produsului: \n";
	cin >> type;
	cout << "Introduceti pretul produsului: \n";
	cin >> price;
	cout << "Introduceti producatorul produsului: \n";
	cin >> producer;

	srv.modify_srv(name, type, price, producer);
}

void Ui::search_ui() {
	string name;
	cout << "Introduceti numele produsului: \n";
	cin >> name;

	Product p = srv.search_srv(name);
	cout << "Name: " << p.get_name() << " || " << "Type: " << p.get_type() << " || " <<
		"Price: " << p.get_price() << " || " << "Producer: " << p.get_producer() << "\n";
}

void Ui::filter_ui() {
	std::map <int, Product> m;
	int pret = 0, choice;
	string filtru = "\0";
	cout << "1.Dupa pret \n";
	cout << "2.Dupa tip \n";
	cout << "3.Dupa producator \n";
	cout << "Filtrul ales: ";

	cin >> choice;
	switch (choice){
	case 1:
		cout << "Pretul: ";
		cin >> pret;
		break;
	case 2:
		cout << "Tip: ";
		cin >> filtru;
		break;
	case 3:
		cout << "Producator: ";
		cin >> filtru;
		break;

	default:
		cout << "Comanda invalida\n";
		break;
	}

	m = srv.filter_srv(choice, filtru, pret);

	for (int i = 0; i < m.size(); i++)
		cout << "Name: " << m[i].get_name() << " || " << "Type: " << m[i].get_type() << " || " <<
		"Price: " << m[i].get_price() << " || " << "Producer: " << m[i].get_producer() << "\n";
}

void Ui::sort_ui() {
	vector <Product> list;
	int choice;
	string filtru = "\0";
	cout << "1.Dupa nume \n";
	cout << "2.Dupa pret \n";
	cout << "3.Dupa nume+tip \n";
	cout << "Criteriul ales: ";

	cin >> choice;
	if (choice == 1 or choice == 2)
		list = srv.sort_srv(choice);
	else
		list = srv.sort2_srv();

	for (const Product& p : list)
		cout << "Name: " << p.get_name() << " || " << "Type: " << p.get_type() << " || " <<
		"Price: " << p.get_price() << " || " << "Producer: " << p.get_producer() << "\n";
}

void Ui::print_all_ui(){
	//vector <Product> product_list;
	for (const Product& p : get_produse())
		cout << "Name: " << p.get_name() << " || " << "Type: " << p.get_type() << " || " <<
		"Price: " << p.get_price() << " || " << "Producer: " << p.get_producer() << "\n";
}

void Ui::show_cart_ui() {
	//vector <Product> product_list;
	for (const Product& p : get_produse_cart())
		cout << "Name: " << p.get_name() << " || " << "Type: " << p.get_type() << " || " <<
		"Price: " << p.get_price() << " || " << "Producer: " << p.get_producer() << "\n";
}

void Ui::save_cart_ui() {
	string filename;
	cout << "Introduceti numele fisierului: ";
	cin >> filename;
	srv.save_cart_srv(filename);
}

void Ui::undo_ui() {
	srv.do_undo_srv();
}

const vector <Product> Ui::get_produse() {
	return srv.get_produse_srv();
}

const vector <Product> Ui::get_produse_cart() {
	return srv.get_produse_cos_srv();
}

void Ui::print_menu() {
	cout << "1.Add product\n";
	cout << "2.Delete product\n";
	cout << "3.Modify product\n";
	cout << "4.Search product\n";
	cout << "5.Filter products\n";
	cout << "6.Sort products\n";
	cout << "7.Save cart to file\n";
	cout << "8.Print all\n";
	cout << "9.Add product to cart\n";
	cout << "10.Empty cart\n";
	cout << "11.Show cart products\n";
	cout << "12.Add random products\n";
	cout << "13.Undo\n";
	cout << "14.Exit\n";
}

void Ui::menu_store() {
	int opt;
	//srv.load_from_file_srv();
	print_menu();
	cout << "Introduceti optiunea: ";
	cin >> opt;

	while (true) {
		try {
			switch (opt) {
			case 1:
				add_ui();
				break;
			case 2:
				del_ui();
				break;
			case 3:
				modify_ui();
				break;
			case 4:
				search_ui();
				break;
			case 5:
				filter_ui();
				break;
			case 6:
				sort_ui();
				break;
			case 7:
				save_cart_ui();
				break;
			case 8:
				print_all_ui();
				break;
			case 9:
				add_cart_ui();
				break;
			case 10:
				empty_cart_ui();
				break;
			case 11:
				show_cart_ui();
				break;
			case 12:
				add_random_cart_ui();
				break;
			case 13:
				undo_ui();
				break;
			case 14:
				break;
			}
			if (opt == 14)
				break;
		}
		catch (const ProductValidatorException& ex) {
			cout << ex << "\n";
		}
		catch (const RepoException& ex) {
			cout << ex << "\n";
		}
		print_menu();
		cout << "Introduceti optiunea: ";
		cin >> opt;
	}
	//srv.save_to_file_srv();
}