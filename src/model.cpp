#include "Model.h"

//Constructor
Model::Model(int k, double alpha) {
    this->k = k;
    this->alpha = alpha;
}

//Analyze text to get frequencies of k-grams and characters that follow.
void Model::train(const string& text) {
    if (text.size() <= static_cast<size_t>(k)) {
        throw invalid_argument(
            "Training text has to contain more than k characters." //defensive
        );
    }

    for (size_t i = 0; i + static_cast<size_t>(k) < text.size(); i++) {
        string kgram = text.substr(i, k);
        frequencies[kgram]++;

        char next = text[i + k];
        transitions[kgram][next]++;
    }

    //Consider final k-gram
    string last_kgram = text.substr(text.size() - k, k);
    frequencies[last_kgram]++;

    //get alphabet of training text
    for (char letter : text) {
        alphabet.insert(letter);
    }
}

//Get probability of possible next character.
void Model::calcprob() {
    for (const auto& entry : frequencies) {
        const string& kgram = entry.first;

        auto trans_it = transitions.find(kgram);

        int totalfreq = 0;
        if (trans_it != transitions.end()) {
            for (const auto& transition : trans_it->second) {
                totalfreq += transition.second;
            }
        }

        double denom = totalfreq + alpha * alphabet.size();

        if (denom == 0) {
            continue;
        }

        for (char c : alphabet) {
            int count = 0;

            if (trans_it != transitions.end()) {
                auto char_it = trans_it->second.find(c);
                if (char_it != trans_it->second.end()) {
                    count = char_it->second;
                }
            }

            double num = count + alpha;
            probabilities[kgram][c] = num / denom;
        }
    }
}

//functions to get the private variables

int Model::get_k() const {
    return k;
}

const map<string, int>& Model::get_frequencies() const {
    return frequencies;
}

const map<string, map<char, double>>&
Model::get_probabilities() const {
    return probabilities;
}

double Model::get_alpha() const {
    return alpha;
}

const set<char>& Model::get_alphabet() const {
    return alphabet;
}