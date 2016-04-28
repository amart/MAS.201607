/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Information.hpp
 * Author: matthewsupernaw
 *
 * Created on April 27, 2016, 11:48 AM
 */

#ifndef INFORMATION_HPP
#define INFORMATION_HPP

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include "third_party/rapidjson/document.h"
#include "Area.hpp"
#include "Population.hpp"
#include "Recruitment.hpp"
#include "LHParameters.hpp"

namespace noaa {
    namespace mas {

        template<class T>
        class Information {
        public:
            size_t number_of_years;
            size_t number_of_seasons;
            size_t number_of_ages;
            size_t number_of_genders;
            size_t number_of_areas;
            size_t number_of_populations;
            size_t number_of_fleets;
            size_t number_of_surveys;



            std::vector<Area<T> > areas;
            //            std::vector<Population<T> > subpopulations;
            //            std::vector<Fleet<T> > fleets;
            //            std::vector<Survey<T> > surveys;

            void ParseConfig(const std::string& path) {
                std::stringstream ss;
                std::ifstream config;
                config.open(path.c_str());
                if (!config.good()) {
                    std::cerr << "MAS Configuration file \"" << path << "\" not found.\n";
                    exit(0);
                }

                while (config.good()) {
                    std::string line;
                    std::getline(config, line);
                    ss << line << "\n";
                }

                rapidjson::Document document;
                document.Parse(ss.str().c_str());

                rapidjson::Document::MemberIterator mit;

                for (mit = document.MemberBegin(); mit != document.MemberEnd(); ++mit) {
                    std::cout << (*mit).name.GetString() << "\n";
                    if (std::string((*mit).name.GetString()) == "areas") {
                        this->CreateAreas(mit);
                    }

                    if (std::string((*mit).name.GetString()) == "populations") {
                        this->CreatePopulations(mit);
                    }
                }


            }

        private:

            void CreateAreas(rapidjson::Document::MemberIterator& mit) {
                rapidjson::Document::ValueIterator it;
                if ((*mit).value.IsArray()) {
                    for (int i = 0; i < (*mit).value.Size(); i++) {
                        rapidjson::Document::MemberIterator jt;
                        rapidjson::Value& v = (*mit).value[i];
                        noaa::mas::Area<T> area;
                        rapidjson::Document::MemberIterator am = v.FindMember("area");
                        if (am != v.MemberEnd()) {
                            area.id = (*am).value.GetInt();
                        }

                        am = v.FindMember("areaName");
                        if (am != v.MemberEnd()) {
                            area.name = (*am).value.GetString();
                        }
                        areas.push_back(area);
                    }
                }
            }

            void CreatePopulations(rapidjson::Document::MemberIterator& mit) {
                if ((*mit).value.IsArray()) {

                    for (int i = 0; i < (*mit).value.Size(); i++) {
                        Population<T> p;
                        rapidjson::Document::MemberIterator jt;
                        rapidjson::Value& v = (*mit).value[i];
                        rapidjson::Document::MemberIterator am = v.FindMember("population");
                        if (am != v.MemberEnd()) {
                            p.id = (*am).value.GetInt();
                        }

                        am = v.FindMember("stock-recruit");
                        if (am != v.MemberEnd()) {
                            this->CreatePopulationStockRecruit(am, p);
                        }

                        am = v.FindMember("LHparameters");
                        if (am != v.MemberEnd()) {
                            this->CreatePopulationLHParamters(am, p);
                        }

                        am = v.FindMember("movement");
                        if (am != v.MemberEnd()) {
                            this->CreatePopulationMovement(am, p);
                        }

                        am = v.FindMember("growth");
                        if (am != v.MemberEnd()) {
                            this->CreatePopulationGrowth(am, p);
                        }



                    }
                }
            }

            void CreatePopulationStockRecruit(rapidjson::Document::MemberIterator& mit, Population<T>& p) {
                rapidjson::Value& v = (*mit).value;
                rapidjson::Document::MemberIterator am = v.FindMember("type");
                if (am != v.MemberEnd()) {
                    RecruitmentType rt = Recruitment<T>::GetRecruitType((*am).value.GetString());
                    Recruitment<T>* recruitment_model;
                    switch (rt) {

                        case BEVERTON_HOLT:
                        {
                            std::cout << "Beverton-Holt\n";
                            recruitment_model = new BevertonHolt<T>();
                            BevertonHolt<T>* bh = (BevertonHolt<T>*)recruitment_model;
                            p.recruitment_model = bh;
                            am = v.FindMember("parameters");
                            if (am != v.MemberEnd()) {
                                rapidjson::Document::MemberIterator param =
                                        (*am).value.FindMember("R0");
                                if (param != (*am).value.MemberEnd()) {
                                    std::stringstream ss;
                                    ss << "R0_" << "pop_" << p.id;
                                    bh->R0.SetName(ss.str());
                                    int phase = 1;
                                    rapidjson::Document::MemberIterator val = (*param).value.FindMember("value");
                                    rapidjson::Document::MemberIterator phase_ = (*param).value.FindMember("phase");
                                    rapidjson::Document::MemberIterator estimated = (*param).value.FindMember("estimated");

                                    if (val != (*param).value.MemberEnd()) {
                                        bh->R0 = static_cast<T> ((*val).value.GetDouble());
                                    }

                                    if (phase_ != (*param).value.MemberEnd()) {
                                        phase = (*phase_).value.GetInt();
                                    }

                                    if (estimated != (*param).value.MemberEnd()) {
                                        if (std::string((*estimated).value.GetString()) == "true") {
                                            bh->estimable.push_back(std::make_pair(&bh->R0, phase));
                                        }
                                    }

                                }

                                param = (*am).value.FindMember("h");
                                if (param != (*am).value.MemberEnd()) {
                                    std::stringstream ss;
                                    ss << "h_" << "pop_" << p.id;
                                    bh->h.SetName(ss.str());
                                    int phase = 1;
                                    rapidjson::Document::MemberIterator val = (*param).value.FindMember("value");
                                    rapidjson::Document::MemberIterator phase_ = (*param).value.FindMember("phase");
                                    rapidjson::Document::MemberIterator estimated = (*param).value.FindMember("estimated");

                                    if (val != (*param).value.MemberEnd()) {
                                        bh->h = static_cast<T> ((*val).value.GetDouble());
                                    }

                                    if (phase_ != (*param).value.MemberEnd()) {
                                        phase = (*phase_).value.GetInt();
                                    }

                                    if (estimated != (*param).value.MemberEnd()) {
                                        if (std::string((*estimated).value.GetString()) == "true") {
                                            bh->estimable.push_back(std::make_pair(&bh->h, phase));
                                        }
                                    }

                                }


                            }
                            break;
                        }
                        default:
                            std::cout << "Unknown recruitment model: " << (*am).value.GetString() << "\n";
                            exit(0);
                    }


                }

            }

            void CreatePopulationLHParamters(rapidjson::Document::MemberIterator& mit, Population<T>& p) {
                rapidjson::Document::MemberIterator am = (*mit).value.FindMember("M");
                if (am != (*mit).value.MemberEnd()) {
                    rapidjson::Value& m = (*am).value;
                    LHParameters<T>* lhp = new LHParameters<T>();
                    if (m.IsArray()) {
                        for (int i = 0; i < m.Size(); i++) {
                            Mortality<T> mort;
                            rapidjson::Value& v = m[i];

                            rapidjson::Document::MemberIterator gender = v.FindMember("gender");
                            if (gender != v.MemberEnd()) {
                                GenderType g = Mortality<T>::GetGenderType(std::string((*gender).value.GetString()));
                                mort.gender = g;
                            }

                            rapidjson::Document::MemberIterator vect = v.FindMember("valuevec");
                            if (vect != v.MemberEnd()) {
                                if ((*vect).value.IsArray()) {
                                    int size = (*vect).value.Size();
                                    mort.m.Resize(size);
                                    for (int j = 0; j < size; j++) {
                                        mort.m(j) = static_cast<T> ((*vect).value[j].GetDouble());
                                        std::cout << mort.m(j) << "\n";
                                    }
                                }
                            }

                            rapidjson::Document::MemberIterator phase_ = v.FindMember("phase");
                            int phase = 1;

                            if (phase_ != v.MemberEnd()) {
                                phase = (*phase_).value.GetInt();
                            }


                            rapidjson::Document::MemberIterator estimated = v.FindMember("estimated");
                            if (estimated != v.MemberEnd()) {
                                if (std::string((*estimated).value.GetString()) == "true") {
                                    for(int j = 0; j < mort.m.Size(0); j++){
                                        mort.estimable.push_back(std::make_pair(&mort.m(j),phase));
                                    }
                                }
                            }
                            lhp->M.push_back(mort);

                        }
                    } else {
                        std::cout << "Error parsing model configuration file for LHParameters M, expected an array";
                        exit(0);
                    }
                } else {
                    std::cout << "Mortality not defined in LHParameters.\n";
                }

            }

            void CreatePopulationMovement(rapidjson::Document::MemberIterator& mit, Population<T>& p) {
                std::cout << __func__ << " not yet implemented.\n";
            }

            void CreatePopulationGrowth(rapidjson::Document::MemberIterator& mit, Population<T>& p) {
                std::cout << __func__ << " not yet implemented.\n";
            }


        };
    }
}


#endif /* INFORMATION_HPP */
