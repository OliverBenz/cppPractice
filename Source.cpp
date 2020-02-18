#include <iostream>
#include <stdio.h>
#include <vector>
#include <cstdarg> // For variadic functions

using namespace std;


// ---------- Testing 1 ----------
// Basic bitwise manipulation
void bitWiseBasics(int a) {
	// Multiplication
	cout << "Double of " << a << " is: " << (a << 1) << endl;
	cout << "Four times " << a << " is: " << (a << 2) << endl;

	cout << endl;
	
	// Division
	cout << "Half of " << a << " is: " << (a >> 1) << endl;
	cout << "One fourth of " << a << " is: " << (a >> 2) << endl;

	cout << endl;

	// Odd or Even
	cout << "The number " << a << " is: " << (a & 1 ? "Odd" : "Even") << endl;

	cout << endl;

	// Size of int
	cout << "The number is " << sizeof(a) << " Bytes long" << endl;
}


// ---------- Testing 2 ----------
// Bitmap class
const uint8_t SW1_BM = 0b00000010;

// A custom 8 bit variable with
// Bit 1-4 used for data
// Bit 5-6 used for testing
// Bit 7 is a switch (On/Off)
// Bit 8 is a switch (On/Off)
// -----
// reg for resetting the union
union bitmap {
	struct {
		uint8_t data : 4;
		uint8_t test : 2;
		uint8_t sw1 : 1;
		uint8_t sw2 : 1;
	};

	uint8_t reg = 0x00;
};

void bitManipulation() {
	bitmap bm;
	bm.reg = 0xFF;

	cout << (bm.sw1 ? 1 : 0) << endl;

	bm.reg = ~bm.reg | SW1_BM;

	// Error -> why bm.sw1 = 0
	cout << (int)bm.reg << " - " << (bm.sw1 > 0 ? 1 : 0) << endl;
}


// ---------- Testing 3 ----------
// Namespace testing
// All sorting algorithms in own sort namespace
namespace ob {
	namespace sort {
		template <typename T>
		vector<T> bubble(vector<T> vals) {
			if (vals.size() == 1) return vals;

			for (size_t i = 0; i < vals.size(); i++)
				for (size_t j = 0; j < vals.size() - 1; j++)
					if (vals[j] > vals[i])
						swap(vals[i], vals[j]);
			return vals;
		}

		// Preferred bubble sort using pointers
		template <typename T>
		void bubble(vector<T>* vals) {
			if (vals->size() == 1) return;

			for (size_t i = 0; i < vals->size(); i++)
				for (size_t j = 0; j < vals->size() - 1; j++)
					if (vals->at(j) > vals->at(i))
						swap(vals->at(i), vals->at(j));
		}
	};
};

// Setup and print result
void sortTest() {
	vector<int> iTest = { 99, 10, 40, 5 };
	vector<float> fTest = { 99.5f, 10.11867f, 99.33f, 5.01f };

	iTest = ob::sort::bubble<int>(iTest);
	ob::sort::bubble<float>(&fTest);

	cout << "Integer Array at Memory Adress: " << &iTest << " -> ";
	for (auto& i : iTest) cout << i << "  ";
	cout << endl;

	cout << "Float Array at Memory Adress: " << &fTest << " -> ";
	for (auto& i : fTest) cout << i << "  ";
	cout << endl;

	iTest.clear(); fTest.clear();
}


// ---------- Testing 4 ----------
// Template testing
namespace ob {
	template <class T>
	class Pair {
	public:
		T first;
		T second;

		Pair(T f, T s) {
			first = f;
			second = s;
		}
	};
	template <typename T>
	ob::Pair<T> make_pair(T one, T two) {
		return ob::Pair<T>(one, two);
	}
};

void classTest() {
	// Pair
	ob::Pair<int>* pair = new ob::Pair<int>(1, 5);
	cout << pair->first << " - " << pair->second << endl;
	delete pair;

	vector<ob::Pair<float>> vPair;
	vPair.push_back(ob::make_pair<float>(2.666f, 12.999f));
	for (auto& i : vPair) cout << i.first << " - " << i.second << endl;
}


// ---------- Testing 5 ----------
// Variable parametercount functions
template <typename T>
T variaSum(int count, ...) {
	va_list numbers;
	va_start(numbers, count);

	T sum = 0;
	for (size_t i = 0; i < count; i++) {
		sum += va_arg(numbers, T);
	}

	va_end(numbers);
	return sum;
}

void variableParamsTest() {
	cout << "Sum of 2 INT: " << variaSum<int>(2, 2, 4) << endl;
	cout << "Sum of 4 DBL: " << variaSum<double>(4, 1.23, 1.56, 2.88, 5.89) << endl;
}


// ---------- Testing 6 ----------
// Macros
#define deb(v) cout << #v << ": " << v << endl
#define max(a, b) ((a > b) ? a : b)

#define even(v) (v & 1 ? false : true)
#define printBool(v) cout << #v << " is even: " << (even(v) ? "True" : "False") << endl;

void macros() {
	int x = 12, y = 13;
	deb(x);
	deb(max(x, y));
	printBool(y);
}



// ---------- Main ----------
int main(){
	cout << "---------- Test 1 ----------" << endl;
	bitWiseBasics(0b10001000);

	cout << endl << "---------- Test 2 ----------" << endl;
	bitManipulation();

	cout << endl << "---------- Test 3 ----------" << endl;
	sortTest();

	cout << endl << "---------- Test 4 ----------" << endl;
	classTest();

	cout << endl << "---------- Test 5 ----------" << endl;
	variableParamsTest();

	cout << endl << "---------- Test 6 ----------" << endl;
	macros();

	//cout << endl << "---------- Test 7 ----------" << endl;
	
	cout << endl;  return 0;
}