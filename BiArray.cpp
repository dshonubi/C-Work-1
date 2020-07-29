#include "BiArray.h"
#include <iostream>
using namespace std;
// default constructor
BiArray::BiArray() {
	_size = 0;
	_capacity = INITIALCAP;
	_position = INITIALCAP / 2;
	_internalArray = new int[_capacity];
}

// value constructor
BiArray::BiArray(int arr[], int size) {
	if (INITIALCAP > LO_THRESHOLD* size) {
		_internalArray = new int[INITIALCAP];
		_size = size;
		_capacity = INITIALCAP;
		_position = INITIALCAP / 2;
	}
	else {
		_internalArray = new int[LO_THRESHOLD * size];
		_position = size;
		_capacity = LO_THRESHOLD * size;
		_size = size;
	}
	for (int i = 0; i < size; i++) {
		_internalArray[_position + i] = arr[i];
	}
}

// destructor
BiArray::~BiArray() {
	delete[] _internalArray;
	_internalArray = nullptr;
}

// copy constructor
BiArray::BiArray(const BiArray& other) {
	_size = other._size;
	_capacity = other._capacity;
	_position = other._position;
	_internalArray = new int[_capacity];

	for (int i = 0; i < _capacity; i++) {
		_internalArray[i] = other._internalArray[i];
	}
}
// move constructor
BiArray::BiArray(BiArray&& other) {
	_size = other._size;
	_capacity = other._capacity;
	_position = other._position;
	_internalArray = other._internalArray;

	other._size = 0;
	other._capacity = 0;
	other._position = 0;
	other._internalArray = nullptr;
}

// copy assignment
BiArray& BiArray::operator=(const BiArray& other) {
	if (this != &other) {
		if (_capacity != other._capacity) {
			delete[] _internalArray;
			_internalArray = new int[other._capacity];
			_capacity = other._capacity;
			_position = other._position;
			_size = other._size;
		}
		for (int i = 0; i < _capacity; i++)
			_internalArray[i] = other._internalArray[i];
	}
	return *this;
}

// move assignment
BiArray& BiArray::operator=(BiArray&& other) {
	if (this == &other)
		return *this;

	int* tmp_internalArray = _internalArray;
	_internalArray = other._internalArray;
	other._internalArray = tmp_internalArray;

	int tmp_size = _size;
	_size = other._size;
	other._size = tmp_size;

	int tmp_capacity = _capacity;
	_capacity = other._capacity;
	other._capacity = tmp_capacity;

	int tmp_position = _position;
	_position = other._position;
	other._position = tmp_position;

	return *this;
}

bool BiArray::get(int i, int& v) const {
	if (i >= _size || i < 0)
		return false;

	v = _internalArray[_position + i];
	return true;
}

bool BiArray::set(int i, int v) {
	if (i >= _size || i < 0)   //is it meant to check for whole array doesn't work if I use the capacity
		return false;

	_internalArray[_position + i] = v;
	return true;
}

int BiArray::operator[](int i) const {
	return _internalArray[_position + i];
}

int& BiArray::operator[](int i) {
	return _internalArray[_position + i];
}

void BiArray::push_back(int v) {
	if ((_position + _size) + 1 > _capacity) {

		//creates temporary array and old position for use when transferring data to new array
		int old_position = 0;
		int* tmp_internalArray = _internalArray;
		_internalArray = new int[LO_THRESHOLD * _size];
		old_position = _position;
		_position = _size;
		_capacity = LO_THRESHOLD * _size;

		for (int i = 0; i < _size; i++) {
			_internalArray[_position + i] = tmp_internalArray[old_position + i];
		}
		_internalArray[_position + _size] = v;
		++_size;
		delete[] tmp_internalArray;
		tmp_internalArray = nullptr;
	}
	else {
		_internalArray[_position + _size] = v;
		++_size;
	}
}

bool BiArray::pop_back() {
	if (_size == 0) {
		return false;
	}

	//creates temporary array and old position for use when transferring data to new array
	_size = _size - 1;
	int* tmp_internalArray = _internalArray;

	if ((_size * 5) < _capacity) {
		int old_position = _position;
		if (INITIALCAP > LO_THRESHOLD* _size) {
			_internalArray = new int[INITIALCAP];
			_size = _size;
			_capacity = INITIALCAP;
			_position = INITIALCAP / 2;
		}
		else {
			_internalArray = new int[LO_THRESHOLD * _size];
			_position = _size;
			_capacity = LO_THRESHOLD * _size;
		}
		for (int i = 0; i < _size; i++) {
			_internalArray[_position + i] = tmp_internalArray[old_position + i];
		}
	}
	else {
		_internalArray = new int[_capacity];
		for (int i = 0; i < _size; i++) {
			_internalArray[_position + i] = tmp_internalArray[_position + i];
		}
	}
	delete[] tmp_internalArray;
	tmp_internalArray = nullptr;
	return true;
}

void BiArray::push_front(int v) {

	//calculates the space remaining in the array if any, and uses that to calculate where the new value will be placed
	int valuesAfterSize = _capacity - (_position + _size);
	int checkSpace = _capacity - _size - valuesAfterSize - 1;
	if (checkSpace <= 0) {

		//creates temporary array and old position for use when transferring data to new array
		int old_position = 0;
		int* tmp_internalArray = _internalArray;
		_internalArray = new int[LO_THRESHOLD * _size];
		old_position = _position;
		_position = _size;
		_capacity = LO_THRESHOLD * _size;

		for (int i = 0; i < _size; i++) {
			_internalArray[_position + i] = tmp_internalArray[old_position + i];
		}
		_internalArray[_position - 1] = v;
		_position = _position - 1;
		++_size;
		delete[] tmp_internalArray;
		tmp_internalArray = nullptr;
	}
	else {
		_internalArray[_position - 1] = v;
		_position = _position - 1;
		++_size;
	}
}

bool BiArray::pop_front() {
	if (_size == 0) {
		return false;
	}
	//creates temporary array and old position for use when transferring data to new array
	_size = _size - 1;
	int* tmp_internalArray = _internalArray;

	if ((_size * 5) < _capacity) {
		int old_position = _position = _position + 1;
		if (INITIALCAP > LO_THRESHOLD* _size) {
			_internalArray = new int[INITIALCAP];
			_size = _size;
			_capacity = INITIALCAP;
			_position = INITIALCAP / 2;
		}
		else {
			_internalArray = new int[LO_THRESHOLD * _size];
			_position = _size;
			_capacity = LO_THRESHOLD * _size;
		}
		for (int i = 0; i < _size; i++) {
			_internalArray[_position + i] = tmp_internalArray[old_position + i];
		}
	}
	else {
		_internalArray = new int[_capacity];
		_position = _position + 1;
		for (int i = 0; i < _size; i++) {
			_internalArray[_position + i] = tmp_internalArray[_position + i];
		}
	}
	delete[] tmp_internalArray;
	tmp_internalArray = nullptr;
	return true;
}

int BiArray::getSize() const {
	return _size;
}

int BiArray::getCapacity() const {
	return _capacity;
}

string BiArray::print() const {
	string elements = "";
	for (int i = 0; i < _size; i++) {
		int j = _internalArray[_position + i];
		string a = to_string(j);
		if (i + 1 != _size) {
			elements += a + " ";
		}
		else {
			elements += a;
		}
	}
	string print = "[" + elements + "]";
	cout << print << endl;
	return print;
}

string BiArray::printAll() const {
	string elements = "";
	for (int i = 0; i < _capacity; i++) {
		int j = _internalArray[i];
		string a = to_string(j);
		if ((i >= _position) && (i <= (_position + _size))) {
			elements = elements + a + " ";
		}
		else if (i + 1 != _capacity) {
			elements = elements + "X" + " ";
		}
		else {
			elements = elements + "X";
		}
	}
	string print = "[" + elements + "\b" + "]";
	return print;
}

bool operator==(const BiArray& lhs, const BiArray& rhs) {//what does he want us to do
	if (lhs.print() == rhs.print()) {
		return true;
	}
	else {
		return false;
	}
}

bool operator!=(const BiArray& lhs, const BiArray& rhs) {
	return !(lhs == rhs);
}


