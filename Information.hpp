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
#include "Common.hpp"
#include "Area.hpp"
#include "Population.hpp"
#include "Recruitment.hpp"
#include "LHParameters.hpp"
#include "Growth.hpp"
#include "Movement.hpp"
#include "Fishery.hpp"

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
            std::vector<Population<T> > subpopulations;
            std::map<int, PopulationData<T> > population_data;
            typedef typename std::map<int,PopulationData<T> >::iterator population_data_iterator;
            std::vector<Fishery<T> > fisheries;
            

            ~Information() {
               
            }
            
            
            void Initialize(){
                for(int i =0; i < this->subpopulations.size(); i++){
                    population_data_iterator it = population_data.find(this->subpopulations[i].id);
                    if(it != population_data.end()){
                        this->subpopulations[i].data = &(*it).second;
                        this->subpopulations[i].valid = true;
                    }else{
                        std::cout<<"Warning: No data found for population with id "<<this->subpopulations[i].data<<"\n";
                        
                    }
                    
                }
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
                            p.recruitment_model = std::make_shared<BevertonHolt<T> >();
                            BevertonHolt<T>* bh = (BevertonHolt<T>*)p.recruitment_model.get();
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
                    p.lh_parameters = lhp;
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

                rapidjson::Document::MemberIterator t = (*mit).value.FindMember("type");
                std::shared_ptr<Growth<T> > growth;

                if (t == (*mit).value.MemberEnd()) {

                    GrowthType gt = Growth<T>::GetGrowthType(std::string((*t).value.GetString()));

                    switch (gt) {

                        case VONB:
                            growth = std::shared_ptr<VonB<T> >(VonB<T>::Create(mit));

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
            
            void CreateFisheries(rapidjson::Document::MemberIterator & mit){
                std::cout<<__func__<<"\n";
                Fishery<T> f = Fishery<T>::Create(mit);
                this->fisheries.push_back(f);
            }

        };
    }
}


#endif /* INFORMATION_HPP */

