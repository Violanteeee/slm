#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Model.h"
#include "TextGenerator.h"

using namespace std;

int main() {
    try {
        ifstream file("moby_dick.txt");

        if (!file.is_open()) {
            throw runtime_error("Could not open moby_dick.txt");
        }
        stringstream buffer;
        buffer << file.rdbuf();
        string text = buffer.str();
        file.close();

        Model model(10, 0.01);
        model.train(text);
        model.calcprob();

        TextGenerator generator(model);
        cout << generator.generate(200) << '\n';

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}