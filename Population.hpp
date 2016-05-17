/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Population.hpp
 * Author: matthewsupernaw
 *
 * Created on April 20, 2016, 9:21 AM
 */

#ifndef POPULATION_HPP
#define POPULATION_HPP


#include <memory>

#include "../ATL/ATL.hpp"

#include "Common.hpp"
#include "Recruitment.hpp"

namespace noaa {
    namespace mas {

        template<typename T>
        struct CatchData {
            int fleet;
            int area;
            int season;

            atl::Vector<int> year_vector;

            ErrorType error_type = NA;
            atl::Vector<T> catch_vector;
            atl::Vector<T> error_vector;

            ErrorType index_error_type = NA;
            atl::Vector<T> index_vector;
            atl::Vector<T> index_error_vector;
        };

        template<typename T>
        std::ostream& operator<<(std::ostream& out, const CatchData<T>& data) {
            out << "Catch Data:\n";
            out << "Fleet: " << data.fleet << "\n";
            out << "Area: " << data.area << "\n";
            out << "Season: " << data.season << "\n";
            out << "Catch:" << data.catch_vector << "\n";

            out << "\n";
            out << "Catch Error Type: " << data.error_type << "\n";

            out << "Catch Error:" << data.error_vector << "\n";

            out << "Index:" << data.index_vector << "\n";
            out << "\n";
            out << "Index Error Type: " << data.index_error_type << "\n";

            out << "Index Error:" << data.index_error_vector << "\n";

            return out;
        }

        template<typename T>
        struct LengthComposition {
            int fleet;
            int area;
            int season;
            GenderType gender;
            atl::Vector<int> year_vector;
            atl::Vector<int> nsample_vector;
            atl::Matrix<T> length_prop_matrix;

        };

        template<typename T>
        std::ostream& operator<<(std::ostream& out, const LengthComposition<T>& data) {
            out << "Length Composition:\n";
            out << "Fleet: " << data.fleet << "\n";
            out << "Area: " << data.area << "\n";
            out << "Season: " << data.season << "\n";
            out << "Gender Type: " << data.gender << "\n";
            out << "Years:" << data.year_vector << "\n";
            out << "Number of Samples:" << data.nsample_vector << "\n";
            out << "Length Prop:\n" << data.length_prop_matrix << "\n";
            return out;
        }

        template<typename T>
        struct AgeComposition {
            int fleet;
            int area;
            int season;
            GenderType gender;
            atl::Vector<int> year_vector;
            atl::Vector<int> nsample_vector;
            atl::Matrix<T> age_propogation_matrix;

        };

        template<typename T>
        std::ostream& operator<<(std::ostream& out, const AgeComposition<T>& data) {
            out << "Age Composition:\n";
            out << "Fleet: " << data.fleet << "\n";
            out << "Area: " << data.area << "\n";
            out << "Season: " << data.season << "\n";
            out << "Gender Type: " << data.gender << "\n";
            out << "Years:" << data.year_vector << "\n";
            out << "Number of Samples:" << data.nsample_vector << "\n";
            out << "Age Prop:\n" << data.age_propogation_matrix << "\n";
            return out;
        }

        template<typename T>
        struct MeanSizeAtAge {
            int fleet;
            int area;
            int season;
            GenderType gender;
            atl::Vector<int> year_vector;
            atl::Matrix<T> msa_matrix;

        };

        template<typename T>
        std::ostream& operator<<(std::ostream& out, const MeanSizeAtAge<T>& data) {
            out << "Mean Size At Age:\n";
            out << "Fleet: " << data.fleet << "\n";
            out << "Area: " << data.area << "\n";
            out << "Season: " << data.season << "\n";
            out << "Gender Type: " << data.gender << "\n";
            out << "Years:" << data.year_vector << "\n";
            out << "MSA:\n" << data.msa_matrix << "\n";
            return out;
        }

        template<typename T>
        struct AgeError {
            GenderType gender;
            atl::Vector<T> age_vector;
            atl::Vector<T> error_vector;

        };

        template<typename T>
        std::ostream& operator<<(std::ostream& out, const AgeError<T>& data) {
            out << "Age Error:\n";
            out << "Gender Type: " << data.gender << "\n";
            out << "Age:" << data.age_vector << "\n";
            out << "Error:\n" << data.error_vector << "\n";
            return out;
        }

        template<typename T>
        struct PopulationData {
            int id;
            std::string name;
            int first_year;
            int last_year;
            int spawn_month;
            std::vector<GenderType> gender_types;
            atl::Vector<T> ages;
            atl::Vector<T> lengths;
            std::vector<CatchData<T> > catch_data;
            std::vector<LengthComposition<T> > length_composition;
            std::vector<AgeComposition<T> > age_composition;
            std::vector<MeanSizeAtAge<T> > msa_data;
            std::vector<AgeError<T> > age_error;

            static const std::map<int,PopulationData<T> > Create(rapidjson::Document::MemberIterator& population_data) {

                std::map<int,PopulationData<T> > data;

                if ((*population_data).value.IsArray()) {
                    for (int i = 0; i < (*population_data).value.Size(); i++) {
                        rapidjson::Value& v = (*population_data).value[i];
                        PopulationData<T> pop_data;

                        rapidjson::Document::MemberIterator pop_id_;

                        pop_id_ = v.FindMember("population");

                        if (pop_id_ != v.MemberEnd()) {
                            pop_data.id = (*pop_id_).value.GetInt();
                        } else {
                            std::cout << "Population data error, expected attribute population.\n";
                            exit(0);
                        }


                        rapidjson::Document::MemberIterator pop_name_;

                        pop_name_ = v.FindMember("popName");

                        if (pop_name_ != v.MemberEnd()) {
                            pop_data.name = std::string((*pop_name_).value.GetString());
                        } else {
                            std::cout << "Population data error, expected attribute popName.\n";
                            exit(0);
                        }

                        rapidjson::Document::MemberIterator first_year_;


                        first_year_ = v.FindMember("firstDataYear");

                        if (first_year_ != v.MemberEnd()) {
                            pop_data.first_year = (*first_year_).value.GetInt();
                        } else {
                            std::cout << "Population data error, expected attribute firstDataYear.\n";
                            exit(0);
                        }


                        rapidjson::Document::MemberIterator last_year_;

                        last_year_ = v.FindMember("lastDataYear");

                        if (last_year_ != v.MemberEnd()) {
                            pop_data.last_year = (*last_year_).value.GetInt();
                        } else {
                            std::cout << "Population data error, expected attribute firstDataYear.\n";
                            exit(0);
                        }

                        rapidjson::Document::MemberIterator spawn_month_;

                        spawn_month_ = v.FindMember("spawnMonth");

                        if (spawn_month_ != v.MemberEnd()) {
                            pop_data.spawn_month = (*spawn_month_).value.GetInt();
                        } else {
                            std::cout << "Population data error, expected attribute spawnMonth.\n";
                            exit(0);
                        }

                        rapidjson::Document::MemberIterator gender_names_;

                        gender_names_ = v.FindMember("genderName");

                        if (gender_names_ != v.MemberEnd()) {
                            if ((*gender_names_).value.IsArray()) {

                                for (int j = 0; j < (*gender_names_).value.Size(); j++) {
                                    rapidjson::Value& elem = (*gender_names_).value[j];
                                    if (std::string(elem.GetString()) == std::string("female")) {
                                        pop_data.gender_types.push_back(FEMALE);
                                    }
                                    if (std::string(elem.GetString()) == std::string("male")) {
                                        pop_data.gender_types.push_back(MALE);
                                    }
                                    if (std::string(elem.GetString()) == std::string("both")) {
                                        pop_data.gender_types.push_back(BOTH);
                                    }
                                }

                            } else {
                                std::cout << "Population data error, attribute genderName should be an array.\n";
                                exit(0);
                            }


                        } else {
                            std::cout << "Population data error, expected attribute genderName.\n";
                            exit(0);
                        }




                        rapidjson::Document::MemberIterator ages_;

                        ages_ = v.FindMember("ages");
                        if (ages_ != v.MemberEnd()) {

                            if ((*ages_).value.IsArray()) {

                                int size = (*ages_).value.Size();
                                pop_data.ages.Resize(size);
                                for (int j = 0; j < size; j++) {
                                    pop_data.ages(j) = static_cast<T> ((*ages_).value[j].GetDouble());
                                }

                            } else {
                                std::cout << "Population data error, attribute ages should be an array.\n";
                                exit(0);
                            }

                        } else {
                            std::cout << "Population data error, expected attribute ages.\n";
                            exit(0);
                        }

                        rapidjson::Document::MemberIterator lengths_;

                        lengths_ = v.FindMember("lengths");
                        if (lengths_ != v.MemberEnd()) {

                            if ((*lengths_).value.IsArray()) {

                                int size = (*lengths_).value.Size();
                                pop_data.lengths.Resize(size);
                                for (int j = 0; j < size; j++) {
                                    pop_data.lengths(j) = static_cast<T> ((*lengths_).value[j].GetDouble());
                                }

                            } else {
                                std::cout << "Population data error, attribute ages should be an array.\n";
                                exit(0);
                            }

                        } else {
                            std::cout << "Population data error, expected attribute ages.\n";
                            exit(0);
                        }
                        rapidjson::Document::MemberIterator catch_;

                        catch_ = v.FindMember("catch");

                        if (catch_ != v.MemberEnd()) {
                            rapidjson::Document::MemberIterator temp;

                            if ((*catch_).value.IsArray()) {
                                //
                                for (int j = 0; j < (*catch_).value.Size(); j++) {
                                    CatchData<T> c;
                                    temp = (*catch_).value[j].FindMember("fleet");
                                    if ((temp) != (*catch_).value[j].MemberEnd()) {
                                        c.fleet = (*temp).value.GetInt();
                                    } else {
                                        std::cout << "Population data error, \"catch\" missing \"fleet\" id.\n";
                                        exit(0);
                                    }

                                    temp = (*catch_).value[j].FindMember("season");
                                    if ((temp) != (*catch_).value[j].MemberEnd()) {
                                        c.season = (*temp).value.GetInt();
                                    } else {
                                        std::cout << "Population data error, \"catch\" missing \"season\" value.\n";
                                        exit(0);
                                    }

                                    temp = (*catch_).value[j].FindMember("errtype");
                                    if ((temp) != (*catch_).value[j].MemberEnd()) {
                                        if (std::string((*temp).value.GetString()) == "CV") {
                                            c.error_type = CV;
                                        }
                                    } else {
                                        std::cout << "Population data error, \"catch\" missing \"area\" value.\n";
                                        exit(0);
                                    }
                                    
                                    

                                    temp = (*catch_).value[j].FindMember("area");
                                    if ((temp) != (*catch_).value[j].MemberEnd()) {
                                        c.area = (*temp).value.GetInt();
                                    } else {
                                        std::cout << "Population data error, \"catch\" missing \"area\" value.\n";
                                        exit(0);
                                    }

                                    temp = (*catch_).value[j].FindMember("yearvec");
                                    if ((temp) != (*catch_).value[j].MemberEnd()) {

                                        if ((*temp).value.IsArray()) {
                                            int s = (*temp).value.Size();
                                            c.year_vector.Resize(s);
                                            for (int k = 0; k < s; k++) {
                                                c.year_vector(k) = (*temp).value[k].GetInt();
                                            }

                                        } else {
                                            std::cout << "Population data error, \"catch\", \"yearvec\" should be an array.\n";
                                            exit(0);
                                        }
                                    } else {
                                        std::cout << "Population data error, \"catch\" missing \"yearvec\" value.\n";
                                        exit(0);
                                    }

                                    temp = (*catch_).value[j].FindMember("catchvec");
                                    if ((temp) != (*catch_).value[j].MemberEnd()) {

                                        if ((*temp).value.IsArray()) {
                                            int s = (*temp).value.Size();
                                            c.catch_vector.Resize(s);
                                            for (int k = 0; k < s; k++) {
                                                c.catch_vector(k) = static_cast<T> ((*temp).value[k].GetDouble());
                                            }

                                        } else {
                                            std::cout << "Population data error, \"catch\", \"catchvec\" should be an array.\n";
                                            exit(0);
                                        }
                                    } else {
                                        std::cout << "Population data error, \"catch\" missing \"catchvec\" value.\n";
                                        exit(0);
                                    }
                                    ////                                    
                                    //


                                    temp = (*catch_).value[j].FindMember("errvec");
                                    if ((temp) != (*catch_).value[j].MemberEnd()) {

                                        if ((*temp).value.IsArray()) {
                                            int s = (*temp).value.Size();
                                            c.error_vector.Resize(s);
                                            for (int k = 0; k < s; k++) {
                                                c.error_vector(k) = static_cast<T> ((*temp).value[k].GetDouble());
                                            }

                                        } else {
                                            std::cout << "Population data error, \"catch\", \"errvec\" should be an array.\n";
                                            exit(0);
                                        }
                                    } else {
                                        std::cout << "Population data error, \"catch\" missing \"errvec\" value.\n";
                                        exit(0);
                                    }
                                    
                                    temp = (*catch_).value[j].FindMember("indexerrtype");
                                    if ((temp) != (*catch_).value[j].MemberEnd()) {
                                        if (std::string((*temp).value.GetString()) == "CV") {
                                            c.index_error_type = CV;
                                        }
                                    } else {
                                        std::cout << "Population data warning, \"catch\" missing \"indexerrtype\" value.\n";
//                                        exit(0);
                                    }
                                    
                                    temp = (*catch_).value[j].FindMember("indexvec");
                                    if ((temp) != (*catch_).value[j].MemberEnd()) {

                                        if ((*temp).value.IsArray()) {
                                            int s = (*temp).value.Size();
                                            c.index_vector.Resize(s);
                                            for (int k = 0; k < s; k++) {
                                                c.index_vector(k) = static_cast<T> ((*temp).value[k].GetDouble());
                                            }

                                        } else {
                                            std::cout << "Population data error, \"catch\", \"indexvec\" should be an array.\n";
                                            exit(0);
                                        }
                                    } else {
                                        std::cout << "Population data warning, \"catch\" missing \"indexvec\" value.\n";
//                                        exit(0);
                                    }
                                    ////                                    
                                    //


                                    temp = (*catch_).value[j].FindMember("indexerrvec");
                                    if ((temp) != (*catch_).value[j].MemberEnd()) {

                                        if ((*temp).value.IsArray()) {
                                            int s = (*temp).value.Size();
                                            c.index_error_vector.Resize(s);
                                            for (int k = 0; k < s; k++) {
                                                c.index_error_vector(k) = static_cast<T> ((*temp).value[k].GetDouble());
                                            }

                                        } else {
                                            std::cout << "Population data error, \"catch\", \"indexerrvec\" should be an array.\n";
                                            exit(0);
                                        }
                                    } else {
                                        std::cout << "Population data warning, \"catch\" missing \"indexerrvec\" value.\n";
                                    }
                                    
                                    
                                    
                                    pop_data.catch_data.push_back(c);
                                }

                            } else {
                                std::cout << "Population data error, \"catch\" attribute should be an array.\n";
                                exit(0);
                            }


                        } else {
                            std::cout << "Population data error, expected attribute catch.\n";
                            exit(0);
                        }


                        rapidjson::Document::MemberIterator length_comp_;
                        length_comp_ = v.FindMember("length_comp");

                        if (length_comp_ != v.MemberEnd()) {
                            rapidjson::Document::MemberIterator temp;

                            if ((*length_comp_).value.IsArray()) {
                                for (int j = 0; j < (*length_comp_).value.Size(); j++) {
                                    LengthComposition<T> lc;

                                    temp = (*length_comp_).value[j].FindMember("fleet");
                                    if ((temp) != (*length_comp_).value[j].MemberEnd()) {
                                        lc.fleet = (*temp).value.GetInt();
                                    } else {
                                        std::cout << "Population data error, \"length_comp\" missing \"fleet\" id.\n";
                                        exit(0);
                                    }


                                    temp = (*length_comp_).value[j].FindMember("season");
                                    if ((temp) != (*length_comp_).value[j].MemberEnd()) {
                                        lc.season = (*temp).value.GetInt();
                                    } else {
                                        std::cout << "Population data error, \"length_comp\" missing \"season\" id.\n";
                                        exit(0);
                                    }

                                    temp = (*length_comp_).value[j].FindMember("area");
                                    if ((temp) != (*length_comp_).value[j].MemberEnd()) {
                                        lc.area = (*temp).value.GetInt();
                                    } else {
                                        std::cout << "Population data error, \"length_comp\" missing \"area\" id.\n";
                                        exit(0);
                                    }

                                    temp = (*length_comp_).value[j].FindMember("gender");
                                    if ((temp) != (*length_comp_).value[j].MemberEnd()) {
#warning gender type tag needs 
                                        lc.gender = (GenderType) (*temp).value.GetInt();
                                    } else {
                                        std::cout << "Population data error, \"length_comp\" missing \"gender\" id.\n";
                                        exit(0);
                                    }

                                    temp = (*length_comp_).value[j].FindMember("yearvec");
                                    if ((temp) != (*length_comp_).value[j].MemberEnd()) {

                                        if ((*temp).value.IsArray()) {
                                            int s = (*temp).value.Size();
                                            lc.year_vector.Resize(s);
                                            for (int k = 0; k < s; k++) {
                                                lc.year_vector(k) = (*temp).value[k].GetInt();
                                            }

                                        } else {
                                            std::cout << "Population data error, \"catch\", \"length_comp\" should be an array.\n";
                                            exit(0);
                                        }
                                    } else {
                                        std::cout << "Population data error, \"catch\" missing \"length_comp\" value.\n";
                                        exit(0);
                                    }


                                    temp = (*length_comp_).value[j].FindMember("nsamplevec");
                                    if ((temp) != (*length_comp_).value[j].MemberEnd()) {

                                        if ((*temp).value.IsArray()) {
                                            int s = (*temp).value.Size();
                                            lc.nsample_vector.Resize(s);
                                            for (int k = 0; k < s; k++) {
                                                lc.nsample_vector(k) = (*temp).value[k].GetInt();
                                            }

                                        } else {
                                            std::cout << "Population data error, \"catch\", \"nsamplevec\" should be an array.\n";
                                            exit(0);
                                        }
                                    } else {
                                        std::cout << "Population data error, \"catch\" missing \"nsamplevec\" value.\n";
                                        exit(0);
                                    }

                                    temp = (*length_comp_).value[j].FindMember("lenpropmatrix");
                                    if ((temp) != (*length_comp_).value[j].MemberEnd()) {

                                        if ((*temp).value.IsArray()) {
                                            int s = (*temp).value.Size();
                                            std::vector<std::vector<T> > lpd;
                                            for (int k = 0; k < s; k++) {
                                                if ((*temp).value[k].IsArray()) {
                                                    std::vector<T> row;
                                                    for (int l = 0; l < (*temp).value[k].Size(); l++) {
                                                        row.push_back(static_cast<T> ((*temp).value[k][l].GetDouble()));
                                                    }
                                                    lpd.push_back(row);
                                                } else {
                                                    std::cout << "Population data error, \"catch\", \"lenpropmatrix\" should be a matrix.\n";
                                                    exit(0);
                                                }

                                            }

                                            lc.length_prop_matrix.Resize(lpd.size(), lpd[0].size());

                                            for (int ii = 0; ii < lc.length_prop_matrix.Size(0); ii++) {
                                                for (int jj = 0; jj < lc.length_prop_matrix.Size(1); jj++) {
                                                    lc.length_prop_matrix(ii, jj) = lpd[ii][jj];
                                                }
                                            }

                                        } else {
                                            std::cout << "Population data error, \"catch\", \"length_comp\" should be an array.\n";
                                            exit(0);
                                        }




                                    } else {
                                        std::cout << "Population data error, \"catch\" missing \"length_comp\" value.\n";
                                        exit(0);
                                    }


                                    pop_data.length_composition.push_back(lc);

                                }
                            }
                        }


                        rapidjson::Document::MemberIterator age_comp_;
                        age_comp_ = v.FindMember("age_comp");

                        if (age_comp_ != v.MemberEnd()) {
                            rapidjson::Document::MemberIterator temp;

                            if ((*age_comp_).value.IsArray()) {
                                for (int j = 0; j < (*age_comp_).value.Size(); j++) {
                                    AgeComposition<T> lc;

                                    temp = (*age_comp_).value[j].FindMember("fleet");
                                    if ((temp) != (*age_comp_).value[j].MemberEnd()) {
                                        lc.fleet = (*temp).value.GetInt();
                                    } else {
                                        std::cout << "Population data error, \"length_comp\" missing \"fleet\" id.\n";
                                        exit(0);
                                    }


                                    temp = (*age_comp_).value[j].FindMember("season");
                                    if ((temp) != (*age_comp_).value[j].MemberEnd()) {
                                        lc.season = (*temp).value.GetInt();
                                    } else {
                                        std::cout << "Population data error, \"length_comp\" missing \"season\" id.\n";
                                        exit(0);
                                    }

                                    temp = (*age_comp_).value[j].FindMember("area");
                                    if ((temp) != (*age_comp_).value[j].MemberEnd()) {
                                        lc.area = (*temp).value.GetInt();
                                    } else {
                                        std::cout << "Population data error, \"length_comp\" missing \"area\" id.\n";
                                        exit(0);
                                    }

                                    temp = (*age_comp_).value[j].FindMember("gender");
                                    if ((temp) != (*age_comp_).value[j].MemberEnd()) {
#warning gender type tag needs 
                                        lc.gender = (GenderType) (*temp).value.GetInt();
                                    } else {
                                        std::cout << "Population data error, \"length_comp\" missing \"gender\" id.\n";
                                        exit(0);
                                    }



                                    temp = (*age_comp_).value[j].FindMember("nsamplevec");
                                    if ((temp) != (*age_comp_).value[j].MemberEnd()) {

                                        if ((*temp).value.IsArray()) {
                                            int s = (*temp).value.Size();
                                            lc.nsample_vector.Resize(s);
                                            for (int k = 0; k < s; k++) {
                                                lc.nsample_vector(k) = (*temp).value[k].GetInt();
                                            }

                                        } else {
                                            std::cout << "Population data error, \"catch\", \"nsamplevec\" should be an array.\n";
                                            exit(0);
                                        }
                                    } else {
                                        std::cout << "Population data error, \"catch\" missing \"nsamplevec\" value.\n";
                                        exit(0);
                                    }


                                    temp = (*age_comp_).value[j].FindMember("agepropmatrix");
                                    if ((temp) != (*age_comp_).value[j].MemberEnd()) {

                                        if ((*temp).value.IsArray()) {
                                            int s = (*temp).value.Size();
                                            std::vector<std::vector<T> > lpd;
                                            for (int k = 0; k < s; k++) {
                                                if ((*temp).value[k].IsArray()) {
                                                    std::vector<T> row;
                                                    for (int l = 0; l < (*temp).value[k].Size(); l++) {
                                                        row.push_back(static_cast<T> ((*temp).value[k][l].GetDouble()));
                                                    }
                                                    lpd.push_back(row);
                                                } else {
                                                    std::cout << "Population data error, \"catch\", \"lenpropmatrix\" should be a matrix.\n";
                                                    exit(0);
                                                }

                                            }

                                            lc.age_propogation_matrix.Resize(lpd.size(), lpd[0].size());

                                            for (int ii = 0; ii < lc.age_propogation_matrix.Size(0); ii++) {
                                                for (int jj = 0; jj < lc.age_propogation_matrix.Size(1); jj++) {
                                                    lc.age_propogation_matrix(ii, jj) = lpd[ii][jj];
                                                }
                                            }

                                        } else {
                                            std::cout << "Population data error, \"catch\", \"length_comp\" should be an array.\n";
                                            exit(0);
                                        }




                                    } else {
                                        std::cout << "Population data error, \"catch\" missing \"age_comp\" value.\n";
                                        exit(0);
                                    }


                                    pop_data.age_composition.push_back(lc);

                                }
                            }
                        }


                        rapidjson::Document::MemberIterator msa_;

                        msa_ = v.FindMember("mean_size_at_age");

                        if (msa_ != v.MemberEnd()) {
                            rapidjson::Document::MemberIterator temp;

                            if ((*msa_).value.IsArray()) {
                                for (int j = 0; j < (*msa_).value.Size(); j++) {
                                    MeanSizeAtAge<T> lc;

                                    temp = (*msa_).value[j].FindMember("fleet");
                                    if ((temp) != (*msa_).value[j].MemberEnd()) {
                                        lc.fleet = (*temp).value.GetInt();
                                    } else {
                                        std::cout << "Population data error, \"length_comp\" missing \"fleet\" id.\n";
                                        exit(0);
                                    }


                                    temp = (*msa_).value[j].FindMember("season");
                                    if ((temp) != (*msa_).value[j].MemberEnd()) {
                                        lc.season = (*temp).value.GetInt();
                                    } else {
                                        std::cout << "Population data error, \"length_comp\" missing \"season\" id.\n";
                                        exit(0);
                                    }

                                    temp = (*msa_).value[j].FindMember("area");
                                    if ((temp) != (*msa_).value[j].MemberEnd()) {
                                        lc.area = (*temp).value.GetInt();
                                    } else {
                                        std::cout << "Population data error, \"length_comp\" missing \"area\" id.\n";
                                        exit(0);
                                    }

                                    temp = (*msa_).value[j].FindMember("gender");
                                    if ((temp) != (*msa_).value[j].MemberEnd()) {
#warning gender type tag needs 
                                        lc.gender = (GenderType) (*temp).value.GetInt();
                                    } else {
                                        std::cout << "Population data error, \"length_comp\" missing \"gender\" id.\n";
                                        exit(0);
                                    }



                                    temp = (*msa_).value[j].FindMember("yearvec");
                                    if ((temp) != (*msa_).value[j].MemberEnd()) {

                                        if ((*temp).value.IsArray()) {
                                            int s = (*temp).value.Size();
                                            lc.year_vector.Resize(s);
                                            for (int k = 0; k < s; k++) {
                                                lc.year_vector(k) = (*temp).value[k].GetInt();
                                            }

                                        } else {
                                            std::cout << "Population data error, \"catch\", \"nsamplevec\" should be an array.\n";
                                            exit(0);
                                        }
                                    } else {
                                        std::cout << "Population data error, \"catch\" missing \"nsamplevec\" value.\n";
                                        exit(0);
                                    }


                                    temp = (*msa_).value[j].FindMember("msaamatrix");
                                    if ((temp) != (*msa_).value[j].MemberEnd()) {

                                        if ((*temp).value.IsArray()) {
                                            int s = (*temp).value.Size();
                                            std::vector<std::vector<T> > lpd;
                                            for (int k = 0; k < s; k++) {
                                                if ((*temp).value[k].IsArray()) {
                                                    std::vector<T> row;
                                                    for (int l = 0; l < (*temp).value[k].Size(); l++) {
                                                        row.push_back(static_cast<T> ((*temp).value[k][l].GetDouble()));
                                                    }
                                                    lpd.push_back(row);
                                                } else {
                                                    std::cout << "Population data error, \"catch\", \"msaamatrix\" should be a matrix.\n";
                                                    exit(0);
                                                }

                                            }

                                            lc.msa_matrix.Resize(lpd.size(), lpd[0].size());

                                            for (int ii = 0; ii < lc.msa_matrix.Size(0); ii++) {
                                                for (int jj = 0; jj < lc.msa_matrix.Size(1); jj++) {
                                                    lc.msa_matrix(ii, jj) = lpd[ii][jj];
                                                }
                                            }

                                        } else {
                                            std::cout << "Population data error, \"catch\", \"msaamatrix\" should be an array.\n";
                                            exit(0);
                                        }




                                    } else {
                                        std::cout << "Population data error, \"catch\" missing \"mean_size_at_age\" value.\n";
                                        exit(0);
                                    }


                                    pop_data.msa_data.push_back(lc);

                                }
                            }
                        }

                        rapidjson::Document::MemberIterator age_error_;
                        age_error_ = v.FindMember("age_err");

                        if (age_error_ != v.MemberEnd()) {
                            rapidjson::Document::MemberIterator temp;
                            if ((*age_error_).value.IsArray()) {
                                for (int j = 0; j < (*age_error_).value.Size(); j++) {
                                    AgeError<T> lc;
                                    temp = (*age_error_).value[j].FindMember("gender");

                                    if (temp != (*age_error_).value[j].MemberEnd()) {
                                        lc.gender = (GenderType) (*temp).value.GetInt();
                                    }

                                    temp = (*age_error_).value[j].FindMember("agevec");
                                    if (temp != (*age_error_).value[j].MemberEnd()) {
                                        if ((*temp).value.IsArray()) {
                                            lc.age_vector.Resize((*temp).value.Size());
                                            for (int k = 0; k < (*temp).value.Size(); k++) {
                                                lc.age_vector(k) = static_cast<T> ((*temp).value[k].GetDouble());
                                            }
                                        } else {

                                        }
                                    }

                                    temp = (*age_error_).value[j].FindMember("errvec");
                                    if (temp != (*age_error_).value[j].MemberEnd()) {
                                        if ((*temp).value.IsArray()) {
                                            lc.error_vector.Resize((*temp).value.Size());
                                            for (int k = 0; k < (*temp).value.Size(); k++) {
                                                lc.error_vector(k) = static_cast<T> ((*temp).value[k].GetDouble());
                                            }
                                        } else {

                                        }
                                    }

                                    pop_data.age_error.push_back(lc);
                                }
                            }
                        }

                        data[pop_data.id] = pop_data;
                    }

                }

                return data;
            }


        };

        template<typename T>
        std::ostream& operator<<(std::ostream& out, PopulationData<T>& data) {

            out << "Begin Population Data: \n";
            out << "Id: " << data.id << "\n";
            out << "Name: " << data.name << "\n";
            out << "First Year: " << data.first_year << "\n";
            out << "Last Year: " << data.last_year << "\n";
            out << "Spawn month: " << data.spawn_month << "\n";
            //            out << "Gender Types:" << data.gender_types << "\n";
            out << "Gender Types:[ ";
            for (int i = 0; i < data.gender_types.size(); i++) {
                out << data.gender_types[i] << " ";
            }
            out << "]\n";
            out << "Ages: " << data.ages << "\n";
            out << "Lengths: " << data.lengths << "\n";

            //            out << "Catch Data:\n";
            for (int i = 0; i < data.catch_data.size(); i++) {
                out << data.catch_data[i] << "\n";
            }

            //            out << "Length Composition:\n";
            for (int i = 0; i < data.length_composition.size(); i++) {
                out << data.length_composition[i] << "\n";
            }

            //            out << "Age Composition:\n";
            for (int i = 0; i < data.age_composition.size(); i++) {
                out << data.age_composition[i] << "\n";
            }

            //            out << "Mean Size at Age:\n";
            for (int i = 0; i < data.msa_data.size(); i++) {
                out << data.msa_data[i] << "\n";
            }

            //            out << "Age Error:\n";
            for (int i = 0; i < data.age_error.size(); i++) {
                out << data.age_error[i] << "\n";
            }
            out << "End Population Data\n";
            return out;
        }

        template<typename T>
        struct Population {
            int id;
            std::shared_ptr<Recruitment<T> > recruitment_model;
            PopulationData<T>* data;
            bool valid = false;
            Population() {
            }

            Population(const Population<T>& other) :
            id(other.id), recruitment_model(other.recruitment_model) {
            }

            ~Population() {
                
            }
        };
        
        template<typename T>
        std::ostream& operator <<(std::ostream& out, const Population<T>& pop){
            out<<"Population:\n";
            out<<pop.id;
            if(pop.valid && pop.data != NULL){
                out<<*pop.data;
            }
            return out;
        }


    }
}


#endif /* POPULATION_HPP */

