
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
 * File:   Area.hpp
 * Author: matthewsupernaw
 *
 * Created on April 20, 2016, 9:19 AM
 */

#ifndef AREA_HPP
#define AREA_HPP

namespace noaa{
    namespace mas{
        
        template<typename T>
        struct Area{
            int id;
            std::string name;
            
        };
        
        template<typename T>
        std::ostream& operator << (std::ostream& out, const Area<T>& a){
            out<<"Area["<<a.id<<","<<a.name<<"]";
            return out;
        }
        
    }
}


#endif /* AREA_HPP */

