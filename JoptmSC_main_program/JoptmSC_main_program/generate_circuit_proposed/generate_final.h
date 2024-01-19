#pragma once
#ifndef GENERATE_FINAL_H
#define GENERATE_FINAL_H

#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <set>
#include <cmath>
#include <cstring>

#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

//double bm1_target_func(double x);

typedef vector <int> one_die_vector_int;
typedef vector <one_die_vector_int> two_die_vector_int;
typedef vector <two_die_vector_int> three_die_vector_int;

typedef vector <char> one_die_vector_char;
typedef vector <one_die_vector_char> two_die_vector_char;

typedef vector <uint64_t> one_die_vector_bit;
typedef vector <one_die_vector_bit> two_die_vector_bit;

typedef vector <double> one_die_vector_double;
typedef vector <one_die_vector_double> two_die_vector_double;

void write_verilog_circuit(two_die_vector_int configuration_all, two_die_vector_int circuit_information, int pds, int degree, two_die_vector_int BS_all, double error_bound, int bm_id_under_test, two_die_vector_int permutation_bit_width, two_die_vector_int LFSR_set,int bit_width);
void write_verilog_testbench(two_die_vector_int configuration_all, two_die_vector_int circuit_information, int pds, int degree, two_die_vector_int BS_all, double error_bound, int bm_id_under_test, two_die_vector_int permutation_bit_width, two_die_vector_int LFSR_set,two_die_vector_int LFSR_output_1,int bit_width);
two_die_vector_int read_ADP(int bm_id_under_test);
two_die_vector_double read_error(int bm_id_under_test);
two_die_vector_int read_confuration(int bm_id_under_test, double approx_error_bound_ratio);
two_die_vector_int obtain_LFSR_polynomial(int bit_width);
two_die_vector_int obtain_output_LFSR(two_die_vector_int LFSR_set,int bit_width,int choose_LFSR);
two_die_vector_char read_library();
two_die_vector_int read_verilog(int bm_id_under_test,double approx_error_bound_ratio,int optimal_circuit,two_die_vector_char gate_all);
two_die_vector_int obtain_permutation_all(int permute_number);
two_die_vector_int obtain_combination_n_k(int element_num, int choose_num, one_die_vector_int given_set);
one_die_vector_int obtain_circuit_information(int bm_id_under_test,double approx_error_bound_ratio);

void error_quit( const char *msg );
void change_path( const char *path );
void rm_dir( const char *path );

#endif
