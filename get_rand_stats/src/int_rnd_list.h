#include "get_rand_stats.h"

//This class inherits from fizz_rnd_list, but always calls its integer
//constructor (so that the random list has values from 0-1000)
class int_rnd_list: public fizz_rnd_list{
  public:
    //Constructor that takes the number N of random numbers as its argument
    int_rnd_list(int N);
    //Destructor
    ~int_rnd_list();
    // I don't choose to reimplement any of the functionality from the original
    // class, because this class can use it just as easily. I would probably
    // not create this second class at all, if I was being most efficient,
    // to save on having to call the virtual destructor
};
