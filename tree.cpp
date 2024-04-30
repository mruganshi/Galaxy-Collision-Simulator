#include "tree.h"
using namespace std;

//---------------------Constructors------------------------//
Node::Node(){
    star =NULL;
    COM = Vec();
    is_leaf = true;
    total_mass = 0;
    node_region = reg();
    for(int i=0; i<4;i++){
        children[i]=NULL;
    }
}
Node::Node(Star* star){
    this->star = star;
    COM = (star->position);
    is_leaf =true;
    total_mass = star->weight;
    node_region = reg();
    for(int i=0; i<4;i++){
        children[i]=NULL;
    }
}
Node::Node(reg r, Star* star){
    this->star = star;
    COM = (star->position);
    total_mass = star->weight;
    is_leaf =true;
    node_region = r;
    for(int i=0; i<4;i++){
        children[i]=NULL;
    }
}
Tree::Tree(){
    root = NULL;
}
//---------------------Tree Methods------------------------//
Node* Tree::insert_recursively(Node* start_node, Node* to_be_inserted){
    if(start_node==NULL){
        start_node = to_be_inserted;
        return start_node;
    }
    if(start_node->is_leaf){
        Node* to_be_inserted_2 = new Node(start_node->node_region,start_node->star);
        start_node->star = NULL;
        start_node->is_leaf = false;
        insert_recursively(start_node,to_be_inserted_2);
        insert_recursively(start_node,to_be_inserted);
        return start_node;
    }
    else if(!(start_node->is_leaf)){
        // if(start_node->node_region.region_are_same(to_be_inserted->node_region)){
        //     cout<<"This should always happen and is happening"<<endl;
        // };
        Vec centre = to_be_inserted->node_region.center;
        double s = to_be_inserted->node_region.size;
        reg sub_region_1(centre + Vec(s/4.0,s/4.0),s/2.0);
        if(sub_region_1.contains_vec(to_be_inserted->star->position)){
            to_be_inserted->node_region = sub_region_1;
            start_node->children[0] = insert_recursively(start_node->children[0],to_be_inserted);
            //cout<<"This is 1"<<endl;
            return start_node;
        }
        reg sub_region_2(centre + Vec(-s/4.0,s/4.0),s/2.0);
        if(sub_region_2.contains_vec(to_be_inserted->star->position)){
            to_be_inserted->node_region = sub_region_2;
            start_node->children[1] = insert_recursively(start_node->children[1],to_be_inserted);
            //cout<<"This is 2"<<endl;
            return start_node;
        }
        reg sub_region_3(centre + Vec(-s/4.0,-s/4.0),s/2.0);
        if(sub_region_3.contains_vec(to_be_inserted->star->position)){
            to_be_inserted->node_region = sub_region_3;
            start_node->children[2] = insert_recursively(start_node->children[2],to_be_inserted);
            //cout<<"This is 3"<<endl;
            return start_node;
        }
        reg sub_region_4(centre + Vec(s/4.0,-s/4.0),s/2.0);
        if(sub_region_4.contains_vec(to_be_inserted->star->position)){
            to_be_inserted->node_region = sub_region_4;
            start_node->children[3] = insert_recursively(start_node->children[3],to_be_inserted);
            //cout<<"This is 4"<<endl;
            return start_node;
        }
        //cout<<"Something which shouldn't happen is happening"<<endl;
    }
    return start_node;     
}
void Tree:: insert(Star* star){
    Node* new_node = new Node(star);
    this->star_array.push_back(star);
    this->root = insert_recursively(this->root,new_node);
}
Vec Tree::Update_COM(Node* start_node){
    Vec c(0,0);
    if(start_node->is_leaf){
        c = start_node->star->position;
        start_node->COM = c;
        start_node->total_mass = start_node->star->weight;
        return c;
    }
    else{
        for(int i=0;i<4;i++){
            if(start_node->children[i]!=NULL){
                c = c + (start_node->children[i]->total_mass)*Update_COM(start_node->children[i]);
                start_node->total_mass += start_node->children[i]->total_mass;
            }
        }
        c = (1/start_node->total_mass)*c;
        start_node->COM = c;
        return c;
    }
}
void Tree::calc_force_and_move(){
    Update_COM(this->root);
    int n = this->star_array.size();
    for(int i=0;i<n;i++){
        Star * current_star = star_array[i];
        Vec force = force_on_star(current_star,this->root);
        //cout<<"Velocity of star "<<i<<" is"<<current_star->velocity.x<<","<<current_star->velocity.y<<" The mag is"<<current_star->velocity.distance(Vec())<<endl;
        current_star->position = current_star->position + DELTA_T*current_star->velocity;
        current_star->velocity = current_star->velocity + ((DELTA_T/current_star->weight)*force);
    }
}
Vec Tree::force_on_star(Star* star, Node* node){
    if(node->is_leaf){
        if(node->star!=star){
            double distance = star->position.distance(node->star->position);
            double force_magnitude = (G*(star->weight)*(node->star->weight))/(pow(distance,3));
            Vec force_direction = node->star->position+(-1*star->position);
            return force_magnitude*force_direction;
        }
        else {
            //cout<<"Is_Leaf wala vec is returned"<<endl;
            return Vec(0,0);
        }
    }
    else{
        double s = (node->node_region).size;
        double r = (star->position).distance(node->COM);
        // double theta = 0.2; // size of the region divided by the distance b/w star and the COM of the region 
        if(s/r<THETA){
            double force_magnitude = (G*(star->weight)*(node->total_mass))/(pow(r,3));
            Vec force_direction = node->COM+(-1*star->position);
            return force_magnitude*force_direction;
        }
        else{
            Vec force(0,0);
            for(int j=0;j<4;j++){
                if(node->children[j]!=NULL){
                    force = force + force_on_star(star,node->children[j]);
                }
            }
            //cout<<"Else wala vec is returned"<<endl;
            //cout<<"Else Force on star is"<<force.x<<","<<force.y<<endl;
            return force;
        }
    }
    return Vec(0,0);
}



//start_node->children[calc_sub_region(start_node->node_region,(to_be_inserted->star)->position)] = ;
        //Vec centre = start_node->node_region.center;
        //double s = start_node->node_region.size;

        // Calculating sub-reg