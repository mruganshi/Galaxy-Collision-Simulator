#ifndef HELPER_H
#define HELPER_H

#define G 0.009
#define THETA 0.097
#define DELTA_T 0.7


#include<bits/stdc++.h>
class Vec{
public:
    double x;
    double y;
    Vec();
    Vec(double a, double b);
    double distance(Vec v);
    friend bool operator== (const Vec &v1, const Vec&v2);
    friend Vec operator+ (const Vec &v1, const Vec&v2);
    friend Vec operator* (const double &k, const Vec&v2);
};
class reg{
public:
    Vec center;
    double size;
    reg();
    //reg(double x1,double x2, double y1, double y2);
    reg(Vec c, double s);
    bool region_are_same(reg r1);
    bool contains_vec(Vec p);
};
#endif