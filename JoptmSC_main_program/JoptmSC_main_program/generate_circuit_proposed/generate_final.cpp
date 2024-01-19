#include "generate_final.h"
#include <chrono>
#include<time.h> 

//#include<boost/random.hpp>
//using  namespace  boost; 

#define PI 3.141592654


using namespace std;

int main(){
	std::ios::sync_with_stdio(false);  // Speed IO
        std::cin.tie(0);
        time_t now = time(NULL);
	tm* tm_t = localtime(&now);
	
        //int bm_id_under_test = 2;
        double approx_error_bound_ratio = 0.02;
        int bit_width = 8;
        
        char log_filename[100];
    	strcpy(log_filename, "log_");
    	strcat(log_filename, std::to_string(approx_error_bound_ratio).data());
    	strcat(log_filename, ".txt");
    	ofstream out;
    	out.open(log_filename);
        
        for(int bm_id_under_test=1;bm_id_under_test<2;bm_id_under_test++){
        	if(bm_id_under_test>5 && bm_id_under_test<15){
        		continue;
        	}
        	out<<"begin generate circuit-"<<to_string(bm_id_under_test)<<endl;
        //two_die_vector_int ADP_two = read_ADP(bm_id_under_test);
        //two_die_vector_double error_all = read_error(bm_id_under_test);
        	two_die_vector_int permutation_bit_width = obtain_permutation_all( bit_width);
        
        	int pds = -1;
        	int degree = -1;
        	int adp_res = 1000000000;
        	int optimal_circuit = 0;
        
        	two_die_vector_int LFSR_set = obtain_LFSR_polynomial(bit_width);
        	two_die_vector_char gate_all = read_library();
		one_die_vector_int circuit_information = obtain_circuit_information( bm_id_under_test, approx_error_bound_ratio);
        
        /*one_die_vector_int configuration_all;
        for(int i=0;i<10;i++){
        	configuration_all.push_back(i);
        }
        
        pds = 10;
        degree = 5;
        two_die_vector_int circuit_information;
        one_die_vector_int circuit_information_temp;
        
        for(int i=0;i<23;i++){
        	circuit_information_temp.clear();
        	circuit_information_temp.push_back(i);
        	for(int j=0;j<5;j++){
        		circuit_information_temp.push_back(j);
        	}
        	circuit_information.push_back(circuit_information_temp);
        }
        circuit_information_temp.clear();
        circuit_information_temp.push_back(20);
        circuit_information_temp.push_back(0);
        circuit_information_temp.push_back(2);
        circuit_information.push_back(circuit_information_temp);
        
        int precision = pds - degree;
        one_die_vector_int given_set;
        for(int i=0;i<bit_width;i++){
        	given_set.push_back(i);
        }
        
        two_die_vector_int BS_all = obtain_combination_n_k(bit_width, precision, given_set);
        
        write_verilog_circuit(configuration_all, circuit_information, pds, degree, BS_all, error_bound, bm_id_under_test, permutation_bit_width, LFSR_set, bit_width);
        write_verilog_testbench(configuration_all, circuit_information, pds, degree, BS_all, error_bound, bm_id_under_test, permutation_bit_width, LFSR_set, bit_width);
        
        exit(-1);*/
        
        //for(int i=3;i<9;i++){
        //	for(int j=1;j<i;j++){
        //		if(adp_res>ADP_two[i-3][j-1] && error_all[i-3][j-1]<=error_bound){
        //			pds = i;
        //			degree = j;
        //			adp_res = ADP_two[i-3][j-1];
        //		}
        //	}
        //}
        
        
         
		pds = circuit_information[0] + circuit_information[1];
		degree = circuit_information[0];
        	two_die_vector_int LFSR_output_1 = obtain_output_LFSR( LFSR_set, bit_width, 0);
        //two_die_vector_int LFSR_output_2 = obtain_output_LFSR( LFSR_set, bit_width, configuration_all[7]);

		two_die_vector_int verilog_circuit = read_verilog(bm_id_under_test,approx_error_bound_ratio,circuit_information[2],gate_all);
		two_die_vector_int configuration_all = read_confuration(bm_id_under_test, approx_error_bound_ratio);  
        //two_die_vector_int circuit_information = read_verilog( bm_id_under_test, error_bound, optimal_circuit, gate_all, pds, degree);

		//circuit_information.pop_back();
        
        	int precision = pds - degree;
        	
        	one_die_vector_int given_set;
        	for(int i=0;i<bit_width;i++){
        		given_set.push_back(i);
        	}
        
        	two_die_vector_int BS_all = obtain_combination_n_k(bit_width, precision, given_set);
        	//cout<<precision<<":"<<pds<<":"<<degree<<endl;
        
        	write_verilog_circuit(configuration_all, verilog_circuit, pds, degree, BS_all, approx_error_bound_ratio, bm_id_under_test, permutation_bit_width, LFSR_set, bit_width);
        	write_verilog_testbench(configuration_all, verilog_circuit, pds, degree, BS_all, approx_error_bound_ratio, bm_id_under_test, permutation_bit_width, LFSR_set, LFSR_output_1, bit_width);
        	std::stringstream ss;
	ss << "year:" << tm_t->tm_year + 1900 << " month:" << tm_t->tm_mon + 1 << " day:" << tm_t->tm_mday
		<< " hour:" << tm_t->tm_hour << " minute:" << tm_t->tm_min << " second:" << tm_t->tm_sec;


		//out<<"cost time"<<to_string(milliseconds1)<<"milliseconds"<<endl;
		//out<<"Accuracy (MAE)"<<to_string(err_min)<<endl;
		out<<ss.str()<<endl;
		out<<"finish generate circuit "<<to_string(bm_id_under_test)<<endl;
        }
        
        return 0;
}

void write_verilog_circuit(two_die_vector_int configuration_all, two_die_vector_int circuit_information, int pds, int degree, two_die_vector_int BS_all, double error_bound, int bm_id_under_test, two_die_vector_int permutation_bit_width, two_die_vector_int LFSR_set,int bit_width){
	int precision = pds - degree;
	string filename = "verilog_proposed";
	mkdir(filename.c_str(),S_IRWXU);
	filename = filename + "/" + to_string(int(10000*error_bound));
	mkdir(filename.c_str(),S_IRWXU);
	filename = filename + "/" + to_string(bm_id_under_test);
	//mkdir(filename.c_str());
	//filename = filename + "/" + to_string(pds) + "_" + to_string(degree);
	mkdir(filename.c_str(),S_IRWXU);
	rm_dir(filename.c_str());
	mkdir(filename.c_str(),S_IRWXU);
	
	filename = filename + "/" + "circuit.v";
	
	int buf_num = 0;
	for(int i=0;i<circuit_information.size();i++){
		if(circuit_information[i][0]==20){
			buf_num++;
		}
	}
	
	ofstream fout;
	fout.open(filename.c_str());
	if(!fout)
        {
            cout<<filename<<endl;
            cout<<"cannot open the filename_verilog_circuit"<<endl;
            exit(-1);
        }
        
        fout<<"module circuit(clk,rst_n,input_s,input_b,output_s,output_circuit";
        
        for(int i=0;i<degree-1;i++){
        	fout<<",in_x_"<<to_string(i+1);
        }
		if(buf_num>0){
			for(int i=0;i<buf_num;i++){
        		fout<<",in_buf_x_"<<to_string(i);
        	}
			for(int i=0;i<degree-1;i++){
        		fout<<",out_x_"<<to_string(i+1);
        	}
			for(int i=0;i<buf_num-1;i++){
        		fout<<",out_buf_x_"<<to_string(i);
        	}
        	fout<<",out_buf_x_"<<to_string(buf_num-1)<<");"<<endl;
		}
		else{

			for(int i=0;i<degree-1;i++){
        		fout<<",out_x_"<<to_string(i+1);
        	}
			//fout<<"out_x_"<<to_string(degree-1);
			fout<<");"<<endl;
		}        
        
        
        
    fout<<"  input clk;"<<endl;
	fout<<"  input rst_n;"<<endl;
	fout<<"  input["<<to_string(bit_width-1)<<":0] input_s;"<<endl;
	fout<<"  input["<<to_string(bit_width-1)<<":0] input_b;"<<endl;
	//fout<<"  input["<<to_string(bit_width-1)<<":0] input_circuit;"<<endl;
	for(int i=0;i<degree-1;i++){
        	fout<<"  input in_x_"<<to_string(i+1)<<";"<<endl;
        }
        for(int i=0;i<buf_num;i++){
        	fout<<"  input in_buf_x_"<<to_string(i)<<";"<<endl;
        }
	fout<<"  output["<<to_string(bit_width-1)<<":0] output_s;"<<endl;
	fout<<"  output output_circuit;"<<endl;
	for(int i=0;i<degree-1;i++){
        	fout<<"  output out_x_"<<to_string(i+1)<<";"<<endl;
        }
        for(int i=0;i<buf_num;i++){
        	fout<<"  output out_buf_x_"<<to_string(i)<<";"<<endl;
        }
	//fout<<"  output output_b;"<<endl;
	fout<<endl;
	
	fout<<"  reg["<<to_string(bit_width-1)<<":0] output_temp_s;"<<endl;
	
	for(int i=0;i<buf_num;i++){
        	fout<<"  reg output_temp_buf_"<<to_string(i)<<";"<<endl;
        }
	
	for(int i=0;i<degree-1;i++){
        	fout<<"  reg out_temp_x_"<<to_string(i+1)<<";"<<endl;
        }
        
        //fout<<"  wire x0;"<<endl;
        for(int i=0;i<pds+circuit_information.size();i++){
        	fout<<"  wire x"<<to_string(i)<<";"<<endl;
        }
	//fout<<"  reg["<<to_string(bit_width-1)<<":0] output_circuit_temp;"<<endl;
	fout<<"  wire["<<to_string(bit_width-1)<<":0] comparator_binary_numer;"<<endl;
	for(int i=0;i<degree;i++){
		fout<<"  wire x_temp_"<<to_string(i)<<";"<<endl;
	}
	
	fout<<"  assign output_s["<<to_string(bit_width-1)<<":0] = output_temp_s["<<to_string(bit_width-1)<<":0];"<<endl;	
	//fout<<"  assign output_l["<<to_string(bit_width-1)<<":0] = output_temp_l["<<to_string(bit_width-1)<<":0];"<<endl;
	fout<<"  assign output_circuit = x"<<to_string(pds)<<";"<<endl;
	//fout<<"  assign x_temp_0 = ;"<<endl;
	for(int i=0;i<degree-1;i++){
		fout<<"  assign x_temp_"<<to_string(i+1)<<" = in_x_"<<to_string(i+1)<<";"<<endl;
	}
	for(int i=0;i<degree-1;i++){
        	fout<<"  assign out_x_"<<to_string(i+1)<<" = out_temp_x_"<<to_string(i+1)<<";"<<endl;
        }
        for(int i=0;i<buf_num;i++){
        	fout<<"  assign out_buf_x_"<<to_string(i)<<" = output_temp_buf_"<<to_string(i)<<";"<<endl;
        }
	
	fout<<endl;
	
	int len_len=pow(2,bit_width)-1;
	int temp[bit_width]={0};
	temp[bit_width-1]=1;

	int non_zero_num=0;

	for(int i=0;i<bit_width;i++){
		if(configuration_all[0][i]==0){
			break;
		}
		non_zero_num++;
	}		
	
	fout<<"  always@(posedge clk)"<<endl;
	fout<<"  begin"<<endl;
	fout<<"    if(!rst_n)"<<endl;
	fout<<"      begin"<<endl;
	for(int i=0;i<bit_width-1;i++){
	    fout<<"        output_temp_s["<<to_string(i)<<"]<=input_s["<<to_string(i+1)<<"];"<<endl;
	}
	fout<<"        output_temp_s["<<to_string(bit_width-1)<<"]<=";
	for(int i=0;i<non_zero_num-2;i++){
	    fout<<"(";
	}
	fout<<"input_s["<<to_string(bit_width-configuration_all[0][0])<<"]^";
	for(int i=1;i<non_zero_num-1;i++){
	    fout<<"input_s["<<to_string(bit_width-configuration_all[0][i])<<"])^";
	}
	fout<<"input_s["<<to_string(bit_width-configuration_all[0][non_zero_num-1])<<"];"<<endl;
	
	fout<<"      end"<<endl;
	fout<<"    else"<<endl;
	fout<<"      begin"<<endl;
	fout<<"        output_temp_s<=0;"<<endl;
	//fout<<"        output_temp_l<=0;"<<endl;
	fout<<"      end"<<endl;
	fout<<"  end"<<endl;

	for(int i=0;i<bit_width;i++){
		int sig_negation = 0;
		fout<<"  assign comparator_binary_numer["<<to_string(i)<<"] = ";
		for(int j=0;j<configuration_all[2].size();j++){
			if(configuration_all[2][j]==configuration_all[4][i]){
				sig_negation = 1;
				break;
			}
		}
		if(sig_negation == 1){
			fout<<"~";
		}
		fout<<"input_s["<<to_string(bit_width - 1 - configuration_all[4][i])<<"];"<<endl;
	}
        fout<<"  assign x_temp_0 = (comparator_binary_numer < input_b) ? 1 : 0;"<<endl;
        fout<<endl;
        
        if(degree>1){
        	fout<<"  always@(posedge clk)"<<endl;
		fout<<"  begin"<<endl;
		fout<<"    if(!rst_n)"<<endl;
		fout<<"      begin"<<endl;
		fout<<"       out_temp_x_1<=x_temp_0;"<<endl;
		for(int i=1;i<degree-1;i++){
        		fout<<"       out_temp_x_"<<to_string(i+1)<<"<=in_x_"<<to_string(i)<<";"<<endl;
        	}
		fout<<"      end"<<endl;
		fout<<"    else"<<endl;
		fout<<"      begin"<<endl;
		for(int i=0;i<degree-1;i++){
        		fout<<"       out_temp_x_"<<to_string(i+1)<<"<=0;"<<endl;
        	}
		fout<<"      end"<<endl;
		fout<<"  end"<<endl;
        }
        
        for(int i=0;i<degree;i++){
        	fout<<"  assign x"<<to_string(i)<<"=x_temp_"<<to_string(configuration_all[6][i])<<";"<<endl;
        }
        
        for(int i=0;i<precision;i++){
			//int sig_negation_2 = 0;
        	fout<<"  assign x"<<to_string(i+degree)<<"=";
			for(int j=0;j<configuration_all[3].size();j++){
				if(configuration_all[3][j]==i){
					//sig_negation_2 = 1;
					fout<<"~";
					break;
				}
			}
			fout<<"input_s["<<to_string(bit_width-1-configuration_all[1][configuration_all[5][i]])<<"];"<<endl;
        }
        fout<<endl;
        
        int buf_used = 0;
        
        for(int i=0;i<circuit_information.size();i++){
        	int gate = circuit_information[i][0];
		switch(gate){
			case 0:
				fout<<"  assign x"<<to_string(circuit_information[i][2])<<"=~x"<<to_string(circuit_information[i][1])<<";"<<endl;
				//O=!a;
				break;
			case 1:
				fout<<"  assign x"<<to_string(circuit_information[i][2])<<"=~x"<<to_string(circuit_information[i][1])<<";"<<endl;
				//O=!a;
				break;
			case 2:
				fout<<"  assign x"<<to_string(circuit_information[i][2])<<"=~x"<<to_string(circuit_information[i][1])<<";"<<endl;
				//O=!a;
				break;
			case 3:
				fout<<"  assign x"<<to_string(circuit_information[i][2])<<"=~x"<<to_string(circuit_information[i][1])<<";"<<endl;
				//O=!a;
				break;
			case 4:
				fout<<"  assign x"<<to_string(circuit_information[i][3])<<"=~(x"<<to_string(circuit_information[i][1])<<"&x"<<to_string(circuit_information[i][2])<<");"<<endl;	
				//O=!(a*b);
				break;
			case 5:
				fout<<"  assign x"<<to_string(circuit_information[i][4])<<"=~(x"<<to_string(circuit_information[i][1])<<"&x"<<to_string(circuit_information[i][2])<<"&x"<<to_string(circuit_information[i][3])<<");"<<endl;
				//O=!(a*b*c);
				break;
			case 6:
				fout<<"  assign x"<<to_string(circuit_information[i][5])<<"=~(x"<<to_string(circuit_information[i][1])<<"&x"<<to_string(circuit_information[i][2])<<"&x"<<to_string(circuit_information[i][3])<<"&x"<<to_string(circuit_information[i][4])<<");"<<endl;
				//O=!(a*b*c*d);
				break;
			case 7:
				fout<<"  assign x"<<to_string(circuit_information[i][3])<<"=~(x"<<to_string(circuit_information[i][1])<<"|x"<<to_string(circuit_information[i][2])<<");"<<endl;
				//O=!(a+b);
				break;
			case 8:
				fout<<"  assign x"<<to_string(circuit_information[i][4])<<"=~(x"<<to_string(circuit_information[i][1])<<"|x"<<to_string(circuit_information[i][2])<<"|x"<<to_string(circuit_information[i][3])<<");"<<endl;
				//O=!(a+b+c);
				break;
			case 9:
				fout<<"  assign x"<<to_string(circuit_information[i][5])<<"=~(x"<<to_string(circuit_information[i][1])<<"|x"<<to_string(circuit_information[i][2])<<"|x"<<to_string(circuit_information[i][3])<<"|x"<<to_string(circuit_information[i][4])<<");"<<endl;
				//O=!(a+b+c+d);
				break;
			case 10:
				fout<<"  assign x"<<to_string(circuit_information[i][3])<<"=x"<<to_string(circuit_information[i][1])<<"&x"<<to_string(circuit_information[i][2])<<";"<<endl;
				//O=a*b;
				break;
			case 11:
				fout<<"  assign x"<<to_string(circuit_information[i][3])<<"=x"<<to_string(circuit_information[i][1])<<"|x"<<to_string(circuit_information[i][2])<<";"<<endl;
				//O=a+b;
				break;
			case 12:
				fout<<"  assign x"<<to_string(circuit_information[i][3])<<"=((x"<<to_string(circuit_information[i][1])<<")&(~x"<<to_string(circuit_information[i][2])<<"))|"<<"((~x"<<to_string(circuit_information[i][1])<<")&(x"<<to_string(circuit_information[i][2])<<"));"<<endl;
				//O=a*!b+!a*b;
				break;
			case 13:
				fout<<"  assign x"<<to_string(circuit_information[i][3])<<"=~(((x"<<to_string(circuit_information[i][1])<<")&(x"<<to_string(circuit_information[i][2])<<"))|"<<"((~x"<<to_string(circuit_information[i][1])<<")&(~x"<<to_string(circuit_information[i][2])<<")));"<<endl;
				//O=!(a*b+!a*!b);
				break;
			case 14:
				fout<<"  assign x"<<to_string(circuit_information[i][3])<<"=(((x"<<to_string(circuit_information[i][1])<<")&(x"<<to_string(circuit_information[i][2])<<"))|"<<"((~x"<<to_string(circuit_information[i][1])<<")&(~x"<<to_string(circuit_information[i][2])<<")));"<<endl;
				//O=a*b+!a*!b;
				break;
			case 15:
				fout<<"  assign x"<<to_string(circuit_information[i][3])<<"=~(((~x"<<to_string(circuit_information[i][1])<<")&(x"<<to_string(circuit_information[i][2])<<"))|"<<"((x"<<to_string(circuit_information[i][1])<<")&(~x"<<to_string(circuit_information[i][2])<<")));"<<endl;
				//O=!(!a*b+a*!b);
				break;
			case 16:
				fout<<"  assign x"<<to_string(circuit_information[i][4])<<"=~(((x"<<to_string(circuit_information[i][1])<<")&(x"<<to_string(circuit_information[i][2])<<"))|"<<"x"<<to_string(circuit_information[i][3])<<");"<<endl;
				//O=!(a*b+c);
				break;
			case 17:
				fout<<"  assign x"<<to_string(circuit_information[i][5])<<"=~(((x"<<to_string(circuit_information[i][1])<<")&(x"<<to_string(circuit_information[i][2])<<"))|"<<"((x"<<to_string(circuit_information[i][3])<<")&(x"<<to_string(circuit_information[i][4])<<")));"<<endl;
				//O=!(a*b+c*d);
				break;
			case 18:
				fout<<"  assign x"<<to_string(circuit_information[i][4])<<"=~(((x"<<to_string(circuit_information[i][1])<<")|(x"<<to_string(circuit_information[i][2])<<"))&"<<"x"<<to_string(circuit_information[i][3])<<");"<<endl;
				//O=!((a+b)*c);
				break;
			case 19:
				fout<<"  assign x"<<to_string(circuit_information[i][5])<<"=~(((x"<<to_string(circuit_information[i][1])<<")|(x"<<to_string(circuit_information[i][2])<<"))&"<<"((x"<<to_string(circuit_information[i][3])<<")|(x"<<to_string(circuit_information[i][4])<<")));"<<endl;
				//O=!((a+b)*(c+d));
				break;
			case 20:
				fout<<"  always@(posedge clk)"<<endl;
				fout<<"  begin"<<endl;
				fout<<"    if(!rst_n)"<<endl;
				fout<<"      begin"<<endl;
				fout<<"       output_temp_buf_"<<to_string(buf_used)<<"=x"<<to_string(circuit_information[i][1])<<";"<<endl;
				fout<<"      end"<<endl;
				fout<<"    else"<<endl;
				fout<<"      begin"<<endl;
        			fout<<"       output_temp_buf_"<<to_string(buf_used)<<"=0;"<<endl;
				fout<<"      end"<<endl;
				fout<<"  end"<<endl;
				fout<<"  assign x"<<to_string(circuit_information[i][2])<<"=in_buf_x_"<<to_string(buf_used)<<";"<<endl;
				buf_used++;
				//O=a;
				break;
			case 21:
				fout<<"  assign x"<<to_string(circuit_information[i][1])<<"=0;"<<endl;
				//O=CONST0;
				break;
			case 22:
				fout<<"  assign x"<<to_string(circuit_information[i][1])<<"=1;"<<endl;
				//O=CONST1;
				break;			
			default:
				cout<<"error in obtaining error"<<endl;
				exit(-1);
				break;
		}
			
	}
        //}
        
        //fout<<endl;
        //fout<<"  always@(posedge clk)"<<endl;
	//fout<<"  begin"<<endl;
	//fout<<"    if(!rst_n)"<<endl;
	//fout<<"      begin"<<endl;
	//fout<<"       output_circuit_temp = input_circuit + x"<<to_string(pds)<<";"<<endl;
	//fout<<"      end"<<endl;
	//fout<<"    else"<<endl;
	//fout<<"      begin"<<endl;
	//fout<<"       output_circuit_temp = 0;"<<endl;
	//fout<<"      end"<<endl;
	//fout<<"  end"<<endl;
	
	fout<<"endmodule"<<endl;
	fout.close();
	return;
}

void write_verilog_testbench(two_die_vector_int configuration_all, two_die_vector_int circuit_information, int pds, int degree, two_die_vector_int BS_all, double error_bound, int bm_id_under_test, two_die_vector_int permutation_bit_width, two_die_vector_int LFSR_set,two_die_vector_int LFSR_output_1,int bit_width){
	int precision = pds - degree;
	string filename = "verilog_proposed";
	//mkdir(filename.c_str());
	filename = filename + "/" + to_string(int(10000*error_bound));
	//mkdir(filename.c_str());
	filename = filename + "/" + to_string(bm_id_under_test);
	//mkdir(filename.c_str());
	//filename = filename + "/" + to_string(pds) + "_" + to_string(degree);
	//mkdir(filename.c_str());
	//rm_dir(filename.c_str());
	//mkdir(filename.c_str());
	
	filename = filename + "/" + "circuit_tst.v";
	
	int buf_num = 0;
	for(int i=0;i<circuit_information.size();i++){
		if(circuit_information[i][0]==20){
			buf_num++;
		}
	}
	
	ofstream fout;
	fout.open(filename.c_str());
	if(!fout)
        {
            cout<<filename<<endl;
            cout<<"cannot open the filename_verilog_circuit_testbench"<<endl;
            exit(-1);
        }
        
        fout<<"`timescale 1 ns/ 1 ps"<<endl;
        fout<<"module circuit_tst();"<<endl;
        fout<<"  reg clk;"<<endl;
	fout<<"  reg rst_n;"<<endl;
	
	fout<<"  reg["<<to_string(bit_width-1)<<":0] input_s;"<<endl;
	fout<<"  reg["<<to_string(bit_width-1)<<":0] input_b;"<<endl;
	//fout<<"  reg["<<to_string(bit_width-1)<<":0] input_l;"<<endl;
	//fout<<"  reg["<<to_string(bit_width-1)<<":0] input_circuit;"<<endl;
	for(int i=0;i<degree-1;i++){
        	fout<<"  reg in_x_"<<to_string(i+1)<<";"<<endl;
        }
        for(int i=0;i<buf_num;i++){
        	fout<<"  reg in_buf_x_"<<to_string(i)<<";"<<endl;
        }
	//fout<<"  wire["<<to_string(bit_width-1)<<":0] output_l;"<<endl;
	fout<<"  wire["<<to_string(bit_width-1)<<":0] output_s;"<<endl;
	fout<<"  wire output_circuit;"<<endl;
	for(int i=0;i<degree-1;i++){
        	fout<<"  wire out_x_"<<to_string(i+1)<<";"<<endl;
        }
        for(int i=0;i<buf_num;i++){
        	fout<<"  wire out_buf_x_"<<to_string(i)<<";"<<endl;
        }

	fout<<endl;
	
	fout<<"  circuit cir("<<endl;
        fout<<"              .clk(clk),"<<endl;
        fout<<"              .rst_n(rst_n),"<<endl;
        fout<<"              .input_s(input_s),"<<endl;
        fout<<"              .input_b(input_b),"<<endl;
        fout<<"              .output_s(output_s),"<<endl;
        //fout<<"              .input_l(input_l),"<<endl;
        //fout<<"              .output_l(output_l),"<<endl;
        //fout<<"              .input_circuit(input_circuit),"<<endl;
        fout<<"              .output_circuit(output_circuit)";
        for(int i=0;i<degree-1;i++){
			fout<<","<<endl;
        	fout<<"              .in_x_"<<to_string(i+1)<<"("<<"in_x_"<<to_string(i+1)<<")";
        }
        for(int i=0;i<buf_num;i++){
			fout<<","<<endl;
        	fout<<"              .in_buf_x_"<<to_string(i)<<"("<<"in_buf_x_"<<to_string(i)<<")";
        }
		if(buf_num>0){
			for(int i=0;i<degree-1;i++){
				fout<<","<<endl;
        		fout<<"              .out_x_"<<to_string(i+1)<<"("<<"out_x_"<<to_string(i+1)<<")";
       		}
        	for(int i=0;i<buf_num-1;i++){
				fout<<","<<endl;
        		fout<<"              .out_buf_x_"<<to_string(i)<<"("<<"out_buf_x_"<<to_string(i)<<")";
        	}
			fout<<","<<endl;
        	fout<<"              .out_buf_x_"<<to_string(buf_num-1)<<"("<<"out_buf_x_"<<to_string(buf_num-1)<<")";
		}
		else{
			for(int i=0;i<degree-1;i++){
				fout<<","<<endl;
        		fout<<"              .out_x_"<<to_string(i+1)<<"("<<"out_x_"<<to_string(i+1)<<")";
       		}
			//fout<<"              .out_x_"<<to_string(degree-1)<<"("<<"out_x_"<<to_string(degree-1)<<")"<<endl;
		}
		fout<<endl;
        fout<<"  );"<<endl;
        
        fout<<"  initial"<<endl;                                                
        fout<<"  begin"<<endl;                                                                        
        fout<<"        input_s=1;"<<endl;;
        //for(int i=0;i<bit_width;i++){
        //	fout<<to_string(LFSR_output_1[configuration_all[8]][i]);
        //}
        //fout<<";"<<endl;
        fout<<"        input_b=0;"<<endl;
        //fout<<"        input_l="<<to_string(bit_width)<<"'b";
        //for(int i=0;i<bit_width;i++){
        //	fout<<to_string(LFSR_output_1[configuration_all[9]][i]);
        //} 
        //fout<<";"<<endl;
        //fout<<"        input_circuit=0;"<<endl; 
        for(int i=0;i<degree-1;i++){
        	fout<<"        in_x_"<<to_string(i+1)<<"= 0;"<<endl;
        }
        for(int i=0;i<buf_num;i++){
        	fout<<"        in_buf_x_"<<to_string(i)<<"= 0;"<<endl;
        }    
        fout<<"        rst_n=1'b0;"<<endl;  
        fout<<"        clk=1'b1;"<<endl; 
        fout<<"        $dumpfile(\"circuit.vcd\");"<<endl; 
        fout<<"        $dumpvars;"<<endl;  
        fout<<"  #10000000; $finish;"<<endl;  		                      
        fout<<"  end"<<endl;                                                      
        fout<<"  always"<<endl;                                                                
        fout<<"  begin"<<endl;                                                    
        fout<<"  #20 input_s = output_s;"<<endl;                                                                                       
        fout<<"  end"<<endl;   
        fout<<"  always #"<<to_string(int(20*(pow(2,bit_width)-1)))<<" input_b = input_b+1;"<<endl;   
        //fout<<"  always #20 input_l = output_l;"<<endl;
        //fout<<"  always #20 input_circuit = output_circuit;"<<endl;  
        for(int i=0;i<degree-1;i++){
        	fout<<"  always #20 "<<"in_x_"<<to_string(i+1)<<" = out_x_"<<to_string(i+1)<<";"<<endl;
        }
        for(int i=0;i<buf_num;i++){
        	fout<<"  always #20 in_buf_x_"<<to_string(i)<<" = out_buf_x_"<<to_string(i)<<";"<<endl;
        }   
        fout<<"  always #10 clk = ~clk;"<<endl;        
        fout<<"  always #10000000 rst_n = ~rst_n;"<<endl;                                            
        fout<<"endmodule"<<endl;  
        fout.close();
        
        filename = "verilog_proposed";
	//mkdir(filename.c_str());
	filename = filename + "/" + to_string(int(10000*error_bound));
	//mkdir(filename.c_str());
	filename = filename + "/" + to_string(bm_id_under_test);
	//mkdir(filename.c_str());
	//filename = filename + "/" + to_string(pds) + "_" + to_string(degree);
	//mkdir(filename.c_str());
	//rm_dir(filename.c_str());
	//mkdir(filename.c_str());
	
	filename = filename + "/" + "circuit_tst_sim.v";
	
	//ofstream fout;
	fout.open(filename.c_str());
	if(!fout)
        {
            cout<<filename<<endl;
            cout<<"cannot open the filename_verilog_circuit_testbench"<<endl;
            exit(-1);
        }
        
        fout<<"`timescale 1 ns/ 1 ps"<<endl;
        fout<<"module circuit_tst();"<<endl;
        fout<<"  reg clk;"<<endl;
	fout<<"  reg rst_n;"<<endl;
	
	fout<<"  reg["<<to_string(bit_width-1)<<":0] input_s;"<<endl;
	fout<<"  reg["<<to_string(bit_width-1)<<":0] input_b;"<<endl;
	//fout<<"  reg["<<to_string(bit_width-1)<<":0] input_l;"<<endl;
	//fout<<"  reg["<<to_string(bit_width-1)<<":0] input_circuit;"<<endl;
	for(int i=0;i<degree-1;i++){
        	fout<<"  reg in_x_"<<to_string(i+1)<<";"<<endl;
        }
        for(int i=0;i<buf_num;i++){
        	fout<<"  reg in_buf_x_"<<to_string(i)<<";"<<endl;
        }
	//fout<<"  wire["<<to_string(bit_width-1)<<":0] output_l;"<<endl;
	fout<<"  wire["<<to_string(bit_width-1)<<":0] output_s;"<<endl;
	fout<<"  wire output_circuit;"<<endl;
	for(int i=0;i<degree-1;i++){
        	fout<<"  wire out_x_"<<to_string(i+1)<<";"<<endl;
        }
        for(int i=0;i<buf_num;i++){
        	fout<<"  wire out_buf_x_"<<to_string(i)<<";"<<endl;
        }

	fout<<endl;
	
	fout<<"  circuit cir("<<endl;
        fout<<"              .clk(clk),"<<endl;
        fout<<"              .rst_n(rst_n),"<<endl;
        fout<<"              .input_s(input_s),"<<endl;
        fout<<"              .input_b(input_b),"<<endl;
        fout<<"              .output_s(output_s),"<<endl;
        //fout<<"              .input_l(input_l),"<<endl;
        //fout<<"              .output_l(output_l),"<<endl;
        //fout<<"              .input_circuit(input_circuit),"<<endl;
        fout<<"              .output_circuit(output_circuit)";
        for(int i=0;i<degree-1;i++){
			fout<<","<<endl;
        	fout<<"              .in_x_"<<to_string(i+1)<<"("<<"in_x_"<<to_string(i+1)<<")";
        }
        for(int i=0;i<buf_num;i++){
			fout<<","<<endl;
        	fout<<"              .in_buf_x_"<<to_string(i)<<"("<<"in_buf_x_"<<to_string(i)<<")";
        }
		if(buf_num>0){
			for(int i=0;i<degree-1;i++){
				fout<<","<<endl;
        		fout<<"              .out_x_"<<to_string(i+1)<<"("<<"out_x_"<<to_string(i+1)<<")";
       		}
        	for(int i=0;i<buf_num-1;i++){
				fout<<","<<endl;
        		fout<<"              .out_buf_x_"<<to_string(i)<<"("<<"out_buf_x_"<<to_string(i)<<")";
        	}
			fout<<","<<endl;
        	fout<<"              .out_buf_x_"<<to_string(buf_num-1)<<"("<<"out_buf_x_"<<to_string(buf_num-1)<<")";
		}
		else{
			for(int i=0;i<degree-1;i++){
				fout<<","<<endl;
        		fout<<"              .out_x_"<<to_string(i+1)<<"("<<"out_x_"<<to_string(i+1)<<")";
       		}
			//fout<<"              .out_x_"<<to_string(degree-1)<<"("<<"out_x_"<<to_string(degree-1)<<")"<<endl;
		}
		fout<<endl;
        fout<<"  );"<<endl;
        
        fout<<"  initial"<<endl;                                                
        fout<<"  begin"<<endl;                                                                        
        fout<<"        input_s=1;"<<endl;
        /*for(int i=0;i<bit_width;i++){
        	fout<<to_string(LFSR_output_1[configuration_all[8]][i]);
        }
        fout<<";"<<endl;*/
        fout<<"        input_b=0;"<<endl;
        /*fout<<"        input_l="<<to_string(bit_width)<<"'b";
        for(int i=0;i<bit_width;i++){
        	fout<<to_string(LFSR_output_1[configuration_all[9]][i]);
        } 
        fout<<";"<<endl;*/
        //fout<<"        input_circuit=0;"<<endl; 
        for(int i=0;i<degree-1;i++){
        	fout<<"        in_x_"<<to_string(i+1)<<"= 0;"<<endl;
        }
        for(int i=0;i<buf_num;i++){
        	fout<<"        in_buf_x_"<<to_string(i)<<"= 0;"<<endl;
        }    
        fout<<"        rst_n=1'b0;"<<endl;  
        fout<<"        clk=1'b1;"<<endl; 
        fout<<"        $dumpfile(\"circuit.vcd\");"<<endl; 
        fout<<"        $dumpvars;"<<endl;  
        fout<<"  #10000000; $finish;"<<endl;  		                      
        fout<<"  end"<<endl;                                                      
        fout<<"  always"<<endl;                                                                
        fout<<"  begin"<<endl;                                                    
        fout<<"  #20 input_s = output_s;"<<endl;                                                                                       
        fout<<"  end"<<endl;   
        fout<<"  always #"<<to_string(int(20*(pow(2,bit_width)-1)))<<" input_b = input_b+1;"<<endl;   
        //fout<<"  always #20 input_l = output_l;"<<endl;
        //fout<<"  always #20 input_circuit = output_circuit;"<<endl;  
        for(int i=0;i<degree-1;i++){
        	fout<<"  always #20 "<<"in_x_"<<to_string(i+1)<<" = out_x_"<<to_string(i+1)<<";"<<endl;
        }
        for(int i=0;i<buf_num;i++){
        	fout<<"  always #20 in_buf_x_"<<to_string(i)<<" = out_buf_x_"<<to_string(i)<<";"<<endl;
        }   
        fout<<"  always #10 clk = ~clk;"<<endl;        
        fout<<"  always #10000000 rst_n = ~rst_n;"<<endl;                                            
        fout<<"endmodule"<<endl;  
        fout.close();
	return;
}

two_die_vector_int read_ADP(int bm_id_under_test){
	string filename = "configuration/" + to_string(bm_id_under_test) + "/ADP_all.txt";
	ifstream fin;
        fin.open(filename.c_str());
        if(!fin)
        {
            cout<<filename<<endl;
            cout<<"cannot open the filename_ADP"<<endl;
            exit(-1);
        }
        one_die_vector_int ADP_one;
        two_die_vector_int ADP_two;
        string line;
        int pds_res = -1;
        while(getline(fin,line)){
        	string str_temp;
        	int site_1 = 0;
        	for(int i=0;i<line.size();i++){
        		if(line[i]!='_'){
        			str_temp = str_temp + line[i];
        		}
        		else
        		{
        			site_1 = i;
        			break;
        		}
        	}
        	int pds_new = atoi(str_temp.c_str());
        	
        	string str_temp_2;
        	int sig = 0;
        	for(int i=site_1+1;i<line.size();i++){
        	        if(sig==0){
        	               if(line[i]==' '){
        	                   sig = 1;
        	               }
        	               continue;
        	        }
        	        str_temp_2 = str_temp_2 + line[i];
        	}
        	int ADP_value = atoi(str_temp_2.c_str());
        	
        	if(pds_new != pds_res){
        		pds_res = pds_new;
        		if(ADP_one.size()!=0){
        			ADP_two.push_back(ADP_one);
        			ADP_one.clear();
        		}
        	}
        	ADP_one.push_back(ADP_value);
        }
        ADP_two.push_back(ADP_one);
        
        fin.close();
        
        return ADP_two;
}

two_die_vector_double read_error(int bm_id_under_test){
	string filename = "configuration/" + to_string(bm_id_under_test) + "/error_all.txt";
	ifstream fin;
        fin.open(filename.c_str());
        if(!fin)
        {
            cout<<filename<<endl;
            cout<<"cannot open the filename_error"<<endl;
            exit(-1);
        }
        one_die_vector_double Error_one;
        two_die_vector_double Error_two;
        string line;
        int pds_res = -1;
        while(getline(fin,line)){
        	string str_temp;
        	int site_1 = 0;
        	for(int i=0;i<line.size();i++){
        		if(line[i]!='_'){
        			str_temp = str_temp + line[i];
        		}
        		else
        		{
        			site_1 = i;
        			break;
        		}
        	}
        	int pds_new = atoi(str_temp.c_str());
        	
        	string str_temp_2;
        	int sig = 0;
        	for(int i=site_1+1;i<line.size();i++){
        	        if(sig==0){
        	               if(line[i]==' '){
        	                   sig = 1;
        	               }
        	               continue;
        	        }
        	        str_temp_2 = str_temp_2 + line[i];
        	}
        	double error_value = stod(str_temp_2);
        	
        	if(pds_new != pds_res){
        		pds_res = pds_new;
        		if(Error_one.size()!=0){
        			Error_two.push_back(Error_one);
        			Error_one.clear();
        		}
        	}
        	Error_one.push_back(error_value);
        }
        Error_two.push_back(Error_one);
        
        fin.close();
        
        return Error_two;
}

two_die_vector_int read_confuration(int bm_id_under_test, double approx_error_bound_ratio){
	string filename = "configuration/error_ratio"  + to_string(int(approx_error_bound_ratio*100)) + "/bm" + to_string(bm_id_under_test)  + "/bm" + to_string(bm_id_under_test) + "-configuration.txt";
	ifstream fin;
        fin.open(filename.c_str());
        if(!fin)
        {
            cout<<filename<<endl;
            cout<<"cannot open the filename_configuration"<<endl;
            exit(-1);
        }
        two_die_vector_int configuration_all;
		one_die_vector_int configuration_temp;
        string line;
        int pds_res = -1;
        getline(fin,line);
        //cout<<line<<endl;
        int count_line = 0;
        while(getline(fin,line)){
        	//cout<<line<<endl;
		configuration_temp.clear();
        	string str_temp;
        	string str_temp_res;
        	int value = 0;
        	for(int i=0;i<line.size();i++){
        		if(line[i]!=','){
        			str_temp = str_temp + line[i];
        		}
        		else
        		{      			
        			value = atoi(str_temp.c_str());
					str_temp = str_temp_res;
        			configuration_temp.push_back(value);
        		}
        	}
        	//value = atoi(str_temp.c_str());
        	//configuration_temp.push_back(value);   
			configuration_all.push_back(configuration_temp);  
			count_line++;
			if(count_line==7){
				break;
			}	
        }
        
        fin.close();
        //exit(-1);
        
        return configuration_all;
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

two_die_vector_char read_library(){
	char cmd[100];
	strcpy(cmd, "mcnc.genlib");
	//cout<<cmd<<endl;

	ifstream in;
	in.open(cmd);
    auto line = string();
    int count = 0;

	one_die_vector_char temp_char;
	two_die_vector_char gate_all;

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
	strcpy(cmd, "output_dir/error_ratio");
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

				int sig_iow = 0;
				while(sig_iow ==0){
					for(int i=start_site;i<line.length();i++){
						if(line[i]!=','&&line[i]!=';'){
							temp_char.push_back(line[i]);
						}
						else{
							temp_char.push_back('\0');
							variable_name.push_back(temp_char);
							temp_char.clear();
							if(line[i]==';'){
								sig_iow = 1;
							}
							i++;
							
						}				
					}
					if(sig_iow==0){
						getline(in,line);
						start_site = 0;
						for(int hj=0;hj<line.length();hj++){
							if(line[hj]==' '){
								start_site++;
							}
						}
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

one_die_vector_int obtain_circuit_information(int bm_id_under_test,double approx_error_bound_ratio){
	char cmd[100];
	int err_site=0;
	strcpy(cmd, "output_dir/error_ratio");
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
	return circuit_information;

}


void error_quit( const char *msg )
{
  perror( msg );
  exit( -1 );
}
void change_path( const char *path )
{
  printf( "Leave %s Successed . . .\n", getcwd( NULL, 0 ) );
  if ( chdir( path ) == -1 )
    error_quit( "chdir" );
  printf( "Entry %s Successed . . .\n", getcwd( NULL, 0 ) );
}
void rm_dir( const char *path )
{
  DIR    *dir;
  struct dirent  *dirp;
  struct stat  buf;
  char    *p = getcwd( NULL, 0 );
  if ( (dir = opendir( path ) ) == NULL )
    error_quit( "OpenDir" );
  change_path( path );
  while ( dirp = readdir( dir ) )
  {
    if ( (strcmp( dirp->d_name, "." ) == 0) || (strcmp( dirp->d_name, ".." ) == 0) )
      continue;
    if ( stat( dirp->d_name, &buf ) == -1 )
      error_quit( "stat" );
    if ( S_ISDIR( buf.st_mode ) )
    {
      rm_dir( dirp->d_name );
      /*if(rmdir(dirp->d_name)==-1)
       *  error_quit("rmdir");
       * printf("rm %s Successed . . .\n",dirp->d_name);*/
      continue;
    }
    if ( remove( dirp->d_name ) == -1 )
      error_quit( "remove" );
    printf( "rm %s Successed . . .\n", dirp->d_name );
  }
  closedir( dir );
  change_path( p );
  if ( rmdir( path ) == -1 )
    error_quit( "rmdir" );
  printf( "rm %s Successed . . .\n", path );
}
