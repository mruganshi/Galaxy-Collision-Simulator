#include "star.h"
using namespace std;
Star::Star(int g, int w, Vec v){
    weight = w;
    velocity = v;
    position = Vec(0,0);
    parent_galaxy = g;
}
Star::Star(int g, int w, Vec v, Vec p){
    weight = w;
    velocity = v;
    position = p;
    parent_galaxy = g;
}
Star::Star(){
    weight=0;
    velocity = Vec();
    position = Vec();
    parent_galaxy = -1;
}