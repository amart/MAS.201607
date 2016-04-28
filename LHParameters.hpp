/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LHParameters.hpp
 * Author: matthewsupernaw
 *
 * Created on April 20, 2016, 9:23 AM
 */

#ifndef LHPARAMETERS_HPP
#define LHPARAMETERS_HPP

#include "Common.hpp"

namespace noaa{
    namespace mas{
        
        template<typename T>
        struct Mortality: ModelFunctor<T>{
            GenderType gender;
            atl::Vector<atl::Variable<T> > m;
            
            static GenderType GetGenderType(const std::string& str){
                if(str == "male"){
                    return MALE;
                }else if(str == "female"){
                    return FEMALE;
                }else if(str == "both"){
                    return BOTH;
                }else{
                    std::cout<<"Gender string \""<<str<<"\" unknown.";
                    return BOTH;
                }
            }
            
            virtual void Evaluate(){}
            
        };
     
        template<typename T>
        struct LHParameters{
            std::vector<Mortality<T> > M;
            
        };
        
        
    }
}


#endif /* LHPARAMETERS_HPP */

