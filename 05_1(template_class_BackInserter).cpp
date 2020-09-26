#include <deque>
#include <iostream>
#include <vector>

template <typename It, typename Pred>
bool any_of(It first, It last, Pred f) {
    for (It cur = first; cur != last; ++cur) {
        if (f(*cur)) {
            return true;
        }
    }
    return false;
}

template<typename Cont>
class BackInsert {
    Cont& cont;
public:
    BackInsert(Cont& _cont) : cont(_cont) {}

    BackInsert& operator++(int) {
        return *this;
    }

    BackInsert& operator*() {
        return *this;
    }

    template <typename T>
    BackInsert& operator=(const T& value) {
        cont.push_back(value);
        return *this;
    }
};

template<typename T>
BackInsert<T> BackInserter(T& cont) {
    return BackInsert<T>(cont);
}




template <typename In, typename Out>
Out Copy(In first, In last, Out dest) {
    while (first != last) {
        *dest++ = *first++;
    }
    return dest;
}

int main() {
    std::vector<int> v = {3, 14, 15, 92, 6};
    std::deque<int> d;

    Copy(v.begin(), v.end(), BackInserter(d));

    for (int elem: d)
        std::cout << elem << '\n';
}
