/*
 * test_Forest.cpp
 *
 *  Created on: May 4, 2016
 *      Author: tadeze
 */



#include "../Forest.hpp"
#include "gtest/gtest.h"
#include "../IsolationForest.hpp"
class ForestTest : public ::testing::Test
{
protected:
	Forest *ff;
	std::vector<std::vector<double> > data ;
	util::dataset *dataset;
	 int ntree,nsample,maxheight;
	 bool rsample,stopheight;
	virtual void SetUp()
     {
    	ntree=100;
    	nsample=50;
    	maxheight=0;
    	rsample=false;
    	stopheight=false;
    	 //Forest(int _ntree,util::dataset* _dataset,int _nsample,int _maxheight, bool _stopheight,bool _rsample)

    	 //Let read data from
    	 std::string filename("./synth2d.dt");
    	 data= util::readcsv((char*) &filename[0],',',true);
    	 //ff = new FacadeForest();
    	  dataset = makeDataset(data);
    	  ff = new IsolationForest(ntree,dataset,nsample,maxheight,stopheight,rsample);

     }
     util::dataset *makeDataset(std::vector<std::vector<double> > &data)
       {
       	util::dataset *dt = new util::dataset();
       	dt->data = data;
       	dt->ncol = (int)data[0].size();
       	dt->nrow = (int)data.size();
       	return dt;
       }

     virtual void TearDown()
     {
    	delete dataset;
    	delete ff;
     }
};

TEST_F(ForestTest, createForest){
    ff->fixedTreeForest();
    ASSERT_EQ(ff->nsample,nsample);
	ASSERT_EQ(ff->ntree,ntree);
	ASSERT_FALSE(ff->rsample);
	ASSERT_EQ(ff->maxheight,maxheight);

}

TEST_F(ForestTest,serialize)
{
   // ASSERT_EQ(9,9);
    // Test serialization of the Forest.
    ff->fixedTreeForest();
    json jj =  ff->to_json();
   ASSERT_EQ(jj["ntree"],ff->ntree);
   ASSERT_EQ(jj["nsample"],ff->nsample);

   std::ofstream ll("forest.json");
   ll<<jj;
   ll.close();

}


TEST_F(ForestTest,deserialize)
{
   Forest* forest;
   ff->fixedTreeForest();
   std::ofstream ll("tforest.json");
   ll<<ff->to_json();
   ll.close();
IsolationForest iff;
forest = &iff;



   std::ifstream in("tforest.json");
   forest->deseralize_bfs(in);
  ASSERT_EQ(forest->ntree,ntree);
  ASSERT_EQ(forest->nsample,nsample);
  
  ASSERT_EQ(forest->trees[2]->leftChild->nodeSize,
          ff->trees[2]->leftChild->nodeSize); //just take two random node and check they are equal 
  
}
//Test remaining module in child

