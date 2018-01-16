//
// Created by zemichet on 1/16/18.
//

#ifndef PYIFOREST_BAGGED_FOREST_H
#define PYIFOREST_BAGGED_FOREST_H

#include "forest.hpp"
namespace osu {
    namespace ad {
        class BaggedForest : public Forest {
        public:
            BaggedForest()= default;
            BaggedForest(int _ntree, std::shared_ptr<util::dataset> _df,
                         int _nsample, int _maxheight, bool _stopheight, bool _rsample);
            void buidForest();
            virtual ~BaggedForest(){};
        private:
            std::vector<std::vector<int> > featureUsed;

        };
    }
}

#endif //PYIFOREST_BAGGED_FOREST_H
