typedef enum { false, true } bool;

struct Generic {
	int a;
	char b;
	int c;
};

typedef  struct Generic Generic;

/*check if the first argument is greater than the second one */
/*must be modified for each implementation*/
bool isGreaterThen(Generic* first, Generic* second) {
	if (first->c > second->c)
	{
		return true;
	}
	else {
		return false;
	}
}

/*check if each member of the first argument are equals to the respective ones in the second argument*/
/*must be modified for each implementation*/
bool isEqualTo(Generic* first, Generic* second) {
	if (
		first->a == second->a &&
		first->b == second->b &&
		first->c == second->c
		)return true;
	else return false;
}

void printAllParams(Generic* content) {
	printf("%d, %c, %d\n", content->a, content->b, content->c);
}