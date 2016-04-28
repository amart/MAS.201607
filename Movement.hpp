/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Movement.hpp
 * Author: matthewsupernaw
 *
 * Created on April 20, 2016, 9:23 AM
 */

#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#include "Common.hpp"

namespace noaa {
    namespace mas {

        template<typename T>
        struct Movement : ModelFunctor<T> {
            int season;
            std::vector<std::vector<T> > movement;

            static Movement<T>* Create(rapidjson::Document::MemberIterator& movement) {
                Movement<T>* m = new Movement<T>();

                rapidjson::Document::MemberIterator season = (*movement).value.FindMember("season");
                //
                int s = 1;
                if (season != (*movement).value.MemberEnd()) {
                    s = (*season).value.GetInt();
                }

                m->season = s;

                rapidjson::Document::MemberIterator mm = (*movement).value.FindMember("matrix");

                if (mm != (*movement).value.MemberEnd()) {

                    if ((*mm).value.IsArray()) {

                        for (int i = 0; i < (*mm).value.Size(); i++) {
                            m->movement.push_back(std::vector<T>());
                            for (int j = 0; j < (*mm).value[i].Size(); j++) {
                                m->movement[i].push_back(static_cast<T> ((*mm).value[i][j].GetDouble()));
                            }
                        }

                    }

                }


                return m;

            }

            void Evaluate() {
            }
        };


    }
}

#endif /* MOVEMENT_HPP */

