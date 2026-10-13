#include "Model.h"
#include <iostream>

//constructor
Model::Model(int k, double alpha) {
    this->k = k;
    this->alpha = alpha;

};
//analyze the text to get frequencies of k-grams and characters that come after
void Model::train(const string& text) {
    for (int i = 0; i < text.size() - k + 1; i++) {
        string kgram = text.substr(i, k);
        frequencies[kgram]++;
        if (i + k < text.size()) {
           char next = text[i+k];
           transitions[kgram][next]++;
        }
    }
    //test the logic print frequencies etc
    for (const auto& entry : frequencies) {
        cout << entry.first << ": " << entry.second << endl;
    }

}