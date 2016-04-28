/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ModelFunctor.hpp
 * Author: matthewsupernaw
 *
 * Created on April 27, 2016, 11:45 AM
 */

#ifndef MODELFUNCTOR_HPP
#define MODELFUNCTOR_HPP

#include "MAS.hpp"


namespace noaa{
    namespace mas{
        
        template<typename T>
        class Growth {
            MASEngine<T>* engine;
            
            public:
                virtual const atl::Variable<T> Evaluate(){
                    
                }
            
            
        };
        
    }
}


#endif /* MODELFUNCTOR_HPP */

