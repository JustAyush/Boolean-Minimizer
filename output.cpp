#include "output.h"
#include "method.h"



Output::Output()
{

}


void Output::print_table() {
    MainOutput << endl << "COMPUTING:" << endl;

    for (int i = 0; i<table.size(); i++) {
        MainOutput << i;


        for (int j = 0; j<table[i].size(); j++) {
            MainOutput << "\tm" << table[i][j].number << "\t";

            print_binary(table[i][j].number);

            MainOutput << endl;

        }
        MainOutput << "\n-------------------------------------" << endl;

    }
}



void Output::print_p_group() {
    MainOutput << endl << "MID PROCESS COMPUTATION:" << endl;

    for (int i = 0; i<p_group.size(); i++) {
        MainOutput << i;

        for (int j = 0; j<p_group[i].size(); j++) {
            MainOutput << "\t\t";

            print_p_binary(p_group[i][j].number, p_group[i][j].dashes);

            MainOutput << endl;

        }
        MainOutput << "\n-------------------------------------" << endl;

    }
}


void Output::print_final_group() {
    MainOutput << endl << "FINAL:\n-------------------------------------" << endl;

    int i, j;

    for (i = 0; i<final_group.size(); i++) {
        for (j = 0; j<final_group[i].size(); j++) {
            if (!is_printed(final_group[i][j])) {

                print_p_binary(final_group[i][j].number,final_group[i][j].dashes);

                MainOutput << endl;

                printed_numbers.push_back(final_group[i][j]);

                result_terms.push_back(final_group[i][j]);
            }
        }
    }
    for (i = 0; i<p_group.size(); i++) {
        for (j = 0; j<p_group[i].size(); j++) {
            if (!p_group[i][j].used) {
                print_p_binary(p_group[i][j].number,p_group[i][j].dashes);
                result_terms.push_back(p_group[i][j]);
                MainOutput << endl;

            }
        }

    }
    for (i = 0; i<table.size(); i++) {
        for (j = 0; j<table[i].size(); j++) {
            if (!table[i][j].used) {
                print_p_binary(table[i][j].number,table[i][j].dashes);
                result_terms.push_back(table[i][j]);
                MainOutput << endl;

            }
        }
    }
    MainOutput << "-------------------------------------" << endl;
    MainOutput << "Result Terms:\n";
    for (i = 0; i < result_terms.size(); i++) {
        MainOutput << 'm' <<result_terms[i].number << "    ";
        for (j = 0; j < result_terms[i].prime_implicants.size(); j++) {
            if (result_terms[i].prime_implicants[j] == 1)
                MainOutput << " X ";
            else
                MainOutput << " -  ";
        }
        MainOutput << endl;
    }
}

/*used to avoid printing duplicates that can exist in the final table*/

bool Output::is_printed(B_number n) {
    for (int i = 0; i<printed_numbers.size(); i++)
        if (n.number ==printed_numbers[i].number && n.dashes ==printed_numbers[i].dashes)
            return true;

    return false;

}


void Output::print_p_binary(unsigned n, unsigned d) {
    unsigned *bits = new unsigned[MIN_BITS];

    int count = 0;

    while (n>0 || count<MIN_BITS) {
        if (!(d % 2))
            bits[count] = n % 2;

        else
            bits[count] = 2;

        n >>= 1;

        d >>= 1;

        count++;

    }
    for (int i = count - 1; i >= 0; i--) {
        if (bits[i] != 2)
            MainOutput << bits[i];

        else
            MainOutput << "-";

    }
    MainOutput << endl;

    delete bits;
}


/*get LSB, arrange it in array, the print array in reverse order so MSB is on
the left */

void Output::print_binary(unsigned number) {
    unsigned *bits = new unsigned[MIN_BITS];

    int count = 0;

    while (number>0 || count<MIN_BITS) {
        bits[count] = number % 2;

        number >>= 1;

        count++;

    }
    for (int i = count - 1; i >= 0; i--)
        MainOutput << bits[i];
    delete bits;
}

void Output::ShowCanonical()
{
    for(int i =0; i < input_values.size(); i++)
           print_Canonical_SOP(input_values[i]);

}
void Output::ShowSOP()
{
    for(int i = 0; i < final_terms.size(); i++)
       {
           print_ans_SOP(final_terms[i].number, final_terms[i].dashes);
       }
}
void Output::ShowPOS()
{
    for(int i = 0; i < final_terms.size(); i++)
       {
           print_ans_POS(final_terms[i].number, final_terms[i].dashes);
       }
}

int Output::for_print=0;
int Output::to_print=0;
int Output::b=0;

void Output::print_ans_SOP(unsigned n, unsigned d) {
    unsigned *bits = new unsigned[MIN_BITS];

    int count = 0;


    while (n>0 || count<MIN_BITS) {
        if (!(d % 2))
            bits[count] = n % 2;

        else
            bits[count] = 2;

        n >>= 1;

        d >>= 1;

        count++;

    }

    if(to_print > 0)
    {
        SOP << "+";
    }

    to_print += 1;

    for (int i = count - 1; i >= 0; i--) {
        if (bits[i] == 1)
            SOP << char(MIN_BITS-i+64);
        else if (bits[i] == 0)
            SOP << char(MIN_BITS-i+64)<<"'";
        else
            SOP<< "";

    }

    delete bits;
}



void Output::print_ans_POS(unsigned n, unsigned d) {
    unsigned *bits = new unsigned[MIN_BITS];

    int count = 0;

    int a = 0;

    while (n>0 || count<MIN_BITS) {
        if (!(d % 2))
            bits[count] = n % 2;

        else
            bits[count] = 2;

        n >>= 1;

        d >>= 1;

        count++;

    }

    if(for_print > 0)
    {
        POS << ".";
    }

    for_print += 1;

    POS << "(";

    for (int i = count - 1; i >= 0; i--) {

        if (bits[i] == 1){
            if(a>0)
            POS << "+";
            POS << char(MIN_BITS-i+64) << "'";
            a++;
        }
        else if (bits[i] == 0){
            if(a>0)
            POS << "+";
            POS << char(MIN_BITS-i+64);
            a++;
        }

        else
            POS<< "";


    }
    POS << ")";

    delete bits;
}


void Output::print_Canonical_SOP(unsigned number) {
    unsigned *bits = new unsigned[MIN_BITS];

    int count = 0;


    while (number>0 || count<MIN_BITS) {
        bits[count] = number % 2;

        number >>= 1;

        count++;

    }

    if(b>0)
        Cano << "+";
    b++;

    for (int i = count - 1; i >= 0; i--){
        if(bits[i] == 1)
            Cano << char(MIN_BITS-i+64);
        else
            Cano << char(MIN_BITS-i+64) << "'";
    }

    delete bits;
}

void Output::Reset() {
    input_values.clear();
    MIN_BITS=2;
    max_terms_count=4;
     table.clear();
     p_group.clear();
     final_group.clear();
     result_terms.clear();
     printed_numbers.clear();
     final_terms.clear();
    total_prime_implicants_to_cover=0;
    Cano.str(string());
    MainOutput.str(string());
    SOP.str(string());
    POS.str(string());
    to_print = 0;
    for_print = 0;
    b = 0;
}
