#ifndef TEXTGENERATOR_H
#define TEXTGENERATOR_H

#include "Model.h"
#include <string>

using namespace std;
class TextGenerator {
    private:
        const Model& model;

    public:
        TextGenerator(const Model& model);
        string choose_kgram() const;
        string generate(int length);
};

#endif
