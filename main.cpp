
#include "ui.h"

void test_all() {
	test_get_and_set();
	test_add_srv();
	test_del_repo();
	test_del_srv();
	test_modify_repo();
	test_modify_srv();
	test_search_repo();
	test_search_srv();
	test_filter_srv();
	test_sort_srv();
	test_sort2_srv();
	test_validate_product();
	test_add_cos();
	test_del_cos();
	test_add_cos_srv();
	test_empty_cos_srv();
	test_add_random_cos_srv();
	test_add_repo();
	test_undo_2();
	cout << "*--ALL-TESTS-PASSED--*\n";
}

int main() {
	test_all();
	FileRepository repo{ "produse.txt"};
	//RepositoryLab repo{0};
	Cos cos;
	Service srv{ repo , cos};
	Ui ui{ srv };
	ui.menu_store();
}