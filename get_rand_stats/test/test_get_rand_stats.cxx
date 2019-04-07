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
//Test that if I create a list with two entries that the standard deviation is
//the square root of the difference of those two entries from their mean divided//by two
void test_rnd_list::test_get_std_dev_one(){
  int_rnd_list test_list(2);
  double* test_rand = test_list.get_list();
  double mean = test_list.get_mean(2);
  double std_dev = test_list.get_std_dev(2);
  assert(std_dev==sqrt((((test_rand[0]-mean)*(test_rand[0]-mean))/2)+(((test_rand[1]-mean)*(test_rand[1]-mean))/2))
);
}

//Test that if I create a list with three entries that the mean is a third of
// the sum of those three entries
void test_rnd_list::test_get_mean_two(){
  int_rnd_list test_list(3);
  double* test_rand = test_list.get_list();
  double mean = test_list.get_mean(3);
  assert(mean==((test_rand[0]+test_rand[1]+test_rand[2])/3));
}

//Test that if I calculate the mean up to index 1, and then calculate the mean
//up to index two, that the result is the same as if I calculate the mean just
//once up to index two
void test_rnd_list::test_get_mean_repeat(){
  int_rnd_list test_list(2);
  double* test_rand = test_list.get_list();
  double mean = test_list.get_mean(1);
  double mean1 = test_list.get_mean(2);
  assert(mean1==((test_rand[0]+test_rand[1])/2));
}

//Test that if I calculate the mean up to index 1, and then calculate the mean
//up to index two, and then calculate the mean up to index 3 that the result is
//the same as if I calculate the mean just once up to index three
void test_rnd_list::test_get_mean_threepeat(){
  int_rnd_list test_list(3);
  double* test_rand = test_list.get_list();
  double mean = test_list.get_mean(1);
  double mean1 = test_list.get_mean(2);
  double mean2 = test_list.get_mean(3);
  assert(mean2==((test_rand[0]+test_rand[1]+test_rand[2])/3));
}
//Test that the get_stats algorithm gets the highest value in the list if I give//a number greater than 1 and the lowest number if I give a number lower than 0
void test_rnd_list::test_get_stats_ends(){
  float in_len = 3;
  fizz_rnd_list test_list(in_len);
  double* test_rand = test_list.get_list();

  std::tuple<double, int, double, double> stats = test_list.get_stats(2);
  assert(std::get<1>(stats)==2 && std::get<0>(stats)==test_rand[2]);

  std::tuple<double, int, double, double> stats1 = test_list.get_stats(-1);
  assert(std::get<1>(stats1)==0 && std::get<0>(stats1)==test_rand[0]);
}
void test_rnd_list::test_get_stats(){
  float in_len = 100000;
  int_rnd_list test_list(in_len);
  int test_val = 500;
  double* test_rand = test_list.get_list();
  std::tuple<double, int, double, double> stats = test_list.get_stats(test_val);

  int cor_ind =0;
  double cor_val=0;
  double diff=1001;
  for(int i=0; i<in_len; ++i){
    double cur_diff=std::abs(test_val-test_rand[i]);
    if(cur_diff<diff){
      cor_ind=i;
      cor_val=test_rand[i];
      diff=cur_diff;
    }
  }
  assert(std::get<1>(stats)==cor_ind && std::get<0>(stats)==cor_val);

}
