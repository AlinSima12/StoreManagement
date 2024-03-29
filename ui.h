#pragma once
#include "srv_store.h"

class Ui {
private:
	Service srv;

public:
	Ui(Service my_srv) : srv{ my_srv }{}
	/// <summary>
	/// add produs
	/// </summary>
	void add_ui();

	void add_cart_ui();

	void add_random_cart_ui();

	/// <summary>
	/// sterge produs
	/// </summary>
	void del_ui();

	void empty_cart_ui();

	/// <summary>
	/// modifica produs
	/// </summary>
	/// <returns></returns>
	void modify_ui();

	void search_ui();

	void filter_ui();

	void sort_ui();

	void sort2_ui();

	/// <summary>
	/// ruleaza meniul
	/// </summary>
	void menu_store();

	/// <summary>
	/// afiseaza toate produsele din lista
	/// </summary>
	void print_all_ui();

	void show_cart_ui();

	/// <summary>
	/// Returneaza toate produsele
	/// </summary>
	const vector <Product> get_produse();

	const vector <Product> get_produse_cart();

	/// <summary>
	/// printeaza meniul
	/// </summary>
	void print_menu();

	void save_cart_ui();

	void undo_ui();

};