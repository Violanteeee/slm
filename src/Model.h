#include <map>
#include <string>
#include <set>

using namespace std;

class Model {

private:
    int k;
    double alpha;
    set<char> alphabet;
    map<string, int>frequencies;
    map<string, map<char, int>> transitions;
    map<string, map<char, double>> probabilities;

public:
    Model(int k, double alpha);
    void train(const string& text);
    void calcprob();
    



};