//
// Created by zemichet on 3/30/16.
//

#ifndef FacadeFOREST_HPP
#define FacadeFOREST_HPP
//#ifdef __linux__
//#define SERIALIZATION
//#endif

#include "main.hpp"

namespace osu {
    namespace ad {
        class FacadeForest {
        private:
            int ntree;
            int nsample;
            int maxHeight;
            bool rotate;
            bool adaptive;
            bool rangeCheck;
            double rho;
            int stopLimit;
            bool cmv;

            std::shared_ptr<util::dataset> traindf, testdf;
            //std::shared_ptr<util::dataset> testdf;
            std::shared_ptr<Forest> iff;


            const int FOREST_NOT_TRAINED = 1;
            const int NO_TEST_DATA = 2;
            const int OK = 0;

            //const int JSON_FORMAT=1;
            enum OUTPUT_FORMAT {
                JSON_FORMAT, BINARY_FORMAT
            };
        public:

            // enum FOREST{IFOREST,RFOREST,CFOREST};
            virtual ~FacadeForest() {};


            FacadeForest();

            void tracepath(std::vector<double> &inst, std::ostream &out) {
                iff->tracePath(inst, out);
            }

            int getNTree() const {
                return iff->ntree;

            }

            int getNSample() const {
                return iff->nsample;
            }

            /*
             *
             void setNsample(int nsample) {
                  FacadeForest::nsample = nsample;
              }
              */

            int getMaxDepth() const {
                return iff->maxheight;
            }


            bool isAdaptive() const {
                return this->adaptive;
            }

            bool isRotate() const {
                return rotate;
            }

            bool isRangeCheck() const {
                return rangeCheck;
            }

            void setRangeCheck(bool rangecheck) {
                FacadeForest::rangeCheck = rangecheck;
            }

            const std::shared_ptr<Forest> getIff() const {
                return iff;
            }

            const std::shared_ptr<util::dataset> getTestdf() const {
                return testdf;
            }

            const std::shared_ptr<util::dataset> getTraindf() const {
                return traindf;
            }

            //Methods

            int trainForest(std::vector<std::vector<double> > &traindf, int _ntree,
                            int _nsample, int _maxheight, bool _rotate, bool _adaptive,
                            bool _rangecheck, double _rho, int _stopLimit,
                            std::vector<int> const &columnIndex = std::vector<int>());

            int trainForest(std::vector<std::vector<double> > &traindf, int _ntree,
                            int _nsample, int _maxheight, bool _rotate) {
                return trainForest(traindf, _ntree, _nsample, _maxheight, _rotate, false, true, 0.01, 5);
            };


            void testForest(std::vector<std::vector<double> > &testdf, bool cmv = false);

            // void saveModel(std::string modelName);

            //void loadModel(std::string modelName,std::string forest_type);
            std::vector<double> getScore();

            std::vector<std::vector<double> > pathLength();

            std::vector<double> averageDepth();

            std::map<int, double> explanation(std::vector<double> &inst);

            void displayData(std::vector<std::vector<double> > &_df);

            int isValidModel() const;

            void load(const std::string &filename, bool binaryFormat = true); //OUTPUT_FORMAT output_format);
            void save(const std::string &filenam, bool binaryFormat = true); //, OUTPUT_FORMAT output_format);

#ifdef SERIALIZATION

            template<class Archive>
            void serialize(Archive &archive) {

                /*archive(cereal::make_nvp("ntree",ntree),cereal::make_nvp("nsample",nsample),
                        cereal::make_nvp("maxHeight",maxHeight),cereal::make_nvp("stopLimit",stopLimit),
                        cereal::make_nvp("rho",rho),cereal::make_nvp("rotate",rotate),
                        cereal::make_nvp("adaptive",adaptive),cereal::make_nvp("forest",iff));
                */
                archive(ntree, nsample, maxHeight, stopLimit,
                        rho, rotate, adaptive, iff);
            };
#endif

        };
    }
}
//CEREAL_REGISTER_TYPE(IsolationForest);
//CEREAL_REGISTER_POLYMORPHIC_RELATION(Forest,IsolationForest);

#endif //IFOREST_ADDIN_FacadeForest_HPP
