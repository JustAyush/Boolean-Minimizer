#include "input.h"

Input::Input()
{

}

bool Input::getinput(int a,string &user_input)
{

    MIN_BITS = a;
    vector<string> separated = split(user_input,' ');
     max_terms_count = pow(2,MIN_BITS);
    input_values.resize(separated.size());
    for(int i=0;i<separated.size();i++) {
       input_values[i] = atoi(separated[i].c_str());
       if(input_values[i]>max_terms_count){
            return false;
            break;
       }

    }

    return true;
}


vector<string> Input::split(const string &text, char sep) {
    vector<string> tokens;
    size_t start = 0, end = 0;

    while ((end = text.find(sep, start)) != string::npos) {
        if (end != start) {
          tokens.push_back(text.substr(start, end - start));
        }
        start = end + 1;
    }
    if (end != start) {
       tokens.push_back(text.substr(start));
    }
    return tokens;
}

