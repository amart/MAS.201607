
/**
 *
 * @author  Matthew R. Supernaw
 *
 * Public Domain Notice
 * National Oceanic And Atmospheric Administration
 *
 * This software is a "United States Government Work" under the terms of the
 * United States Copyright Act.  It was written as part of the author's official
 * duties as a United States Government employee and thus cannot be copyrighted.
 * This software is freely available to the public for use. The National Oceanic 
 * And Atmospheric Administration and the U.S. Government have not placed any 
 * restriction on its use or reproduction.  Although all reasonable efforts have 
 * been taken to ensure the accuracy and reliability of the software and data, 
 * the National Oceanic And Atmospheric Administration and the U.S. Government 
 * do not and cannot warrant the performance warrant the performance or results 
 * that may be obtained by using this  software or data. The National Oceanic 
 * And Atmospheric Administration and the U.S. Government disclaim all 
 * warranties, express or implied, including warranties of performance, 
 * merchantability or fitness for any particular purpose.
 *
 * Please cite the author(s) in any work or product based on this material.
 *
 */

/* 
 * File:   main.cpp
 * Author: matthewsupernaw
 *
 * Created on April 18, 2016, 11:45 AM
 */

#include <cstdlib>
#include "Information.hpp"
#include "MAS.hpp"
#include "ThreadPool.hpp"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    
    atl::Variable<double>::gradient_structure_g.derivative_trace_level = atl::FIRST_ORDER;
    noaa::mas::Information<double>* info = new noaa::mas::Information<double>();
    info->ParseConfig("beta.config.json");
    info->ParseData("beta.data.json");
    info->Initialize();
    
    noaa::mas::MASEngine<double> engine;
    engine.info = info;
    engine.Initialize();
    for (int i = 0; i < 1000; i++)
        engine.Evaluate();
    atl::Variable<double>::gradient_structure_g.Accumulate();
    atl::Variable<double>::gradient_structure_g.Reset();
    //    for(int i =0; i < info.subpopulations.size(); i++){
    //        std::cout<<info.subpopulations[i]<<"\n";
    //    }

    return 0;
}

