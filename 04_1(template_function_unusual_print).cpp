#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

template <typename Iter1, typename Iter2>
Iter2 copy(Iter1 first, Iter1 last, Iter2 dest) {
    while (first != last) {
        *dest++ = *first++;
    }
    return dest;
}

int main() {
    
    vector v = { 3, 14, 15 };
    ::copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
    cout << '\n';

    return 0;
}
