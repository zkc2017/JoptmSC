#pragma once
#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <set>
#include <cmath>
#include <cstring >
using namespace std;

//double bm1_target_func(double x);

typedef vector <int> one_die_vector_int;
typedef vector <one_die_vector_int> two_die_vector_int;
typedef vector <two_die_vector_int> three_die_vector_int;

typedef vector <char> one_die_vector_char;
typedef vector <one_die_vector_char> two_die_vector_char;

typedef vector <uint64_t> one_die_vector_bit;
typedef vector <one_die_vector_bit> two_die_vector_bit;

double simulation_main(int bm_id_under_test, double approx_error_bound_ratio, int bit_width, int simulation_num);
two_die_vector_int obtain_LFSR_polynomial(int bit_width);
two_die_vector_int obtain_output_LFSR(two_die_vector_int LFSR_set,int bit_width,int choose_LFSR);
one_die_vector_int compute_binary_number_LFSR(int bit_width,two_die_vector_int output_bit);
one_die_vector_int obtain_circuit_information(int bm_id_under_test,double approx_error_bound_ratio);
two_die_vector_char read_library();
two_die_vector_int read_verilog(int bm_id_under_test,double approx_error_bound_ratio,int optimal_circuit,two_die_vector_char gate_all);
two_die_vector_int obtain_permutation_all(int permute_number);
two_die_vector_int obtain_combination_n_k(int element_num, int choose_num, one_die_vector_int given_set);
double algorithm_search_minimum_error(int bit_width,one_die_vector_int circuit_information,three_die_vector_int information_combine,int simulation_num,double(*fp1)(double),int bm_id_under_test,double approx_error_bound_ratio);
void output_configuration(int configuration_res[7],three_die_vector_int information_combine,two_die_vector_int negation_set_variable,two_die_vector_int negation_set_constant,int bm_id_under_test,double approx_error_bound_ratio);
two_die_vector_int obtain_random_binary_number(int bit_width, two_die_vector_int LFSR_bit, one_die_vector_int NG_1, one_die_vector_int SR_1, one_die_vector_int SR_3);
two_die_vector_bit obtain_random_bit(int bit_width, two_die_vector_int LFSR_bit, one_die_vector_int BS, one_die_vector_int NG_2, one_die_vector_int SR_2);
two_die_vector_bit obtain_input_bit(int bit_width, two_die_vector_bit random_bit, two_die_vector_int random_binary_number, double x);
double obtain_error(two_die_vector_int verilog_circuit, int bit_width, two_die_vector_int random_binary_number, two_die_vector_bit random_bit, int simulation_num,double(*fp1)(double),double Err_minimum);
void function_check();

one_die_vector_bit inv1(int len_len, two_die_vector_bit gate_input_bit);
one_die_vector_bit inv2(int len_len, two_die_vector_bit gate_input_bit);
one_die_vector_bit inv3(int len_len, two_die_vector_bit gate_input_bit);
one_die_vector_bit inv4(int len_len, two_die_vector_bit gate_input_bit);
one_die_vector_bit nand2(int len_len, two_die_vector_bit gate_input_bit);
one_die_vector_bit nand3(int len_len, two_die_vector_bit gate_input_bit);
one_die_vector_bit nand4(int len_len, two_die_vector_bit gate_input_bit);
one_die_vector_bit nor2(int len_len, two_die_vector_bit gate_input_bit);
one_die_vector_bit nor3(int len_len, two_die_vector_bit gate_input_bit);
one_die_vector_bit nor4(int len_len, two_die_vector_bit gate_input_bit);
one_die_vector_bit and2(int len_len, two_die_vector_bit gate_input_bit);
one_die_vector_bit or2(int len_len, two_die_vector_bit gate_input_bit);
one_die_vector_bit xor2(int len_len, two_die_vector_bit gate_input_bit);
one_die_vector_bit xor2b(int len_len, two_die_vector_bit gate_input_bit);
one_die_vector_bit xnor2(int len_len, two_die_vector_bit gate_input_bit);
one_die_vector_bit xnor2b(int len_len, two_die_vector_bit gate_input_bit);
one_die_vector_bit aoi21(int len_len, two_die_vector_bit gate_input_bit);
one_die_vector_bit aoi22(int len_len, two_die_vector_bit gate_input_bit);
one_die_vector_bit oai21(int len_len, two_die_vector_bit gate_input_bit);
one_die_vector_bit oai22(int len_len, two_die_vector_bit gate_input_bit);
one_die_vector_bit buf(int len_len, two_die_vector_bit gate_input_bit);
one_die_vector_bit zero(int len_len, two_die_vector_bit gate_input_bit);
one_die_vector_bit one(int len_len, two_die_vector_bit gate_input_bit);

double bm1_target_funcs(double x);
double bm2_target_funcs(double x);
double bm3_target_funcs(double x);
double bm4_target_funcs(double x);
double bm5_target_funcs(double x);
double bm6_target_funcs(double x);
double bm7_target_funcs(double x);
double bm8_target_funcs(double x);
double bm9_target_funcs(double x);
double bm10_target_funcs(double x);
double bm11_target_funcs(double x);
double bm12_target_funcs(double x);
double bm13_target_funcs(double x);
double bm14_target_funcs(double x);

#endif