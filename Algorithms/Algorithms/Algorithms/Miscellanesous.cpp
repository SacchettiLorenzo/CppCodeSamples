#include <iostream>

using namespace std;
#define length 8

long Fact(int n);
long Fact_rec(int n);
void Div(int n, int m, int& q, int& r);
double CosRoot(double a, double b, double eps);
int MCD(int n, int m);
double exponential(double x, double epsilon);
bool Twins(int* array);
bool Twins_better(int* array);
bool Twins_best(int* array);
void sort(int* array, int i, int j);
bool somma17(int* array);
bool somma17_best(int* array);

int main()
{
    int array[length] = { 7,4,1,8,2,1,6,5 };
    cout << "somma17_best:" << somma17_best(array) << endl;;
    
    /*std::cout << "Fact: " << Fact(10) << endl;
    std::cout << "Fact recursive:" << Fact_rec(10) << endl;

    int q,r;
    Div(100, 7, q, r);
    cout << "q = " << q << ",r = " << r << endl;
    cout << "CosRoot: " << CosRoot(15, 12, 1) << endl;;
    cout << "MCD:" << MCD(7, 3) << endl;
    cout << "exponential " << exponential(4, 1) << endl;*/
}

/**
 * @brief return the factorial of n
 * 
 * @param n 
 * @return long 
 * @pre n>=0
 * @post return n!
 */
long Fact(int n) {
    long fact = 1;
    int i = 2;
    while (i <= n)
    {
        fact = fact * i;
        i = i + 1;
    }
    return fact;
}

long Fact_rec(int n) {
    long fact = 1;
    if (n < 2) {
        return 1;
    }
    else {
        return Fact_rec(n - 1)* n;
    }
}

/**
 * @brief performa a division with iterative subtraction
 * 
 * @param n dividend
 * @param m divider
 * @param q quotient
 * @param r remainder
 * @pre n>=0, m != 0
 * @post q is the quotient and r is the remainder of n/m
 */
void Div(int n, int m, int&q, int& r) {
    q = 0;
    r = n;
    while (r >= m) {
        r = r - m;
        q++;
    }
}

/**
 * @brief this funtion perform cos(alpha/2) = +/-sqrt((1-cos(alpha))/2)
 * 
 * @param a 
 * @param b 
 * @param eps tolerance level
 * @return double 
 * @pre cos(a) ann cos(b) have the different sign
 * @post return x in [a,b] with cos(x) = 0
 */
double CosRoot(double a, double b, double eps) {
    double delta = fabs(a - b);
    double c;
    double p;
    while (delta >= eps) {
        c = (a + b) / 2;
        p = cos(a) * cos(c);
        if (p > 0) {
            a = c;
        }
        else if (p < 0) {
            b = c;
        }
        else {
            a = b = c;
        }
        delta = fabs(a - b);
    }
    return c;

}


/**
 * @brief return the MDC of n and m
 * 
 * @param n 
 * @param m 
 * @return int 
 * @pre n != 0 and m != 0
 * @post return MCD
 */
int MCD(int n , int m) {
    int a = n;
    int b = m;
    int r = 0;
    while (b > 0)
    {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

/**
 * @brief calculate e^x
 * 
 * @param x 
 * @param epsilon max error
 * @return double 
 * @pre epsilon >= 0
 * @post return e^x with error less then epsilon
 */
double exponential(double x, double epsilon) {
    double s = 1;
    double t = 1;
    double s_old = 10;
    int k = 1;
    while (abs(s - s_old) > epsilon) {
        s_old = s;
        t = t * x / k;  // t = x^k/k!
        s = s + t;      // s = sum_(j = 0)^k x^j/j!
        k++;
    }
    return s;
}

/**
 * @brief perform x*n
 * 
 * @param x 
 * @param n 
 * @return int 
 * @pre n positive integer
 * @post return x*n
 * @invariant x*n = z+x*y
 */
int Molt(int x, int n) {
    int z = 0;
    int y = n;
    while (y > 0)
    {
        z = z + x; 
        y = y - 1;
    }
    return z;
}

/**
 * @brief perform m*n
 * 
 * @param m 
 * @param n 
 * @return int
 * @pre n and m positive integer
 * @post return n*m
 * @invariant n*m = z+a*b 
 */
int MoltRussa(int m, int n) {
    int a = n;
    int b = m;
    int z = 0;
    while (a > 0)
    {
        if (a % 2 == 1) {
            z = z + b;
        }
        a = a / 2;
        b = b + b;
    }
    return z;
}

/**
 * @brief 
 * 
 * @param array 
 * @return true 
 * @return false 
 * @pre
 * @post 
 * @invariant  
 */
bool Twins(int* array) {
    for (size_t i = 0; i < length; i++)
    {
        for (size_t j = 0; j < length; j++)
        {
            if (i != j && array[i] == array[j]) {
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief 
 * 
 * @param array 
 * @return true 
 * @return false 
 * @pre
 * @post 
 * @invariant  
 */
bool Twins_better(int* array) {
    for (size_t i = 0; i < length; i++)
    {
        for (size_t j = i+1; j < length; j++)
        {
            if (array[i] == array[j]) {
                return true;
            }
        }
    }
    return false;
}

//merge sort
void sort(int* array, int i, int j) {
    int middle = (i + j) / 2;
    if (i < j) {
        sort(array, i, middle);
        sort(array, middle + 1, j);
    }
    int placeholder = 0;
    int left = i; //i
    int right = middle + 1; //j
    int tmp[length];

    while (left <= middle && right <= j)
    {
        if (array[left] < array[right]) {
            tmp[placeholder] = array[left];
            left++;
        }
        else {
            tmp[placeholder] = array[right];
            right++;
        }
        placeholder++;
    }

    while (left <= middle)
    {
        tmp[placeholder] = array[left];
        left++;
        placeholder++;
    }

    while (right <= j)
    {
        tmp[placeholder] = array[right];
        right++;
        placeholder++;
    }


    for (size_t k = i; k <= j; k++)
    {
        array[k] = tmp[k - i];
    }

}

/**
 * @brief 
 * 
 * @param array 
 * @return true 
 * @return false 
 * @pre
 * @post 
 * @invariant  
 */
bool Twins_best(int* array) {
    sort(array, 0, length - 1);
    for (size_t i = 0; i < length; i++)
    {
        if (array[i] == array[i + 1]) {
            return true;
        }
    }
    return false;
}

/**
 * @brief 
 * 
 * @param array 
 * @return true 
 * @return false 
 * @pre
 * @post 
 * @invariant 
 */
bool somma17(int* array) {
    for (size_t i = 0; i < length; i++)
    {
        for (size_t j = i+1; i < length; j++)
        {
            if (array[i] + array[j] == 17) {
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief 
 * 
 * @param array 
 * @return true 
 * @return false 
 * @pre
 * @post 
 * @invariant 
 */
bool somma17_best(int* array) {
    bool C[18];
    for (size_t i = 0; i < 17; i++)
    {
        C[i] = false;
    }
    for (size_t i = 0; i < length; i++)
    {
        if (array[i] < 17) {
            C[array[i]] = true;
        }
    }

    int i = 0;
    int j = 17;

    while (i< j && !(C[i] && C[j]))
    {
        i++; j--;
    }
    return i < j;

}