#include <iostream>
#include <stdio.h>

using namespace std;


// ---------- Testing 1 ----------
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

	cout << "The number is " << sizeof(a) << " Bytes long" << endl;
}



// ---------- Testing 2 ----------
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

#include <vector>



// ---------- Testing 3 ----------
// All sorting algorithms in own sort namespace
namespace obSort {
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

// Setup and print result
void sortTest() {
	vector<int> iTest = { 99, 10, 40, 5 };
	vector<float> fTest = { 99.5f, 10.11867f, 99.33f, 5.01f };

	iTest = obSort::bubble(iTest);
	obSort::bubble(&fTest);

	cout << "Integer Array at Memory Adress: " << &iTest << " -> ";
	for (auto& i : iTest) cout << i << "  ";
	cout << endl;

	cout << "Float Array at Memory Adress: " << &fTest << " -> ";
	for (auto& i : fTest) cout << i << "  ";
	cout << endl;
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


	cout << endl;  return 0;
}