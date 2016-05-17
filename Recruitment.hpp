/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
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
        struct Recruitment : ModelFunctor<T> {

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

