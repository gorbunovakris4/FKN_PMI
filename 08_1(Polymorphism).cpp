#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class Color {
    Green,
    Brown,
    Red
};

class Animal {
    string name;
    Color color;
public:
    Animal (const string& _name, Color _color): name(_name), color(_color) {

    }
    virtual string voice() const {
        return "Not implemented yet";
    }
    virtual ~Animal()
    {
        cout << "~Animal()\n";
    }
};

class Cat: public Animal {
public:
    Cat (const string& _name, Color _color): Animal(_name, _color) {
    }

    string voice() const override {
        return "Meow";
    }
    ~Cat() override
    {
        cout << "~Cat()\n";
    }
};

class Dog: public Animal {
    string breed;
public:
    Dog (const string& _name, Color _color, const string& _breed)
        : Animal(_name, _color)
        , breed(_breed) {

    }
    string voice() const override {
        return "Gav " + breed;
    }
    ~Dog() override
    {
        cout << "~Dog()\n";
    }};

int main() {
    Cat c("Kitty", Color::Green);
    Animal* a = &c;
    Animal& a1 = c;
    Animal a2 = c;
    cout << a->voice() << '\n';
    cout << a1.voice() << '\n';
    cout << a2.voice() << '\n';

    vector<Animal*> animals;
    animals.push_back(new Cat("Kitty", Color::Green));
    animals.push_back(new Dog("Polkan", Color::Brown, "ovcharka"));
    Dog* dog = dynamic_cast<Dog*>(animals.back());
    for (auto animal: animals) {
        cout << animal->voice() << '\n';
    }
    for (auto animal: animals) {
        delete animal;
    }
    //Cat c("Kitty", Color::Green);
    //Dog d("Polkan", Color::Brown, "ovcharka");

    //cout << c.voice() << '\n';
    //cout << d.voice() << '\n';

    return 0;
}
