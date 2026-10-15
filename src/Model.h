#ifndef MODEL_H
#define MODEL_H
#include <map>
#include <string>
#include <set>

using namespace std;

class Model {

private:
    int k;
    double alpha;
    set<char> alphabet;
    map<string, int> frequencies;
    map<string, map<char, int>> transitions;
    map<string, map<char, double>> probabilities;

public:
    Model(int k, double alpha);
    void train(const string& text);
    void calcprob();
    
    // get the private variables (will be used in TextGenerator)
    int get_k() const;
    const map<string, int>& get_frequencies() const;
    const map<string, map<char, double>>& get_probabilities() const;
    double get_alpha() const;
    const set<char>& get_alphabet() const;



};

#endif