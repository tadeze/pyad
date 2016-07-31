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
    	 std::string filename("../synth2d.csv");
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
	ASSERT_EQ(ff->nsample,nsample);
	ASSERT_EQ(ff->ntree,ntree);
	ASSERT_FALSE(ff->rsample);
	ASSERT_EQ(ff->maxheight,maxheight);

}
/*
TEST_F(ForestTest,serializeTree){
// Serialize tree
//int  tree = (int)ff->trees.size();
//ASSERT_EQ(tree,ntree);
//std::string dumped =  ff->serialize_tree(tree).dump();

//EXPECT_EQ(dumped.size(),5);

}*/
TEST_F(ForestTest,serialize)
{
    ASSERT_EQ(9,9);
}
TEST_F(ForestTest,deserialize)
{
    ASSERT_EQ(6,6);
}
//Test remaining module in child

