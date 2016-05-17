
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
 * This software is freely available to the public for use. The National Park
 * Service and the U.S. Government have not placed any restriction on its use
 * or reproduction.  Although all reasonable efforts have been taken to ensure
 * the accuracy and reliability of the software and data, the National Park
 * Service and the U.S. Government do not and cannot warrant the performance
 * or results that may be obtained by using this software or data. The National
 * Park Service and the U.S. Government disclaim all warranties, express or
 * implied,   including warranties of performance, merchantability or fitness
 * for any particular purpose.
 *
 * Please cite the author(s) in any work or product based on this material.
 *
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

