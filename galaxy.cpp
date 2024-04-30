#include "galaxy.h"
Galaxy::Galaxy(int id,int nos, double x, double y, double r){
    this->id = id;
    this->radius = r;
    this->number_of_stars = nos;
    this->stars = new Star[nos];
    black_hole_centre = Star(id,500000,Vec(rand()%10-5,rand()%10-5),Vec(x,y));
    for(int i=0;i<nos;i++){
        double a = rand()*r/INT_MAX + 10;
        double theta = rand()*6.283/INT_MAX;
        //double a = 100.0;
        //double theta = 0;
        double x_cord = x + a*cos(theta);
        double y_cord = y + a*sin(theta);
        Vec velo = Vec(-sqrt(G*black_hole_centre.weight/a)*sin(theta),sqrt(G*black_hole_centre.weight/a)*cos(theta)) + black_hole_centre.velocity;
        //Vec velo = Vec(-sqrt(G*100/a)*sin(theta),sqrt(G*100/a)*cos(theta)) + Vec(rand()%10-5,rand()%10-5); //black_hole_centre.velocity;
        //Vec velo = Vec((id*-1*2)+1,0); Vec(((id*-1*2)+1)*x/100,((id*-1*2)+1)*y/100)
        Vec pos = Vec(x_cord,y_cord);
        stars[i] = Star(id,1,velo,pos);
    }
}
