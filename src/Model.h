#include <map>
#include <string>

using namespace std;

class Model {

private:
    int k;
    double alpha;
    map<string, int>frequencies;
    map<string, map<char, int>> transitions;
public:
    Model(int k, double alpha);
    void train(const string& text);
    



};