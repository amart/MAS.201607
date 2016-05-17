
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

