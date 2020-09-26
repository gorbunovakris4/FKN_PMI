#include <array>
#include <iostream>
#include <random>
#include <string>
#include <unordered_map>

using namespace std;

using TFreqs = array<int, (1 << 8)>;
using TModel = unordered_map<string, TFreqs>;

void readModel(TModel& model, size_t frameLength) {
    char c;
    string curFrame;
    while (cin.get(c)) {
        if (curFrame.size() == frameLength) {
            model[curFrame][c]++;
        }
        curFrame.push_back(c);
        if (curFrame.size() > frameLength) {
            curFrame.erase(curFrame.begin());
        }
    }
}

size_t nextChar(const TFreqs& freq) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    discrete_distribution<> distr(freq.begin(), freq.end());
    return distr(gen);
}

string generate(const TModel& model, size_t len, size_t frameLength) {
    string result = "To be, or not to be: that is the question";
    string frame = result.substr(result.size() - frameLength);
    while (result.size() < len) {
        if (model.count(frame)) {
            result.push_back(nextChar(model.at(frame)));
            frame.erase(frame.begin());
            frame.push_back(result.back());
        } else {
            break;
        }
    }
    return result;
}

int main() {
    TModel model;
    const int frameLength = 3;
    readModel(model, frameLength);
    const int len = 1000;
    string text = generate(model, len, frameLength);
    cout << text << '\n';
}
