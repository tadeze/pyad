/*
 * IsolationForest.hpp
 *
 *  Created on: May 5, 2015
 *      Author: tadeze
 */

#ifndef ISOLATIONFOREST_HPP_
#define ISOLATIONFOREST_HPP_
#include "forest.hpp"

namespace osu {
	namespace ad {

		class IsolationForest : public Forest {
		public:
			IsolationForest() {};

			IsolationForest(int _ntree, std::shared_ptr<util::dataset> _df,
							int _nsample, int _maxheight, bool _stopheight, bool _rsample);

			//int adaptiveForest(double alpha,int stopLimit);
			void buildForest();

			virtual ~IsolationForest() {
			}

			//convergent iForest
			int adaptiveForest(double alpha, int stopLimit);

			void fixedTreeForest();

			int confTree(double alpha, double rho, int init_tree);

		};

	}
}
#ifdef SERIALIZATION
#include "cereal/types/polymorphic.hpp"
CEREAL_REGISTER_TYPE(osu::ad::IsolationForest);
CEREAL_REGISTER_POLYMORPHIC_RELATION(osu::ad::Forest, osu::ad::IsolationForest);
#endif
#endif /* ISOLATIONFOREST_HPP_ */
