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
 Specify number of trees to build.
Default value is 100.
 -s S, --sampsize=S
 Specify subsampling rate for each tree. (Value of 0 indicates to use entire data set).
 Default value is 2048.
 -d MAX, --maxdepth=MAX
 Specify maximum depth of trees. (Value of 0 indicates no maximum).
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
#include "utility.hpp"
#include "facade_forest.hpp"
#include "command_parser.hpp"

//log file
//std::ofstream util::logfile("logfile.csv");
/*
 * Display vector data
 */


int main(int argc, char* argv[]) {
    using namespace osu::ad;
    //parseInput(argc,argv);
    //Tree::rangeCheck = true;
    //util::logfile.open("logfile.txt",std::ios_base::out);
    //std::string log_filename ("outputlog.txt");
    //util::init_log(log_filename);
    Parser args;
    args.parse_argument(argc, argv);
    
    std::string filename = args.input_name;//util::filename();
    int ntree = args.ntrees;
    int nsample = args.nsample;
    
    // TODO: Incorporate the command parser into main file
    
    
    std::vector<std::vector<double> > dataxx = util::syntheticData(4,1000);   //util::readcsv((char *) &filename[0], ',', true);

    //util::write_log(filename);
    //util::close_log();
    bool check_missing_value = true;//false;//true;

    // From facadeForest
    FacadeForest ff;

    ff.trainForest(dataxx, 100, 256, 0, false, false, false, 0.01, 0);
    std::cout << ff.getNSample() << " ==" << ff.getNTree() << std::endl;
    std::cout <<"Size of training set"
              <<dataxx.size()
              <<","<<dataxx[0].size()<<std::endl;
    // Insert missing values.

    dataxx[1][0] = -9999.0;
    dataxx[2][1] = -9999.0;
    dataxx[3][1] = -9999.0;
    dataxx[4][1] = -9999.0;
    dataxx[4][2] = -9999.0;


    ff.testForest(dataxx,check_missing_value);
    std::vector<double> score = ff.getScore();
    std::cout<<"Checking scores\n";
    for (auto const &sce : score)
        std::cout << sce << "\t";
    //std::string forest_name = "facadeforest.bin";
    std::ofstream tracedpath("tracedpath2.csv");
    ff.explanation(dataxx[2]);
    ff.tracepath(dataxx[2],tracedpath);
    tracedpath.close();

    //ff.save(forest_name,true);


    /** checking from forest **/

//    std::shared_ptr<util::dataset> dataset;
//    dataset = data::makeDataset(data);
//
//    std::cout<<dataset->data[5][0]<<"\n";
//    int i = 2;
//    std::cout << dataset->ncol << " Column \n";
//    dataset->print(i);
//    auto explan = ff.explanation(dataset->data[i]);
//    std::cout << "\n Explanations" << std::endl;
//    for (const auto &mpr : explan)
//        std::cout << mpr.first << "\t" << mpr.second << std::endl;


    // Register the derivedtype class
    // Serialize
/*
    std::string filenamex{"forest.cereal"};
    {
    std::ofstream file{filenamex};
    if (!file.is_open()) {
        throw std::runtime_error{filenamex + " could not be opened"};
    }
    //cereal::JSONOutputArchive archive{file};
    cereal::BinaryOutputArchive archive{file};
    archive(ff);
    }
*/
    // Read forest

  /*      std::ifstream ifile{filenamex};
        if (!ifile.is_open()) {
            throw std::runtime_error{filenamex + " could not be opened"};
        }
        FacadeForest newff;
       //cereal::JSONInputArchive iarchive{ifile};
       cereal::BinaryInputArchive iarchive(ifile); // Create an input archive
        iarchive(newff);

        newff.testForest(data,check_missing_value);
        auto  new_score = newff.getScore();
       for(auto &sc : new_score)
           std::cout<<sc<<"\t";
*/
    // TODO: explanation returns vad pointer need to be updated.
   // auto tr = std::make_shared<Tree>();
    //tree_sh->iTree(dataIndex,dataset,0,0,false)


    /* checking contributions  from trees **/
	//std::vector<std::vector<double> > data = util::readcsv((char*) &filename[0],',',true);

//	Tree *tr = new Tree();
	/*
    std::vector<int> dataIndex;//(dataset->nrow);
	for(int i=0;i<dataset->nrow;i++)
		dataIndex.push_back(i);
	tr->iTree(dataIndex,dataset,0,0,false);
	std::cout<<tr->pathLength(dataset->data[4])<<" Depth\n";
	std::cout<<"Feature explanations\n";

	auto feature = tr->explanation(dataset->data[5]);
   */
   // archive(cereal::make_nvp("tree",tr));
    //file.close();

/*	std::cout<<feature.size()<<std::endl;
	//dataset->print(2
  for(const auto & mpr : feature)
		std::cout<<mpr.first<<"\t"<<mpr.second<<std::endl;
*///
  //  std::cout<<" Second anomalies";
//    feature = tr->featureContribution(dataset->data[4]);
//    std::cout<<feature.contributions.size()<<std::endl;
//    dataset->print(4);
//    for(const auto & mpr : feature.featureContribution())
//        std::cout<<mpr.first<<"\t"<<mpr.second<<std::endl;


    /*for(auto sc : score){
           std::cout<<sc<<std::endl;

       }
    */
	//displayVec(ff.getTraindf()->data);

   /* util::dataset *dt = makeDataset(data);

    std::cout<<dt->nrow<<","<<dt->ncol<<" Row/column"<<std::endl;

    IsolationForest iff(100,dt,256,0,false,false);
    iff.fixedTreeForest();
    std::vector<double> score = iff.AnomalyScore(dt);
    for(auto sc : score){
    	std::cout<<sc<<std::endl;

    }
    delete dt;
*/
   //util::logfile.close();
   	return 0;
}












