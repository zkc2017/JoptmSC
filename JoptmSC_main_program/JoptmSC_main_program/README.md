# Joint optimization of randomizer and computing core for low-cost stochastic circuits

This project implements the method to jointly optimize the randomizer and the computing core for low-cost stochastic circuits.

Related papers:
- [1]: Joint optimization of randomizer and computing core for low-cost stochastic circuits (Kuncai Zhong, Xuan Wang, Chen Wang, and Weikang Qian, NANOARCH 2023)

Reference papers:
- [2]: Stochastic Circuit Synthesis by Cube Assignment (Xuesong Peng, and Weikang Qian, TCAD 2018)
- [3]: Exploring Target Function Approximation for Stochastic Circuit Minimization (Chen Wang, Weihua Xiao, John P. Hayes, and Weikang Qian, ICCAD 2020)
- [4]: MinSC: An Exact Synthesis-Based Method for Minimal-AreaStochastic Circuits under Relaxed Error Bound (Xuan Wang, Zhufei Chu, and Weikang Qian, ICCAD 2021)
- [5]: Towards Low-Cost High-Accuracy Stochastic Computing Architecture for Univariate Functions: Design and Design Space Exploration (Kuncai Zhong, Zexi Li, Weikang Qian, DATE 2022)

## Requirements

- OS: 64-bit Linux
- gcc
- g++
- EDA logic synthesis tools: [ABC](http://people.eecs.berkeley.edu/~alanmi/abc/), [MVSIS](https://github.com/sterin/mvsis) executable files
- SMT Solver: [Z3](https://github.com/Z3Prover/z3)

## Important Notes

- For the setup of the code, you can consult [MinSC](https://github.com/SJTU-ECTL/MinSC) and [TFASC](https://github.com/SJTU-ECTL/TFASC/tree/master/TFASC%20main%20program).

## How to run

- `g++ clause.hpp clause.cpp hash_extend.h node.h node.cpp obtain_circuit_main.cpp target_functions.h target_functions.cpp simulation.h simulation.cpp -lz3 -o simulation`
- `./simulation`
- Alternatively, you can directly execute  `sh run.sh` as well.
 

### Input Format
- `approx_error_bound_ratio` : the error ratio which controls the error bound of approximation. In our paper, we set error ratio as 0.02 and 0.05, respectively.
- `bm_id_under_test` : the index of benchmark functions;
   ```
   target function ID    target function
    -------------------------------------
    1                     sin(x)
    2                     cos(x)
    3                     tanh(x)
    4                     exp(-x)
    5                     log(x+1)
    6                     x^2.2
    7                     sin(Pi*x)/Pi
    8                     exp(-2x)
    9                     1/(x+1)
    10                    tanh(Pi*x)
    11                    x^0.45
    12                    sqrt(x)
    13                    tan(x/2)
    14                    x*ln(x/2)+1
    15                    1/(1+exp(-1*x))
   ```
   
## Program Organization

```
<program_dir>
| readme.md
|----src
|     |----(source files)
|----gate_library
|     |----mcnc.genlib
|     |----gate.txt(the gate library after extending mcnc.genlib)
|----FVnm
|     |----1.txt
|     |----2.txt
|     |----(and so on)
|----temp_dir
|     |----(temporary files)
|----output_dir
|     |----error_ratio2
|     |     |----bm1
|     |     |----bm2
|     |     |----(and so on)
|     |----error_ratio5
|     |     |----bm1
|     |     |----bm2
|     |     |----(and so on)
|----configuration
|     |----error_ratio2
|     |     |----bm1
|     |     |----bm2
|     |     |----(and so on)
|     |----error_ratio5
|     |     |----bm1
|     |     |----bm2
|     |     |----(and so on)
|----LFSR
|     |----bit_4.txt
|     |----bit_5.txt
|     |----(and so on)
|----DCV_MGS
|     |----error_ratio2
|     |     |----5.txt
|     |     |----8.txt
|     |     |----(and so on)
|     |----error_ratio5
|     |     |----13.txt
|     |     |----14.txt
|     |     |----(and so on)
|----log_file
|     |----log_0.020000.txt
|     |----log_0.050000.txt
```

- `src`: contains all source files and header files.
- `gate_library`: contains the mcnc.genlib and gate.txt. The file gate.txt is the gate library after extending mcnc.genlib. For a gate with the fanin number less than4, it is extended to a 4-input gate with some fake fanins.
- `FVnm`: contains the initial feature vectors of different degrees and precisions for all benchmark functions.
   Format of each row in the `bm_id_under_test`.txt file:
```
   degree n precision m feature vector
```
- `temp_dir`: contains temporary files generated during the running of the program.
- `LFSR`: contains the feedback polynomial information for LFSRs.
- `log file`: contains the log information under different `approx_error_bound_ratio` values.
- `DCV_MGS`: contains [POA and MGS](https://github.com/SJTU-ECTL/MinSC/tree/master/MinSC_main_program) information for some functions.
- `output_dir`: contains two sub-folders, i.e., `error_ratio2` and `error_ratio5`. `error_ratio2` contains the output files for all the benchmarks with error ratio 0.02 in each sub-folder such as `bm1`, `bm2`, etc., while `error_ratio5` contains the output files for all the benchmarks with error ratio 0.05 used in each sub-folder such as `bm1`, `bm2`, etc..
  The output files are:
  - `<bm_name>-bestSol_summary.txt`: overall summary of the best solution with minimal area for `<bm_name>`.
  - `<bm_name>-solution<num>.v`: gate-level Verilog file for the solution with number `<num>`.
- `configuration`: contains two sub-folders, i.e., `error_ratio2` and `error_ratio5`. `error_ratio2` contains the configuration files of the randomizers for all the benchmarks with error ratio 0.02 in each sub-folder such as `bm1`, `bm2`, etc., while `error_ratio5` contains the configuration files of the randomizers for all the benchmarks with error ratio 0.05 used in each sub-folder such as `bm1`, `bm2`, etc..
  The configuration files are:
  - `<bm_name>-configuration.txt`: overall configurations for the randomizer for `<bm_name>`.
