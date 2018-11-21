#ifndef METHOD_H
#define METHOD_H

#include "input.h"

class Output;

class Method : public Input
{
public:
    Method();
    unsigned count_1s(unsigned number);

    struct B_number {
        unsigned number;
        unsigned dashes;
        bool used;
        vector<int> prime_implicants;
        };
    B_number init_B_number(unsigned n, int d, bool u);
    void create_table();
    void create_p_group();
    void create_final_group();
    void finalMinimize();
    bool is_prime_implicants_remaining(int *p);
    int get_term_with_least_x(vector<B_number> &rt);
    void flag_implicants_covered_by(B_number b, vector<B_number> &rt,int *p);

protected:
    vector<vector<B_number> > table;
    vector<vector<B_number> > p_group;
    vector<vector<B_number> > final_group;
    vector<B_number> result_terms;
    vector<B_number> printed_numbers;
    vector<B_number> final_terms;
    int total_prime_implicants_to_cover;


};

#endif // METHOD_H
