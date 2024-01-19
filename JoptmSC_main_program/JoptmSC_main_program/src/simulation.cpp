#include "simulation.h"
#include <chrono>
#include <random>
#include "clause.hpp"
#include "target_functions.h"
#include "node.h"
#include<time.h> 

//#include<boost/random.hpp>
//using  namespace  boost;

#define PI 3.141592654


using namespace std;

/*int main(int argc, char* argv[]){
    std::ios::sync_with_stdio(false);  // Speed IO
    std::cin.tie(0);

    int bm_id_under_test = 1;
    double approx_error_bound_ratio = 0.02;
	int bit_width=8;
	int simulation_num=1000;

	cout<<"begin"<<endl;

	double err_min = simulation_main( bm_id_under_test, approx_error_bound_ratio, bit_width, simulation_num);

	return 0;
}*/

int main(int argc, char* argv[]){
    std::ios::sync_with_stdio(false);  // Speed IO
    std::cin.tie(0);
    	time_t now = time(NULL);
	tm* tm_t = localtime(&now);
    
    double approx_error_bound_ratio = 0.02;
    int bit_width=8;
    int simulation_num=1000;
	double err_min=0;
	double time_cost_max = 0;
	double time_cost_all = 0;
	
    char log_filename[100];
    strcpy(log_filename, "log_");
    strcat(log_filename, std::to_string(approx_error_bound_ratio).data());
    strcat(log_filename, ".txt");
    ofstream out;
    out.open(log_filename);
	
	
    
    for(int bm_id_under_test=1;bm_id_under_test<2;bm_id_under_test++){
    	auto start = chrono::system_clock::now();
        if(bm_id_under_test>6 && bm_id_under_test<15){
            continue;
        }
        out<<"begin search function-"<<to_string(bm_id_under_test)<<endl;
		double err_prev_res = 100.0;
		one_die_vector_int infor;
		infor.push_back(1000);
		infor.push_back(1000);
		infor.push_back(1000);
		infor.push_back(0);
        //int bm_id_under_test = 1;
    

		double approx_error_bound_ratio_real = approx_error_bound_ratio*1.5;

		bool whether_loop = true;

		int sig_res = 0;
		int sig;
		err_min = 1;

		while(whether_loop){
			obtain_circuit_main( bm_id_under_test, approx_error_bound_ratio, bit_width, simulation_num, approx_error_bound_ratio_real);
			double err_min_res = err_min;
			err_min = simulation_main( bm_id_under_test, approx_error_bound_ratio, bit_width, simulation_num, infor);

			/*for(int iop=0;iop<4;iop++){
				cout<<infor[iop]<<":";
			}
			cout<<endl;*/
			//double err_min=0;
			if(infor[3]==1){
				err_min = err_min_res;
			}
			if(err_min<approx_error_bound_ratio){
				break;
			}
			if(err_min>approx_error_bound_ratio){
				approx_error_bound_ratio_real = approx_error_bound_ratio_real - max(err_min - approx_error_bound_ratio, approx_error_bound_ratio/10);
			}
		}
		cout << "Finish!-"<<bm_id_under_test<< endl;
		auto end1 = chrono::system_clock::now();
		auto duration1 = chrono::duration_cast<std::chrono::milliseconds>(end1 - start);
		auto milliseconds1 = duration1.count();
		cout << "milliseconds: " << milliseconds1 << endl;
		
		std::stringstream ss;
	ss << "year:" << tm_t->tm_year + 1900 << " month:" << tm_t->tm_mon + 1 << " day:" << tm_t->tm_mday
		<< " hour:" << tm_t->tm_hour << " minute:" << tm_t->tm_min << " second:" << tm_t->tm_sec;


		out<<"cost time"<<to_string(milliseconds1)<<"milliseconds"<<endl;
		out<<"Accuracy (MAE)"<<to_string(err_min)<<endl;
		out<<ss.str()<<endl;
		out<<"finish function"<<to_string(bm_id_under_test)<<endl;
		/*auto hours1 = milliseconds1 / 3600000;
		milliseconds1 -= hours1 * 3600000;
		auto minitues1 = milliseconds1 / 60000;
		milliseconds1 -= minitues1 * 60000;
		auto seconds1 = milliseconds1 / 1000;
		milliseconds1 -= seconds1 * 1000;
		cout << "Time used-all: ";
		cout << hours1 << ":";
		cout.fill('0');
		cout.width(2);
		cout << minitues1 << ":";
		cout.fill('0');
		cout.width(2);
		cout << seconds1 << ".";
		cout.fill('0');
		cout.width(3);
		cout << milliseconds1 << endl;
		cout << endl;*/
		//DWORD endTime_temp = GetTickCount();
		double time_cost = milliseconds1;
		cout<<"time cost:"<<time_cost/1000<<"s"<<endl;
		time_cost_all = time_cost_all + time_cost;
		if (time_cost_max<time_cost)
		{
			time_cost_max = time_cost;
		}
		
	}
	cout<<"time cost average:"<<time_cost_all/15000<<"s"<<endl;
	cout<<"time cost maximum:"<<time_cost_max/1000<<"s"<<endl;
	out.close();
    
	return 0;
}

double simulation_main(int bm_id_under_test, double approx_error_bound_ratio, int bit_width, int simulation_num, one_die_vector_int &infor){

    double(*fp_target_func)(double);

	//function_check();
	//exit(-1);

    // assign target function
	switch(bm_id_under_test){
		case 1:
			fp_target_func = &bm1_target_funcs;
			break;
		case 2:
			fp_target_func = &bm2_target_funcs;
			break;
		case 3:
			fp_target_func = &bm3_target_funcs;
			break;
		case 4:
			fp_target_func = &bm4_target_funcs;
			break;
		case 5:
			fp_target_func = &bm5_target_funcs;
			break;
		case 6:
			fp_target_func = &bm6_target_funcs;
			break;
		case 7:
			fp_target_func = &bm7_target_funcs;
			break;
		case 8:
			fp_target_func = &bm8_target_funcs;
			break;
		case 9:
			fp_target_func = &bm9_target_funcs;
			break;
		case 10:
			fp_target_func = &bm10_target_funcs;
			break;
		case 11:
			fp_target_func = &bm11_target_funcs;
			break;
		case 12:
			fp_target_func = &bm12_target_funcs;
			break;
		case 13:
			fp_target_func = &bm13_target_funcs;
			break;
		case 14:
			fp_target_func = &bm14_target_funcs;
			break;
		case 15:
			fp_target_func = &bm15_target_funcs;
			break;
	}

    two_die_vector_int LFSR_set = obtain_LFSR_polynomial(bit_width);

	int LFSR_choose=0;
	two_die_vector_int LFSR_bit = obtain_output_LFSR(LFSR_set,bit_width, LFSR_choose);
	one_die_vector_int binary_number = compute_binary_number_LFSR(bit_width,LFSR_bit);

	//cout<<"here"<<endl;

	//sort(binary_number.begin(), binary_number.end());

	one_die_vector_int circuit_information = obtain_circuit_information( bm_id_under_test, approx_error_bound_ratio);

	int infor_sig = 0;

	for(int i=0;i<3;i++){
		
		if(infor[i]!=circuit_information[i]){
			infor_sig = 1;
			break;
		}
	}
	if(infor_sig==0){
		infor[3] = 1;
		//cout<<infor[0]<<endl;
		//exit(-1);
		return 100.0;
	}
	else{
		for(int i=0;i<3;i++){
			infor[i] = circuit_information[i];
			
		}
		infor[3] = 0;
		//cout<<infor[0]<<endl;
		//exit(-1);
		//return 0.0501197;
	}

	/*cout<<circuit_information.size()<<endl;
	cout<<circuit_information[0]<<endl;
	for(int i=0;i<circuit_information.size();i++){
		cout<<circuit_information[i]<<" ";
	}
	cout<<endl;*/

	///cout<<"read_library_begin"<<endl;
	two_die_vector_char gate_all = read_library();

	/*for(int i=0;i<gate_all.size();i++){
		for(int j=0;j<gate_all.size();j++){
			cout<<gate_all[i][j];
		}
		cout<<endl;
	}
	cout<<"read_library"<<endl;*/
	two_die_vector_int verilog_circuit = read_verilog(bm_id_under_test,approx_error_bound_ratio,circuit_information[2],gate_all);

	//cout<<"read_verilog"<<endl;

	/*circuit_information[0] = 4;
	circuit_information[1] = 6;*/
	two_die_vector_int permutation_bit_width = obtain_permutation_all(bit_width);
	two_die_vector_int permutation_input_scrambling = obtain_permutation_all(circuit_information[0]);
	two_die_vector_int permutation_bit_selection = obtain_permutation_all(circuit_information[1]);
	//cout<<"ok"<<endl;


	//two_die_vector_int tyu = obtain_permutation_all(1);

	/*for(int i=0;i<verilog_circuit.size();i++){
		for(int j=0;j<verilog_circuit[i].size();j++){
			cout<<verilog_circuit[i][j]<<" ";
		}
		cout<<endl;
	}*/

	int element_num = bit_width;
	int choose_num = circuit_information[1];
	one_die_vector_int given_set;

	for(int i=0;i<element_num;i++){
		given_set.push_back(i);
	}

	//cout<<"okk"<<endl;
	two_die_vector_int combination_set = obtain_combination_n_k( element_num, choose_num,  given_set);
	//cout<<"ok"<<endl;

	three_die_vector_int information_combine;

	information_combine.push_back(LFSR_set);
	information_combine.push_back(verilog_circuit);
	information_combine.push_back(permutation_bit_width);
	information_combine.push_back(permutation_input_scrambling);
	information_combine.push_back(permutation_bit_selection);
	information_combine.push_back(combination_set);

	//cout<<"algorithm_search_minimum_error"<<endl;

	double err_minimum = algorithm_search_minimum_error( bit_width, circuit_information, information_combine, simulation_num, fp_target_func,bm_id_under_test,approx_error_bound_ratio);

	return err_minimum;
}

two_die_vector_int obtain_LFSR_polynomial(int bit_width) {
	char cmd[100];
	strcpy(cmd, "LFSR/bit_");
	strcat(cmd, std::to_string(bit_width).data());
	strcat(cmd, ".txt");

	ifstream in;
	in.open(cmd);
    auto line = string();
    int count = 0;

    one_die_vector_int polynomial;
    two_die_vector_int LFSR_set;
    if(in){
		//cout << "line" << endl;
        while(getline(in,line)){
            stringstream ss(line);
            vector <int> res;
            res.clear();
            int i;

			char pp[10];

			int r = 0;
			int num = 0;

			for(int i=0;i<line.length();i++){
				if(line[i]!=',' && line[i]!='.'){
					pp[r]=line[i];
					r++;
				}
				else{
					num = 0;
					for(int j=0;j<r;j++){
						num=num*10+pp[j]-48;
					}
					polynomial.push_back(num);
					r = 0;
				}
			}
			LFSR_set.push_back(polynomial);
			polynomial.clear();
        }
    }
	return LFSR_set;

}

two_die_vector_int obtain_output_LFSR(two_die_vector_int LFSR_set,int bit_width,int choose_LFSR){
	int len_len=pow(2,bit_width)-1;
	int temp[bit_width]={0};
	temp[bit_width-1]=1;

	int non_zero_num=0;

	for(int i=0;i<bit_width;i++){
		if(LFSR_set[choose_LFSR][i]==0){
			break;
		}
		non_zero_num++;
	}

	one_die_vector_int temp_bit;
	two_die_vector_int output_bit;

	for(int i=0;i<bit_width;i++){
		temp_bit.push_back(temp[i]);
	}
	output_bit.push_back(temp_bit);
	temp_bit.clear();

	int generate_bit=0;

	for(int i=0;i<len_len-1;i++){
		generate_bit=temp[LFSR_set[choose_LFSR][0]-1];
		for(int j=0;j<non_zero_num-1;j++){
			generate_bit=generate_bit^temp[LFSR_set[choose_LFSR][j+1]-1];
		}

		for(int j=bit_width-1;j>0;j--){
			temp[j]=temp[j-1];
		}
		temp[0]=generate_bit;

		for(int j=0;j<bit_width;j++){
			temp_bit.push_back(temp[j]);
		}
		output_bit.push_back(temp_bit);
		temp_bit.clear();
	}
	return output_bit;
}

one_die_vector_int compute_binary_number_LFSR(int bit_width,two_die_vector_int output_bit){
	int len_len=pow(2,bit_width)-1;
	int temp=0;
	one_die_vector_int binary_number;
	for(int i=0;i<len_len;i++){
		temp=0;
		for(int j=0;j<bit_width;j++){
			temp=temp*2+output_bit[i][j];
		}
		binary_number.push_back(temp);
	}
	return binary_number;
}

one_die_vector_int obtain_circuit_information(int bm_id_under_test,double approx_error_bound_ratio){
	char cmd[100];
	int err_site=0;
	strcpy(cmd, "./output_dir/error_ratio");
	if(approx_error_bound_ratio==0.02){
		err_site=2;
	}
	else if(approx_error_bound_ratio==0.05){
		err_site=5;
	}
	else{
		cout << "error-obtain_circuit_information" << endl;
		exit(-1);
	}
	strcat(cmd, std::to_string(err_site).data());
	strcat(cmd, "/bm");
	strcat(cmd, std::to_string(bm_id_under_test).data());
	strcat(cmd, "/bm");
	strcat(cmd, std::to_string(bm_id_under_test).data());
	strcat(cmd, "-bestSol_summary.txt");

	//cout<<cmd<<endl;

	ifstream in;
	in.open(cmd);
    auto line = string();
    int count = 0;

    one_die_vector_int circuit_information;
    if(in){
		//cout << "line" << endl;
        while(getline(in,line)){
            stringstream ss(line);
			//cout<<line<<endl;
			char pp[10];

			int r = 0;
			int num = 0;

			for(int i=0;i<line.length();i++){
				if(line[i]!=' '&&line[i]!='.'){
					pp[r]=line[i];
					r++;
				}
				else{
					num = 0;
					for(int j=0;j<r;j++){
						num=num*10+pp[j]-48;
					}
					circuit_information.push_back(num);
					r = 0;
				}
			}
			break;
        }
    }
    //cout<<"line finish"<<endl;
	return circuit_information;

}

two_die_vector_char read_library(){
	char cmd[100];
	strcpy(cmd, "./gate_library/mcnc_buf1.genlib");
	//cout<<cmd<<endl;

	ifstream in;
	in.open(cmd);
    auto line = string();
    int count = 0;

	one_die_vector_char temp_char;
	two_die_vector_char gate_all;

	//cout<<in<<endl;
	//cout << "line-1" << endl;

	if(in){
		//cout << "line" << endl;
        while(getline(in,line)){
			stringstream ss(line);
			int r = 0;

			for(int i=5;i<line.length();i++){
				if(line[i]!=' '&&line[i]!='	'){
					temp_char.push_back(line[i]);
				}
				else{
					temp_char.push_back('\0');
					gate_all.push_back(temp_char);
					temp_char.clear();
					break;
				}
			}
        }
    }

	/*for(int i=0;i<gate_all.size();i++){
		char a[50];
		for(int j=0;j<gate_all[i].size();j++){
			a[j]=gate_all[i][j];
		}
		cout<< a <<endl;
	}*/
	return gate_all;
}

two_die_vector_int read_verilog(int bm_id_under_test,double approx_error_bound_ratio,int optimal_circuit,two_die_vector_char gate_all){
	//char gate_all[23][20]={"inv1","inv2","inv3","inv4","nand2","nand3","nand4","nor2","nor3","nor4","and2","or2","xor2","xor2b","xnor2","xnor2b","aoi21","aoi22","oai21","oai22","buf","zero","one"};

	char cmd[100];
	int err_site=0;
	strcpy(cmd, "./output_dir/error_ratio");
	if(approx_error_bound_ratio==0.02){
		err_site=2;
	}
	else if(approx_error_bound_ratio==0.05){
		err_site=5;
	}
	else{
		cout << "error-obtain_circuit_information" << endl;
		exit(-1);
	}
	strcat(cmd, std::to_string(err_site).data());
	strcat(cmd, "/bm");
	strcat(cmd, std::to_string(bm_id_under_test).data());
	strcat(cmd, "/bm");
	strcat(cmd, std::to_string(bm_id_under_test).data());
	strcat(cmd, "-solution");
	strcat(cmd, std::to_string(optimal_circuit).data());
	strcat(cmd, ".v");

	//cout<<cmd<<endl;

	ifstream in;
	in.open(cmd);
    auto line = string();
    int count = 0;

    one_die_vector_int temp_int;
    two_die_vector_int verilog_circuit;
	one_die_vector_char temp_char;
	two_die_vector_char variable_name;

	int re=0;
    if(in){
		//cout << "line" << endl;
        while(getline(in,line)){
			stringstream ss(line);
			//cout<<line<<endl;
			if(re<3){
				re++;
				continue;
			}

			int r = 0;

			char input_check[50];

			for(int i=0;i<5;i++){
				input_check[i] = line[i+2];
			}
			input_check[5] = '\0';

			char output_check[50];

			for(int i=0;i<6;i++){
				output_check[i] = line[i+2];
			}
			output_check[6] = '\0';

			char wire_check[50];

			for(int i=0;i<4;i++){
				wire_check[i] = line[i+2];
			}
			wire_check[4] = '\0';

			if(strcmp(input_check,"input")==0||strcmp(output_check,"output")==0||strcmp(wire_check,"wire")==0){
				int start_site=0;

				switch(re){
		     		case 3:
						start_site = 8;
						break;
					case 4:
						start_site = 9;
						break;
					case 5:
						start_site = 7;
					break;
				}

				for(int i=start_site;i<line.length();i++){
					if(line[i]!=','&&line[i]!=';'){
						temp_char.push_back(line[i]);
					}
					else{
						temp_char.push_back('\0');
						variable_name.push_back(temp_char);
						temp_char.clear();
						i++;
					}
				}

				re++;
				continue;
			}


			if(line=="endmodule")
			{
				//cout<<line<<endl;
				break;
			}

			int start_site_2=0;
			char a[50];

			//cout<<line.length()<<endl;
			//cout<<a<<endl;

			for(int i=2;i<line.length();i++){
				//cout<<line[i]<<endl;
				if(line[i]!=' '){
					a[i-2]=line[i];
					start_site_2++;
				}
				else{
					a[i-2]='\0';
					break;
				}
			}

			//cout<<a<<endl;
			//exit(-1);

			for(int i=0;i<gate_all.size();i++){
				char b[50];
				for(int j=0;j<gate_all[i].size();j++){
					b[j]=gate_all[i][j];
				}
				int sig = strcmp(a,b);
				if(sig==0){
					//cout<<a<<":"<<b<<endl;
					temp_int.push_back(i);
					break;
				}
			}

			//cout<<start_site_2<<endl;


			start_site_2=start_site_2+2;


			for(int i=start_site_2;i<line.length();i++){
				//cout<<line[i];
				if(line[i]=='.'){
					i=i+3;
					for(int j=i;j<line.length();j++){
						if(line[j]!=')'){
							a[j-i]=line[j];
						}
						else{
							a[j-i]='\0';
							i=j;
							break;
						}
					}
					//cout<<a<<endl;

					for(int k=0;k<variable_name.size();k++){
						char b[50];
						for(int j=0;j<variable_name[k].size();j++){
							b[j]=variable_name[k][j];
						}
						int sig = strcmp(a,b);
						//cout<<a<<" "<<b<<endl;
						//cout<<sig<<endl;
						if(sig==0){
							temp_int.push_back(k);
							break;
						}
					}
				}
			}



			verilog_circuit.push_back(temp_int);
			temp_int.clear();
			re++;
			//cout<<re<<endl;
			//exit(-1);
        }
    }
	/*for(int i=0;i<temp_two_char.size();i++){
		char a[50];
		for(int j=0;j<temp_two_char[i].size();j++){
			a[j]=temp_two_char[i][j];
		}
		cout<< a <<endl;
	}*/
	/*for(int i=0;i<verilog_circuit.size();i++){
		for(int j=0;j<verilog_circuit[i].size();j++){
			cout<< verilog_circuit[i][j] << " ";
		}
		cout<<endl;
	}*/
	return verilog_circuit;

}

two_die_vector_int obtain_permutation_all(int permute_number){
	int num[permute_number];

	one_die_vector_int temp;
	two_die_vector_int permutation_all;

	for(int i=0;i<permute_number;i++){
		num[i]=i;
	}
	do
    {
		for(int i=0;i<permute_number;i++){
			temp.push_back(num[i]);
		}
		permutation_all.push_back(temp);
		temp.clear();

    }while(next_permutation(num,num+permute_number));
	return permutation_all;
}

two_die_vector_int obtain_combination_n_k(int element_num, int choose_num, one_die_vector_int given_set){
	one_die_vector_int given_set_2;
	one_die_vector_int temp;
	two_die_vector_int combination_n_k;

	if(element_num<choose_num){
		cout<< "obtain combination error" <<endl;
		exit(-1);
	}

	if(choose_num==0){
		combination_n_k.push_back(temp);
		return combination_n_k;
	}

	if(choose_num==1){
		for(int i=0;i<element_num;i++){
			temp.push_back(given_set[i]);
			combination_n_k.push_back(temp);
			temp.clear();
		}
		return combination_n_k;
	}

	//cout<<element_num<<":"<<choose_num<<endl;

	for(int i=0;i<element_num-choose_num+1;i++){
		for(int j=i+1;j<element_num;j++){
			given_set_2.push_back(given_set[j]);
		}
		two_die_vector_int sub_combination_set = obtain_combination_n_k( element_num-i-1, choose_num-1, given_set_2);
		given_set_2.clear();

		for(int j=0;j<sub_combination_set.size();j++){
			temp.push_back(given_set[i]);
			for(int k=0;k<choose_num-1;k++){
				temp.push_back(sub_combination_set[j][k]);
			}
			combination_n_k.push_back(temp);
			temp.clear();
		}
	}
	return combination_n_k;
}

double algorithm_search_minimum_error(int bit_width,one_die_vector_int circuit_information,three_die_vector_int information_combine,int simulation_num,double(*fp1)(double),int bm_id_under_test,double approx_error_bound_ratio){

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	mt19937 rand_num(seed);  // 大随机数
	uniform_int_distribution<long long> dist(0, 1000000000);  // 给定范围

	two_die_vector_int LFSR_set = information_combine[0];
	two_die_vector_int verilog_circuit = information_combine[1];
	two_die_vector_int permutation_bit_width = information_combine[2];
	two_die_vector_int permutation_input_scrambling = information_combine[3];
	two_die_vector_int permutation_bit_selection = information_combine[4];
	two_die_vector_int combination_set = information_combine[5];

	three_die_vector_int LFSR_bit_all;
	two_die_vector_int LFSR_bit_temp;

	for(int i=0;i<LFSR_set.size();i++){
		LFSR_bit_temp = obtain_output_LFSR(LFSR_set,bit_width, i);
		LFSR_bit_all.push_back(LFSR_bit_temp);
		LFSR_bit_temp.clear();
	}

    int LFSR_num = LFSR_set.size();
	int variable_input_num = circuit_information[0];
	int constant_input_num = circuit_information[1];
	int permutation_bw_num = permutation_bit_width.size();
	int permutation_is_num = permutation_input_scrambling.size();
	int permutation_bs_num = permutation_bit_selection.size();
	int combination_num = combination_set.size();

	two_die_vector_int negation_set_variable;
	two_die_vector_int negation_set_constant;
	one_die_vector_int given_set_1;
	one_die_vector_int given_set_2;
	one_die_vector_int one_die_temp;
	two_die_vector_int two_die_temp;

	for(int i=0;i<bit_width;i++){
		given_set_1.push_back(i);
	}

	negation_set_variable.push_back(one_die_temp);

    for(int i=1;i<=bit_width;i++){
		 two_die_temp = obtain_combination_n_k( bit_width, i,  given_set_1);

		 for(int j=0;j<two_die_temp.size();j++){
			 negation_set_variable.push_back(two_die_temp[j]);
		 }

		 two_die_temp.clear();
	}

	for(int i=0;i<constant_input_num;i++){
		given_set_2.push_back(i);
	}

	negation_set_constant.push_back(one_die_temp);

    for(int i=1;i<=constant_input_num;i++){
		 two_die_temp = obtain_combination_n_k( constant_input_num, i,  given_set_2);

		 for(int j=0;j<two_die_temp.size();j++){
			 negation_set_constant.push_back(two_die_temp[j]);
		 }

		 two_die_temp.clear();
	}

	/*for(int  i=0;i<negation_set_constant.size();i++){
		for(int j=0;j<negation_set_constant[i].size();j++){
			cout<<negation_set_constant[i][j]<<" ";
		}
		cout<<endl;
	}*/


	bool whether_loop = true;

    int configuration_res[7];

	configuration_res[0] = 0; //LFSR_res
	configuration_res[1] = 0; //BS_res
	configuration_res[2] = negation_set_variable.size()-1; //NG_1_res
	configuration_res[3] = negation_set_constant.size()-1; //NG_2_res
	configuration_res[4] = permutation_bw_num-1; //SR_1_res
	configuration_res[5] = 0; //SR_2_res
	configuration_res[6] = 0; //SR_3_res

	int configuration_temp[7];

	for(int i=0;i<7;i++){
		configuration_temp[i] = configuration_res[i];
	}

	two_die_vector_int LFSR_set_apply = LFSR_bit_all[configuration_temp[0]];
	one_die_vector_int NG1 = negation_set_variable[configuration_temp[2]];
	one_die_vector_int SR1 = permutation_bit_width[configuration_temp[4]];
	one_die_vector_int SR3 = permutation_input_scrambling[configuration_temp[6]];

	two_die_vector_int random_binary_number = obtain_random_binary_number(bit_width,LFSR_set_apply,NG1,SR1,SR3);

	one_die_vector_int BS = combination_set[configuration_temp[1]];
	one_die_vector_int NG_2 = negation_set_constant[configuration_temp[3]];
	one_die_vector_int SR_2 = permutation_bit_selection[configuration_temp[5]];

	two_die_vector_bit random_bit = obtain_random_bit( bit_width, LFSR_set_apply, BS, NG_2, SR_2);

	double x=0.1;

	two_die_vector_bit input_bit = obtain_input_bit( bit_width, random_bit, random_binary_number, x);

	cout<<"obtain error"<<endl;

	double error = obtain_error( verilog_circuit, bit_width, random_binary_number, random_bit, simulation_num, fp1, 100);

	//cout<<error<<endl;

	//exit(-1);

	/*for(int j=0;j<SR3.size();j++){
		for(int i=0;i<pow(2,bit_width)-1;i++){
			cout<<random_binary_number[j][i]<<",";
		}
		cout<<endl;
	}*/
	/*for(int j=0;j<permutation_input_scrambling[configuration_temp[6]].size();j++){
		for(int i=0;i<pow(2,bit_width)-1;i++){
			cout<<random_binary_number[j][i]<<",";
		}
		cout<<endl;
	}*/
	//exit(-1);

	/*for(int i=0;i<7;i++){
		cout<<configuration_res[i]<<" ";
	}
	cout<<endl;*/

	double Err_minimum = error;
	double Err_prev = Err_minimum;
	double Err_temp = error;

	int sumulation_time = 1;
	while(whether_loop){
		for(int i=0;i<combination_num;i++){ //algorithm-1
			configuration_temp[1] = i;

			for(int j=0;j<negation_set_variable.size();j++){
				configuration_temp[2] = j;

				for(int k=0;k<negation_set_constant.size();k++){
					configuration_temp[3] = k;
					double p = dist(rand_num)*1.0/1000000000;
					configuration_temp[0] = round((LFSR_num-1)*p);

					//cout<< i<<":"<< j<<":"<<k <<endl;

					two_die_vector_int LFSR_set_apply = LFSR_bit_all[configuration_temp[0]];
					one_die_vector_int NG1 = negation_set_variable[configuration_temp[2]];
					one_die_vector_int SR1 = permutation_bit_width[configuration_temp[4]];
					one_die_vector_int SR3 = permutation_input_scrambling[configuration_temp[6]];

					two_die_vector_int random_binary_number = obtain_random_binary_number(bit_width,LFSR_set_apply,NG1,SR1,SR3);

					one_die_vector_int BS = combination_set[configuration_temp[1]];
					one_die_vector_int NG_2 = negation_set_constant[configuration_temp[3]];
					one_die_vector_int SR_2 = permutation_bit_selection[configuration_temp[5]];

					two_die_vector_bit random_bit = obtain_random_bit( bit_width, LFSR_set_apply, BS, NG_2, SR_2);

					Err_temp = obtain_error( verilog_circuit, bit_width, random_binary_number, random_bit, simulation_num, fp1, Err_minimum);

					if(Err_temp<Err_minimum){
						for(int t=0;t<7;t++){
							configuration_res[t] = configuration_temp[t];
							Err_minimum = Err_temp;
							
						}
						cout<<Err_minimum<<endl;
					}
					sumulation_time++;
					if(Err_minimum<approx_error_bound_ratio){
					    break;
					}
					

				}
				if(Err_minimum<approx_error_bound_ratio){
					break;
			        }
			}
			if(Err_minimum<approx_error_bound_ratio){
				break;
			}
		}

		for(int i=0;i<7;i++){
			configuration_temp[i] = configuration_res[i];
		}

		for(int i=0;i<permutation_bw_num;i++){ //algorithm-2-loop-1
			configuration_temp[4] = i;

			double p1 = dist(rand_num)*1.0/1000000000;
			configuration_temp[0] = round((LFSR_num-1)*p1);

			double p2 = dist(rand_num)*1.0/1000000000;
			configuration_temp[5] = round((permutation_bs_num-1)*p2);

			two_die_vector_int LFSR_set_apply = LFSR_bit_all[configuration_temp[0]];
			one_die_vector_int NG1 = negation_set_variable[configuration_temp[2]];
			one_die_vector_int SR1 = permutation_bit_width[configuration_temp[4]];
			one_die_vector_int SR3 = permutation_input_scrambling[configuration_temp[6]];

			two_die_vector_int random_binary_number = obtain_random_binary_number(bit_width,LFSR_set_apply,NG1,SR1,SR3);

			one_die_vector_int BS = combination_set[configuration_temp[1]];
			one_die_vector_int NG_2 = negation_set_constant[configuration_temp[3]];
			one_die_vector_int SR_2 = permutation_bit_selection[configuration_temp[5]];

			two_die_vector_bit random_bit = obtain_random_bit( bit_width, LFSR_set_apply, BS, NG_2, SR_2);

			Err_temp = obtain_error( verilog_circuit, bit_width, random_binary_number, random_bit, simulation_num, fp1, Err_minimum);

			if(Err_temp<Err_minimum){
				for(int t=0;t<7;t++){
					configuration_res[t] = configuration_temp[t];
					Err_minimum = Err_temp;
					
				}
				cout<<Err_minimum<<endl;
			}
			sumulation_time++;
			if(Err_minimum<approx_error_bound_ratio){
				break;
			}
		}

		for(int i=0;i<permutation_bs_num;i++){ //algorithm-2-loop-2
			configuration_temp[5] = i;

			double p1 = dist(rand_num)*1.0/1000000000;
			configuration_temp[0] = round((LFSR_num-1)*p1);

			double p2 = dist(rand_num)*1.0/1000000000;
			configuration_temp[4] = round((permutation_bw_num-1)*p2);

			two_die_vector_int LFSR_set_apply = LFSR_bit_all[configuration_temp[0]];
			one_die_vector_int NG1 = negation_set_variable[configuration_temp[2]];
			one_die_vector_int SR1 = permutation_bit_width[configuration_temp[4]];
			one_die_vector_int SR3 = permutation_input_scrambling[configuration_temp[6]];

			two_die_vector_int random_binary_number = obtain_random_binary_number(bit_width,LFSR_set_apply,NG1,SR1,SR3);

			one_die_vector_int BS = combination_set[configuration_temp[1]];
			one_die_vector_int NG_2 = negation_set_constant[configuration_temp[3]];
			one_die_vector_int SR_2 = permutation_bit_selection[configuration_temp[5]];

			two_die_vector_bit random_bit = obtain_random_bit( bit_width, LFSR_set_apply, BS, NG_2, SR_2);

			Err_temp = obtain_error( verilog_circuit, bit_width, random_binary_number, random_bit, simulation_num, fp1, Err_minimum);

			if(Err_temp<Err_minimum){
				for(int t=0;t<7;t++){
					configuration_res[t] = configuration_temp[t];
					Err_minimum = Err_temp;
					
				}
				cout<<Err_minimum<<endl;
			}
			if(Err_minimum<approx_error_bound_ratio){
				break;
			}
			sumulation_time++;
		}


		for(int i=0;i<7;i++){
			configuration_temp[i] = configuration_res[i];
		}

		for(int i=0;i<permutation_is_num;i++){ //algorithm-3
			configuration_temp[6] = i;

			two_die_vector_int LFSR_set_apply = LFSR_bit_all[configuration_temp[0]];
			one_die_vector_int NG1 = negation_set_variable[configuration_temp[2]];
			one_die_vector_int SR1 = permutation_bit_width[configuration_temp[4]];
			one_die_vector_int SR3 = permutation_input_scrambling[configuration_temp[6]];

			two_die_vector_int random_binary_number = obtain_random_binary_number(bit_width,LFSR_set_apply,NG1,SR1,SR3);

			one_die_vector_int BS = combination_set[configuration_temp[1]];
			one_die_vector_int NG_2 = negation_set_constant[configuration_temp[3]];
			one_die_vector_int SR_2 = permutation_bit_selection[configuration_temp[5]];

			two_die_vector_bit random_bit = obtain_random_bit( bit_width, LFSR_set_apply, BS, NG_2, SR_2);

			Err_temp = obtain_error( verilog_circuit, bit_width, random_binary_number, random_bit, simulation_num, fp1, Err_minimum);

			if(Err_temp<Err_minimum){
				for(int t=0;t<7;t++){
					configuration_res[t] = configuration_temp[t];
					Err_minimum = Err_temp;					
				}
				cout<<Err_minimum<<endl;
			}
			sumulation_time++;
			if(Err_minimum<approx_error_bound_ratio){
				break;
			}
		}

		for(int i=0;i<7;i++){
			configuration_temp[i] = configuration_res[i];
		}
		cout<<Err_prev<<":"<<Err_minimum<<endl;
		if(Err_minimum>=Err_prev){
			whether_loop = false;
		}
		else{
			
			Err_prev = Err_minimum;
		}
	}

//	output_configuration( configuration_res, information_combine, negation_set_variable, negation_set_constant, bm_id_under_test, approx_error_bound_ratio);
	output_configuration( configuration_res, information_combine, negation_set_variable, negation_set_constant, bm_id_under_test, approx_error_bound_ratio,sumulation_time,Err_minimum);

	return Err_minimum;
}

void output_configuration(int configuration_res[7],three_die_vector_int information_combine,two_die_vector_int negation_set_variable,two_die_vector_int negation_set_constant,int bm_id_under_test,double approx_error_bound_ratio,int sumulation_time,double Err_minimum){
	char cmd[100];
	int err_site=0;
	strcpy(cmd, "./configuration/error_ratio");
	if(approx_error_bound_ratio==0.02){
		err_site=2;
	}
	else if(approx_error_bound_ratio==0.05){
		err_site=5;
	}
	else{
		cout << "error-output_configuration" << endl;
		exit(-1);
	}
	strcat(cmd, std::to_string(err_site).data());
	strcat(cmd, "/bm");
	strcat(cmd, std::to_string(bm_id_under_test).data());
	strcat(cmd, "/bm");
	strcat(cmd, std::to_string(bm_id_under_test).data());
	strcat(cmd, "-configuration.txt");

	//cout<<cmd<<endl;

	ofstream out(cmd);

	two_die_vector_int LFSR_set = information_combine[0];
	two_die_vector_int verilog_circuit = information_combine[1];
	two_die_vector_int permutation_bit_width = information_combine[2];
	two_die_vector_int permutation_input_scrambling = information_combine[3];
	two_die_vector_int permutation_bit_selection = information_combine[4];
	two_die_vector_int combination_set = information_combine[5];

	one_die_vector_int LFSR = LFSR_set[configuration_res[0]];
	one_die_vector_int BS = combination_set[configuration_res[1]];
	one_die_vector_int NG1 = negation_set_variable[configuration_res[2]];
	one_die_vector_int NG2 = negation_set_constant[configuration_res[3]];
	one_die_vector_int SR1 = permutation_bit_width[configuration_res[4]];
	one_die_vector_int SR2 = permutation_bit_selection[configuration_res[5]];
	one_die_vector_int SR3 = permutation_input_scrambling[configuration_res[6]];

	two_die_vector_int all_configuration;
	all_configuration.push_back(LFSR);
	all_configuration.push_back(BS);
	all_configuration.push_back(NG1);
	all_configuration.push_back(NG2);
	all_configuration.push_back(SR1);
	all_configuration.push_back(SR2);
	all_configuration.push_back(SR3);

	out<<sumulation_time<<endl;

	for(int i=0;i<all_configuration.size();i++){
		for(int j=0;j<all_configuration[i].size();j++){
			out<<all_configuration[i][j]<<",";
		}
		out<<endl;
	}
	out<<Err_minimum<<endl;
	out.close();

	return;

}

two_die_vector_int obtain_random_binary_number(int bit_width, two_die_vector_int LFSR_bit, one_die_vector_int NG_1, one_die_vector_int SR_1, one_die_vector_int SR_3){
	two_die_vector_int random_binary_number;
	one_die_vector_int new_bit_temp;
	int len_len=pow(2,bit_width)-1;

	two_die_vector_int LFSR_bit_negation;

	for(int i=0;i<len_len;i++){ //NG1
		for(int j=0;j<bit_width;j++){
			new_bit_temp.push_back(LFSR_bit[i][j]);
		}

		for(int j=0;j<NG_1.size();j++){
			new_bit_temp[NG_1[j]]=1-new_bit_temp[NG_1[j]];
		}

		LFSR_bit_negation.push_back(new_bit_temp);
		new_bit_temp.clear();
	}

	two_die_vector_int LFSR_bit_scrambling;

	for(int i=0;i<len_len;i++){ //SR1
		for(int j=0;j<bit_width;j++){
			new_bit_temp.push_back(LFSR_bit_negation[i][j]);
		}

		for(int j=0;j<SR_1.size();j++){
			new_bit_temp[j]=LFSR_bit_negation[i][SR_1[j]];
		}

		LFSR_bit_scrambling.push_back(new_bit_temp);
		new_bit_temp.clear();
	}


	one_die_vector_int binary_number = compute_binary_number_LFSR(bit_width,LFSR_bit_scrambling);

	two_die_vector_int binary_number_all;

	binary_number_all.push_back(binary_number);

	one_die_vector_int binary_number_temp;

	for(int i=0;i<SR_3.size()-1;i++){
		binary_number_temp.push_back(binary_number[len_len-1]);
		for(int j=1;j<len_len;j++){
			binary_number_temp.push_back(binary_number[j-1]);
		}
		binary_number_all.push_back(binary_number_temp);

		for(int j=0;j<len_len;j++){
			binary_number[j]=binary_number_temp[j];
		}
		binary_number_temp.clear();
	}

	/*for(int j=0;j<SR_3.size();j++){
		for(int i=0;i<pow(2,bit_width)-1;i++){
			cout<<binary_number_all[j][i]<<",";
		}
		cout<<endl;
	}*/

	for(int i=0;i<SR_3.size();i++){ //SR3
		random_binary_number.push_back(binary_number_all[SR_3[i]]);
	}

	/*for(int j=0;j<SR_3.size();j++){
		for(int i=0;i<pow(2,bit_width)-1;i++){
			cout<<random_binary_number[j][i]<<",";
		}
		cout<<endl;
	}*/

	return random_binary_number;
}

two_die_vector_bit obtain_random_bit(int bit_width, two_die_vector_int LFSR_bit, one_die_vector_int BS, one_die_vector_int NG_2, one_die_vector_int SR_2){
	int len_len = pow(2, bit_width)-1;
	two_die_vector_int LFSR_bit_selection_negation;
	one_die_vector_int bit_temp;

	for(int i=0;i<BS.size();i++){ //Bit selection
		for(int j=0;j<len_len;j++){
			bit_temp.push_back(LFSR_bit[j][BS[i]]);
		}
		LFSR_bit_selection_negation.push_back(bit_temp);
		bit_temp.clear();
	}

	for(int i=0;i<NG_2.size();i++){ //NG_2
		for(int j=0;j<len_len;j++){
			LFSR_bit_selection_negation[NG_2[i]][j] = 1-LFSR_bit_selection_negation[NG_2[i]][j];
		}
	}

	two_die_vector_int LFSR_bit_scrambling;

	for(int i=0;i<SR_2.size();i++){ //SR_2
		for(int j=0;j<len_len;j++){
			bit_temp.push_back(LFSR_bit_selection_negation[SR_2[i]][j]);
		}
		LFSR_bit_scrambling.push_back(bit_temp);
		bit_temp.clear();
	}

	/*for(int i=0;i<SR_2.size();i++)
	{
		for(int j=0;j<len_len;j++)
		{
			cout<<j<<"-"<<LFSR_bit_scrambling[i][j]<<" ";
		}
		cout<<endl;
	}*/

	two_die_vector_bit random_bit;
	one_die_vector_bit SN;

	uint64_t bit;

	for(int i=0;i<SR_2.size();i++){
		for(int j=0;j<len_len;j++){
			if(LFSR_bit_scrambling[i][j]==1){
				bit |= (1ULL << (j%64));
			}
			else{
				bit &= (~(1ULL<<(j%64)));
			}

			if(j%64==63 || j == len_len-1){
				if(j == len_len-1){
					bit &= (~(1ULL<<(len_len%64)));
				}

				SN.push_back(bit);
				//cout<< bit<<endl;
			}
		}
		random_bit.push_back(SN);
		SN.clear();
	}

	/*two_die_vector_int temp_all;
	one_die_vector_int temp;

	for(int i=0;i<SR_2.size();i++){
		for(int j=0;j<len_len;j++){
			if(((random_bit[i][j/64]>>(j%64))&1ULL)==1){
				temp.push_back(1);
				//cout<<j<<"-1"<<" ";
			}
			else{
				temp.push_back(0);
				//cout<<j<<"-0"<<" ";
			}
		}
		temp_all.push_back(temp);
		temp.clear();
		//cout<<endl;
	}*/

	/*for(int i=0;i<SR_2.size();i++){
		for(int j=0;j<len_len;j++){
			if(temp_all[i][j]!=LFSR_bit_scrambling[i][j]){
				cout<<temp_all[i][j]<<":"<<LFSR_bit_scrambling[i][j]<<endl;
				cout<<"error"<<i<<":"<<j<<endl;
				//exit(-1);
			}
		}
	}*/

	return random_bit;
}

two_die_vector_bit obtain_input_bit(int bit_width, two_die_vector_bit random_bit, two_die_vector_int random_binary_number, double x){
	int len_len = pow(2,bit_width)-1;
	int input_X = round(x*len_len);

	//cout<<input_X<<endl;

	uint64_t bit;
	two_die_vector_bit input_bit;
	one_die_vector_bit SN;

	for(int i=0;i<random_binary_number.size();i++){
		for(int j=0;j<len_len;j++){
			if(random_binary_number[i][j]<input_X){
				bit |= (1ULL << (j%64));
			}
			else{
				bit &= (~(1ULL<<(j%64)));
			}
			if(j%64==63 || j == len_len-1){
				if(j == len_len-1){
					bit &= (~(1ULL<<(len_len%64)));
				}

				SN.push_back(bit);
			}
		}
		input_bit.push_back(SN);
		SN.clear();
	}

	for(int i=0;i<random_bit.size();i++){
		input_bit.push_back(random_bit[i]);
	}

	/*int count = 0;
	//cout<<"input_X:"<<input_X<<endl;
	if(x==0.006){
		cout<<"input_X:"<<input_X<<endl;
	for(int i=0;i<input_bit.size();i++){
		for(int j=0;j<len_len;j++){
			if(((input_bit[i][j/64]>>(j%64))&1ULL)==1){
				count++;
				cout<<j<<"-1 ";
			}
			else{
				cout<<j<<"-0 ";
			}
		}
		cout<<endl;

		//exit(-1);

		cout<< count<<endl;
		count=0;
	}
	exit(-1);
	}*/

	return input_bit;
}

double obtain_error(two_die_vector_int verilog_circuit, int bit_width, two_die_vector_int random_binary_number, two_die_vector_bit random_bit, int simulation_num, double(*fp1)(double),double Err_minimum){

	double error = 0;
	double x[simulation_num];
	int len_len = pow(2,bit_width)-1;

	for(int i=0;i<simulation_num;i++){
		x[i] = 1.0/simulation_num*(i+1);

		//cout<<x[i]<<" ";
	}
	//cout<<endl;

	uint64_t bit;
	one_die_vector_bit bit_temp;
	two_die_vector_bit bit_all;

	for(int i=0;i<ceil(len_len*1.0/64);i++){
		bit_temp.push_back(bit);
	}

	for(int i=0;i<random_bit.size()+verilog_circuit.size()+random_binary_number.size();i++){
		bit_all.push_back(bit_temp);
	}

	bit_temp.clear();

	two_die_vector_bit gate_input_bit;

	double Err_upper = pow(Err_minimum,2) * simulation_num;

	for(int i=0;i<simulation_num;i++){
		two_die_vector_bit input_bit = obtain_input_bit( bit_width,  random_bit,  random_binary_number, x[i]);

		for(int j=0;j<input_bit.size();j++){
			for(int k=0;k<input_bit[j].size();k++){
				bit_all[j][k]=input_bit[j][k];
			}
		}

		for(int j=0;j<verilog_circuit.size();j++){
			for(int k=1;k<verilog_circuit[j].size()-1;k++){
				for(int l=0;l<bit_all[verilog_circuit[j][k]].size();l++){
					bit_temp.push_back(bit_all[verilog_circuit[j][k]][l]);
				}
				gate_input_bit.push_back(bit_temp);
				bit_temp.clear();
			}

			int gate = verilog_circuit[j][0];
			one_die_vector_bit gate_output_bit;

			//cout<<i<<gate<<endl;

			switch(gate){
			case 0:
				gate_output_bit = inv1( len_len, gate_input_bit);
				break;
			case 1:
				gate_output_bit = inv2( len_len, gate_input_bit);
				break;
			case 2:
				gate_output_bit = inv3( len_len, gate_input_bit);
				break;
			case 3:
				gate_output_bit = inv4( len_len, gate_input_bit);
				break;
			case 4:
				gate_output_bit = nand2( len_len, gate_input_bit);
				break;
			case 5:
				gate_output_bit = nand3( len_len, gate_input_bit);
				break;
			case 6:
				gate_output_bit = nand4( len_len, gate_input_bit);
				break;
			case 7:
				gate_output_bit = nor2( len_len, gate_input_bit);
				break;
			case 8:
				gate_output_bit = nor3( len_len, gate_input_bit);
				break;
			case 9:
				gate_output_bit = nor4( len_len, gate_input_bit);
				break;
			case 10:
				gate_output_bit = and2( len_len, gate_input_bit);
				break;
			case 11:
				gate_output_bit = or2( len_len, gate_input_bit);
				break;
			case 12:
				gate_output_bit = xor2( len_len, gate_input_bit);
				break;
			case 13:
				gate_output_bit = xor2b( len_len, gate_input_bit);
				break;
			case 14:
				gate_output_bit = xnor2( len_len, gate_input_bit);
				break;
			case 15:
				gate_output_bit = xnor2b( len_len, gate_input_bit);
				break;
			case 16:
				gate_output_bit = aoi21( len_len, gate_input_bit);
				break;
			case 17:
				gate_output_bit = aoi22( len_len, gate_input_bit);
				break;
			case 18:
				gate_output_bit = oai21( len_len, gate_input_bit);
				break;
			case 19:
				gate_output_bit = oai22( len_len, gate_input_bit);
				break;
			case 20:
				gate_output_bit = buf1( len_len, gate_input_bit);
				break;
			case 21:
				gate_output_bit = zero( len_len, gate_input_bit);
				break;
			case 22:
				gate_output_bit = one( len_len, gate_input_bit);
				break;

			default:
			    cout<<"error in obtaining error"<<endl;
				exit(-1);
				break;
			}

			//cout<<"bit"<<gate_output_bit.size()<<endl;
			//cout<<verilog_circuit[j][verilog_circuit[j].size()-1]<<endl;
			//cout<<bit_all.size()<<endl;
			for(int k=0;k<gate_output_bit.size();k++){
				bit_all[verilog_circuit[j][verilog_circuit[j].size()-1]][k]=gate_output_bit[k];
			}
			gate_input_bit.clear();

			//cout<<"bit_finish"<<endl;
		}

		int count = 0;
		for(int j=0;j<len_len;j++){
			if(((bit_all[random_bit.size()+random_binary_number.size()][j/64]>>(j%64))&1ULL)==1){
				count++;
			}
		}

		//cout<<count<<endl;



		double circuit_output = count*1.0/(len_len+1);

		//cout<<x[i]<<"-"<<circuit_output<<endl;

		double accurate_output = (*fp1)(x[i]);

		error = error + pow(circuit_output-accurate_output,2);

		if(error>Err_upper){
			return 100.0;
		}

		/*if(i==5){
			cout<<x[i]<<":"<<count<<":"<<circuit_output<<endl;
		}*/

		//exit(-1);

		//cout<< count<<endl;
	}

	//cout<<endl;

	double result = sqrt(error / double(simulation_num));

	/*cout<<result<<endl;

	exit(-1);	*/

	//double x=0.1;

	//two_die_vector_bit input_bit = obtain_input_bit( bit_width,  random_bit,  random_binary_number, x);

	return result;
}

void function_check(){ //check whether the gate functions are correct
	int bit_width = 4;
	one_die_vector_int given_set_1;
	two_die_vector_int negation_set_variable;
	one_die_vector_int one_die_temp;
	two_die_vector_int two_die_temp;

	for(int i=0;i<bit_width;i++){
		given_set_1.push_back(i);
	}

	negation_set_variable.push_back(one_die_temp);

    for(int i=1;i<=bit_width;i++){
		 two_die_temp = obtain_combination_n_k( bit_width, i,  given_set_1);

		 for(int j=0;j<two_die_temp.size();j++){
			 negation_set_variable.push_back(two_die_temp[j]);
		 }

		 two_die_temp.clear();
	}

	two_die_vector_int input_int;

	for(int j=0;j<bit_width;j++){
		one_die_temp.push_back(0);
	}

	for(int i=0;i<negation_set_variable.size();i++){
		input_int.push_back(one_die_temp);
		for(int j=0;j<negation_set_variable[i].size();j++){
			input_int[i][negation_set_variable[i][j]] = 1;
		}
	}

	two_die_vector_bit gate_input_bit;
    one_die_vector_bit input_temp;
	uint64_t bit;

	for(int i=0;i<bit_width;i++){
		for(int j=0;j<negation_set_variable.size();j++){
			if(input_int[j][i]==1){
				bit |= (1ULL << (j%64));
			}
			else{
				bit &= (~(1ULL<<(j%64)));
			}
		}
		input_temp.push_back(bit);
		gate_input_bit.push_back(input_temp);
		input_temp.clear();
	}

	int len_len = negation_set_variable.size();

	one_die_vector_bit output_bit = one( len_len, gate_input_bit);

	for(int i=0;i<1;i++){
		cout<<"input-"<<i<<": ";
		for(int j=0;j<negation_set_variable.size();j++){
			if(((gate_input_bit[i][j/64]>>(j%64))&1ULL)==1){
				cout<<"1"<<" ";
			}
			else{
				cout<<"0"<<" ";
			}
		}
		cout<<endl;
	}

	cout<<"output"<<" : ";
	for(int j=0;j<negation_set_variable.size();j++){
		//cout<<"here"<<output_bit[0]<<endl;
		if(((output_bit[j/64]>>(j%64))&1ULL)==1){
			cout<<"1"<<" ";
		}
		else{
			cout<<"0"<<" ";
		}
	}
	cout<<endl;

	return;
}

one_die_vector_bit inv1(int len_len, two_die_vector_bit gate_input_bit){ //GATE inv1	1	O=!a;		PIN * INV 1 999 0.9 0.3 0.9 0.3 right
	one_die_vector_bit gate_out_bit;
	uint64_t bit;
	for(int i=0;i<ceil(len_len*1.0/64);i++){
		bit = ~ gate_input_bit[0][i];
		gate_out_bit.push_back(bit);
	}
	return gate_out_bit;
}

one_die_vector_bit inv2(int len_len, two_die_vector_bit gate_input_bit){ //GATE inv2	2	O=!a;		PIN * INV 2 999 1.0 0.1 1.0 0.1 right
	one_die_vector_bit gate_out_bit;
	uint64_t bit;
	for(int i=0;i<ceil(len_len*1.0/64);i++){
		bit = ~ gate_input_bit[0][i];
		gate_out_bit.push_back(bit);
	}
	return gate_out_bit;
}

one_die_vector_bit inv3(int len_len, two_die_vector_bit gate_input_bit){ //GATE inv3	3	O=!a;		PIN * INV 3 999 1.1 0.09 1.1 0.09 right
	one_die_vector_bit gate_out_bit;
	uint64_t bit;
	for(int i=0;i<ceil(len_len*1.0/64);i++){
		bit = ~ gate_input_bit[0][i];
		gate_out_bit.push_back(bit);
	}
	return gate_out_bit;
}

one_die_vector_bit inv4(int len_len, two_die_vector_bit gate_input_bit){ //GATE inv4	4	O=!a;		PIN * INV 4 999 1.2 0.07 1.2 0.07 right
	one_die_vector_bit gate_out_bit;
	uint64_t bit;
	for(int i=0;i<ceil(len_len*1.0/64);i++){
		bit = ~ gate_input_bit[0][i];
		gate_out_bit.push_back(bit);
	}
	return gate_out_bit;
}

one_die_vector_bit nand2(int len_len, two_die_vector_bit gate_input_bit){ //GATE nand2	2	O=!(a*b);	PIN * INV 1 999 1.0 0.2 1.0 0.2 right
	one_die_vector_bit gate_out_bit;
	uint64_t bit;
	for(int i=0;i<ceil(len_len*1.0/64);i++){
		bit = ~ (gate_input_bit[0][i] & gate_input_bit[1][i]);
		gate_out_bit.push_back(bit);
	}
	return gate_out_bit;
}

one_die_vector_bit nand3(int len_len, two_die_vector_bit gate_input_bit){ //GATE nand3	3	O=!(a*b*c);	PIN * INV 1 999 1.1 0.3 1.1 0.3 right
	one_die_vector_bit gate_out_bit;
	uint64_t bit;
	for(int i=0;i<ceil(len_len*1.0/64);i++){
		bit = ~ (gate_input_bit[0][i] & gate_input_bit[1][i] & gate_input_bit[2][i]);
		gate_out_bit.push_back(bit);
	}
	return gate_out_bit;
}

one_die_vector_bit nand4(int len_len, two_die_vector_bit gate_input_bit){ //GATE nand4 	4	O=!(a*b*c*d);	PIN * INV 1 999 1.4 0.4 1.4 0.4 right
	one_die_vector_bit gate_out_bit;
	uint64_t bit;
	for(int i=0;i<ceil(len_len*1.0/64);i++){
		bit = ~ (gate_input_bit[0][i] & gate_input_bit[1][i] & gate_input_bit[2][i] & gate_input_bit[3][i]);
		gate_out_bit.push_back(bit);
	}
	return gate_out_bit;
}

one_die_vector_bit nor2(int len_len, two_die_vector_bit gate_input_bit){ //GATE nor2	2	O=!(a+b);	PIN * INV 1 999 1.4 0.5 1.4 0.5 right
	one_die_vector_bit gate_out_bit;
	uint64_t bit;
	for(int i=0;i<ceil(len_len*1.0/64);i++){
		bit = ~ (gate_input_bit[0][i] | gate_input_bit[1][i]);
		gate_out_bit.push_back(bit);
	}
	return gate_out_bit;
}

one_die_vector_bit nor3(int len_len, two_die_vector_bit gate_input_bit){ //GATE nor3	3	O=!(a+b+c);	PIN * INV 1 999 2.4 0.7 2.4 0.7 right
	one_die_vector_bit gate_out_bit;
	uint64_t bit;
	for(int i=0;i<ceil(len_len*1.0/64);i++){
		bit = ~ (gate_input_bit[0][i] | gate_input_bit[1][i] | gate_input_bit[2][i]);
		gate_out_bit.push_back(bit);
	}
	return gate_out_bit;
}

one_die_vector_bit nor4(int len_len, two_die_vector_bit gate_input_bit){ //GATE nor4	4	O=!(a+b+c+d);	PIN * INV 1 999 3.8 1.0 3.8 1.0 right
	one_die_vector_bit gate_out_bit;
	uint64_t bit;
	for(int i=0;i<ceil(len_len*1.0/64);i++){
		bit = ~ (gate_input_bit[0][i] | gate_input_bit[1][i] | gate_input_bit[2][i] | gate_input_bit[3][i]);
		gate_out_bit.push_back(bit);
	}
	return gate_out_bit;
}

one_die_vector_bit and2(int len_len, two_die_vector_bit gate_input_bit){ //GATE and2	3	O=a*b;		PIN * NONINV 1 999 1.9 0.3 1.9 0.3 right
	one_die_vector_bit gate_out_bit;
	uint64_t bit;
	for(int i=0;i<ceil(len_len*1.0/64);i++){
		bit = gate_input_bit[0][i] & gate_input_bit[1][i];
		gate_out_bit.push_back(bit);
	}
	return gate_out_bit;
}

one_die_vector_bit or2(int len_len, two_die_vector_bit gate_input_bit){ //GATE or2	3	O=a+b;		PIN * NONINV 1 999 2.4 0.3 2.4 0.3 right
	one_die_vector_bit gate_out_bit;
	uint64_t bit;
	for(int i=0;i<ceil(len_len*1.0/64);i++){
		bit = gate_input_bit[0][i] | gate_input_bit[1][i];
		gate_out_bit.push_back(bit);
	}
	return gate_out_bit;
}

one_die_vector_bit xor2(int len_len, two_die_vector_bit gate_input_bit){ //GATE xor2	5	O=a*!b+!a*b;	PIN * UNKNOWN 2 999 1.9 0.5 1.9 0.5 right
	one_die_vector_bit gate_out_bit;
	uint64_t bit;
	for(int i=0;i<ceil(len_len*1.0/64);i++){
		bit = (gate_input_bit[0][i] & (~ gate_input_bit[1][i])) | ((~ gate_input_bit[0][i]) &  gate_input_bit[1][i]);
		gate_out_bit.push_back(bit);
	}
	return gate_out_bit;
}

one_die_vector_bit xor2b(int len_len, two_die_vector_bit gate_input_bit){ //GATE xor2b	5	O=!(a*b+!a*!b);	PIN * UNKNOWN 2 999 1.9 0.5 1.9 0.5 right
	one_die_vector_bit gate_out_bit;
	uint64_t bit;
	for(int i=0;i<ceil(len_len*1.0/64);i++){
		bit = ~ ((gate_input_bit[0][i] & gate_input_bit[1][i]) | ((~ gate_input_bit[0][i]) &  (~ gate_input_bit[1][i])));
		gate_out_bit.push_back(bit);
	}
	return gate_out_bit;
}

one_die_vector_bit xnor2(int len_len, two_die_vector_bit gate_input_bit){ //GATE xnor2	5	O=a*b+!a*!b;	PIN * UNKNOWN 2 999 2.1 0.5 2.1 0.5 right
	one_die_vector_bit gate_out_bit;
	uint64_t bit;
	for(int i=0;i<ceil(len_len*1.0/64);i++){
		bit = (gate_input_bit[0][i] & gate_input_bit[1][i]) | ((~ gate_input_bit[0][i]) &  (~ gate_input_bit[1][i]));
		gate_out_bit.push_back(bit);
	}
	return gate_out_bit;
}

one_die_vector_bit xnor2b(int len_len, two_die_vector_bit gate_input_bit){ //GATE xnor2b	5	O=!(!a*b+a*!b);	PIN * UNKNOWN 2 999 2.1 0.5 2.1 0.5 right
	one_die_vector_bit gate_out_bit;
	uint64_t bit;
	for(int i=0;i<ceil(len_len*1.0/64);i++){
		bit = ~ ( ((~ gate_input_bit[0][i]) &  gate_input_bit[1][i]) | (gate_input_bit[0][i] & (~ gate_input_bit[1][i])) );
		gate_out_bit.push_back(bit);
	}
	return gate_out_bit;
}

one_die_vector_bit aoi21(int len_len, two_die_vector_bit gate_input_bit){ //GATE aoi21	3	O=!(a*b+c);	PIN * INV 1 999 1.6 0.4 1.6 0.4 right
	one_die_vector_bit gate_out_bit;
	uint64_t bit;
	for(int i=0;i<ceil(len_len*1.0/64);i++){
		bit = ~ (( gate_input_bit[0][i] &  gate_input_bit[1][i] ) | gate_input_bit[2][i] );
		gate_out_bit.push_back(bit);
	}
	return gate_out_bit;
}

one_die_vector_bit aoi22(int len_len, two_die_vector_bit gate_input_bit){ //GATE aoi22	4	O=!(a*b+c*d);	PIN * INV 1 999 2.0 0.4 2.0 0.4 right
	one_die_vector_bit gate_out_bit;
	uint64_t bit;
	for(int i=0;i<ceil(len_len*1.0/64);i++){
		bit = ~ ( ( gate_input_bit[0][i] &  gate_input_bit[1][i] ) | (gate_input_bit[2][i] & gate_input_bit[3][i]) );
		gate_out_bit.push_back(bit);
	}
	return gate_out_bit;
}

one_die_vector_bit oai21(int len_len, two_die_vector_bit gate_input_bit){ //GATE oai21	3	O=!((a+b)*c);	PIN * INV 1 999 1.6 0.4 1.6 0.4 right
	one_die_vector_bit gate_out_bit;
	uint64_t bit;
	for(int i=0;i<ceil(len_len*1.0/64);i++){
		bit = ~ (( gate_input_bit[0][i] |  gate_input_bit[1][i] ) & gate_input_bit[2][i] );
		gate_out_bit.push_back(bit);
	}
	return gate_out_bit;
}

one_die_vector_bit oai22(int len_len, two_die_vector_bit gate_input_bit){ //GATE oai22	4	O=!((a+b)*(c+d)); PIN * INV 1 999 2.0 0.4 2.0 0.4 right
	one_die_vector_bit gate_out_bit;
	uint64_t bit;
	for(int i=0;i<ceil(len_len*1.0/64);i++){
		bit = ~ ( ( gate_input_bit[0][i] |  gate_input_bit[1][i] ) & (gate_input_bit[2][i] | gate_input_bit[3][i]) );
		gate_out_bit.push_back(bit);
	}
	return gate_out_bit;
}

one_die_vector_bit buf1(int len_len, two_die_vector_bit gate_input_bit){ //GATE buf        1       O=a;            PIN * NONINV 1 999 1.0 0.0 1.0 0.0 right
	one_die_vector_bit gate_out_bit;
	uint64_t bit;
	one_die_vector_int temp;

	for(int j=0;j<len_len;j++){
		if(((gate_input_bit[0][j*1.0/64]>>(j%64))&1ULL)==1){
			temp.push_back(1);
		}
		else{
			temp.push_back(0);
		}
	}

	one_die_vector_int temp_shift;

	temp_shift.push_back(temp[len_len-1]);

	for(int i=0;i<len_len-1;i++){
		temp_shift.push_back(temp[i]);
	}

	for(int j=0;j<len_len;j++){
		if(temp_shift[j]==1){
			bit |= (1ULL << (j%64));
		}
		else{
			bit &= (~(1ULL<<(j%64)));
		}

		if(j%64==63 || j == len_len-1){
			if(j == len_len-1){
				bit &= (~(1ULL<<(len_len%64)));
			}

			gate_out_bit.push_back(bit);
				//cout<< bit<<endl;
		}
	}
	return gate_out_bit;
}

one_die_vector_bit zero(int len_len, two_die_vector_bit gate_input_bit){ //GATE zero	0	O=CONST0; right
	one_die_vector_bit gate_out_bit;
	uint64_t bit;
	for(int i=0;i<ceil(len_len*1.0/64);i++){
		for(int j=0;j<64;j++){
			bit &= (~(1ULL<<(j%64)));
		}
		gate_out_bit.push_back(bit);
	}
	return gate_out_bit;
}

one_die_vector_bit one(int len_len, two_die_vector_bit gate_input_bit){ //GATE one	0	O=CONST1; right
	one_die_vector_bit gate_out_bit;
	uint64_t bit;
	for(int i=0;i<ceil(len_len*1.0/64);i++){
		for(int j=0;j<64;j++){
			bit |= (1ULL << (j%64));
		}
		gate_out_bit.push_back(bit);
	}
	return gate_out_bit;
}

double bm1_target_funcs(double x) {
     return sin(x);
}

double bm2_target_funcs(double x) {
    return cos(x);
}

double bm3_target_funcs(double x) {
    return tanh(x);
}

double bm4_target_funcs(double x) {
    return exp(-x);
}

double bm5_target_funcs(double x) {
    return log(x + 1);
}

double bm6_target_funcs(double x) {
    return pow(x, 2.2);
}

double bm7_target_funcs(double x) {
    return sin(PI * x) / PI;
}

double bm8_target_funcs(double x) {
    return exp(-2 * x);
}
double bm9_target_funcs(double x) {
    return 1 / (1 + x);
}

double bm10_target_funcs(double x) {
    return tanh(PI * x);
}

double bm11_target_funcs(double x) {
    return pow(x, 0.45);
}

double bm12_target_funcs(double x) {
    return sqrt(x);
}

double bm13_target_funcs(double x) {
    return tan(x/2);
}

double bm14_target_funcs(double x) {
    return x*log(x/2)+1;
}

double bm15_target_funcs(double x) {
    return 1 / (1 + exp(-1 * x));
}

