#ifndef SOURCEMC_H
#define SOURCEMC_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>
#include <ctime>
#include <cmath>
#include <thread>
#include <chrono>
#include <sys/time.h>
#include <TRandom.h>

/*
bool read_sim_range(double _pressure, std::vector<double> &_range_Am241_sim, std::vector<double> &_range_Am243_sim);

long long seed();

double smear_xy(std::vector<double> &_range_sim);

double smear_z_range(std::vector<double> &_range_sim);

std::vector<double>  apply_collimator();

double choose_emission_point();

double smear_z_range_by_source(double prim_range);

int activity_ratio();*/

bool read_sim_range(double _pressure, std::vector<double> &_range_Am241_sim, std::vector<double> &_range_Am243_sim, std::vector<double> &_range_Cm243_sim){
    std::vector<double> press_Am241, press_Am243, press_Cm243, range_Am241_db, strugg_xy_Am241, strugg_z_Am241, range_Am243_db, strugg_xy_Am243, strugg_z_Am243, range_Cm243_db, strugg_xy_Cm243, strugg_z_Cm243;
    double tmp;
    std::ifstream data_Am241("../docs_logs/am241_range.txt");
    if(!data_Am241.is_open()){
         std::cerr<<"Am241 data base not upload!"<<std::endl;
         return false;
    }
    while(!data_Am241.eof()){
        data_Am241>>tmp;
        press_Am241.push_back(tmp);
        data_Am241>>tmp;
        range_Am241_db.push_back(tmp);
        data_Am241>>tmp;
        strugg_z_Am241.push_back(tmp);
        data_Am241>>tmp;
        strugg_xy_Am241.push_back(tmp);
    }
    std::cout<<"Data base for Am241 upload"<<std::endl;
    data_Am241.close();
    std::cout<<"Data base for Am241 closed"<<std::endl;
    std::ifstream data_Am243("../docs_logs/am243_range.txt");
    if(!data_Am243.is_open()){
        std::cerr<<"Am243 data base not upload!"<<std::endl;
        return false;
    }
    while(!data_Am243.eof()){
        data_Am243>>tmp;
        press_Am243.push_back(tmp);
        data_Am243>>tmp;
        range_Am243_db.push_back(tmp);
        data_Am243>>tmp;
        strugg_z_Am243.push_back(tmp);
        data_Am243>>tmp;
        strugg_xy_Am243.push_back(tmp);       
    }
    std::cout<<"Data base for Am243 upload"<<std::endl;
    data_Am243.close();
    std::cout<<"Data base for Am243 closed"<<std::endl;
    
    std::ifstream data_Cm243("../docs_logs/cm243_range.txt");
    if(!data_Cm243.is_open()){
        std::cerr<<"Cm243 data base not upload!"<<std::endl;
        return false;
    }
    while(!data_Cm243.eof()){
        data_Cm243>>tmp;
        press_Cm243.push_back(tmp);
        data_Cm243>>tmp;
        range_Cm243_db.push_back(tmp);
        data_Cm243>>tmp;
        strugg_z_Cm243.push_back(tmp);
        data_Cm243>>tmp;
        strugg_xy_Cm243.push_back(tmp);       
    }
    std::cout<<"Data base for Cm243 upload"<<std::endl;
    data_Cm243.close();
    std::cout<<"Data base for Cm243 closed"<<std::endl;
    
    if(press_Am241.size()>0 && press_Am243.size()>0 && press_Cm243.size()>0 && range_Am241_db.size()>0 && strugg_xy_Am241.size()>0 && strugg_z_Am241.size()>0 && range_Am243_db.size()>0 && strugg_xy_Am243.size()>0 && strugg_z_Am243.size()>0 && range_Cm243_db.size()>0 && strugg_xy_Cm243.size()>0 && strugg_z_Cm243.size()>0){
        for(unsigned int ip241=0; ip241<press_Am241.size(); ip241++){
            if(press_Am241.at(ip241)>(_pressure-_pressure*0.05) && press_Am241.at(ip241)<(_pressure+_pressure*0.05)){
                _range_Am241_sim.push_back(range_Am241_db.at(ip241));
                _range_Am241_sim.push_back(strugg_z_Am241.at(ip241));
                _range_Am241_sim.push_back(strugg_xy_Am241.at(ip241));
            }
        }
        for(unsigned int ip243=0; ip243<press_Am243.size(); ip243++){
            if(press_Am243.at(ip243)>(_pressure-_pressure*0.05) && press_Am243.at(ip243)<(_pressure+_pressure*0.05)){
                 _range_Am243_sim.push_back(range_Am243_db.at(ip243));
                 _range_Am243_sim.push_back(strugg_z_Am243.at(ip243));
                 _range_Am243_sim.push_back(strugg_xy_Am243.at(ip243));
            }
        }
        for(unsigned int ipc243=0; ipc243<press_Cm243.size(); ipc243++){
            if(press_Cm243.at(ipc243)>(_pressure-_pressure*0.05) && press_Cm243.at(ipc243)<(_pressure+_pressure*0.05)){
                 _range_Cm243_sim.push_back(range_Cm243_db.at(ipc243));
                 _range_Cm243_sim.push_back(strugg_z_Cm243.at(ipc243));
                 _range_Cm243_sim.push_back(strugg_xy_Cm243.at(ipc243));
            }
        }
    }
    else {
        std::cerr<<"Data base processing problem"<<std::endl;
        return false;
    }
    return true;    
}

long long seed(){
    struct timeval tp;
    gettimeofday(&tp, NULL);
    long long ms = (long long)tp.tv_sec * 1000L + tp.tv_usec / 1000;
    return ms;
}

double smear_xy(double _range, std::vector<double> &_range_sim){
    gRandom = new TRandom();
    gRandom->SetSeed(seed());
    if(_range_sim.size()>0)
        return gRandom->Gaus(_range, _range_sim.at(2));
    else{
        std::cerr<<"Alpha range characteristics not given. Cannot process!"<<std::endl;
        return 0;
    }
}
double smear_z_range(double _range, std::vector<double> &_range_sim){
    gRandom = new TRandom();
    gRandom->SetSeed(seed());
    if(_range_sim.size()>0)
        return gRandom->Gaus(_range, _range_sim.at(1)+0.6);
    else{
        std::cerr<<"Alpha range characteristics not given. Cannot process!"<<std::endl;
        return 0.0;
    }
}

std::vector<double>  apply_collimator(){
    double tmp;
    std::vector<double> collimator;
    std::string Trash;
    std::ifstream collimator_constants("../docs_logs/collimator.txt");
    if(!collimator_constants.is_open()){
         std::cerr<<"Collimator characteristics not applied"<<std::endl;
         collimator.clear();
    }
     for(int i=0; i<3; i++){
        collimator_constants>>Trash;
        collimator_constants>>tmp;
        collimator.push_back(tmp);
    }
    return collimator;
}

double choose_emission_point(){
     double d;
    std::string Trash;
    std::ifstream source_constants("../docs_logs/source.txt");
    if(!source_constants.is_open()){
         std::cerr<<"Source characteristics not applied. Particles emitted from the center of the source"<<std::endl;
         return 0.0;
    }
     else{
        source_constants>>Trash;
        source_constants>>d;
    }
    gRandom = new TRandom();
    gRandom->SetSeed(seed());
    return gRandom->Uniform(0.0, (d/2.0));
}

double smear_z_range_by_source(double prim_range){
    std::vector<double> collimator = apply_collimator();
    if(collimator.size()!=3){
//         std::cout<<"Collimator characteristics not applied. Type: \n 1 - to process without emission angle smearing \n 2  - to process angle smearing without any collimator \n 3 - to stop"<<std::endl;
        // To be finished...
        return prim_range;
    }
    double emission = choose_emission_point();
    if(!(emission>0.0)){
        return prim_range;
    }
    gRandom = new TRandom();
    gRandom->SetSeed(seed());
    double angle_max1 = atan2 (std::abs(emission), collimator.at(0));
    double angle_max2 = atan2 (std::abs(emission+1.0), collimator.at(0));
/*    if(){
        
    }   */     
    double angle = gRandom->Uniform(0.0, angle_max1);
    double range_z = prim_range * cos(angle);
    return range_z;
}

std::vector <int> activity_ratio(){
     double a241, a243, cm243;
     std::vector<int> activity;
    std::string Trash;
    std::ifstream source_constants("../docs_logs/source.txt");
    if(!source_constants.is_open()){
         std::cerr<<"Source characteristics not applied. Am241/Am243 ratio = 1"<<std::endl;
         activity.push_back(1);
         activity.push_back(1);
    }
     else{
        source_constants>>Trash>>Trash>>Trash;
        source_constants>>a241;
        source_constants>>Trash;
        source_constants>>a243;
        source_constants>>Trash;
        source_constants>>cm243;
        activity.push_back(round(a243/a241));
        activity.push_back(round(a243/cm243));
        std::cout<<a243/cm243<<std::endl;
    }
    return activity;
}
#endif
