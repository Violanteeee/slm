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
    //alphabet generation 
    for (int i = 0; i < text.size(); i++) {
        char letter = text[i];
        alphabet.insert(letter);
    }   
    //test the logic print frequencies etc
    for (const auto& entry : frequencies) {
        cout << entry.first << ": " << entry.second << endl;
    }
}

void Model::calcprob() {
    for (const auto& entry : frequencies) {
        string kgram = entry.first;

        int totalfreq = 0;
        for (const auto& transition : transitions[kgram]) {
            totalfreq += transition.second;
        }

        for (char c : alphabet) {
            double num = transitions[kgram][c] + alpha;
            double denom = totalfreq + alpha * alphabet.size();
            double prob = num / denom;
            if (denom == 0) {
                continue;
            }
            probabilities[kgram][c] = prob;
        }

        // TEST: print the probabilities for this k-gram
        cout << "K-gram: " << kgram << endl;
        for (const auto& entry : probabilities[kgram]) {
            cout << "  " << entry.first << ": "
                 << entry.second << endl;
        }
    }
}
