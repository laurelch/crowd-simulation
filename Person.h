#ifndef PERSON_H
#define PERSON_H
#include <algorithm>
#include <math.h>
#include <vector>
#include <string>
#include <stdio.h>
#include "particle.h"
class Person{
public:
    std::vector<float> X;
    std::vector<float> V;
    std::vector<float> destination;
    float desired_speed;
    std::vector<float> desired_velocity;

    Person();
    Person(int,std::vector<float>,std::vector<float>,std::vector<float>,float,int);
    Person(int,std::vector<float>,std::vector<float>,std::vector<float>,float,int,float,bool,bool);
    void update(float,std::vector<std::vector<float>>);
    void update(float,std::vector<std::vector<float>>,float,float);
    void updateXV(float,std::vector<float>);
    void updateDisease(float,float);
    void updateImmunity(float,float);
    void updateImmunity(float,float,float);

    float getDesiredSpeed();
    std::vector<float> getDesiredVelocity();
    float getDisease();
    float getDiseaseSq();
    status getStatus();
    int getID();

    void setDesiredSpeed(float);
    void setDesiredVelocity();
    void setDisease(int);
    static std::vector<float> diff(std::vector<float> a,std::vector<float> b);
    float dist(Person*);
    static float dist(std::vector<float>,std::vector<float>);
    float clamp(float,float,float);
private:
    int people_ID;
    int group_ID;
    float disease;
    float mask;
    float immunity;
    float immunity_strength;
};

#endif // PERSON_H
