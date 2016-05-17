
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
 * File:   Growth.hpp
 * Author: matthewsupernaw
 *
 * Created on April 20, 2016, 9:23 AM
 */

#ifndef GROWTH_HPP
#define GROWTH_HPP

#include "Common.hpp"

namespace noaa {
    namespace mas {

        template<typename T>
        struct Growth : ModelFunctor<T> {

            static GrowthType GetGrowthType(const std::string& str) {
                if (str == "vonB") {
                    return VONB;
                } else {
                    return UNKNOWN_GROWTH;
                }
            }

            virtual void Evaluate() {
            }

        };

        template<typename T>
        struct VonB : Growth<T> {
            atl::Vector<atl::Variable<T> > Amin;
            atl::Vector<atl::Variable<T> > Amax;
            atl::Vector<atl::Variable<T> > L1;
            atl::Vector<atl::Variable<T> > CV_L1;
            atl::Vector<atl::Variable<T> > L2;
            atl::Vector<atl::Variable<T> > CV_L2;
            atl::Vector<atl::Variable<T> > k;

            static VonB<T>* Create(rapidjson::Document::MemberIterator& growth) {

                rapidjson::Document::MemberIterator parameters = (*growth).value.FindMember("parameters");
                VonB<T>* vonb = new VonB<T>();
                if (parameters != (*growth).value.MemberEnd()) {


                    rapidjson::Document::MemberIterator param = (*parameters).value.FindMember("Amin");
                    rapidjson::Document::MemberIterator valuevec = (*param).value.FindMember("valuevec");
                    rapidjson::Document::MemberIterator estimated_ = (*param).value.FindMember("estimated");
                    rapidjson::Document::MemberIterator phase_ = (*param).value.FindMember("phase");


                    bool estimated = false;
                    int phase = 1;

                    //Amin
                    if (valuevec != (*param).value.MemberEnd()) {
                        if ((*valuevec).value.IsArray()) {
                            int size = (*valuevec).value.Size();
                            vonb->Amax.Resize(size);

                            for (int i = 0; i < size; i++) {
                                std::stringstream ss;
                                ss << "Amin" << i;
                                vonb->Amin(i).SetName(ss.str());
                                vonb->Amin(i) = static_cast<T> ((*valuevec).value[i].GetDouble());
                            }
                        }
                    }

                    if (estimated_ != (*param).value.MemberEnd()) {
                        estimated = (*estimated_).value.GetBool();
                        if (phase_ != (*param).value.MemberEnd()) {
                            phase = (*param).value.GetInt();
                        }

                        for (int i = 0; i < vonb->Amin.Size(0); i++) {
                            vonb->estimable.push_back(std::make_pair(&vonb->Amin(i), phase));
                        }

                    }
                    estimated = false;
                    phase = 1;

                    //Amax
                    param = (*parameters).value.FindMember("Amax");
                    valuevec = (*param).value.FindMember("valuevec");
                    estimated_ = (*param).value.FindMember("estimated");
                    phase_ = (*param).value.FindMember("phase");

                    if (valuevec != (*param).value.MemberEnd()) {
                        if ((*valuevec).value.IsArray()) {
                            int size = (*valuevec).value.Size();
                            vonb->Amax.Resize(size);

                            for (int i = 0; i < size; i++) {
                                std::stringstream ss;
                                ss << "Amax_" << i;
                                vonb->Amax(i).SetName(ss.str());
                                vonb->Amax(i) = static_cast<T> ((*valuevec).value[i].GetDouble());
                            }
                        }
                    }

                    if (estimated_ != (*param).value.MemberEnd()) {
                        estimated = (*estimated_).value.GetBool();
                        if (phase_ != (*param).value.MemberEnd()) {
                            phase = (*param).value.GetInt();
                        }

                        for (int i = 0; i < vonb->Amax.Size(0); i++) {
                            vonb->estimable.push_back(std::make_pair(&vonb->Amax(i), phase));
                        }

                    }


                    //L1
                    param = (*parameters).value.FindMember("L1");
                    valuevec = (*param).value.FindMember("valuevec");
                    estimated_ = (*param).value.FindMember("estimated");
                    phase_ = (*param).value.FindMember("phase");

                    if (valuevec != (*param).value.MemberEnd()) {
                        if ((*valuevec).value.IsArray()) {
                            int size = (*valuevec).value.Size();
                            vonb->L1.Resize(size);

                            for (int i = 0; i < size; i++) {
                                std::stringstream ss;
                                ss << "L1_" << i;
                                vonb->L1(i).SetName(ss.str());
                                vonb->L1(i) = static_cast<T> ((*valuevec).value[i].GetDouble());
                            }
                        }
                    }

                    if (estimated_ != (*param).value.MemberEnd()) {
                        estimated = (*estimated_).value.GetBool();
                        if (phase_ != (*param).value.MemberEnd()) {
                            phase = (*param).value.GetInt();
                        }

                        for (int i = 0; i < vonb->L1.Size(0); i++) {
                            vonb->estimable.push_back(std::make_pair(&vonb->L1(i), phase));
                        }

                    }

                    //CV_L1
                    param = (*parameters).value.FindMember("CV_L1");
                    valuevec = (*param).value.FindMember("valuevec");
                    estimated_ = (*param).value.FindMember("estimated");
                    phase_ = (*param).value.FindMember("phase");

                    if (valuevec != (*param).value.MemberEnd()) {
                        if ((*valuevec).value.IsArray()) {
                            int size = (*valuevec).value.Size();
                            vonb->CV_L1.Resize(size);

                            for (int i = 0; i < size; i++) {
                                std::stringstream ss;
                                ss << "CV_L1_" << i;
                                vonb->CV_L1(i).SetName(ss.str());
                                vonb->CV_L1(i) = static_cast<T> ((*valuevec).value[i].GetDouble());
                            }
                        }
                    }

                    if (estimated_ != (*param).value.MemberEnd()) {
                        estimated = (*estimated_).value.GetBool();
                        if (phase_ != (*param).value.MemberEnd()) {
                            phase = (*param).value.GetInt();
                        }

                        for (int i = 0; i < vonb->CV_L1.Size(0); i++) {
                            vonb->estimable.push_back(std::make_pair(&vonb->CV_L1(i), phase));
                        }

                    }

                    //CV_L1
                    param = (*parameters).value.FindMember("L2");
                    valuevec = (*param).value.FindMember("valuevec");
                    estimated_ = (*param).value.FindMember("estimated");
                    phase_ = (*param).value.FindMember("phase");

                    if (valuevec != (*param).value.MemberEnd()) {
                        if ((*valuevec).value.IsArray()) {
                            int size = (*valuevec).value.Size();
                            vonb->L2.Resize(size);

                            for (int i = 0; i < size; i++) {
                                std::stringstream ss;
                                ss << "L2_" << i;
                                vonb->L2(i).SetName(ss.str());
                                vonb->L2(i) = static_cast<T> ((*valuevec).value[i].GetDouble());
                            }
                        }
                    }

                    if (estimated_ != (*param).value.MemberEnd()) {
                        estimated = (*estimated_).value.GetBool();
                        if (phase_ != (*param).value.MemberEnd()) {
                            phase = (*param).value.GetInt();
                        }

                        for (int i = 0; i < vonb->L2.Size(0); i++) {
                            vonb->estimable.push_back(std::make_pair(&vonb->L2(i), phase));
                        }

                    }

                    //CV_L2
                    param = (*parameters).value.FindMember("CV_L2");
                    valuevec = (*param).value.FindMember("valuevec");
                    estimated_ = (*param).value.FindMember("estimated");
                    phase_ = (*param).value.FindMember("phase");

                    if (valuevec != (*param).value.MemberEnd()) {
                        if ((*valuevec).value.IsArray()) {
                            int size = (*valuevec).value.Size();
                            vonb->CV_L2.Resize(size);

                            for (int i = 0; i < size; i++) {
                                std::stringstream ss;
                                ss << "CV_L2_" << i;
                                vonb->CV_L2(i).SetName(ss.str());
                                vonb->CV_L2(i) = static_cast<T> ((*valuevec).value[i].GetDouble());
                            }
                        }
                    }

                    if (estimated_ != (*param).value.MemberEnd()) {
                        estimated = (*estimated_).value.GetBool();
                        if (phase_ != (*param).value.MemberEnd()) {
                            phase = (*param).value.GetInt();
                        }

                        for (int i = 0; i < vonb->CV_L2.Size(0); i++) {
                            vonb->estimable.push_back(std::make_pair(&vonb->CV_L2(i), phase));
                        }

                    }


                     //k
                    param = (*parameters).value.FindMember("k");
                    valuevec = (*param).value.FindMember("valuevec");
                    estimated_ = (*param).value.FindMember("estimated");
                    phase_ = (*param).value.FindMember("phase");

                    if (valuevec != (*param).value.MemberEnd()) {
                        if ((*valuevec).value.IsArray()) {
                            int size = (*valuevec).value.Size();
                            vonb->k.Resize(size);

                            for (int i = 0; i < size; i++) {
                                std::stringstream ss;
                                ss << "k_" << i;
                                vonb->k(i).SetName(ss.str());
                                vonb->k(i) = static_cast<T> ((*valuevec).value[i].GetDouble());
                            }
                        }
                    }

                    if (estimated_ != (*param).value.MemberEnd()) {
                        estimated = (*estimated_).value.GetBool();
                        if (phase_ != (*param).value.MemberEnd()) {
                            phase = (*param).value.GetInt();
                        }

                        for (int i = 0; i < vonb->k.Size(0); i++) {
                            vonb->estimable.push_back(std::make_pair(&vonb->k(i), phase));
                        }

                    }





                }
                return vonb;

            }

            virtual void Evaluate() {
            }

        };



    }
}

#endif /* GROWTH_HPP */

