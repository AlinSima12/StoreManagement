#pragma once
#define CAPACITATE 2
template<typename TElement>
class Iterator;

template<typename TElement>

class MyList {
private:
	// reprezentare
	TElement* elems;

	int capacitate;

	int lungime;

	// pentru redimensionare
	void redim();
public:
	// constructor default
	MyList();

	// constructor de copiere
	MyList(const MyList& ot);

	// operator de asignare =
	MyList& operator=(const MyList& ot);

	//deconstructor
	~MyList();

	// pastram numele functiilor ca si cele din stl
	// functie de adaugare
	void push_back(TElement e);

	// functie de stergere
	// erase
	// get element de pe o pozitie
	TElement& get(int poz);

	// set element pe o pozitie
	void set(TElement elem, int poz);

	// get-er pentru dimensiune
	int size();

	//iterator
	friend class Iterator<TElement>;

	Iterator<TElement> begin();
	Iterator<TElement> end();

};

template<typename TElement>

class Iterator {
private:
	const MyList<TElement>& vec;

	int poz = 0;

public:
	Iterator(const MyList<TElement>& v) noexcept;

	Iterator(const MyList<TElement>& v, int poz) noexcept;

	bool valid() const;

	TElement& element() const;

	void next();

	TElement& operator*();

	Iterator& operator++();

	bool operator==(const Iterator& ot) noexcept;

	bool operator!=(const Iterator& ot) noexcept;
};

// puteam si intr un program cpp separat sa facem asta

// pentru MyList..................................

template<typename TElement>

MyList<TElement>::MyList() {
	this->elems = new TElement[CAPACITATE];
	this->lungime = 0;
	this->capacitate = CAPACITATE;
}

template<typename TElement>

MyList<TElement>::MyList(const MyList& ot) {

	// alocam spatiu
	this->elems = new TElement[ot.capacitate];

	// copiem elmentele
	for (int i = 0; i < ot.lungime; i++) {
		this->elems[i] = ot.elems[i];
	}

	this->capacitate = ot.capacitate;
	this->lungime = ot.lungime;
}

template<typename TElement>

MyList<TElement>& MyList<TElement>::operator=(const MyList& ot) {

	//daca v1=v1
	if (this == &ot) {
		return *this;
	}

	delete[] this->elems;

	this->elems = new TElement[ot.capacitate];
	for (int i = 0; i < ot.capacitate; i++) {
		this->elems[i] = ot.elems[i];
	}

	this->lungime = ot.lungime;
	this->capacitate = ot.capacitate;
	return *this;
}

template<typename TElement>

void MyList<TElement>::redim() {
	int newcapacity = this->capacitate * 2;
	TElement* newElems = new TElement[newcapacity];

	for (int i = 0; i < this->capacitate; i++) {
		newElems[i] = this->elems[i];
	}

	delete[] this->elems;
	this->elems = newElems;
	this->capacitate = newcapacity;
}

template<typename TElement>

MyList<TElement>::~MyList() {
	delete[] this->elems;
}

// adaugare
template<typename TElement>

void MyList<TElement>::push_back(TElement e) {
	if (this->lungime == this->capacitate)
		redim();

	this->elems[this->lungime] = e;
	this->lungime++;
}

template<typename TElement>

TElement& MyList<TElement>::get(int poz) {
	return this->elems[poz];
}

template<typename TElement>

int MyList<TElement>::size() {
	return this->lungime;
}

template<typename TElement>

Iterator<TElement> MyList<TElement>::begin() {
	return Iterator<TElement>(*this);
}
template<typename TElement>

Iterator<TElement> MyList<TElement>::end() {
	return Iterator<TElement>(*this, this->lungime);
}

// pentru iterator...............................
template<typename TElement>

Iterator<TElement>::Iterator(const MyList<TElement>& v) noexcept : vec{ v } {};

template<typename TElement>

Iterator<TElement>::Iterator(const MyList<TElement>& v, int poz) noexcept : vec{ v }, poz{ poz } {};

template<typename TElement>

bool Iterator<TElement>::valid() const {
	return this->poz < this->vec.lungime;
}

template<typename TElement>

TElement& Iterator<TElement>::element() const {
	return this->vec.elems[this->poz];
}

template<typename TElement>

void Iterator<TElement>::next() {
	this->poz++;
}

// operatori

template<typename TElement>

TElement& Iterator<TElement>::operator*() {
	return this->element();
}

template<typename TElement>

Iterator<TElement>& Iterator<TElement>::operator++() {
	this->next();
	return *this;
}

template<typename TElement>

bool Iterator<TElement>:: operator==(const Iterator<TElement>& ot) noexcept {
	return this->poz == ot.poz;
}

template<typename TElement>

bool Iterator<TElement>:: operator!=(const Iterator<TElement>& ot) noexcept {
	return this->poz != ot.poz;
}
