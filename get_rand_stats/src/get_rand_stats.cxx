#include "get_rand_stats.h"

//Initialize fizz_rnd_list if the input array length, N, is a float
fizz_rnd_list::fizz_rnd_list(float N): cur_N__(static_cast<int>(N)),x_mean__(0),max_mean_ind__(0){
  int int_N = static_cast<int>(N);
  random_list__ = new double[int_N]();
  //Initialize the maps and the random list once when the class is initiated to
  //avoid spending time looking through the maps for a key later
  for(int i=0; i<int_N; ++i){
    mean_map__[i]=0;
    std_dev_map__[i]=0;
    random_list__[i]=((float)rand()/(float)(RAND_MAX));
  }
  //Sort the algorithm on initialization so that subsequent calls to get_stats
  // can be O(log(n)) instead of O(n)
  std::sort(&random_list__[0],&random_list__[int_N]);
}

//Initialize fizz_rnd_list if the input array length, N, is an int
fizz_rnd_list::fizz_rnd_list(int N): cur_N__(N), x_mean__(0), max_mean_ind__(0){
  random_list__ = new double[N]();
  //Initialize the maps and the random list once when the class is initiated to
  //avoid spending time looking through the maps for a key later
  for(int i=0; i<N; ++i){
    mean_map__[i]=0;
    std_dev_map__[i]=0;
    random_list__[i]=rand() % 1000;
  }
  //Sort the algorithm on initialization so that subsequent calls to get_stats
  // can be O(log(n)) instead of O(n)
  std::sort(&random_list__[0],&random_list__[N]);
}

//Destruct fizz_rnd_list, making sure to abolish the dynamically allocated array
fizz_rnd_list::~fizz_rnd_list(){
  delete [] random_list__;
}

double* fizz_rnd_list::get_list(){
  return random_list__;
}

double fizz_rnd_list::get_mean(int X_ind){
  double cur_tot = 0;
  //If the value already exists, don't calculate it again. This is much more
  //efficient than calculating the mean for the same list multiple times when
  //it has already been calculated before
  if(mean_map__[X_ind]!=0){
    return mean_map__[X_ind];
  }
  //If the current index is greater than the previous highest index, get the
  //start calculating the mean at the previous highest index
  if(X_ind>max_mean_ind__){
    cur_tot = max_mean_ind__*mean_map__[max_mean_ind__];
  } 

  //Calculate the mean continuously and save the value up to the current index
  for(int i=max_mean_ind__; i<(X_ind); ++i){
    cur_tot+=random_list__[i]; 
    mean_map__[i+1]=cur_tot/(i+1);
  }

  //If the current index is higher than the previous index, replace it as the
  //maximum index
  if(X_ind>max_mean_ind__){
    max_mean_ind__=X_ind;
  }

  return cur_tot/(float)(X_ind);
}

double fizz_rnd_list::get_std_dev(int X_ind){
  double cur_tot = 0;
  //If the standard deviation has already been calculated, don't calculate it 
  //again, to be more efficient.
  if(std_dev_map__[X_ind]!=0){
    return std_dev_map__[X_ind];
  }
  //Otherwise calculate the stardard deviation from the current value of the mean
  for(int i=0; i<(X_ind); ++i){
    cur_tot+=(random_list__[i]-mean_map__[X_ind])*(random_list__[i]-mean_map__[X_ind]); 
  }
  //Save the current value in the map
  std_dev_map__[X_ind]=sqrt(cur_tot/(float)(X_ind));

  return sqrt(cur_tot/(float)(X_ind));
}

double fizz_rnd_list::get_uniform_std_dev(int X_ind){
  return sqrt((((float)(X_ind-1)/float(cur_N__))*((float)(X_ind-1)/float(cur_N__)))/12); 
}

//Return stats as tuple with 1)Value closes to X 2)Index of Value 3)Mean up to
//Index and 4)Std. Dev up to Index
std::tuple<double, int, double, double> fizz_rnd_list::get_stats(double X){
  //Fail if there are no entries in the array
  if(cur_N__==0){
    std::cerr<<"ERROR: Random array has no entries"<<std::endl;
    exit(EXIT_FAILURE);
  } 
  int cur_index = -1;
  double close_val = -1;
  int cur_len = cur_N__; 
  double* cur_list = random_list__;
  while(cur_len>1){
    //In order to quickly access the halves, instead of copying from the 
    // original array I just make pointers to certain parts of the array 
    double *firstHalf = &cur_list[0];
    double *secondHalf = &cur_list[(cur_len/2)];
    //Use a binary tree in order to keep only looking in parts of the list
    //that contain the final value, so the algorithm will be O(log(n)) and 
    // not O(n)
    if(firstHalf[(cur_len/2)-1]==secondHalf[0]){
      //If the values in the middle of the list are equal, move to the low 
      //values if the difference between the input and the middle value is 
      //negative. This is because, if the value is negative, then that means the
      //middle value is greater than the input value, so therefore we should 
      //take the list containing smaller values (the left branch'''
      if((X-firstHalf[(cur_len/2)-1])<=0){

        if(cur_len==cur_N__){
          cur_index = 0;
        }
        cur_len = (cur_len/2);
        cur_list = firstHalf;

      }
      else{
        if(cur_len==cur_N__){
          cur_index = cur_len/2;
        }
        else{
          cur_index = cur_index + (cur_len/2);
        }
        cur_len = ceil((float)cur_len/2.0);
        cur_list = secondHalf;

      }

    }
    //If the values are not equal, go in the direction that is closer to the 
    //input value X
    else if(std::abs(firstHalf[(cur_len/2)-1]-X)<=std::abs(secondHalf[0]-X)){
      if(cur_len==cur_N__){
        cur_index = 0;
      }
      cur_len = (cur_len/2);
      cur_list = firstHalf;
    }
    else{
      if(cur_len==cur_N__){
        cur_index = cur_len/2; 
      }
      else{
        cur_index = cur_index + (cur_len/2);
      }
      cur_len = ceil((float)cur_len/2.0);
      cur_list = secondHalf;
    }
    if(cur_len==1){
      close_val=cur_list[0];
    }
  }
  //If the previous value is the same as the current value, look backwards in 
  //the list by halves (splitting the list) until it finds the earliest value
  //that is the same. This fixes the problem where the closest value is smaller
  //than the input value and occurs multiple times. 
  if(cur_index>0 && close_val==random_list__[cur_index-1]){
    double* cur_half = random_list__;
    int cur_len = cur_index+1; 
    int new_index = 0; 
    while(cur_len>1){
      double *firstHalf = &cur_half[0];
      double *secondHalf = &cur_half[cur_len/2];
      if((close_val-firstHalf[(cur_len/2)-1])==0){
        if(cur_len==cur_index+1){
          new_index = 0;
        }
        cur_half=firstHalf;
        cur_len = (cur_len/2);
      }
      else{
        if(cur_len==cur_index+1){
          new_index = cur_len/2;
        }
        else{
          new_index = new_index + (cur_len/2);
        }
        cur_half=secondHalf;
        cur_len = ceil((float)cur_len/2.0);

      }
    }
    cur_index=new_index;
  }
  //Implement a method for calculating the mean that stores the results for 
  // every index so they don't have to be calculated again
  //Implement a brute force method for calculating the standard deviation
  //using the fact that it is sampled from a uniform distribution. If the
  //length of the random list is >1000 the error is mostly <10%
  double x_mean__=0;
  double std_dev=0;
  if(cur_index==0){
    return std::make_tuple(close_val,cur_index,x_mean__,std_dev);
  }

  x_mean__ = get_mean(cur_index);
  if(cur_N__<1000){
    std_dev = get_std_dev(cur_index);
  }
  else{
    std_dev = get_uniform_std_dev(cur_index);
  }

  return std::make_tuple(close_val,cur_index,x_mean__,std_dev);
}
