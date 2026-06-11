struct Foo {
    // Single parameter constructor, can be used as an implicit conversion.
    // Such a constructor is called "converting constructor".
    Foo(int x) {}
};
struct Faz {
    // Also a converting constructor.
    Faz(Foo foo) {}
};

// The parameter is of type Foo, not of type int, so it looks like
// we have to pass a Foo.
void bar(Foo foo) {};

struct Foo_ {
     Foo_(int x) {}
};

struct Faz_ {
    //need to pass Foo because explicit conversion is now required
    explicit Faz_(Foo_ foo) {}
};

int main() {
    // However, the converting constructor allows us to pass an int.
    bar(42);
    // Also allowed thanks to the converting constructor.
    Foo foo = 42;
    // Error! This would require two conversions (int -> Foo -> Faz).
    //Faz faz = 42;
}

