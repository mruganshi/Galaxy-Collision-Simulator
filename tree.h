#ifndef TREE_H
#define TREE_H
#include "star.h"
class Node{
public:
    //----------------------Attributes-------------------------//
    Star* star;
    Vec COM;
    double total_mass;
    bool is_leaf;
    reg node_region;
    Node* children[4];
    //---------------------Constructors------------------------//
    Node();
    Node(Star* star);
    Node(reg r, Star* star);
};
class Tree{
public:
    //----------------------Attributes-------------------------//
    Node* root;
    std::vector <Star*> star_array;
    //---------------------Constructors------------------------//
    Tree();
    //------------------------Methods--------------------------//
    void insert(Star* star);
    Node* insert_recursively(Node* start_node, Node* to_be_inserted);
    Vec Update_COM(Node* start_node);
    void calc_force_and_move();
    Vec force_on_star(Star* star, Node* node);
};
#endif
