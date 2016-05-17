
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

