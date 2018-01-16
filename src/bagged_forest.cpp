//
// Created by zemichet on 1/16/18.
//

#include "bagged_forest.h"
using namespace osu::ad;

//assert isinstance(train_df, np.ndarray)
//nrow, ncol = train_df.shape
//self.trees_proj = np.zeros([self.ntree, ncol])
//if self.nsample > nrow:
//        self.nsample = nrow
//n_bagged = int(np.ceil(ncol/np.sqrt(ncol)))
//for tree in range(self.ntree):
//sample_index = np.random.choice(nrow, self.nsample, False)
//itree = pft.IsolationTree()
//cols = np.random.choice(ncol, n_bagged, False)
//itree.iTree(sample_index, train_df[:,cols], 0, self.max_height)
//self.trees.append({"tree": itree, "cols":cols})
//self.trees_proj[tree,cols] = 1

void BaggedForest::buidForest() {

    std::vector<int> sampleIndex;
    std::vector<int> sampleColumn;
    //build forest through all trees
    for (int n = 0; n < this->ntree; n++)
    {

        //Sample and shuffle the data.
        sampleIndex.clear();
        sampleColumn.clear();
        getSample(sampleIndex,nsample,rsample,dataframe->nrow);
        //getSample(sampleColumn,(),rsample,dataframe->nrow);

        this->featureUsed.push_back(subSampleFeatures(dataframe->ncol));
        //build tree
        auto tree = std::make_shared<Tree>();
        tree->setParent_id(n);
        //	tree->rangeCheck = this->rangecheck;
        tree->iTree(sampleIndex,dataframe, 0, maxheight, stopheight);
        this->trees.push_back(tree); //add tree to forest
        //	Tree::treeIndx++;
    }


}

BaggedForest::BaggedForest(int _ntree, std::shared_ptr<util::dataset> _df, int _nsample, int _maxheight,
                           bool _stopheight, bool _rsample):Forest(_ntree,_df,_nsample,_maxheight,_stopheight,_rsample){


}

