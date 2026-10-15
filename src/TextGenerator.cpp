#include "TextGenerator.h"
#include <random>
#include <vector>
#include <stdexcept>

//refer to Model
TextGenerator::TextGenerator(const Model& model) : model(model) {
}
//chose starting kgram with std distribution
string TextGenerator::choose_kgram() const {
    vector<string> kgrams;
    vector<double> weights;

    const auto& freq = model.get_frequencies();

    for (const auto& entry : freq) {
        kgrams.push_back(entry.first);
        weights.push_back(entry.second);
    }

    if (kgrams.empty()) {
        throw std::runtime_error(
            "Can't choose starting k-gram: the model has no k-grams."
        );
    }

    static std::mt19937 rng(std::random_device{}());
    std::discrete_distribution<> dist(weights.begin(), weights.end());

    int index = dist(rng);
    return kgrams[index];
}
//text generation
string TextGenerator::generate(int length) {
    if (length <= 0 || length < model.get_k()) {
        throw std::invalid_argument(
            "Output text length needs to be positive and at least k." //defensive
        );
    }

    string output = choose_kgram();
    string current = output;

    while (output.length() < static_cast<size_t>(length)) {
        const auto& probabilities = model.get_probabilities();
        auto it = probabilities.find(current);

        if (it == probabilities.end() && model.get_alpha() == 0) {
            break;
        }

        vector<char> characters;
        vector<double> weights;

        if (it != probabilities.end()) {
            //Known k-gram: use calculated probabilities
            for (const auto& entry : it->second) {
                characters.push_back(entry.first);
                weights.push_back(entry.second);
            }
        } else {
            //new k-gram: use uniform distribution
            for (char c : model.get_alphabet()) {
                characters.push_back(c);
                weights.push_back(1.0);
            }
        }

        static std::mt19937 rng(std::random_device{}());
        std::discrete_distribution<> dist(
            weights.begin(), weights.end()
        );

        int index = dist(rng);
        char next = characters[index];

        output += next;
        current = current.substr(1) + next;
    }

    return output;
}
