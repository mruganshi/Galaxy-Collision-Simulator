#ifndef STAR_H
#define STAR_H
#include "helper.h"
class Star{
private:
    unsigned int parent_galaxy;
public:
    int weight;
    Vec velocity;
    Vec position;
    Star();
    Star(int g, int w, Vec v);
    Star(int g, int w, Vec v, Vec p);
};
#endif