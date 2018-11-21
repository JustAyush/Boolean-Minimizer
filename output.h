#ifndef OUTPUT_H
#define OUTPUT_H

#include "method.h"

#include <iostream>
#include <vector>
#include <string>
#include <QString>
#include <math.h>
#include <QDebug>
#include <sstream>

using namespace std;

class Output : public Method
{
public:
    Output();
    void print_table(); //print the table
    void print_p_group(); //print it
    void print_final_group(); //print final table with -'s and unused terms
    bool is_printed(B_number n);
    void print_p_binary(unsigned n, unsigned d);
    void print_binary(unsigned number);
    void print_Canonical_SOP(unsigned number);
    void print_ans_SOP(unsigned n, unsigned d);
    void print_ans_POS(unsigned n, unsigned d);
    void ShowCanonical();
    void ShowSOP();
    void ShowPOS();
    void Reset();
    stringstream MainOutput;
    stringstream Cano;
    stringstream SOP;
    stringstream POS;
    static int to_print;
    static int for_print;
    static int b;
};

#endif // OUTPUT_H
