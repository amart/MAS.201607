
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
#include "ThreadPool.hpp"

namespace noaa {
    namespace mas {

        template<typename T>
        void PopulationTread(std::vector<noaa::mas::Population<T> >& pops, int start, int end) {
            //            pop.EvaluateBiology();
            for (int i = start; i < end; i++) {
                pops[i].EvaluateBiology();
            }
        }

        template<typename T>
        class MASEngine : public atl::ObjectiveFunction<T> {
        public:
            Information<T>* info;
            ThreadPool thread_pool_m;

            void Initialize() {
                size_t np = this->info->subpopulations.size();
                size_t nt = std::thread::hardware_concurrency();
                np < nt ? nt =np: nt=nt;
                thread_pool_m.Start(nt);
                //loop through info initialize objects and register all 
                //estimable parameters     
                
                for(int i =0; i < info->subpopulations.size(); i++){
                    if(!info->subpopulations[i].IsValid()){
                        exit(0);
                    }
                }

            }

            const atl::Variable<T> Evaluate() {
                atl::Variable<T> ret;
                size_t np = info->subpopulations.size();
                size_t nt = thread_pool_m.Size();
                std::cout << "nt = " << nt << std::endl;

                size_t range = 1;
                if (np < nt) {
                    nt = np;
                } else {
                    range = np / nt;
                }


                for (int i = 0; i < np; i++) {
                    int start = i*range;
                    int end = 0;
                    i == (np - 1) ? end = np : end = (i + 1) * range;
                    thread_pool_m.DoJob(std::bind(PopulationTread<T>, std::ref(info->subpopulations), start, end), true);
                }
                thread_pool_m.Wait();






                // loop through populations and estimate number and biomass
                for (int year = 0; year < info->number_of_years; year++) {
                    for (int season = 0; season < info->number_of_seasons; season++) {
                        for (int population = 0; population < info->subpopulations.size(); population++) {
                            //                                            info->subpopulations[population].SetCurrentYear(year);
                            //                                            info->subpopulations[population].SetCurrentSeason(year);
                            //                                            info->subpopulations[population].Evaluate();
                        }
                    }
                }
                //do movement

                //get total numbers 

                //return liklihood
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

