#include <iostream>
#include <algorithm>
#include <vector>

#include <numeric>

using namespace std;

struct DivisibleBy
{
	const int d;
	DivisibleBy(int n) : d(n) {}
	bool operator()(int n) const { return n % d == 0; }
};

int main() {
	//vector<int> v{1,3,5,7,9};
	vector<int> v{2,4,6,8};
	//vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9};
	if (std::all_of(v.cbegin(), v.cend(), [](int i) { return i % 2 == 0; }))
		std::cout << "All numbers are even\n";

	if (std::none_of(v.cbegin(), v.cend(), [](int i) { return !(i % 2 == 0); }))
		std::cout << "No numbers are odd\n";

	if (std::any_of(v.cbegin(), v.cend(), DivisibleBy(7)))
		std::cout << "At least one number is divisible by 7\n";

	// increment every elements 
	std::for_each(v.begin(), v.end(), [](int& n) { n++; });

	// multiply 3 element
	std::for_each_n(v.begin(), 3, [](auto& n) { n *= 2; });
	
}
/*
* The algorithms library defines functions for a variety of purposes (e.g. searching, sorting, counting, manipulating) that operate on ranges of elements. 
Note that a range is defined as [first, last) where last refers to the element past the last element to inspect or modify.
*/

/* all_of - none_of - any_of
*  check if the container have all - none - at least one element that respect the condition
*/

/* for_each
*  applies the given function to every element dereferenced by the iterator in the given range
*  the function ca be normal or lambda
*/

/* for_each_n
*  like for_each applies the given function to the first n elelemt 
*/

/*
* a lot mre can be found in the c++ reference
*/