#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <unordered_map>

using namespace std;

struct Student {
    string name;
    string surname;
};

bool operator<(const Student& A, const Student& B) {
    return tie(A.surname, A.name) < tie(B.surname, B.name);
}

bool operator==(const Student& A, const Student& B) {
    return tie(A.surname, A.name) == tie(B.surname, B.name);
}

class MyHash {
public:
    size_t operator()(const Student& s) const {
        std::hash <string> h;
        return h(s.name) ^ h(s.surname);
    }
};

namespace std {
    template <>
    struct hash<Student> {
        size_t operator()(const Student& s) const {
            std::hash <string> h;
            return h(s.name) ^ h(s.surname);
        }
    };
}

int main() {
    map<Student, double> rates;
    unordered_map<Student, double, MyHash> rates2;
    unordered_map<Student, double> rates3;
    
}
