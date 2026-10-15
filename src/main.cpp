#include "Model.h"
#include "TextGenerator.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

//readfile
string readf(const string& filename) {
            ifstream file(filename);
            if (!file) {
                throw runtime_error("File not found: " + filename);
            }
            stringstream buffer;
            buffer << file.rdbuf();
            return buffer.str();
}


int main(int argc, char* argv[]) {
    try {
        vector<string> args(argv + 1, argv + argc); //put args in vector
        double alpha = 0.0;
        if (!args.empty() && args[0] == "-a") { //bad alpha
           if (args.size() < 2) {
              throw invalid_argument("Missing alpha value after -a.");
           }
        size_t pos;
        alpha = stod(args[1], &pos);
        if (pos != args[1].size()) { //bad alpha
            throw invalid_argument("alpha has to be a number.");
        }
        if (!isfinite(alpha)) { //bad alpha
            throw invalid_argument("alpha has to be finite.");
        }
        args.erase(args.begin(), args.begin() + 2);
        }
        if (alpha < 0.0) { //bad alpha
            throw invalid_argument("alpha has to be non-negative.");
        }
        if (args.size() != 3) { //wrong number of args
            throw invalid_argument("usage: slm [-a alpha] k file length");
        }
        size_t pos;
        int k = stoi(args[0], &pos);
        if (pos != args[0].size()) { //bad k
            throw invalid_argument("k has to be an integer.");
        }       
        if (k <= 0) { //bad k
            throw invalid_argument("k has to be a positive integer.");
        }
        int length = stoi(args[2], &pos);
        if (pos != args[2].size()) { //bad length
            throw invalid_argument("length has to be an integer.");
        }       
        if (length <= 0 || length < k) { //bad length
            throw invalid_argument("length has to be positive and at least k.");
        }
        //open training text and train the model
        string trainingtext = args[1];
        string text = readf(trainingtext);
        Model model(k, alpha);
        model.train(text);
        model.calcprob();
        //create the text generator and print output
        TextGenerator artificialidiot(model);
        string output = artificialidiot.generate(length);
        cout << output << '\n';
    }
    //error handling
    catch (const exception& e) {
        cerr << "slm: " << e.what() << '\n';
        return 1;
    }

    return 0;
}