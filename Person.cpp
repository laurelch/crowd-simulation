#include "Person.h"

//Person::Person(float* X_in, float* V_in, float* destination_in, float desired_speed_in, int group_ID_in)
//{
//    X[0] = X_in[0];
//    X[1] = X_in[1];
//    V[0] = V_in[0];
//    V[1] = V_in[1];
//    destination[0] = destination_in[0];
//    destination[1] = destination_in[1];
//    desired_speed = desired_speed_in;
//    group_ID = group_ID_in;
//}

//Person MIGBasicSim::initialize(float initial_X[], float initial_V[], float desired_displacement[], int group_ID)
//{
//    //Places
//    float destination[2];
//    destination[0] = initial_X[0] + desired_displacement[0];
//    destination[1] = initial_X[1] + desired_displacement[1];
//    return Person(initial_X, initial_V, destination, desired_speed, group_ID);
//}

Person::Person(int i, vector<float> X, vector<float> V, vector<float> displacement, float speed, int group)
{
    people_ID=i;
    this->X = X;
    this->V = V;
    group_ID = group;
    destination.push_back(X[0]+displacement[0]);
    destination.push_back(X[1]+displacement[1]);
    desired_speed = speed;
    setDesiredVelocity();
}

float Person::getDesiredSpeed()
{
    return desired_speed;
}

void Person::setDesiredSpeed(float s)
{
    desired_speed = s;
}

vector<float> Person::getDesiredVelocity()
{
    return desired_velocity;
}

//float* Person::get_desired_velocity()
//{
//    float* ans = diff(X, destination);
//    float distance = dist(ans);
//    if (distance <= 0.001) {
//        ans[0] = 0.0;
//        ans[1] = 0.0;
//        return ans;
//    }
//    ans[0] = ans[0] / distance * desired_speed;
//    ans[1] = ans[1] / distance * desired_speed;
//    return ans;
//}

void Person::setDesiredVelocity(){
    vector<float> df = diff(X,destination);
    float dst = dist(X,destination);
    vector<float> velocity;
    if(dst <= 0.001) {
        velocity.push_back(0.0);
        velocity.push_back(0.0);
    }else{
        velocity.push_back(df[0]/dst*getDesiredSpeed());
        velocity.push_back(df[1]/dst*getDesiredSpeed());
    }
    desired_velocity=velocity;
}

//void Person::update_pos_vel(float dt, float acceleration[]){
//    X[0] = X[0] + V[0] * dt;
//    X[1] = X[1] + V[1] * dt;
//    V[0] = V[0] + acceleration[0] * dt;
//    V[1] = V[1] + acceleration[1] * dt;
//}


/**
 * @brief update position and velocity
 * @param dt
 * @param a
 */
void Person::updateXV(float dt, vector<float> a){
    X[0] = X[0] + V[0] * dt;
    X[1] = X[1] + V[1] * dt;
    V[0] = V[0] + a[0] * dt;
    V[1] = V[1] + a[1] * dt;
}

void Person::updateDisease(float dt, float disease_in){
    disease += disease_in * dt;
    if (disease > 1.0) {
        disease = 1.0;
    }
}

float Person::getDisease(){
    return disease;
}

void Person::setDisease(int d){
    disease = d;
}

vector<float> Person::getStatus(){
    vector<float> status = {X[0],X[1],V[0],V[1],float(group_ID),getDisease()};
    return status;
}

//vector<float> diff(float* a, float* b){
//    vector<float> d;
//    d.push_back(a[0]-b[0]);
//    d.push_back(a[1]-b[1]);
//    return d;
//}

//float dist(float* a, float* b){
//    float x1 = a[0];
//    float y1 = a[1];
//    float x2 = b[0];
//    float y2 = b[1];
//    return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
//}

//float dist(float diffs[])
//{
//    if (!((diffs[0] * diffs[0]) + (diffs[1] * diffs[1]) >= 0)) {
//        printf("Less than 0\n");
//        printf("%f\n", (diffs[0] * diffs[0]) + (diffs[1] * diffs[1]));
//        exit(1);
//    }
//    return sqrt((diffs[0] * diffs[0]) + (diffs[1] * diffs[1]));
//}

vector<float> Person::diff(vector<float> a, vector<float> b){
    vector<float> d;
    d.push_back(a[0]-b[0]);
    d.push_back(a[1]-b[1]);
    return d;
}

float Person::dist(vector<float> a, vector<float> b){
    float x1 = a[0];
    float y1 = a[1];
    float x2 = b[0];
    float y2 = b[1];
    return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}

float Person::dist(Person* b){
    float x1 = X[0];
    float y1 = X[1];
    float x2 = b->X[0];
    float y2 = b->X[1];
    return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}
