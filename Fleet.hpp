/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Fleet.hpp
 * Author: matthewsupernaw
 *
 * Created on April 20, 2016, 9:25 AM
 */

#ifndef FLEET_HPP
#define FLEET_HPP

#include "Selectivity.hpp"

namespace noaa{
    namespace mas{
     
        template<typename T>
        struct Fleet{
            int id;
            std::string fleet_name;
            std::vector<std::shared_ptr<Selectivity<T> > > selectivity;
        };
        
        
    }
}


#endif /* FLEET_HPP */

