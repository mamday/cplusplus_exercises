#include "test_get_rand_stats.h"

//Implement my unit test framework
test_rnd_list::test_rnd_list(){
}

test_rnd_list::~test_rnd_list(){
}

//Test that initiation of fizz_rnd_list class produces 10 entries between 0 and
//1
void test_rnd_list::test_fizz_rnd_list_initiation(){
  float l_len = 10;
  fizz_rnd_list test_list(l_len);
  double* test_rand = test_list.get_list();
  int test_len = 0;
  while(test_len<l_len){
    assert(test_rand[test_len]>0 && test_rand[test_len]<1);
    test_len+=1;
  }
}

//Test that initiation of int_rnd_list class produces 10 entries between 0 and 
//1000
void test_rnd_list::test_int_rnd_list_initiation(){
  int l_len = 10;
  int_rnd_list test_list(l_len);
  double* test_rand = test_list.get_list();
  int test_len = 0;
  while(test_len<l_len){
    assert(test_rand[test_len]>0 && test_rand[test_len]<1000);
    test_len+=1;
  }
}

//Test that uniform standard deviation algorithm returns the expected value
//given a uniform distribution
void test_rnd_list::test_uniform_std_dev(){
  int l_len=1000;
  int_rnd_list test_list(l_len);
  double u_std_dev = test_list.get_uniform_std_dev(300);

  assert((u_std_dev-0.0866)<0.0001);
}

//Test that if I create a list with one entry that the mean is that entry
void test_rnd_list::test_get_mean_zero(){
  int_rnd_list test_list(1);
  double* test_rand = test_list.get_list();
  double mean = test_list.get_mean(1);
  assert(mean==test_rand[0]);
}

//Test that if I create a list with one entry that the standard deviation is 
//zero 
void test_rnd_list::test_get_std_dev_zero(){
  int_rnd_list test_list(1);
  double* test_rand = test_list.get_list();
  double mean = test_list.get_mean(1);
  double std_dev = test_list.get_std_dev(1);
  assert(std_dev==0);
}

//Test that if I create a list with two entries that the mean is half of the sum
//of those two entries 
void test_rnd_list::test_get_mean_one(){
  int_rnd_list test_list(2);
  double* test_rand = test_list.get_list();
  double mean = test_list.get_mean(2);
  assert(mean==((test_rand[0]+test_rand[1])/2));
}

int main(int argc, char* argv[]){
  //If one input is given, and the name of the input is 'test', then run the 
  //tests
  if(argc == 2){
    std::string in_string(argv[1]);
    if(in_string!="test"){
      std::cerr<<"ERROR: Received the incorrect number of arguments"<<std::endl;
      exit(EXIT_FAILURE);
    }
    test_rnd_list tester;
    tester.test_fizz_rnd_list_initiation();
    tester.test_int_rnd_list_initiation();
    tester.test_uniform_std_dev();
    tester.test_get_mean_zero();
    tester.test_get_std_dev_zero();
    tester.test_get_mean_one();
    tester.test_get_std_dev_one();
    tester.test_get_mean_two();
    tester.test_get_mean_repeat();
    tester.test_get_mean_threepeat();
    tester.test_get_stats();
    tester.test_get_stats_ends();
    std::cout<<"Passed!"<<std::endl;
  }
  else{
    std::cerr<<"ERROR: Received the incorrect number of arguments"<<std::endl;
    exit(EXIT_FAILURE);
  }
}
