#include "get_rand_stats.h"

class test_rnd_list{
  public:
    test_rnd_list();
    virtual ~test_rnd_list();

    void test_fizz_rnd_list_initiation();
    void test_int_rnd_list_initiation();
    void test_uniform_std_dev();
    void test_get_mean_zero();
    void test_get_std_dev_zero();
    void test_get_mean_one();
    void test_get_std_dev_one();
    void test_get_mean_two();
    void test_get_mean_repeat();
    void test_get_mean_threepeat();
    void test_get_stats();
    void test_get_stats_ends();
};
