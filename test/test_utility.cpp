#include "../utility.hpp"
#include "gtest/gtest.h"

/*
 * Test utility class
 */


TEST(UtilTest, testmean)
{
    std::vector<double> x = {1,2,3,4,5};
    double mean = util::mean(x);
    EXPECT_EQ(mean,3);
}
TEST(UtilTest,readcsv)
{
    std::string filename("../synth2d.csv");
    std::vector<std::vector<double> > data = util::readcsv((char*) &filename[0],',',true);
    EXPECT_EQ(data.size(),105); //check number of rows 
    EXPECT_EQ(data[0].size(),2); //check number of columns
}


