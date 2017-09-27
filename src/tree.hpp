/*
 * Tree.h
 *
 *  Created on: Mar 24, 2015
 *      Author: Tadeze
 */

#ifndef TREE_H_
#define TREE_H_
#include "utility.hpp"
#ifdef SERIALIZE
#include "cereal/cereal.hpp"
#include "cereal/types/vector.hpp"
#include "cereal/types/memory.hpp"
#endif
#include <memory>
#include "feature_contribution.hpp"
namespace  osu {
    namespace ad {
        class Tree : public std::enable_shared_from_this<Tree> {
        private:
            std::shared_ptr<Tree> leftChild, rightChild, parent;
            int nodeSize, splittingAtt, depth;
            double splittingPoint, minAttVal, maxAttVal;

            std::shared_ptr<util::dataset> makeDataset(std::vector<std::vector<double> > &data);

            int parent_id;
        public:
            int getParent_id() const;

            void setParent_id(int parent_id);

        public:
            const std::shared_ptr<Tree> &getLeftChild() const;

            const std::shared_ptr<Tree> &getRightChild() const;

            int getNodeSize() const;

            void setNodeSize(int nodeSize);

            int getSplittingAtt() const;

            void setSplittingAtt(int splittingAtt);

            int getDepth() const;

            void setDepth(int depth);

            double getSplittingPoint() const;

            void setSplittingPoint(double splittingPoint);

            double getMinAttVal() const;

            void setMinAttVal(double minAttVal);

            double getMaxAttVal() const;

            void setMaxAttVal(double maxAttVal);

            static bool rangeCheck;

//    json tracePath(std::vector<double> &inst);
            Tree() : leftChild(nullptr), rightChild(nullptr), parent(nullptr),
                     nodeSize(0), splittingAtt(-1), depth(0), splittingPoint(-9999), minAttVal(0), maxAttVal(0) {};

            virtual ~Tree() {};

            void
            iTree(std::vector<int> const &dIndex, const std::shared_ptr<util::dataset> dt, int height, int maxHeight,
                  bool stopheight);

            void iTree(std::vector<int> const &dIndex, std::vector<std::vector<double> > traindata, int height,
                       int maxHeight, bool stopheight);

            double pathLength(std::vector<double> &inst, bool cmv = false);

            double pathLengthM(std::vector<double> &inst);

            int maxTreeDepth();

            //Contribution
            contrib featureContribution(std::vector<double> &inst) const;

            std::map<int, double> explanation(std::vector<double> &inst) const;
#ifdef SERIALIZATION
            // Serialization
            template<class Archive>
            void serialize(Archive &archive) {
                /*archive(cereal::make_nvp("nodesize",nodeSize),cereal::make_nvp("depth",depth),
                        cereal::make_nvp("splittingAtt",splittingAtt),cereal::make_nvp("splittingPoint",splittingPoint),
                        cereal::make_nvp("minAttVal",minAttVal),cereal::make_nvp("maxAttVal",maxAttVal),
                        cereal::make_nvp("leftChild",leftChild),cereal::make_nvp("rightChild",rightChild)

                );*/
                archive(nodeSize, depth,
                        splittingAtt, splittingPoint,
                        minAttVal, maxAttVal, leftChild, rightChild

                );
            }
#endif

        };
    }
}
#endif /* TREE_H_ */
