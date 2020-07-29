#include <iostream>
#include "BiArray.h"
using namespace std;

int main() {

	BiArray a; // zero con
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);
	a.push_front(5);
	a.push_front(6);
	a.push_front(7);
	a.push_front(8);
	a.push_front(9);
	a.push_front(10);
	cout << a[3] << endl;
	cout << a.print() << endl;
	int v=-1;
	a.get(3,v);
	cout << v << endl;

	int arr[10]{10,9,8,7,6,5,1,2,3,4};
	BiArray b{arr,10}; // value con
	cout << "a==b? " << (a==b) << endl;

	BiArray bb = b; // copy con
	cout << bb.print() << endl;

	b[3] = 77;
	b.set(4,66);
	cout << b.print() << endl;
	cout << "a==b? " << (a==b) << endl;

	BiArray c;
	c = std::move(b); // move asg
	cout << c.print() << endl;

	a.pop_back();
	cout << a.print() << endl;
	a.pop_front();
	cout << a.print() << endl;
	cout << a.getSize() << endl;
	cout << a.getCapacity() << endl;

}
