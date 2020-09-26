#include <iostream>
#include <string>
#include <utility>
#include <vector>

class C {
private:
    static inline int counter = 0;
public:
    int x;

    C() {
        ++counter;
        x = counter;
        std::cout << "C() " << x << "\n";
    }

    C(const C& /*other*/) {
        ++counter;
        x = counter;
        std::cout << "C(const C&) " << x << "\n";
    }

    C(C&& /*other*/){
        ++counter;
        x = counter;
        std::cout << "C(C&&) " << x << "\n";
    }

    C& operator=(const C& other) {
        std::cout << "operator=(const C&) " << other.x << ' ' << x << "\n";
        return *this;
    }



    ~C(){
        std::cout << "~C() " << x << "\n";
    }
};

//int C::counter = 0;

void f(const C& item) {
    std::cout << "f(C&) " << item.x << '\n';
}

void f(C&& item){
    std::cout << "f(C&&) " << item.x << '\n';
    item.x = -1;
}

int main() {
    /*
    C x1;
    C x2(x1);  //copy ctor
    C x3 = x1; //copy ctor
    x3 = x1;   //operator =

    f(x1);
    f(C());
    C x5;
    f(std::move(x5));

    C x6 = C(C());  //copy elision in C++17
    C y = std::move(x6);

    std::cout << "finish\n";
    */

    C* ptr1 = new C();
    C* ptr2 = new C[100];
    delete ptr1;
    delete[] ptr2;

    return 0;
}
