#include <iostream>
#include <random>
#include <cmath>
#include <unordered_map>
#include "useful_functions.hpp"

using namespace std;


/* make user interface 
random non collinear points generator 
make line class
rotate line
detect collision with point
change axis of rotation
add the number of times,line has come to that certain point
<find pattern-in case odd, find subpatterns-in case even> function
*/
    //making user interface
int main(){
    int user_input;
    int num_points;
    int random_seed;
    int x_coord;
    int y_coord;
    int num_itterations;
    int customized=0;
    rotating_line l({0,0},0,0);
    vector<vector<int>> vec;
    cout<<"This is an application which aims to solve imo 2011 windmill problem(q2)"<<endl<<"user can either go for randomised non collinear points generator or can input non collinear points manually or you can go on full custimize mode in which you can select the initial slope and centre of rotation point for line"<<endl<<"enter [1] for randomised points generator"<<endl<<"enter [2] for manually entering points"<<endl<<"enter [3] for entering full customizable mode"<<endl;
    cin>>user_input;
    if(user_input==3){
        cout<<"do you want to get randomised points or you want to manually enter them?"<<endl<<"Enter [1] for randomised point generation"<<endl<<"Enter [2] for manually entering points"<<endl;
        cin>>customized;
    }
    if(user_input==1 || customized==1){
        cout<<"Enter number of points to test and random seed to take:";
        cin>>num_points;
        cin>>random_seed;
        vec=random_points_generator(num_points,random_seed);
    }
    else if(user_input==2 || customized==2){
        cout<<"Number of non collinear points you want to enter:";
        cin>>num_points;
        for(int i=0;i<num_points;i++){
            cin>>x_coord;
            cin>>y_coord;
            vec.push_back({x_coord,y_coord});
        }
    }
    else{
        cout<<"Invalid user input,try again later!"<<endl;
        return 0;
    }
    cout<<endl;
    //checking for non collinearity
    bool colinearity_checker=colinearity_checker(vec);
    for(int i=0;i<vec.size();i++){
        int x=vec[i][0];
        int y=vec[i][1];
        for(int j=i+1;j<vec.size();j++){
            int x1=vec[j][0];
            int y1=vec[j][1];
            for(int k=j+1;k<vec.size();k++){
                int x2=vec[k][0];
                int y2=vec[k][1];
                if(x1*y2-x2*y1+x*y1-x1*y+x2*y-x*y2==0){ //3 points determinant=0
                    cout<<"Points entered are collinear,try again!"<<endl;
                    return 0;
                }
            }
        }
    }
    vector<double> custom_mid_point={0,0};
    double custom_slope;
    int count=1;
    if(user_input==3){
        for(vector<int>& v:vec){
            cout<<"point "<<count<<":";
            for(int& num:v){
                cout<<num<<" ";
            }
            cout<<endl;
            count++;
        }
        cout<<"Enter centre of rotation point:";
        cin>>custom_mid_point[0];
        cin>>custom_mid_point[1];
        cout<<endl;
        cout<<"Enter slope of line:";
        cin>>custom_slope;
        cout<<endl;
        l.middle_point=custom_mid_point;
        l.slope=custom_slope;
    }
    cout<<"number of times collisions till which you want your line to keep rotating:";
    cin>>num_itterations;
    cout<<endl;
    int verbose;
    cout<<"set verbose(for less info enter 0 , for more enter 1):";
    cin>>verbose;
    if(verbose!=0 && verbose!=1){
        cout<<"Invalid user input,try again later!"<<endl;
        return 0;
    }
    if(user_input==1 || user_input==2){
        l=find_optimal_line(vec,0);
    }
    double special_slope=l.slope;
    count=1;
    if(verbose==1 &&(user_input==1 || user_input==2)){
        for(vector<int>& v:vec){
            cout<<"point "<<count<<":";
            for(int& num:v){
                cout<<num<<" ";
            }
            cout<<endl;
            count++;
        }
    }
    if(user_input==1 || user_input==2){
        cout<<"================="<<"  OPTIMAL LINE  "<<"================="<<endl;
        cout<<"Centre of rotation point: "<<l.middle_point[0]<<" "<<l.middle_point[1]<<endl;
        cout<<"Slope: "<<l.slope<<endl;
        cout<<"Angular velocity: "<<l.angular_velocity<<endl;
        cout<<"=================================================="<<endl;
    }
    vector<vector<double>> vec_to_double;
    for(vector<int> point:vec){
        vector<double> some_point;
        for(int p:point){
            some_point.push_back((double)p);
        }
        vec_to_double.push_back(some_point);
    }
    unordered_map<vector<double>*,int> count_map;
    int index=0;
    int special_index=0;
    for(int k=0;k<vec_to_double.size();k++){
        vector<double>* memory_address=&vec_to_double[k];
        count_map[memory_address]=0;
    }
    for(int k=0;k<vec_to_double.size();k++){
            if(vec_to_double[k]==l.middle_point){
                special_index=k;
            }
        }
    count_map[&vec_to_double[special_index]]=1;
    vector<double> point;
    double slope;
    bool flag=true;
    int next_index;
    vector<double> middle_point;
    vector<double> path;
    path.push_back(l.middle_point[0]);
    path.push_back(l.middle_point[1]);
    path.push_back(l.slope);
    vector<vector<double>> line_path;
    line_path.push_back(path);
    for(int j=0;j<=num_itterations;j++){
        path={};
        next_index=l.closest_point_index(vec);
        middle_point=vec_to_double[next_index];
        if(middle_point[0]-l.middle_point[0]!=0){
            slope=(middle_point[1]-l.middle_point[1])/(middle_point[0]-l.middle_point[0]);
        }
        else{
            slope=100000;
        }
        l=change_line_attributes(l,middle_point,slope-0.00005,l.angular_velocity);
        path.push_back(l.middle_point[0]);
        path.push_back(l.middle_point[1]);
        path.push_back(l.slope);
        line_path.push_back(path);
        for(int k=0;k<vec_to_double.size();k++){
            if(vec_to_double[k]==l.middle_point){
                index=k;
                break;
            }
        }
        count_map[&vec_to_double[index]]+=1;
        //testing
        if((count_map[&vec_to_double[special_index]]==2)&(flag==true)){
            for(pair<vector<double>*,int> p:count_map){
                if (p.first==0){
                    if(verbose==1){
                        cout<<"wrong algorithm!"<<endl;
                    }
                    flag=false;
                    break;
                }
            }
            if(flag==true){
                flag=false;
                if(verbose==1){
                    cout<<"algorithm is correct!"<<endl;
                }
            }
        }
    }
    for(pair<vector<double>*,int> p:count_map){
        cout<<"("<<(*p.first)[0]<<" "<<(*p.first)[1]<<"):"<<p.second<<endl;
    }
    cout<<"line path:"<<endl;
    int local_count=0;
    bool whether_reached=false;
    vector<double> slopes;
    bool another_flag=false;
    int cycle_length;
    for(vector<double> point:line_path){
        local_count+=1;
        if(another_flag==true){
            break;
        }
        if(whether_reached==true){
            another_flag=true;
        }
        if((point[0]==vec_to_double[special_index][0])&(point[1]==vec_to_double[special_index][1])){
            slopes.push_back(point[2]);
            if(vec_to_double.size()%2==1 && slopes.size()==2){
                cycle_length=local_count-1;
                whether_reached=true;
            }
            else if(vec_to_double.size()%2==0 && slopes.size()==3){
                cycle_length=local_count-1;
                whether_reached=true;
            }
        }
        cout<<"("<<point[0]<<" "<<point[1]<<",slope="<<point[2]<<")->";
    }
    for(vector<double> point:line_path){
        if((point[0]==vec_to_double[special_index][0])&(point[1]==vec_to_double[special_index][1])){
            slopes.push_back(point[2]);
        }
    }
    cout<<"repeat"<<endl;
    bool is_every_element_touched=true;
    for(pair<vector<double>*,int> p:count_map){
        if(p.second==0){
            is_every_element_touched=false;
        }
    }
    if(whether_reached==true && is_every_element_touched==true){
        cout<<"cycle detected!"<<endl;
        cout<<"Length of cycle="<<cycle_length<<endl;
    }
    else{
        cout<<"cycle not detected!"<<endl;
    }  
    // if(verbose==1){
    //     cout<<"slopes of line when they reached the initial point"<<endl;
    //     for(double slope:slopes){
    //         cout<<slope<<endl;
    // }
    // }
    return 0;
}