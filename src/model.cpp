#include "Model.h"

// Constructor
Model::Model(int k, double alpha) {
    this->k = k;
    this->alpha = alpha;
}

// Analyze the text to get frequencies of k-grams
// and the characters that follow them.
void Model::train(const string& text) {
    // There must be at least k+1 characters to have
    // a k-gram followed by a character.
    if (text.size() <= static_cast<size_t>(k)) {
        throw invalid_argument(
            "Training text must contain more than k characters."
        );
    }

    for (size_t i = 0; i + static_cast<size_t>(k) < text.size(); i++) {
        string kgram = text.substr(i, k);
        frequencies[kgram]++;

        char next = text[i + k];
        transitions[kgram][next]++;
    }

    // Count the final k-gram too, even though it has no
    // following character.
    string last_kgram = text.substr(text.size() - k, k);
    frequencies[last_kgram]++;

    // Build the alphabet from the training text.
    for (char letter : text) {
        alphabet.insert(letter);
    }
}

// Calculate the probability of each possible next character.
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