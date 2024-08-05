#include <iostream>
#include <random>

using namespace std;

int* random_points_generator(int num_points,int seed){
    int* arr=new int[num_points];
    mt19937 gen(seed); 
    int lower_bound = -40;
    int upper_bound = 40;
    uniform_real_distribution<> dis(lower_bound, upper_bound);
    for(int i=0;i<num_points;i++){
        arr[i]=dis(gen);
    }
    return arr;
}

int main(){
    /* random non collinear points generator 
    make line class
    rotate line
    detect collision with point
    change axis of rotation
    add the number of times,line has come to that certain point
    <find pattern-in case odd, find subpatterns-in case even> function
    */
    //testing random point generator
    int* arr=random_points_generator(5,100);
    for(int i=0;i<5;i++){
        cout<<*(arr+i)<<endl;
    }
    //
}



