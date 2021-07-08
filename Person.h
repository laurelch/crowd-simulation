#ifndef PERSON_H
#define PERSON_H
#include <math.h>
#include <vector>
#include <string>
#include <stdio.h>
using namespace std;
class Person{
public:
    static const int dim = 2;

    //float X[dim];
    //float V[dim];
    //float destination[dim];
    vector<float> X;
    vector<float> V;
    vector<float> destination;
    float desired_speed;
    vector<float> desired_velocity;
    float disease = 0.0;
    float mask = 0.0;

    Person();
    //Person(float* X_in, float* V_in, float* destination_in, float desired_speed_in, int group_ID_in);
    Person(int,vector<float>,vector<float>,vector<float>,float,int);
    float getDesiredSpeed();
    void setDesiredSpeed(float);
    //float* get_desired_velocity();
    vector<float> getDesiredVelocity();
    void setDesiredVelocity();
    //void update_pos_vel(float dt, float acceleration[]);
    void updateXV(float,vector<float>);
    void updateDisease(float dt, float disease_in);
    float getDisease();
    void setDisease(int);
    vector<float> getStatus();
    static vector<float> diff(vector<float> a, vector<float> b);
    float dist(Person*);
    float dist(vector<float>, vector<float>);
private:
    int people_ID;
    int group_ID;
};

#endif // PERSON_H
