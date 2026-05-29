#include <iostream>
#include <cassert>
#include <type_traits>

const int& getRef(const int* p) { return *p; }
auto getRefFwdBad(const int* p) { return getRef(p); } // the return type is auto at compile time

int main()
{
struct A { double x; };
const A* a;
const A* aa;

[[maybe_unused]]
decltype(a->x) y;
[[maybe_unused]]
decltype(aa->x) yy;
//static_assert(std::is_same_v<y,yy>);

// is_same_v checks if two types are the same
// static_assert(std::is_same_v<y,yy>); wont compile because y and yy are variables containing types

static_assert(std::is_same_v<decltype(a->x),decltype(aa->x)>);
// static_assert(std::is_same_v<decltype(a->x),decltype(aa->x)>); compile because it is comparing two types

[[maybe_unused]]
decltype((a->x)) z = y; // this is a const double& because of the parenthesized expression
//static_assert(std::is_same_v<decltype((a->x)),decltype(a->x)>);
//static_assert(std::is_same_v<decltype((a->x)),decltype(a->x)>); will fail because decltype((a->x)) and decltype(a->x) are different types

static_assert(std::is_same_v<decltype(getRef), const int&(const int*)>);

static_assert(std::is_same_v<decltype(getRefFwdBad), int(const int*)>,
    "Just returning auto isn't perfect forwarding.");
decltype(auto) getRefFwdGood(const int* p) { return getRef(p); }
static_assert(std::is_same_v<decltype(getRefFwdGood), const int&(const int*)>,
    "Returning decltype(auto) perfectly forwards the return type.");
}

/*  Inspect the delered type of an entity or the type and value category of an expression
*   it is used to define the type of a variable or an expression at compile time without its evaluation.
[[maybe_unused]] used to silence warnings at comile time
*/

