#include "MIGBasicSim.h"
#include <math.h>

MIGBasicSim::MIGBasicSim()
{
    readDescriptionTxt();
    initializeCrowd();
}

MIGBasicSim::~MIGBasicSim()
{

    for(auto p:people){
        delete p;
    }
    people.clear();
}

void MIGBasicSim::readDescriptionTxt(){
    social_force_strength=5.0;
    social_force_range_b=1.0;
    social_force_radius=1.0;
    contact_force_strength=10.0;
    particle_radius=0.05;
    disease_a=0;
    disease_s=1.0;
    disease_radius=2.0;
    disease_range_rs=1.0;
    mask_prob=0;
    healthy_life_prob=0.5;
    vaccine_factor=0;
    relaxation_time=1.0;
    desired_speed=1.0;
    dt=0.01;
    total_time=100;
    time_steps_per_frame=10;
    group_init_radius=10;
    people_per_group=50;
    num_groups=2;
    num_people=num_groups*people_per_group;
    std::vector<float> init_coords_1={-30,0};
    std::vector<float> displacement_coords_1={600,0};
    std::vector<float> init_coords_2={30,0};
    std::vector<float> displacement_coords_2={-600,0};
    initial_centers={init_coords_1,init_coords_2};
    displacements={displacement_coords_1,displacement_coords_2};
}

void MIGBasicSim::initializeCrowd(){
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_real_distribution<float> distribution(-1*group_init_radius,group_init_radius);
    std::uniform_real_distribution<float> probability(0,1);
    for(int g=0;g<num_groups;++g){
        std::vector<float> init_center=initial_centers[g];
        std::vector<float> disp_center=displacements[g];
        //printf("(%f, %f)\t(%f, %f)\n",init_center[0], init_center[1], disp_center[0], disp_center[1]);
        for(int i=0;i<people_per_group;++i){
            std::vector<float> rand_coords={distribution(e1),distribution(e1)};
            std::vector<float> origin={0,0};
            while(Person::dist(rand_coords,origin)>group_init_radius)
                rand_coords={distribution(e1),distribution(e1)};
            std::vector<float> X0={rand_coords[0]+init_center[0],rand_coords[1]+init_center[1]}; //position
            std::vector<float> V0={0.0,0.0}; //velocity
            //std::vector<float> destination={X0[0]+rand_coords[0]+disp_center[0],X0[1]+rand_coords[1]+disp_center[1]};
            std::vector<float> destination={X0[0]+disp_center[0],X0[1]+disp_center[1]};
            bool masked=probability(e1)<mask_prob;
            bool healthy_life=probability(e1)<healthy_life_prob;
            Person* p;
            int p_index=g*people_per_group+i;
            p=new Person(p_index,X0,V0,destination,desired_speed,g,disease_range_rs,masked,healthy_life);
            printf("p[%d],(%f,%f),group=%d,destination=(%f,%f)\n",p_index,X0[0],X0[1],g,destination[0],destination[1]);
            people.push_back(p);
        }
    }
}

void MIGBasicSim::initializeCrowdNoMask(){
    row_in_group=5;
    column_in_group=num_people/(num_groups*row_in_group);
    int p_index=0;
    for(int i=0;i<row_in_group;++i){
        for(int j=0;j<column_in_group;++j){
            std::vector<float> X;
            X.push_back(initial_centers[0][0]-j);
            X.push_back(initial_centers[0][1]+i);
            Person* p;
            p = new Person(p_index,X,initial_velocity,displacements[0],desired_speed,0);
            ++p_index;
            people.push_back(p);
        }
    }
    for(int i=0;i<row_in_group;++i){
        for(int j=0;j<column_in_group;++j){
            std::vector<float> X;
            X.push_back(initial_centers[1][0]-j);
            X.push_back(initial_centers[1][1]+i);
            Person* p;
            p = new Person(p_index,X,initial_velocity,displacements[1],desired_speed,1);
            ++p_index;
            people.push_back(p);
        }
    }
}

std::vector<std::vector<float>> MIGBasicSim::interaction_force_and_disease_spread(Person* p1, Person* p2){
    std::vector<float> difference = Person::diff(p1->X,p2->X);
    float distance = p1->dist(p2);
    float mult_factor = interaction_strength * exp(-1 * distance / interaction_range);
    float disease_mult_factor = 1.0;
    if(distance>interaction_radius){
        return std::vector<std::vector<float>> {{0,0},{0,0}};
    }

    std::vector<float> force = {mult_factor*difference[0]/distance, mult_factor*difference[1]/distance};
    float d_disease = std::max(p2->getDisease()-p1->getDisease(),0.0f); //if p1 is more more infected than p2, p2 cannot infect p1.
    float distance_sq = distance*distance;
    std::vector<float> disease = {(exp(-1*distance)*d_disease*disease_mult_factor)/distance_sq};

    std::vector<std::vector<float>> force_disease;
    force_disease.push_back(force);
    force_disease.push_back(disease);
    return force_disease;
}

std::vector<std::vector<float>> MIGBasicSim::net_interaction_force_and_disease_spread(Person* one){
    std::vector<float> force = {0.0,0.0};
    std::vector<float> disease_change = {0.0};

    for(auto p: people){
        if(p!=one){
            std::vector<std::vector<float>> current_spread = interaction_force_and_disease_spread(one,p);
            std::vector<float> current_force = current_spread[0];
            force[0]+=current_force[0];
            force[1]+=current_force[1];
            disease_change[0]+=current_spread[1][0];
        }
    }
    std::vector<std::vector<float>> force_disease;
    force_disease.push_back(force);
    force_disease.push_back(disease_change);
    return force_disease;
}

void MIGBasicSim::update(){
    for(auto p:people){
        updateOnePerson(p);
    }
}

void MIGBasicSim::updateOnePerson(Person* one){
    std::vector<float> desired_velocity = one->getDesiredVelocity();
    std::vector<float> desired_velocity_force = Person::diff(desired_velocity,one->V);
    std::vector<std::vector<float>> force_disease = net_interaction_force_and_disease_spread(one);
    one->update(dt,force_disease);
}

void MIGBasicSim::outputCSV(int i){
    //zero padding
    std::stringstream ss;
    ss<<std::setw(4)<<std::setfill('0')<<i;
    std::string filename(".\\output\\"+ss.str()+".csv");

    std::fstream fout;
    fout.open(filename,std::fstream::out);
    fout<<"pos_x,pos_y,v_x,v_y,group_ID,disease"<<std::endl<<std::flush;
    for(auto p:people){
        status status = p->getStatus();
        fout<<Particle::statusString(status)<<std::flush;
        fout<<std::endl<<std::flush;
    }
    fout.close();
}

int MIGBasicSim::getNumPeople(){
    return num_people;
}

void MIGBasicSim::setNumPeople(int n){
    num_people = n;
}

void MIGBasicSim::setInfection(int p_index, int disease){
    if(p_index<int(people.size())){
        Person* p = people[p_index];
        p->setDisease(disease);
    }
}

float MIGBasicSim::getInteractionStrength(){
    return interaction_strength;
}

void MIGBasicSim::setInteractionStrength(float s){
    interaction_strength = s;
}

float MIGBasicSim::getInteractionRange(){
    return interaction_range;
}

void MIGBasicSim::setInteractionRange(float r){
    interaction_range = r;
}

float MIGBasicSim::getRelaxationTime(){
    return relaxation_time;
}

void MIGBasicSim::setRelaxationTime(float t){
    relaxation_time = t;
}

float MIGBasicSim::getDesiredSpeed(){
    return desired_speed;
}

void MIGBasicSim::setDesiredSpeed(float s){
    desired_speed = s;
}

float MIGBasicSim::getInteractionRadius(){
    return interaction_radius;
}

void MIGBasicSim::setInteractionRadius(float r){
    interaction_radius = r;
}

float MIGBasicSim::getMaxInteractionForce(){
    return max_interation_force;
}

void MIGBasicSim::setMaxInteractionForce(float f){
    max_interation_force = f;
}

status MIGBasicSim::getStatus(int p_index){
    return people[p_index]->getStatus();
}
