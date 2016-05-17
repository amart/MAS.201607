
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
 * File:   Fishery.hpp
 * Author: matthewsupernaw
 *
 * Created on April 20, 2016, 9:24 AM
 */

#ifndef FISHERY_HPP
#define FISHERY_HPP

#include "Fleet.hpp"
#include "Selectivity.hpp"
#include "third_party/rapidjson/document.h"

namespace noaa {
    namespace mas {

        template<typename T>
        struct Fishery {
            std::vector<Fleet<T> > fleets;

            static const Fishery<T> Create(rapidjson::Document::MemberIterator & fishery) {
                Fishery<T> fish;
                if ((*fishery).value.IsArray()) {
                    for (int i = 0; i < (*fishery).value.Size(); i++) {
                        Fleet<T> fleet;
                        rapidjson::Value& v = (*fishery).value[i];

                        rapidjson::Document::MemberIterator temp = v.FindMember("fleet");

                        if (temp != v.MemberEnd()) {
                            fleet.id = (*temp).value.GetInt();
                        } else {
                            std::cout << "Fishery parser error: fleet has no id.\n";
                        }

                        temp = v.FindMember("fleetName");
                        if (temp != v.MemberEnd()) {
                            fleet.fleet_name = std::string((*temp).value.GetString());
                        } else {
                            std::cout << "Fishery parser error: fleet has no name.\n";
                        }

                        temp = v.FindMember("selectivity");
                        if (temp != v.MemberEnd()) {


                            if ((*temp).value.IsArray()) {
                                for (int j = 0; j < (*temp).value.Size(); j++) {
                                    rapidjson::Document::MemberIterator atemp;
                                    rapidjson::Document::MemberIterator base;
                                    rapidjson::Value& vv = (*temp).value[j];


                                    base = vv.FindMember("base");
                                    bool is_length_based = false;
                                    if (base != vv.MemberEnd()) {
                                        if (std::string((*base).value.GetString()) == std::string("length")) {
                                            is_length_based = true;
                                        }
                                    } else {
                                        std::cout << "warning: selectivity has no base declared, assuming age based.\n";
                                    }

                                    atemp = vv.FindMember("type");

                                    if (atemp != vv.MemberEnd()) {

                                        if (std::string((*atemp).value.GetString()) == std::string("logistic")) {
                                            if (is_length_based) {
                                                std::cout << "Length based Selex\n";
                                                std::shared_ptr<LengthBasedLogistic<T> > selex(new LengthBasedLogistic<T>());

                                                rapidjson::Document::MemberIterator season = vv.FindMember("season");
                                                if (season != vv.MemberEnd()) {
                                                    selex->season = (*season).value.GetInt();
                                                }

                                                rapidjson::Document::MemberIterator area = vv.FindMember("area");
                                                if (area != vv.MemberEnd()) {
                                                    selex->area = (*area).value.GetInt();
                                                }

                                                rapidjson::Document::MemberIterator parameters = vv.FindMember("parameters");
                                                if (parameters != vv.MemberEnd()) {
                                                    rapidjson::Document::MemberIterator p = (*parameters).value.FindMember("alpha");
                                                    rapidjson::Document::MemberIterator est;
                                                    rapidjson::Document::MemberIterator phaze;

                                                    if (p != (*parameters).value.MemberEnd()) {
                                                        rapidjson::Document::MemberIterator value;
                                                        value = (*p).value.FindMember("value");
                                                        if (value != (*p).value.MemberEnd()) {
                                                            selex->alpha = (*value).value.GetDouble();
                                                        }


                                                        est = (*p).value.FindMember("estimated");
                                                        if (est != (*p).value.MemberEnd()) {
                                                            if (std::string((*est).value.GetString()) == std::string("true")) {
                                                                int phase = 1;
                                                                phaze = (*p).value.FindMember("phase");
                                                                if (phaze != (*p).value.MemberEnd()) {
                                                                    phase = (*phaze).value.GetInt();
                                                                }

                                                                selex->estimable.push_back(std::make_pair(&selex->alpha, phase));
                                                            }
                                                        }
                                                    }

                                                    p = (*parameters).value.FindMember("beta");
                                                    if (p != (*parameters).value.MemberEnd()) {
                                                        rapidjson::Document::MemberIterator value;
                                                        value = (*p).value.FindMember("value");
                                                        if (value != (*p).value.MemberEnd()) {
                                                            selex->alpha = (*value).value.GetDouble();
                                                        }


                                                        est = (*p).value.FindMember("estimated");
                                                        if (est != (*p).value.MemberEnd()) {
                                                            if (std::string((*est).value.GetString()) == std::string("true")) {
                                                                int phase = 1;
                                                                phaze = (*p).value.FindMember("phase");
                                                                if (phaze != (*p).value.MemberEnd()) {
                                                                    phase = (*phaze).value.GetInt();
                                                                }

                                                                selex->estimable.push_back(std::make_pair(&selex->alpha, phase));
                                                            }
                                                        }
                                                    }


                                                }


                                                fleet.selectivity.push_back(selex);
                                            } else {
                                                std::cout << "Age based Selex\n";
                                                std::shared_ptr<AgeBasedLogistic<T> > selex(new AgeBasedLogistic<T>());

                                                rapidjson::Document::MemberIterator season = vv.FindMember("season");
                                                if (season != vv.MemberEnd()) {
                                                    selex->season = (*season).value.GetInt();
                                                }

                                                rapidjson::Document::MemberIterator area = vv.FindMember("area");
                                                if (area != vv.MemberEnd()) {
                                                    selex->area = (*area).value.GetInt();
                                                }

                                                rapidjson::Document::MemberIterator parameters = vv.FindMember("parameters");
                                                if (parameters != vv.MemberEnd()) {
                                                    rapidjson::Document::MemberIterator p = (*parameters).value.FindMember("alpha");
                                                    rapidjson::Document::MemberIterator est;
                                                    rapidjson::Document::MemberIterator phaze;

                                                    if (p != (*parameters).value.MemberEnd()) {
                                                        rapidjson::Document::MemberIterator value;
                                                        value = (*p).value.FindMember("value");
                                                        if (value != (*p).value.MemberEnd()) {
                                                            selex->alpha = (*value).value.GetDouble();
                                                        }


                                                        est = (*p).value.FindMember("estimated");
                                                        if (est != (*p).value.MemberEnd()) {
                                                            if (std::string((*est).value.GetString()) == std::string("true")) {
                                                                int phase = 1;
                                                                phaze = (*p).value.FindMember("phase");
                                                                if (phaze != (*p).value.MemberEnd()) {
                                                                    phase = (*phaze).value.GetInt();
                                                                }

                                                                selex->estimable.push_back(std::make_pair(&selex->alpha, phase));
                                                            }
                                                        }
                                                    }

                                                    p = (*parameters).value.FindMember("beta");
                                                    if (p != (*parameters).value.MemberEnd()) {
                                                        rapidjson::Document::MemberIterator value;
                                                        value = (*p).value.FindMember("value");
                                                        if (value != (*p).value.MemberEnd()) {
                                                            selex->alpha = (*value).value.GetDouble();
                                                        }


                                                        est = (*p).value.FindMember("estimated");
                                                        if (est != (*p).value.MemberEnd()) {
                                                            if (std::string((*est).value.GetString()) == std::string("true")) {
                                                                int phase = 1;
                                                                phaze = (*p).value.FindMember("phase");
                                                                if (phaze != (*p).value.MemberEnd()) {
                                                                    phase = (*phaze).value.GetInt();
                                                                }

                                                                selex->estimable.push_back(std::make_pair(&selex->alpha, phase));
                                                            }
                                                        }
                                                    }


                                                }

                                                fleet.selectivity.push_back(selex);
                                            }

                                        }


                                    } else {
                                        std::cout << "Fishery parser error: selectivity has type.\n";
                                    }
                                }
                            } else {
                                std::cout << "Fishery parser error: fleet selectivity should be an array.\n";
                            }
                        } else {
                            std::cout << "Fishery parser error: fleet has no selectivity entries.\n";
                        }

                    }
                }
                return fish;
            }
        };


    }
}


#endif /* FISHERY_HPP */

