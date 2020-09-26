#include <iostream>
#include <utility>

template<typename T>
struct Node {
    T elem;
    Node* prev = nullptr;
    Node* next = nullptr;
};

template <typename T>
class List {
private:
    Node<T>* begin = nullptr;
    Node<T>* last = nullptr;
public:

    ~List() {
        while (!empty()) {
            pop_back();
        }
    }

    bool empty() const {
        return last == nullptr;
    }

    void pop_back() {
        Node<T>* node = last->prev;
        if (!node){
            begin = nullptr;
        } else {
            node->next = nullptr;
        }

        delete last;
        last = node;
    }

    void push_back(const T& val) {
        Node<T>* node = new Node<T>;
        node->elem = val;
        node->prev = last;
        if (last) {
            last->next = node;
            last = node;
        } else {
            begin = last = node;
        }
    }

    void push_back(T&& val) {
        Node<T>* node = new Node<T>;
        node->elem = std::move(val);
        node->prev = last;
        if (last) {
            last->next = node;
            last = node;
        } else {
            begin = last = node;
        }
    }

    void print_all() const {
        for (auto node = begin; node != nullptr; node=node->next){
            std::cout << node->elem << '\n';
        }
    }
};

int main() {
    List<int> l;
    l.push_back(3);
    l.push_back(5);
    l.print_all();
    l.pop_back();
    l.print_all();
    return 0;
}
