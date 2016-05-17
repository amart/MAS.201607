/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Common.hpp
 * Author: matthewsupernaw
 *
 * Created on April 27, 2016, 1:05 PM
 */

#ifndef COMMON_HPP
#define COMMON_HPP

#include "third_party/rapidjson/document.h"
#include "ATL/ATL.hpp"

namespace noaa {
    namespace mas {

        enum GenderType{
            MALE = 0,
            FEMALE,
            BOTH
        };
        
        enum GrowthType{
            VONB = 0,
            UNKNOWN_GROWTH
        };
        
        enum ErrorType {
            NA= -1,
            CV
        };

        template<typename T>
        struct ModelFunctor {
            //variable, phase
            std::vector<std::pair<atl::Variable<T>*, int> > estimable;
            virtual void Evaluate() = 0;
        };
    }
}

#endif /* COMMON_HPP */

