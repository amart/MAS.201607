/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Population.hpp
 * Author: matthewsupernaw
 *
 * Created on April 20, 2016, 9:21 AM
 */

#ifndef POPULATION_HPP
#define POPULATION_HPP

#include "../ATL/ATL.hpp"

#include "Common.hpp"
#include "Recruitment.hpp"

namespace noaa {
    namespace mas {

        template<typename T>
        struct CatchData {
            int fleet;
            int area;
            int season;
            
            ErrorType error_type;
            atl::Vector<T> catch_vector;
            atl::Vector<T> error_vector;
            
            ErrorType index_error_type;
            atl::Vector<T> index_vector;
            atl::Vector<T> index_error_vector;
        };

        template<typename T>
        struct Population {
            int id;
            Recruitment<T>* recruitment_model = NULL;
            std::vector<CatchData<T> > catch_data;
            
            ~Population(){
                if(recruitment_model){
                    delete recruitment_model;
                }
            }
        };


    }
}


#endif /* POPULATION_HPP */

