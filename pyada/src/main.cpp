/*
 * main.cpp
 *
 @Created on: Mar 22, 2015
 * @Author: Tadeze
 * Main entry: accepts the the
 * @param argv
 *    Usage: iforest [options]
 *      -i FILE, --infile=FILE
 Specify path to input data file. (Required).
 -o FILE, --outfile=FILE
 Specify path to output results file. (Required).
 -m COLS, --metacol=COLS
 Specify columns to preserve as meta-data. (Separated by ',' Use '-' to specify ranges).
 -t N, --ntrees=N
 Specify number of trees_ to build.
Default value is 100.
 -s S, --sampsize=S
 Specify subsampling rate for each tree. (Value of 0 indicates to use entire data set).
 Default value is 2048.
 -d MAX, --maxdepth=MAX
 Specify maximum depth_ of trees_. (Value of 0 indicates no maximum).
 Default value is 0.
 -H, --header
 Toggle whether or not to expect a header input.
 Default value is true.
 -v, --verbose
 Toggle verbose ouput.
 Default value is false.
 -h, --help
 Print this help message and exit.
 */

#include "facade_forest.hpp"
#include "command_parser.hpp"
#include "bagged_forest.hpp"

//log file
#include <cmath>
/*
 * Display vector data
 */

std::ofstream osu::ad::util::log_file; //("log_file.csv");

inline std::vector<int> fill_vector(int start, int end, int step = 1){
    std::vector<int> data;
    for (int i = start; i < end; i += step)
        data.push_back(i);
    return data;
}
inline std::shared_ptr<osu::ad::util::Dataset> make_dataset(std::vector<std::vector<double>> &data){
    std::shared_ptr<osu::ad::util::Dataset> dt = std::make_shared<osu::ad::util::Dataset>();
    dt->data = data;
    dt->ncol = (int)data[0].size();
    dt->nrow = (int)data.size();
    return dt;
}

void testBaggedForest(){
    std::cout << " Checking Bagged forest \n";
    std::vector<std::vector<double>> dataxx = osu::ad::util::synthetic_data(4, 1000); //util::readcsv((char *) &filename[0], ',', true);

    //util::write_log(filename);
    //util::close_log();
    bool check_missing_value = true; //false;//true;

    auto dataset = make_dataset(dataxx);
    // From facadeForest
    osu::ad::BaggedForest bf(100, dataset, 256, 0, false, true);
    bf.check_missing_value_ = true;
    bf.buidForest();
    std::cout << bf.instance_score(dataxx[0]);
    std::cout << "\n End of bagged forest \n";
}

int main(int argc, char **argv){
    Parser args;
    args.parse_argument(argc, argv);
    args.display_argument();

    // util::debug = seed;
    //util::initialize();
    std::string input_name = args.input_name;
    std::string output_name = args.output_name;
    std::string test_name = args.test_name;
    std::string load_forest = args.loadpath;
    std::string save_forest = args.savepath;
    std::string meta_cols = args.metacols;
    int ntree = args.ntrees;
    int nsample = args.nsample;
    int maxheight = args.maxdepth;
    bool header = args.header;

    /*  bool use_subsample_ = num_sample_ != 0;
    bool stop_height_ = max_height_ != 0;
    int stop_limit_ = pargs->adaptive_;
    bool rangecheck = pargs->rangecheck;
    bool rotate_ = pargs->rotate_;
    bool pathlength = pargs->pathlength;
    float rho_ = pargs->precision;
    float alpha = pargs->alpha;
    int epoch = pargs->epoch;
    bool oob = pargs->oobag;

    //Input file to dataframe_
    bool explanation = pargs->explanation;

*/
}

void experimentalCodes(){
    //parseInput(argc,argv);
    //Tree::range_check = true;
    osu::ad::util::log_file.open("log_file.txt", std::ios_base::out);

    std::vector<std::vector<double>> dataxx = osu::ad::util::synthetic_data(4, 1000); //util::readcsv((char *) &filename[0], ',', true);
    testBaggedForest();

    //util::write_log(filename);
    //util::close_log();
    bool check_missing_value = true; //false;//true;

    // From facadeForest
    osu::ad::FacadeForest ff;
    std::vector<int> columnindx = {}; //0,1,2};
    ff.train(dataxx, 100, 256, 0, false, false, false, 0.01, 0, columnindx);
    std::cout << ff.num_sample() << " ==" << ff.num_trees() << std::endl;
    std::cout << "Size of training set"
              << dataxx.size()
              << "," << dataxx[0].size() << std::endl;
    // Insert missing values.

    auto dataset = make_dataset(dataxx);
    auto indexx = fill_vector(0, 256, 1);
    auto tree = std::make_shared<osu::ad::Tree>(); //Tree();
    tree->iTree(indexx, dataset, 0, 0, false);
    std::cout << tree->path_length(dataset->data[0], true) << "\t";
    std::cout << dataset->data[0][0];
    dataset->data[0][0] = NAN;
    std::cout << dataset->data[0][0];
    ff.score(dataxx, check_missing_value);
    std::vector<double> score = ff.anomaly_score();

    std::cout << "Checking scores\n";
    std::cout << "\n checking path" << std::endl;

    std::cout << tree->path_length(dataset->data[0], true) << "\t";
    std::cout << tree->path_length(dataset->data[0], false);
}
