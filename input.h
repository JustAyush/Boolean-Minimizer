#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <vector>
#include <string>
#include <QString>
#include <math.h>
#include <QDebug>

using namespace std;

class Input
{
protected:
    vector<unsigned> input_values;
    int MIN_BITS;
    int max_terms_count;


public:
    Input();
    bool getinput(int a, string &user_input);
    vector<string> split(const string &text, char sep);

};

#endif // INPUT_H
