/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Season.hpp
 * Author: matthewsupernaw
 *
 * Created on July 20, 2016, 9:26 AM
 */

#ifndef SEASON_HPP
#define SEASON_HPP
namespace noaa {
    namespace mas {

        struct Season {
            int id;
            std::string name;
            uint32_t months = 12;

            Season() {
            }

            Season(int id, std::string name, uint32_t months) :
            id(id), name(name), months(months) {
            }

        };

    }
}


#endif /* SEASON_HPP */

