/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
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

