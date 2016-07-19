
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
 * File:   Recruitment.hpp
 * Author: matthewsupernaw
 *
 * Created on April 20, 2016, 9:22 AM
 */

#ifndef RECRUITMENT_HPP
#define RECRUITMENT_HPP
#include "Common.hpp"
namespace noaa {
    namespace mas {

        enum RecruitmentType {
            BEVERTON_HOLT = 0,
            UNKOWN_RECRUITMENT
        };

        template<typename T>
        struct Recruitment : PopulationFunctor<T> {

            static RecruitmentType GetRecruitType(const std::string& str) {
                if (str == "Beverton-Holt") {
                    return BEVERTON_HOLT;
                } else {
                    return UNKOWN_RECRUITMENT;
                }
            }

            virtual void Evaluate() {
                std::cout << __func__ << " not implemented.\n";
            }

            virtual ~Recruitment() {

            }
            
            virtual void Show() {}

        };

        template<typename T>
        std::ostream& operator<<(std::ostream& out, Recruitment<T>& bh) {
            out << "Recruitment base:\n";
            return out;
        }

        template<typename T>
        struct BevertonHolt : Recruitment<T> {
            atl::Variable<T> R0;
            atl::Variable<T> h;

            virtual void Evaluate() {
                std::cout << __func__ << " not implemented.\n";
            }

            void Show() {
                std::cout << "Beverton-Holt:\n";
                std::cout << "R0 = " << R0 << "\n";
                std::cout << "h = " << h << "\n";
            }

        };

        template<typename T>
        std::ostream& operator<<(std::ostream& out, BevertonHolt<T>& bh) {
            out << "Beverton-Holt:\n";
            out << "R0 = " << bh.R0 << "\n";
            out << "h = " << bh.h << "\n";
            return out;
        }


    }
}


#endif /* RECRUITMENT_HPP */

