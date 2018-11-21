#include "method.h"

Method::Method()
{
    total_prime_implicants_to_cover = 0;
}


void Method::create_table() {
    short tmp;

    B_number temp_num;

    for (int i = 0; i<input_values.size(); i++) {
        tmp = count_1s(input_values[i]);

        if (tmp + 1>table.size()) // check if more groups required
            table.resize(tmp + 1);


        temp_num = init_B_number(input_values[i], 0, false);
        temp_num.prime_implicants[temp_num.number] = 1; // 1 = X = location of X. Added

        table[tmp].push_back(temp_num);

    }
    qDebug() << "a";
}

void Method::create_p_group() {
    short tmp;

    B_number temp_num;

    unsigned temp_number, temp_dashes;

    for (int i = 0; i<table.size() - 1; i++) {
        for (int j = 0; j<table[i].size(); j++) {
            for (int k = 0; k<table[i + 1].size(); k++) {
                temp_number = table[i][j].number & table[i + 1][k].number;

                temp_dashes = table[i][j].number ^ table[i + 1][k].number;

                if (count_1s(temp_dashes) == 1) {
                    table[i][j].used = true;

                    table[i + 1][k].used = true;


                    tmp = count_1s(temp_number);


                    if (tmp + 1>p_group.size())
                        p_group.resize(tmp + 1);


                    temp_num = init_B_number(temp_number, temp_dashes, false);
                    temp_num.prime_implicants[table[i][j].number] = 1;
                    temp_num.prime_implicants[table[i + 1][k].number] = 1;

                    p_group[tmp].push_back(temp_num);

                }
            }
        }
    }
    qDebug() << "b";
}
void Method::create_final_group() {
    short tmp;

    B_number temp_num;

    unsigned temp_number, temp_dashes;

    for (int i = 0; i<p_group.size() - 1; i++) {
        for (int j = 0; j<p_group[i].size(); j++) {
            for (int k = 0; k<p_group[i + 1].size(); k++) {

                if (p_group[i][j].dashes == p_group[i + 1][k].dashes) {
                    temp_number = p_group[i][j].number & p_group[i + 1][k].number;

                    temp_dashes = p_group[i][j].number ^ p_group[i + 1][k].number;

                    if (count_1s(temp_dashes) == 1)
                    {
                        temp_dashes ^= p_group[i][j].dashes;


                        p_group[i][j].used = true;

                        p_group[i + 1][k].used = true;


                        tmp = count_1s(temp_number);


                        if (tmp + 1>final_group.size())
                            final_group.resize(tmp + 1);


                        temp_num = init_B_number(temp_number, temp_dashes, true);

                        for (int z = 0; z < p_group[i][j].prime_implicants.size(); z++) {
                            if (p_group[i][j].prime_implicants[z] == 1)
                                temp_num.prime_implicants[z] = 1;
                            if (p_group[i + 1][k].prime_implicants[z] == 1)
                                temp_num.prime_implicants[z] = 1;
                        }
                        final_group[tmp].push_back(temp_num);

                    }
                }
            }
        }
    }
    qDebug()<<"c";
}



unsigned Method::count_1s(unsigned number) {
    short bit = 0;

    int count = 0;

    while (number>0) {
        bit = number % 2;

        number >>= 1;

        if (bit) {
            count++;

        }
    }
    return count;

}

/* initialize a B_number variable - like a constructor */

Method::B_number Method::init_B_number(unsigned n, int d, bool u) {
    B_number num;

    num.number = n;

    num.dashes = d;

    num.used = u;

    num.prime_implicants.resize(max_terms_count); // Added
    for (int i = 0; i < num.prime_implicants.size(); i++) {
        num.prime_implicants[i] = 0;
    }

    return num;

}


void Method::finalMinimize() {
    /*

    for prime implicants 0 to max_terms_count except not required to process
        find count of X in the column
        if count = 1 then
            select this term as essential
            find the prime implicants taken by it
            for all the taken implicants, flag them as not required to process
    next
    */



    int *prime_implicants = new int[max_terms_count]; // = { 0 }; // initially non are selected, all required to be processed


    int i, j, k, l;
    int countX = 0;
    int count_1_term_index;
    int *temp_flags = new int[max_terms_count] ; //= { 0 };

    // initialize prime_implicants
    for(i=0;i<max_terms_count;i++) {
        prime_implicants[i] = 0;
    }

    // find in which location there is X
    for (j = 0; j < result_terms.size(); j++) {
        for (i = 0; i < max_terms_count; i++) {
            if (result_terms[j].prime_implicants[i] == 1)
                temp_flags[i] = 1;
        }
    }

    //find in how many locations there is X
    for (i = 0; i < max_terms_count; i++) {
        if (temp_flags[i] == 0)
            prime_implicants[i] = 1; //flag as no need to process
        total_prime_implicants_to_cover += temp_flags[i];
    }

    for (i = 0; i < max_terms_count; i++) {
        if (prime_implicants[i] == 1) {
            continue; // skip if not required to process
        }

        countX = 0;
        count_1_term_index = -1; // means term not selected
        for (j = 0; j < result_terms.size(); j++) {
            countX += result_terms[j].prime_implicants[i];
            if (result_terms[j].prime_implicants[i] == 1)  // this technique requied to select the term which gives count of X = 1
                count_1_term_index = j;
        }
        if (countX != 1) { // since above technique cannot see total count
            count_1_term_index = -1;
        }
        if (count_1_term_index != -1) {

            for (l = 0; l < result_terms[count_1_term_index].prime_implicants.size(); l++) {
                if (result_terms[count_1_term_index].prime_implicants[l] == 1) {
                    prime_implicants[l] = 1; //flag all taken implicants as not requird to process
                }
                for (j = 0; j < result_terms.size(); j++) {
                    if (j == count_1_term_index)
                        continue;
                    if (result_terms[count_1_term_index].prime_implicants[l] == 1) {
                        result_terms[j].prime_implicants[l] = 0; // remove X covered by selected term
                    }
                }
            }
            // finalize selection of term
            B_number temp = result_terms[count_1_term_index];
            final_terms.push_back(temp);
            result_terms.erase(result_terms.begin() + count_1_term_index );
        }
    }

    /*
    untill prime implicants remains
    find term causing column with least X's
    select that term
    remove affected implicants
    loop

    */
    //return;

    int loop_safety = 0;
    int term;
    while (is_prime_implicants_remaining(prime_implicants)) {
        if (result_terms.size() == 0)
            break;
        term = get_term_with_least_x(result_terms);
        if (term == -1) // means no X left
            break;
        flag_implicants_covered_by(result_terms[term], result_terms,prime_implicants);

        B_number temp = result_terms[term];
        final_terms.push_back(temp);
        result_terms.erase(result_terms.begin() + term);

        loop_safety++;
        if (loop_safety > max_terms_count)
            break;
    }
    delete prime_implicants;
    delete temp_flags;
}


bool Method::is_prime_implicants_remaining(int *p) {
    int sum = 0;
    for (int i = 0; i < max_terms_count; i++) {
        sum += p[i];
    }
    if (sum == total_prime_implicants_to_cover)
        return false;
    return true;
}

int Method::get_term_with_least_x(vector<B_number> &rt) {
    int i, j, k;
    int *flags = new int[max_terms_count];
    for (i = 0; i < max_terms_count; i++) {
        flags[i] = 0; // initial value
        for (j = 0; j < rt.size(); j++) {
            flags[i] += rt[j].prime_implicants[i];
        }
    }



    int min_col = -1 ;
    int min_col_val = -1 ;
    for (i = 0; i < max_terms_count; i++) {
        if (flags[i] > 0) {
            min_col = i;
            min_col_val = flags[i];
            continue;
        }
    }

    if (min_col == -1)
        return -1;
    for (i = 0; i < max_terms_count; i++) {
        if (flags[i] == 0)
            continue;
        if (min_col_val > flags[i])
        {
            min_col_val = flags[i];
            min_col = i;
        }
    }

    int term_select = -1;
    int term_max = 0;
    int term_sum = 0;
    for (i = 0; i < rt.size(); i++) {
        if (rt[i].prime_implicants[min_col] == 1) {
            term_sum = 0;
            for(j=0;j<max_terms_count;j++) {
                term_sum += rt[i].prime_implicants[j];
            }

            if (term_max < term_sum) {
                term_select = i;
                term_max = term_sum;
            }
        }
    }
    return term_select;
}

void Method::flag_implicants_covered_by(B_number b, vector<B_number> &rt,int *p) {
    int i, j;
    for (j = 0; j < rt.size(); j++) {
        for (i = 0; i < b.prime_implicants.size(); i++) {
            if (b.prime_implicants[i] == 1) {
                p[i] = 1;
                rt[j].prime_implicants[i] = 0; // erase X as it is covered by selected terms's Xs
            }
        }
    }
}
