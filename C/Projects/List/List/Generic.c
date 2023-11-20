#include "Generic.h"
#include <stdio.h>
#include <stdlib.h>

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

	if(content == NULL){
		printf("content is NULL");
	}
	printf("%d, %c, %d\n", content->a, content->b, content->c);
}