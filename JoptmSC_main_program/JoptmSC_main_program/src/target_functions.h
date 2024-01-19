#pragma once
#ifndef TARGET_FUNC_H
#define TARGET_FUNC_H

#define NORM_EVAL_POINT_NUM 1000


//===========================================================
// add declaration of user-defined target functions here

double user_defined_target_function(double x);
//#define TARGET_FUNCTION_L2NORM_RELATIVE_ERROR_BOUND 0.02


//===========================================================

double bm1_target_func(double x);
double bm2_target_func(double x);
double bm3_target_func(double x);
double bm4_target_func(double x);
double bm5_target_func(double x);
double bm6_target_func(double x);
double bm7_target_func(double x);
double bm8_target_func(double x);
double bm9_target_func(double x);
double bm10_target_func(double x);
double bm11_target_func(double x);
double bm12_target_func(double x);
double bm13_target_func(double x);
double bm14_target_func(double x);
double bm15_target_func(double x);


void obtain_circuit_main(int bm_id_under_test, double approx_error_bound_ratio, int bit_width, int simulation_num, double approx_error_bound_ratio_real);


#endif
