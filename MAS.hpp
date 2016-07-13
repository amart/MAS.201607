
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
 * File:   MAS.hpp
 * Author: matthewsupernaw
 *
 * Created on April 18, 2016, 1:08 PM
 */

#ifndef MAS_HPP
#define MAS_HPP


#include "../FunctionMinimizer/FunctionMinimizer.hpp"
#include "Information.hpp"

namespace noaa {
    namespace mas {

        template<typename T>
        class MASEngine : public atl::ObjectiveFunction<T> {
        public:
            Information<T>* info;

            void Initialize() {

                //loop through info initialize objects and register all 
                //estimable parameters     
                //

            }

            const atl::Variable<T> Evaluate() {
                atl::Variable<T> ret;
                //loop through populations and estimate number and biomass
                //do movement
                //get total numbers 
                //return liklihood
                std::cout<<info->number_of_years<<"\n";
                for (int year = 0; year < info->number_of_years; year++) {
                    std::cout<<"year = "<<year<<"\n";
                    for (int season = 0; season < info->number_of_seasons; season++) {
                        std::cout<<"season = "<<season<<"\n";
                        for (int population = 0; population < info->subpopulations.size(); population++) {
                            std::cout<<"population = "<<population<<"\n";
                            info->subpopulations[population].Evaluate();
                        }
                    }
                }
                return ret;
            }

            void Forecast() {

            }

            void Report() {

            }

        };
    }
}




#endif /* MAS_HPP */

