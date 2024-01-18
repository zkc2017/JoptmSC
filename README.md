# JoptmSC
This project implements the method to jointly optimize the randomizer and the computing core for low-cost stochastic circuits [1].

Related papers:

- [1]: Joint optimization of randomizer and computing core for low-cost stochastic circuits (Kuncai Zhong, Xuan Wang, Chen Wang, and Weikang Qian, NANOARCH 2023)

The following three directories provide the three major programs.

- [Obtain_Initial_Feature_Vector_by_Bernstein_Polynomial_Approximation](https://github.com/SJTU-ECTL/MinSC/tree/master/Obtain_Initial_Feature_Vector_by_Bernstein_Polynomial_Approximation) is supposed to be run before MinSC program to prepare the input file for it.

- [MinSC_main_program (on 64-bit Linux)](https://github.com/SJTU-ECTL/MinSC/tree/master/MinSC_main_program) is the program for the MinSC method used for optimizing the computing core.

- [JoptmSC_main_program (on 64-bit Linux)](https://github.com/zkc2017/JoptmSC) is the program for the joint optimization method.

Please refer to README.md in both directories for more details.

If you have any questions or suggestions, please feel free to eamil to kczhong@alumni.sjtu.edu.cn, thanks!
