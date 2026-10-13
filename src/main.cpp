#include <iostream>
#include "Model.h"

using namespace std;

//test training logic 
int main() {
    Model model(2, 0.0);
    model.train("ababac");
    model.calcprob();
    return 0;
}