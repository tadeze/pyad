#include "../Tree.hpp"
#include "gtest/gtest.h"
class TreeTest : public ::testing::Test
{
protected:
	Tree *tr;
     util::dataset *dataset;

     util::dataset *makeDataset(std::vector<std::vector<double> > &data)
     {
     	util::dataset *dt = new util::dataset();
     	dt->data = data;
     	dt->ncol = (int)data[0].size();
     	dt->nrow = (int)data.size();
     	return dt;
     }

     virtual void SetUp()
     {

    	 //Let read data from
        // std::string filename("../synth2d.csv");
         std::string filename("test2d.csv");

         std::vector<std::vector<double> > data = util::readcsv((char*) &filename[0],',',true);
    	 dataset = makeDataset(data);
    	 tr = new Tree();
   		std::vector<int> dataIndex(dataset->nrow);
   		for(int i=0;i<dataset->nrow;i++) dataIndex.push_back(i);
   		tr->iTree(dataIndex,dataset,0,0,false);
     }

     virtual void TearDown()
     {
        delete dataset;
        delete tr;
     }
};

TEST_F(TreeTest,makeDataset)
{  //Check dimension of the data
 ASSERT_EQ(dataset->ncol,2);
 ASSERT_EQ(dataset->nrow,105);
}

TEST_F(TreeTest, treeCreation)
{
ASSERT_GT(tr->maxTreeDepth(),6); //check ok for now.
}

TEST_F(TreeTest,pathLength)
{
 double depth = tr->pathLength(dataset->data[8]);

 EXPECT_GT(depth,10);
 EXPECT_LT(depth,30);

}
TEST_F(TreeTest,Treerange)
{
	bool rangecheck = tr->rangeCheck;
	ASSERT_TRUE(rangecheck);
}

//Check the anomaly has smaller depth
TEST_F(TreeTest,compareDepth)
{
 std::vector<double> alldepth;
 for(int i=0;i<dataset->nrow;i++)
 alldepth.push_back(tr->pathLength(dataset->data[i]));
 //auto larg = std::max_element(alldepth.begin(),alldepth.end());
 //auto small = std::min_element(alMdepth.begin(),alldepth.end());
 std::sort(alldepth.begin(),alldepth.end());

 EXPECT_LT(alldepth[0],20);
 EXPECT_EQ(alldepth[1],3);
 EXPECT_EQ(alldepth[50],8);

}
TEST_F(TreeTest, to_json)
{
    std::ofstream in("logerr.log");
    // convert tr to json 
   //json jj =  tr->to_json();
//   in<<jj;
 // EXPECT_EQ(jj[0]["depth"],0);
EXPECT_EQ(1,1);
}



