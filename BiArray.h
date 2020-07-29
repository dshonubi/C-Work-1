#include <string>
using namespace std;

class BiArray {

public:
	// GENERAL CLASS CONSTRUCTION/ASSIGNMENT

	// Zero-parameter constructor. Initialize size to 0 and capacity to
	// INITIALCAP. Also make it ready for the first element to be
	// inserted at the middle i.e. position INITIALCAP/2
	BiArray();

	// Value constructor. Sets capacity of internal array to either
	// LO_THRESHOLD*size, or INITIALCAP, whichever is bigger,
	// and initialize contents of BiArray to be same as
	// the input array arr.	Contents should be centered.
	// For example, if arr = [1,2], then using the notation in the pdf,
	// the internal array should be like [X X 1 2 X X].
	// size is the size of arr. If size is not actually the size of arr,
	// behaviour is undefined
	BiArray(int arr[], int size);

	~BiArray(); // destructor
	BiArray(const BiArray& other); // copy constructor
	BiArray(BiArray&& other); // move constructor
	BiArray& operator=(const BiArray& other); // copy assignment
	BiArray& operator=(BiArray&& other); // move assignment

	// GETTERS AND SETTERS

	// Sets v to the value of the i-th element (by reference).
	// Return false if i is out of bounds, true otherwise.
	// If i is out of bounds, v is not changed
	bool get(int i, int& v) const;

	// Sets the i-th element to v.
	// Return false if i is out of bounds, true otherwise.
	// If out of bounds, no changes are made
	bool set(int i, int v);

	// Overloaded operator[] to support array indexing-style access.
	// In honour of the great C++ tradition, bounds checking is not
	// required. Out of bounds behaviour is undefined
	int operator[](int i) const; // accessor
	int& operator[](int i); // mutator

	// STRUCTURAL MODIFIERS

	// You should also resize the data structure and recenter the
	// elements, if required, as described in the pdf

	// Insert v to the back
	void push_back(int v);

	// Remove last element and return true
	// If biarray is empty, return false and do nothing
	bool pop_back();

	// Insert v to the front
	void push_front(int v);

	// Remove first element and return true
	// If biarray is empty, return false and do nothing
	bool pop_front();

	// PRINTING AND SIZE INFORMATION

	// Returns the number of elements
	int getSize() const;

	// Returns the capacity, i.e. the size of the internal array,
	// part of which may not contain elements.
	// Shouldn't really need such a public interface but it helps me test
	// your resizing...
	int getCapacity() const;

	// Returns a string that lists all elements, in order, separated by
	// a space and with square brackets at the beginning and the end
	// e.g. "[4 2 13 5 77]"
	string print() const;

	// Prints the internal array including unoccupied spaces with an X,
	// following the notation described in the pdf file.
	// This is optional and for the benefit of your debugging only.
	string printAll() const;

	// COMPARISON OPERATORS

	// Non-member functions.
	// Returns a boolean value indicating whether the contents of the
	// two biarrays are equal. The order of the integers matters, while
	// the empty space does not matter. E.g. [1 2 3] is not equal to
	// [2 3 1], and (with the printAll() notation) [X X 1 2 3] is
	// equal to [1 2 3 X X].
	friend bool operator==(const BiArray& lhs, const BiArray& rhs);
	friend bool operator!=(const BiArray& lhs, const BiArray& rhs);

private:
	int _capacity;
	int _size;
	int _position;
	int* _internalArray{nullptr};
};

static constexpr int INITIALCAP = 5;
static constexpr int LO_THRESHOLD = 3;
static constexpr int HI_THRESHOLD = 5;
