#ifndef GALAXY_H
#define GALAXY_H
#include "star.h"
class Galaxy{
public:
    //----------------------Attributes-------------------------//
    Star black_hole_centre;
    Star* stars;
    int id;
    int number_of_stars;
    double radius;
    //---------------------Constructors------------------------//
    Galaxy(int id, int nos, double x, double y, double r);
};
#endif
