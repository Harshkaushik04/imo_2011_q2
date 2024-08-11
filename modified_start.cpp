#include <iostream>
#include <random>
#include <cmath>
#include <unordered_map>
#include <SFML/Graphics.hpp>

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

            // int count=0;
            // for(int j=0;j<vec.size();j++){
            //     bool flag=true;
            //     vector<int> point=vec[j];
            //     double static_slope=(double)(new_vec.at(1)-point.at(1))/(double)(new_vec.at(0)-point.at(0));
            //     cout<<new_vec[0]<<endl;
            //     for(int k=j+1;k<vec.size();k++){
            //         vector<int> dynamic_point=vec[k];
            //         double dynamic_slope=(double)(dynamic_point.at(1)-point.at(1))/(double)(dynamic_point.at(0)-point.at(0));
            //         if((dynamic_slope-static_slope>-0.01)&(dynamic_slope-static_slope<0.01)){
            //             flag=false;
            //             cout<<"hi"<<endl;
            //             break;
            //         }
            //     }
            //     if(flag==false){
            //         break;
            //     }
            //     count++;
            // }
            // if(count==vec.size()){
            //     vec.push_back(new_vec);
            // }
        // }
        // else{
        //     vec.push_back(new_vec);
        // }

class rotating_line{
public:
    vector<double> middle_point;
    double slope;
    double angular_velocity;

public:
    rotating_line(vector<double> middle_point,double slope,double angular_velocity){
        this->middle_point=middle_point;
        this->slope=slope;
        this->angular_velocity=angular_velocity;
    }
    
public:
    int closest_point_index(vector<vector<int>> vec){
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
        // cout<<"before_hi:"<<endl;
        if (normal_dict.size()>0){
            for(pair<vector<int>*,double> pair:normal_dict){
                // cout<<"normal_dict element:("<<(*pair.first)[0]<<" "<<(*pair.first)[1]<<") "<<pair.second<<endl;
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
        //normal_dict size=0
        else{
            for(pair<vector<int>*,double> pair:exception_dict){
                // cout<<"exception_dict element:("<<(*pair.first)[0]<<" "<<(*pair.first)[1]<<") "<<pair.second<<endl;
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

    // double distance=100.0;
        // double x=this->middle_point[0];
        // double y=this->middle_point[1];
        // int index=0;
        // for(int i=0;i<vec.size();i++){
        //     double x1=(double)vec[i][0];
        //     double y1=(double)vec[i][1];
        //     double m=this->slope;
        //     //dot product of vector(1):between mid point and external point,vector(2):projected point on line to middle point 
        //     // if(m*(-m*x1+y1+m*x-y)*(x1-x)/(pow(m,2)+1)+(m*x1-y1-m*x+y)*(y1-y)/(pow(m,2)+1)>0)
        //     if((y1-m*x1+m*x-y>0)&((y1-m*x1+m*x-y)/sqrt(pow(m,2)+1)<distance)){ //line-point distance
        //         distance=(y1-m*x1+m*x-y)/sqrt(pow(m,2)+1);
        //         index=i;
        //     }
        //     else if((y1-m*x1+m*x-y<0)&((-y1+m*x1-m*x+y)/sqrt(pow(m,2)+1)<distance)){
        //         distance=(-y1+m*x1-m*x+y)/sqrt(pow(m,2)+1);
        //         index=i;
        //     }
        // }
        // return index;

    // double time_to_collide(int index,vector<vector<int>> vec){
    //     vector<int> point=vec[index];

    // }
};

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
                // if (flag==false){
                //     break;
                // }
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

class simulation{
public:
    int window_width;
    int window_height;
    sf::RenderWindow* window;
    vector<vector<double>> points_list_vector;
    int fps;
public:
    simulation(int window_width,int window_height,sf::RenderWindow* window,vector<vector<double>> points_list_vector,int fps){
        this->window_width=window_width;
        this->window_height=window_height;
        this->window=window;
        this->points_list_vector=points_list_vector;
        this->fps=fps;
    }
public:
    void show_points(float addition_x_offset,float addition_y_offset,float multiplication_x_offset,float multiplication_y_offset){
        sf::Event event;
        vector<sf::CircleShape> point_objects; 
        for(vector<double> point:this->points_list_vector){
            double x=point[0];
            double y=point[1];
            sf::CircleShape circle(0.5*multiplication_x_offset);
            circle.setOrigin(circle.getRadius(),circle.getRadius());
            circle.setPosition(x*multiplication_x_offset+addition_x_offset+(this->window->getSize().x)/2,y*multiplication_y_offset+addition_y_offset+(this->window->getSize().y)/2);
            circle.setFillColor(sf::Color(0,0,255));
            point_objects.push_back(circle);
        }

        while(this->window->isOpen()){

            //event handling
            while(this->window->pollEvent(event)){
                if(event.type==sf::Event::Closed){
                    this->window->close();
                }
            }

            //rendering part of main game loop
            this->window->clear();

            //draw things
            for(int i=0;i<point_objects.size();i++){
                this->window->draw(point_objects[i]);
            }
            this->window->display();
        }
    }

    bool isPointInRectangle(const sf::Vector2f& point, const sf::RectangleShape& rect) {
        return rect.getGlobalBounds().contains(point);
    }

//,float line_height,float angular_velocity,vector<vector<double>> points_list_vector,vector<double> intial_centre,float initial_slope
    bool checkCollision(const sf::CircleShape& circle, const sf::RectangleShape& rectangle) {
        // Get circle position and radius
        sf::Vector2f circlePos = circle.getPosition();
        float circleRadius = circle.getRadius();

        // Get rectangle position, size, and bounds
        sf::FloatRect rectBounds = rectangle.getGlobalBounds();
        
        // Find the closest point on the rectangle to the circle's center
        float closestX = std::max(rectBounds.left, std::min(circlePos.x, rectBounds.left + rectBounds.width));
        float closestY = std::max(rectBounds.top, std::min(circlePos.y, rectBounds.top + rectBounds.height));
        
        // Compute the distance between the closest point and the circle's center
        float distanceX = circlePos.x - closestX;
        float distanceY = circlePos.y - closestY;
        float distanceSquared = distanceX * distanceX + distanceY * distanceY;
        
        // Check if the distance is less than or equal to the radius squared
        return distanceSquared <= (circleRadius * circleRadius);
    }
    void start_simulation(float addition_x_offset,float addition_y_offset,float multiplication_x_offset,float multiplication_y_offset,vector<double> initial_point,double slope,float angular_velocity){
            bool flag=false;
            for(vector<double> point:points_list_vector){
                if(initial_point==point){
                    flag=true;
                    break;
                }
            }
            if(flag==false){
                cout<<"point not found!"<<endl;
                return;
            }
            sf::Event event;
            vector<sf::CircleShape> point_objects; 
            vector<vector<double>>simulation_vec_to_double;
            for(vector<double> point:this->points_list_vector){
                double x=point[0];
                double y=point[1];
                simulation_vec_to_double.push_back({x*multiplication_x_offset+addition_x_offset+(this->window->getSize().x)/2,y*multiplication_y_offset+addition_y_offset+(this->window->getSize().y)/2});
            }
            for(vector<double> point:this->points_list_vector){
                double x=point[0];
                double y=point[1];
                sf::CircleShape circle(0.5*multiplication_x_offset);
                circle.setOrigin(circle.getRadius(),circle.getRadius());
                circle.setPosition(x*multiplication_x_offset+addition_x_offset+(this->window->getSize().x)/2,y*multiplication_y_offset+addition_y_offset+(this->window->getSize().y)/2);
                circle.setFillColor(sf::Color(0,0,255));
                point_objects.push_back(circle);
            }
            sf::RectangleShape line(sf::Vector2f(2*max(addition_x_offset,addition_y_offset)*max(multiplication_x_offset,multiplication_y_offset),2));
            line.setOrigin(line.getSize().x/2,line.getSize().y/2);
            initial_point[0]=initial_point[0]*multiplication_x_offset+addition_x_offset+(this->window->getSize().x)/2;
            initial_point[1]=initial_point[1]*multiplication_y_offset+addition_y_offset+(this->window->getSize().y)/2;
            line.setPosition(initial_point[0],initial_point[1]);
            line.setFillColor(sf::Color(0,255,0));
            line.rotate(-atan(slope)*180/3.14159);
            sf::CircleShape current_point;
            bool another_flag=false;
            for(sf::CircleShape point:point_objects){
                if((initial_point[0]==point.getPosition().x)&(initial_point[1]==point.getPosition().y)){
                    current_point=point;
                    another_flag=true;
                    break;
                }
            }
            if(another_flag==false){
                cout<<"logic wrong in current_point!"<<endl;
                return;
            }
            another_flag=false;
            while(this->window->isOpen()){

                //event handling
                while(this->window->pollEvent(event)){
                    if(event.type==sf::Event::Closed){
                        this->window->close();
                    }
                }
                //logic handling
                for(sf::CircleShape point_object:point_objects){
                    if(point_object.getPosition().x!=current_point.getPosition().x || point_object.getPosition().y!=current_point.getPosition().y){
                        if(isPointInRectangle({point_object.getPosition().x,point_object.getPosition().y},line)){
                            line.setOrigin(point_object.getPosition().x,point_object.getPosition().y);
                            current_point=point_object;
                        }
                    }
                }

                //rendering part of main game loop
                this->window->clear();

                //draw things
                for(int i=0;i<point_objects.size();i++){
                    this->window->draw(point_objects[i]);
                }
                this->window->draw(line);
                line.rotate(angular_velocity);
                this->window->display();
            }
        }
};



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
    vector<vector<int>> vec=random_points_generator(105,29);
    // vector<vector<int>> vec={{0,0},{2,2},{2,-2},{1,0}};
    rotating_line l=find_optimal_line(vec,0);
    double special_slope=l.slope;
    for(vector<int>& v:vec){
        for(int& num:v){
            cout<<num<<" ";
        }
        cout<<endl;
    }
    cout<<l.middle_point[0]<<endl;
    cout<<l.middle_point[1]<<endl;
    cout<<l.slope<<endl;
    cout<<l.angular_velocity<<endl;
    vector<vector<double>> vec_to_double;
    for(vector<int> point:vec){
        vector<double> some_point;
        for(int p:point){
            some_point.push_back((double)p);
        }
        vec_to_double.push_back(some_point);
    }
    unordered_map<vector<double>*,int> count_map;
    // vector<double>* mem_address;
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
    // line_path.push_back(l.middle_point);
    for(int j=0;j<=400;j++){
        path={};
        next_index=l.closest_point_index(vec);
        // cout<<"new:"<<next_index<<endl;
        middle_point=vec_to_double[next_index];
        // line_path.push_back(middle_point);
        // cout<<"hi: "<<l.middle_point[0]<<" "<<l.middle_point[1]<<endl;
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
        // for(double p:l.middle_point){
        //     cout<<p<<" ";
        // }
        // cout<<endl;
        for(int k=0;k<vec_to_double.size();k++){
            // point=vec_to_double[k];
            if(vec_to_double[k]==l.middle_point){
                index=k;
                // mem_address=&point;
                // cout<<"hi"<<endl;
                // cout<<"new_hi: "<<l.middle_point[0]<<" "<<l.middle_point[1]<<" "<<l.slope<<endl;
                // cout<<"wow: "<<mem_address<<" "<<&point<<endl;
                break;
            }
        }
        // cout<<mem_address<<endl;
        count_map[&vec_to_double[index]]+=1;
        //testing
        if((count_map[&vec_to_double[special_index]]==2)&(flag==true)){
            for(pair<vector<double>*,int> p:count_map){
                if (p.first==0){
                    cout<<"wrong algorithm!"<<endl;
                    flag=false;
                    break;
                }
            }
            if(flag==true){
                flag=false;
                cout<<"algorithm is correct!"<<endl;
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
    for(vector<double> point:line_path){
        local_count+=1;
        if(another_flag==true){
            break;
        }
        if(whether_reached==true){
            another_flag=true;
        }
        if((point[2]-special_slope<0.05)&(point[0]==vec_to_double[special_index][0])&(point[1]==vec_to_double[special_index][1])&(local_count!=1)){
            whether_reached=true;
        }
        if((point[0]==vec_to_double[special_index][0])&(point[1]==vec_to_double[special_index][1])){
            slopes.push_back(point[2]);
        }
        cout<<"( "<<point[0]<<" "<<point[1]<<",slope="<<point[2]<<")->";
    }
    cout<<"end"<<endl;
    if(whether_reached==true){
        cout<<"cycle detected!"<<endl;
    }

    else{
        cout<<"cycle not detected!"<<endl;
    }  
    cout<<"slopes of line when they reached the initial point"<<endl;
    for(double slope:slopes){
        cout<<slope<<endl;
    }
    int window_width=800;
    int window_height=600;
    int fps=60;

    sf::RenderWindow window(sf::VideoMode(window_width,window_height),"simulation");
    sf::RenderWindow* window_address= &window;
    simulation new_simulation(window_width,window_height,window_address,vec_to_double,fps);
    // new_simulation.show_points(40,40,5,5)
    new_simulation.start_simulation(40,40,5,5,{29,24},0.7535,0.001);
    return 0;
}
