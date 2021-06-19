#include <vector>
#include <array>
#include <numeric>

class Type{
	int data{};

	constexpr action() const { return data + 3; }
	constexpr actionOne() const { return data + 6; }
};

constexpr std::vector<int> getVector(){
	std::vector<int> vec {1, 2, 3, 4, 5, 6};

	if(vec[2] == 3)
		vec.push_back(7);

	return vec;
}

constexpr std::size_t getVectorSize(){
	std::vector<int> vec = getVector();
	return vec.size();
}

constexpr int getVectorSum(){
	std::vector<int> vec = getVector();
	return std::accumulate(vec.begin(), vec.end(), 0);
}

template <std::size_t Size>
constexpr std::array<int, Size> getValues(){
	std::vector<int> vec = getVector();
	std::array<int, Size> result{};
	std::copy(vec.begin(), vec.end(), result.begin());
	return result;
}

int main(){
	// Cannot have constexpr vector -> Get a constexpr array.
	constexpr std::size_t size = getVectorSize();
	constexpr values<size> = getValues();

	// If evaluated at compile time -> Only if OR else will be compiled!
	Type object;
	if constexpr (sizeof(long) > 4)
		object.action();
	else
		object.actionOne();


	return 0;
}