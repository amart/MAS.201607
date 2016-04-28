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
    return 0;
}

