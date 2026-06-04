#include <iostream>
#include <algorithm>
#include <vector>
#include <string>


#include <numeric>

using namespace std;

struct DivisibleBy
{
	const int d;
	DivisibleBy(int n) : d(n) {}
	bool operator()(int n) const { return n % d == 0; }
};

bool is_even(int i)
{
    return i % 2 == 0;
}

int main() {

/*
	vector<int> a{1,3,5,7,9};
	if (std::all_of(a.cbegin(), a.cend(), [](int i) { return i % 2 == 0; }))
	{
		std::cout << "All numbers are even\n";
	}
		
	vector<int> b{ 2,4,6,8 };
	if (std::none_of(b.cbegin(), b.cend(), [](int i) { return !(i % 2 == 0); }))
	{
		std::cout << "No numbers are odd\n";
	}

	vector<int> c{1, 2, 3, 4, 5, 6, 7, 8, 9};
	if (std::any_of(c.cbegin(), c.cend(), DivisibleBy(7)))
	{
		std::cout << "At least one number is divisible by 7\n";
	}

	vector<int> d{1,2,3,4};
	for (const int item_to_search :{3,5} ){
		if(std::find(d.begin(), d.end(),item_to_search) == d.end()){
			std::cout << "vector does not contains: " << item_to_search << std::endl;
		}else{
			std::cout << "vector contains: " << item_to_search << std::endl;
		}
	}

	vector<int> e{1,2,3,4};
	if(std::find_if(e.begin(), e.end(),is_even) == e.end()){
		std::cout << "vector does not contains event numbers"<< std::endl;
	}else{
		std::cout << "vector contains even numbers" << std::endl;
	}

	vector<int> f{1,3,5,4};
	//vector<int> f{6,4};
	if(std::find_if_not(f.begin(), f.end(),is_even) == f.end()){
		std::cout << "vector contains only even numbers" << std::endl;
	}else{
		std::cout << "vector contais number that are not even"<< std::endl;
	}

	const auto g= {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4};
    for (auto const& x : {std::array{1, 2, 3}, {4, 5, 6}})
    {
		//first, last, first_to_search, last_to_search, comparator
        auto iter = std::find_end(g.begin(), g.end(), x.begin(), x.end()); 
        if(iter == g.end())
		{
			std::cout << "Sequence not found\n";
		}else{
			std::cout << "Sequence found at: " << std::distance(g.begin(), iter) << std::endl;
		}	
    }

	for (auto const& x : {std::array{1, 2, 3}, {4, 5, 6}})
    {
		//first, last, first_to_search, last_to_search, comparator
        auto iter = std::find_first_of(g.begin(), g.end(), x.begin(), x.end()); 
        if(iter == g.end())
		{
			std::cout << "Sequence not found\n";
		}else{
			std::cout << "Sequence found at: " << std::distance(g.begin(), iter) << std::endl;
		}		
    }
	

	// increment every elements 
	std::for_each(v.begin(), v.end(), [](int& n) { n++; });

	// multiply 3 element
	std::for_each_n(v.begin(), 3, [](auto& n) { n *= 2; });

	std::stable_sort(v.begin(), v.end());

	auto it = std::lower_bound(v.begin(), v.end(), 4);

	std::next_permutation(v.begin(), v.end());
	

	std::string str_a = "abcd";
	std::string str_b = "abce";
	auto mismach_res = std::mismatch(str_a.begin(), str_a.end(), str_b.begin(), str_b.end());
	std::cout << *mismach_res.first << std::endl;
	std::cout << *mismach_res.second << std::endl;

	
	const auto h= {1,1,2,2,2,2,3,3,5,6};
	auto search_n_res = std::search_n(h.begin(), h.end(), 2,3);
	if(search_n_res != h.end()){
		std::cout << "found sequence at position: " << std::distance(h.begin(), search_n_res) << std::endl;
	}
	*/

	std::string str_c = "hello";
	std::transform(str_c.cbegin(), str_c.cend(), str_c.begin(), ::toupper);
	std:: cout << str_c << std::endl;
	vector<int> transform_res(5);
	std::transform(str_c.cbegin(), str_c.cend(), transform_res.begin(),[](const char c){return (int)c;} );
	std::for_each(transform_res.begin(), transform_res.end(), [](int& n) { std:: cout << n << " "; });
	std::cout << std::endl;
	

}
/*
* The algorithms library defines functions for a variety of purposes (e.g. searching, sorting, counting, manipulating) that operate on ranges of elements.
Note that a range is defined as [first, last) where last refers to the element past the last element to inspect or modify.
*/

/* all_of - none_of - any_of
*  check if the container have all - none - at least one element that respect the condition
*/

/* find
*  return the first iterator that satisfy the equality condition, or the last iteratori instead
*/

/* find_if
*  return the first iterator that satisfy the provided condition (function that check a specific condition), or the last iteratori instead
*/

/* find_if
*  return the first iterator that does not satisfy the provided condition (function that check a specific condition), or the last iteratori instead
*/

/* find_end
*  return the last iterator to the beginning of the specified sequence, it is possible to specify a comparator function different from the equa comparator
*/

/* find_first_of
*  return the iterator to the first element that matches one of the element in the list containing the element to search
*/

/* for_each
*  applies the given function to every element dereferenced by the iterator in the given range
*  the function can be normal or lambda
*/

/* for_each_n
*  like for_each applies the given function to the first n elelemt
*/

/* mismatch
* return a std::pair containing the iterators to the first elements in both lists that mismatch
*/

/* search_n
* return an iterator to the first element of the sequence
*/

/* transform
* applies a function to a range of elements, storing results in a destination range (same or different from the original range)
*/

/*
* a lot more can be found in the c++ reference
*/