#include "helper.h"
using namespace std;
Vec::Vec(){
    x=0;
    y=0;
}
Vec::Vec(double a, double b){
    x=a;
    y=b;
}
double Vec::distance(Vec v){
    return (sqrt(pow((this->x-v.x),2)+pow((this->y-v.y),2)));
}
bool operator== (const Vec &v1, const Vec&v2){
    return(v1.x == v2.x && v1.y == v2.y);
}
Vec operator+ (const Vec &v1, const Vec&v2){
    return(Vec(v1.x+v2.x,v1.y+v2.y));
}
Vec operator* (const double &k, const Vec&v2){
    return(Vec(v2.x*k,k*v2.y));
}
reg::reg(){
    this->center = Vec(0,0);
    this->size = 2048;
}
reg::reg(Vec c, double s){
    this->center=c;
    this->size=s;
}
bool reg::region_are_same(reg r1){
    return (r1.center==this->center);
}
bool reg::contains_vec(Vec p){
    bool x_true =  (this->center.x-(this->size)/2.0) < p.x && (this->center.x+(this->size)/2.0) > p.x ;
    bool y_true =  (this->center.y-(this->size)/2.0) < p.y && (this->center.y+(this->size)/2.0) > p.y ;
    return x_true && y_true;
}