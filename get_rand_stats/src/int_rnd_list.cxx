#include "get_rand_stats.h"

//Initialize int_rnd_list, using the constructor from fizz_rnd_list that takes
// an integer. By using the overloaded constructor, I avoid making an 
// unnecessary extra initialization of fizz_rnd_list
int_rnd_list::int_rnd_list(int N):fizz_rnd_list(N){

}

//Destruct int_rnd_list
int_rnd_list::~int_rnd_list(){

}
