/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: matthewsupernaw
 *
 * Created on April 18, 2016, 11:45 AM
 */

#include <cstdlib>
#include "Information.hpp"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    noaa::mas::Information<double> info;
    info.ParseConfig("beta.config.json");
    info.ParseData("beta.data.json");
    info.Initialize();
//    noaa::mas::Information<double>::population_data_iterator it;
//    for (it = info.population_data.begin(); it !=  info.population_data.end(); ++it) {
//        std::cout<<(*it).second<<"\n";
//    }
    
    for(int i =0; i < info.subpopulations.size(); i++){
        std::cout<<info.subpopulations[i]<<"\n";
    }
    
    return 0;
}

