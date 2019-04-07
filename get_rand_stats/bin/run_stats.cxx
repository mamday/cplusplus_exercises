#include "int_rnd_list.h"

// Get the length of the array and the number of times to iterate from the 
// command line (num_iters). Then initialize fizz_rnd_list.
// The get_stats() function will get a tuple
// that contains 1)The closest value close_val, to X (which is randomly generated in the 
// loop and is called 'rand_num') 2)The index of close_val 3)The mean of all
// the values up to the index 4)The standard deviation of all the values up to
// the index 
// If the second parameter on the command line is 'thousand' it generates a list of random integers
// If it is 'one' it generates a list of random floats
int main(int argc, char* argv[]){
  //Initialize random number generator
  srand(time(NULL));
  //Exit if the wrong number of inputs are given
  if(argc != 3){
    std::cerr<<"ERROR: Received the incorrect number of arguments"<<std::endl;
    exit(EXIT_FAILURE);
  } 
  else{
    //Make the input a float so that we get the correct behavior of fizz_rnd_list
    float num_iters = atof(argv[1]);
    //Change the input char array into a string that is easier to parse
    std::string in_string(argv[2]);
    std::tuple<double,int,double,double> fin_tup;
    double rand_num;
    if(in_string=="thousand"){
      int_rnd_list i_rnd(num_iters);
      for(int i=0; i<(num_iters+1); ++i){
        rand_num = rand() % 1000;
        fin_tup = i_rnd.get_stats(rand_num);
        //The following will print the tuple closest value to the random number, index of closest value, mean of all sorted values up to that number, standard deviation of all sorted numbers up to that value
        std::cout<<rand_num<<" "<<std::get<0>(fin_tup)<<" "<<std::get<1>(fin_tup)<<" "<<std::get<2>(fin_tup)<<" "<<std::get<3>(fin_tup)<<std::endl;
      }
    }
    else if(in_string=="one"){
      fizz_rnd_list f_rnd(num_iters);
      for(int i=0; i<(num_iters+1); ++i){
        rand_num = (float)rand()/(float)(RAND_MAX);
        fin_tup = f_rnd.get_stats(rand_num); 
        //The following will print the tuple closest value to the random number, index of closest value, mean of all sorted values up to that number, standard deviation of all sorted numbers up to that value
        std::cout<<rand_num<<" "<<std::get<0>(fin_tup)<<" "<<std::get<1>(fin_tup)<<" "<<std::get<2>(fin_tup)<<" "<<std::get<3>(fin_tup)<<std::endl;

      }
    }
    else{
      //Fail if the input is not 'one' or 'thousand'
      std::cerr<<"ERROR: Invalid algorithm classifier"<<std::endl;
      exit(EXIT_FAILURE);
    }
  }
}
