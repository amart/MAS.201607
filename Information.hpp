
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
#include "Common.hpp"
#include "Area.hpp"
#include "Population.hpp"
#include "Recruitment.hpp"
#include "LHParameters.hpp"
#include "Growth.hpp"
#include "Movement.hpp"
#include "Fishery.hpp"
#include "Season.hpp"

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
            std::map<int, noaa::mas::Season> seasons;


            std::vector<Area<T> > areas;
            std::vector<Population<T> > subpopulations;
            std::map<int, PopulationData<T> > population_data;
            typedef typename std::map<int, PopulationData<T> >::iterator population_data_iterator;
            std::vector<Fishery<T> > fisheries;

            ~Information() {

            }

            void Initialize() {
                int max_max_first_year = std::numeric_limits<int>::min();
                int min_max_first_year = std::numeric_limits<int>::max();

                int max_max_last_year = std::numeric_limits<int>::min();
                int min_max_last_year = std::numeric_limits<int>::max();
                int s, e;
                for (int i = 0; i < this->subpopulations.size(); i++) {
                    population_data_iterator it = population_data.find(this->subpopulations[i].id);
                    if (it != population_data.end()) {
                        this->subpopulations[i].data = &(*it).second;
                        this->subpopulations[i].data_is_valid = true;
                        if (this->subpopulations[i].data->first_year > max_max_first_year) {
                            max_max_first_year = this->subpopulations[i].data->first_year;
                        }
                        if (this->subpopulations[i].data->first_year < min_max_first_year) {
                            min_max_first_year = this->subpopulations[i].data->first_year;
                        }

                        if (this->subpopulations[i].data->first_year > max_max_last_year) {
                            max_max_last_year = this->subpopulations[i].data->first_year;
                        }
                        if (this->subpopulations[i].data->first_year < min_max_last_year) {
                            min_max_last_year = this->subpopulations[i].data->first_year;
                        }

                        if (i == 0) {
                            s = this->subpopulations[i].data->first_year;
                            e = this->subpopulations[i].data->last_year;
                            this->number_of_years = e - s;
                        }

                    } else {
                        std::cout << "Warning: No data found for population with id " << this->subpopulations[i].data << "\n";

                    }

                }

                if (max_max_first_year != min_max_first_year) {
                    std::cout << "Warning: population data not consistent for First years\n Press 'q' to quit or any other key to continue! ";
                    char temp;
                    std::cin >> temp;
                    if (temp == 'q') {
                        exit(0);
                    }
                }

                if (max_max_last_year != min_max_last_year) {
                    std::cout << "Warning: population data not consistent for Last years\n Press 'q' to quit or any other key to continue! ";
                    char temp;
                    std::cin >> temp;
                    if (temp == 'q') {
                        exit(0);
                    }
                }

                std::cout << "number of years = " << this->number_of_years << "\n";
            }

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
                    if (std::string((*mit).name.GetString()) == "areas") {
                        this->CreateAreas(mit);
                    }

                    if (std::string((*mit).name.GetString()) == "populations") {
                        this->CreatePopulations(mit);
                    }
                    if (std::string((*mit).name.GetString()) == "fisheries") {
                        this->CreateFisheries(mit);
                    }

                    if (std::string((*mit).name.GetString()) == "seasons") {
                        //                        rapidjson::Document::MemberIterator sid = (*mit).value.FindMember("")
                        //                        std::cout << "Not yet implemented!\n";
                        if ((*mit).value.IsArray()) {

                            for (int i = 0; i < (*mit).value.Size(); i++) {
                                rapidjson::Value& v = (*mit).value[i];
                                rapidjson::Document::MemberIterator sid = v.FindMember("season");
                                rapidjson::Document::MemberIterator sname = v.FindMember("seasonName");
                                rapidjson::Document::MemberIterator smonths = v.FindMember("months");
                                noaa::mas::Season s((*sid).value.GetInt(),std::string((*sname).value.GetString()),(*smonths).value.GetInt());
                                this->seasons[s.id] = s;
                            }
                            this->number_of_seasons = this->seasons.size();

                        } else {
                            std::cout << "Seasons Error: Expected an array!\n";
                            exit(0);
                        }
                    }

                }


            }

            void ParseData(const std::string& path) {
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

                    if (std::string((*mit).name.GetString()) == "populations") {
                        this->CreatePopulationsData(mit);
                    }
                }

            }

        private:

            void CreateAreas(rapidjson::Document::MemberIterator & mit) {
                rapidjson::Document::ValueIterator it;
                if ((*mit).value.IsArray()) {
                    for (int i = 0; i < (*mit).value.Size(); i++) {
                        //                        rapidjson::Document::MemberIterator jt;
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

            void CreatePopulations(rapidjson::Document::MemberIterator & mit) {
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


                        this->subpopulations.push_back(p);
                    }
                }
            }

            void CreatePopulationStockRecruit(rapidjson::Document::MemberIterator& mit, Population<T>& p) {
                std::cout << __func__ << ":";
                rapidjson::Value& v = (*mit).value;
                rapidjson::Document::MemberIterator am = v.FindMember("type");
                if (am != v.MemberEnd()) {
                    RecruitmentType rt = Recruitment<T>::GetRecruitType((*am).value.GetString());
                    Recruitment<T>* recruitment_model;
                    switch (rt) {

                        case BEVERTON_HOLT:
                        {
                            std::cout << "BEVERTON_HOLT \n";
                            //                            recruitment_model = std::make_signed<BevertonHolt<T> >();
                            p.recruitment_model_m = std::make_shared<BevertonHolt<T> >();
                            BevertonHolt<T>* bh = (BevertonHolt<T>*)p.recruitment_model_m.get();
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
                    std::shared_ptr<LHParameters<T> > lhp(new LHParameters<T>());
                    p.lh_parameters_m = lhp;
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
                                    for (int j = 0; j < mort.m.Size(0); j++) {
                                        mort.estimable.push_back(std::make_pair(&mort.m(j), phase));
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
                Movement<T>::Create(mit);
            }

            void CreatePopulationGrowth(rapidjson::Document::MemberIterator& mit, Population<T>& p) {

                std::cout << "Growth!!!!!!!\n";
                rapidjson::Document::MemberIterator t = (*mit).value.FindMember("type");
                std::shared_ptr<Growth<T> > growth;

                if (t != (*mit).value.MemberEnd()) {

                    GrowthType gt = Growth<T>::GetGrowthType(std::string((*t).value.GetString()));

                    switch (gt) {

                        case VONB:
                            p.growth_model_m = std::shared_ptr<VonB<T> >(VonB<T>::Create(mit));
                            std::cout << "valid?" << p.growth_model_m.operator bool() << "\n";
                            break;

                        default:
                            std::cout << "Unknown Growth!\n";



                    }


                }


            }

            void CreatePopulationsData(rapidjson::Document::MemberIterator & mit) {
                this->population_data =
                        PopulationData<T>::Create(mit);
            }

            void CreateFisheries(rapidjson::Document::MemberIterator & mit) {
                std::cout << __func__ << "\n";
                Fishery<T> f = Fishery<T>::Create(mit);
                this->fisheries.push_back(f);
            }

        };
    }
}


#endif /* INFORMATION_HPP */

