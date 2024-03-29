
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
 * File:   Common.hpp
 * Author: matthewsupernaw
 *
 * Created on April 27, 2016, 1:05 PM
 */

#ifndef COMMON_HPP
#define COMMON_HPP

#include "third_party/rapidjson/document.h"
//#include "Population.hpp"
#include "ATL/ATL.hpp"
#include "Information.hpp"

namespace noaa {
    namespace mas {

        enum GenderType {
            MALE = 0,
            FEMALE,
            BOTH
        };

        enum GrowthType {
            VONB = 0,
            SCHNUTE,
            CASE_II,
            CASE_III,
            CASE_IV,
            UNKNOWN_GROWTH
        };

        enum RecruitmentType {
            BEVERTON_HOLT = 0,
            UNKOWN_RECRUITMENT
        };

        enum ErrorType {
            NA = -1,
            CV
        };

        template<typename T>
        struct ModelFunctor {
            //variable, phase
            std::vector<std::pair<atl::Variable<T>*, int> > estimable;

            virtual void Evaluate() {
            }

            virtual void Initialize() {

            }
            
            virtual void PushLocalEstimable(){
                
            }
        };


        template<typename T>
        struct Population;

        template<typename T>
        struct PopulationFunctor : ModelFunctor<T> {
            mas::Population<T>* population_m;

            virtual void Evaluate() {
            }

            virtual void Initialize() {

            }
            
             virtual void PushLocalEstimable(){
                 for(int i =0; i < this->estimable.size(); i++){
                     this->population_m->local_estimable.push_back(this->estimable[i]);
                 }
            }
        };


        template<typename T>
        struct Information;

        template<typename T>
        struct FleetFunctor : ModelFunctor<T> {
            mas::Information<T>* info_m;

            virtual void Evaluate() {
            }

            virtual void Initialize() {

            }
        };
    }
}

#endif /* COMMON_HPP */

