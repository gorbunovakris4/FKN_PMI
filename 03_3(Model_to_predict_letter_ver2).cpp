#include <array>
#include <iostream>
#include <random>
#include <string>
#include <unordered_map>

using namespace std;

class TModel {
private:
    static const size_t size = 1 << 8;
    using TFreqs = array<int, size>;
    unordered_map<string, TFreqs> model;
    size_t frameLength;

    static size_t nextChar(const TFreqs& freq) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        discrete_distribution<> distr(freq.begin(), freq.end());
        return distr(gen);
    }
public:
    void read(size_t _frameLength) {
        frameLength = _frameLength;
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

    string generate(size_t len) const {
        string result = "To be, or not to be: that is the question";
        string frame = result.substr(result.size() - frameLength);
        while (result.size() < len) {
            if (model.count(frame)) {
                result.push_back(nextChar(model.at(frame)));
                frame.erase(frame.begin());
                frame.push_back(result.back());
            }
            else {
                break;
            }
        }
        return result;
    }
};

int main() {
    TModel model;
    const int frameLength = 5;
    model.read(frameLength);
    const int len = 1000;
    string text = model.generate(len);
    cout << text << '\n';
}
