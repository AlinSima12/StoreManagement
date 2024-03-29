#include "produs.h"
#include <assert.h>

void test_get_and_set() {
	Product p("ciocolata", "aliment", 5, "Kinder");

	assert(p.get_name() == "ciocolata");
	assert(p.get_type() == "aliment");
	assert(p.get_price() == 5);
	assert(p.get_producer() == "Kinder");

	p.set_name("CIOCOLATA");
	p.set_type("ALIMENT");
	p.set_price(55);
	p.set_producer("KINDER");

	assert(p.get_name() == "CIOCOLATA");
	assert(p.get_type() == "ALIMENT");
	assert(p.get_price() == 55);
	assert(p.get_producer() == "KINDER");
}