/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Selectivity.hpp
 * Author: matthewsupernaw
 *
 * Created on April 20, 2016, 9:25 AM
 */

#ifndef SELECTIVITY_HPP
#define SELECTIVITY_HPP

#include "Common.hpp"

namespace noaa {
    namespace mas {

        template<typename T>
        struct Selectivity : ModelFunctor<T> {
            int season;
            int area;

            virtual void Evaluate() {

            }
        };

        template<typename T>
        struct Logistic : Selectivity<T> {
            atl::Variable<T> alpha;
            atl::Variable<T> beta;

            virtual void Evaluate() {

            }
        };

        template<typename T>
        struct LengthBasedLogistic : Logistic<T> {

            virtual void Evaluate() {

            }
        };

        template<typename T>
        struct AgeBasedLogistic : Logistic<T> {

            virtual void Evaluate() {

            }
        };



    }
}


#endif /* SELECTIVITY_HPP */

