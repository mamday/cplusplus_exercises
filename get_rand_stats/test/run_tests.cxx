#include "test_get_rand_stats.h"

int main(int argc, char* argv[]){
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
