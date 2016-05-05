/*
 * test_FacadeForest.cpp
 *
 *  Created on: May 4, 2016
 *      Author: tadeze
 */


#include "../FacadeForest.hpp"
#include "gtest/gtest.h"
class FacadeForestTest : public ::testing::Test
{
protected:
	FacadeForest ff;
	 std::vector<std::vector<double> > data ;
	//util::dataset *dataset;
     virtual void SetUp()
     {

    	 //Let read data from
    	 std::string filename("../synth2d.csv");
    	 data= util::readcsv((char*) &filename[0],',',true);
    	 ff.trainForest(data,100,256,0,false,false,false,0.01,0);  //Just train a forest
    	 ff.testForest(data);

     }

     virtual void TearDown()
     {
    	// delete ff;
     }
};

TEST_F(FacadeForestTest, creatFF){
	ASSERT_EQ(ff.getNsample(),256);
	ASSERT_EQ(ff.getNtree(),100);
	ASSERT_EQ(ff.getTraindf()->nrow,105);

}

TEST_F(FacadeForestTest, creaScore){

	std::vector<double> scores = ff.getScore();
	 std::sort(scores.begin(),scores.end());
	 EXPECT_GT(scores[104],0.74852);
	 EXPECT_LT(scores[0],0.453423);
	 EXPECT_GT(scores[50],0.450967);

}
TEST_F(FacadeForestTest, pathLength){

	std::vector<std::vector<double> > depths = ff.PathLength();
	EXPECT_EQ(depths.size(),105);  //Make sure dimension first
	EXPECT_EQ(depths[0].size(),100);

	 /*(std::sort(scores.begin(),scores.end());
	 EXPECT_GT(scores[104],0.74852);
	 EXPECT_LT(scores[0],0.453423);
	 EXPECT_GT(scores[50],0.450967);
*/
}
TEST_F(FacadeForestTest, avgDepth){
	std::vector<double> scores = ff.averageDepth(); //average depth
	 std::sort(scores.begin(),scores.end());
	 EXPECT_GT(scores[104],3);
	 EXPECT_LT(scores[0],10);
	 EXPECT_GT(scores[50],7);

}
