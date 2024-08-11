#include <iostream>
#include <random>
#include <cmath>
#include <unordered_map>
#include "..\include\geometric.hpp"

using namespace std;


vector<vector<int>> random_points_generator(int num_points,int seed){
    vector<vector<int>> vec;
    mt19937 gen(seed); 
    int lower_bound = -40;
    int upper_bound = 40;
    uniform_int_distribution<> dis(lower_bound, upper_bound);
    while(vec.size()<num_points){
        vector<int> new_vec={dis(gen),dis(gen)};
        int x=new_vec[0];
        int y=new_vec[1];
        if(vec.size()>1){
            bool flag=true;
            for(int j=0;j<vec.size();j++){
                int x1=vec[j][0];
                int y1=vec[j][1];
                for(int k=j+1;k<vec.size();k++){
                    int x2=vec[k][0];
                    int y2=vec[k][1];
                    if(x1*y2-x2*y1+x*y1-x1*y+x2*y-x*y2==0){ //3 points determinant=0
                        flag=false;
                        break;
                    }
                }
                if(flag==false){
                    break;
                }
            }
            if(flag==true){
                vec.push_back(new_vec);
            }
        }
        else if((vec.size()==0)||(vec.size()==1)){
            vec.push_back(new_vec);
        }
    }
    return vec;
}

bool colinearity_checker(vector<vector<int>> vec){
    bool flag=true;
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
                    return false;
                }
            }
        }
    }
    if(flag==true){
        return true;
    }
}

rotating_line::rotating_line(vector<double> middle_point,double slope,double angular_velocity){
        this->middle_point=middle_point;
        this->slope=slope;
        this->angular_velocity=angular_velocity;
    }

int rotating_line::closest_point_index(vector<vector<int>> vec){
    vector<vector<int>> priority_list;
    unordered_map<vector<int>*,double> normal_dict;
    unordered_map<vector<int>*,double> exception_dict;
    double m=this->slope;
    double x=this->middle_point[0];
    double y=this->middle_point[1];
    vector<int>* memory_address;
    double x1;
    double y1;
    for(int i=0;i<vec.size();i++){
        memory_address=&vec[i];
        x1=(double)vec[i][0];
        y1=(double)vec[i][1];
        if((x1!=x)||(y1!=y)){
            if(x1-x!=0){
                double m1=(y1-y)/(x1-x);
                if(m1>m){
                    exception_dict[memory_address]=m1;
                }
                else{
                    normal_dict[memory_address]=m1;
                }
            }
            else{
                if(m>0){
                    exception_dict[memory_address]=100000;
                }
                else if(m<0){
                    normal_dict[memory_address]=-100000;
                }
            }
        }
    }
    double max_m=-1000000;
    vector<int> selected_point;
    int selected_index;
    if (normal_dict.size()>0){
        for(pair<vector<int>*,double> pair:normal_dict){
            if(pair.second>max_m){
                max_m=pair.second;
                selected_point=*pair.first;
            }
        }
        for(int i=0;i<vec.size();i++){
            if(vec[i]==selected_point){
                selected_index=i;
            }
        }
    }
    else{
        for(pair<vector<int>*,double> pair:exception_dict){
            if(pair.second>max_m){
                max_m=pair.second;
                selected_point=*pair.first;
            }
        }
        for(int i=0;i<vec.size();i++){
            if(vec[i]==selected_point){
                selected_index=i;
            }
        }
    }
    return selected_index;
}

double find_value(rotating_line l,vector<double> point){
    double x1=l.middle_point[0];
    double y1=l.middle_point[1];
    double m=l.slope;
    double x=point[0];
    double y=point[1];
    double value=m*x+y1-m*x1;
    return value;
}

rotating_line find_optimal_line(vector<vector<int>> vec,double angular_velocity){
    vector<vector<double>> vec_to_double;
    rotating_line l({0,0},0,0);
    int positive;
    int negative;
    for(vector<int> point:vec){
        vector<double> some_point;
        for(int p:point){
            some_point.push_back((double)p);
        }
        vec_to_double.push_back(some_point);
    }
    for(vector<double> point:vec_to_double){
        double value;
        for(int m=0;m<360;m++){
            positive=0;
            negative=0;
            bool flag=true;
            if((m!=90) & (m!=270)){
                double slope=tan(m*3.14159/180);
                l.middle_point=point;
                l.slope=slope;
                l.angular_velocity=angular_velocity;
                for(vector<double> other_point:vec_to_double){
                    if(point!=other_point){
                        value=find_value(l,other_point);
                        if(value==0){
                            //flag=false;
                            break;
                        }
                        else if(value>0){
                            positive+=1;
                        }
                        else if(value<0){
                            negative+=1;
                        }
                    }
                }
            }
            if(vec.size()%2==1){
                if((positive==negative)&(positive+negative==vec.size()-1)){
                    cout<<"positive:"<<positive<<" negative:"<<negative<<endl;
                    return l;
                }
            }
            else if((vec.size()%2==0)&(positive+negative==vec.size()-1)){
                if(positive==negative+1 || negative==positive+1){
                    cout<<"positive:"<<positive<<" negative:"<<negative<<endl;
                    return l;
                }
            }
        }
    }
    cout<<"need more values!"<<endl;
    return l;
}

rotating_line change_line_attributes(rotating_line l,vector<double> middle_point,double slope,double angular_velocity){
    l.middle_point=middle_point;
    l.slope=slope;
    l.angular_velocity=angular_velocity;
    return l;
}
