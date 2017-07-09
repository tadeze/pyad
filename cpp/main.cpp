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

#include "FacadeForest.hpp"


using namespace std;

//log file
ofstream util::logfile("treepath.csv");

/*
//Save score to flat file
void saveScoreToFile(std::vector<double> &scores,std::vector<std::vector<double> > &pathLength,
		const ntstringframe* metadata, string fName,bool savePathLength=false)
{

  //Compute the AUC of the score 
  vector<double> groundtruth(scores.size(),0);
  // make 0/1 from label 

  ofstream outscore(fName);
  if(!savePathLength)
	 outscore << "groundtruth,score\n";
	for (int j = 0; j < (int) scores.size(); j++)
    {
      if (metadata)
        {
          outscore<<metadata->data[j][0]<<",";
          //if(metadata->data[j][0]=="anomaly" || metadata->data[j][0] ==1)
            //groundtruth[j] = 1;
         }
		
	outscore  << scores[j]; //<<util::mean(pathLength[j])<<","<<rscores[j];
  if(savePathLength)
   {
      //for generating all depth 
    	for(int i=0;i<(int)pathLength[1].size();i++)
	      {	
		      outscore<<','<<pathLength[j][i];
	       }
    }
    outscore<<"\n";

	}

  outscore.close();

}


void buildForest(Forest &iff, util::doubleframe* test_dt, const double alpha,int stopLimit,float rho,
		string output_name,ntstringframe* metadata,bool savePathLength)
{
    if(iff.ntree>0)
      iff.fixedTreeForest() ;
    else
    {
     //int treeRequired = iff.adaptiveForest(ALPHA,stopLimit);
    	if(rho<0){
    	int treeRequired = iff.adaptiveForest(alpha,stopLimit);
    	std::cout<<"\n# of Tree required from k-agreement \n "<<treeRequired;
    	}else{
    		const int initial_tree=50;
    		int treeRequired = iff.confTree(alpha,rho,initial_tree);
    		std::cout<<"\n# of Tree required from rho based stopping\n "<<treeRequired;
    	}

    }
    vector<double> scores = iff.AnomalyScore(test_dt); //generate anomaly score
   	vector<vector<double> > pathLength = iff.pathLength(test_dt); //generate Depth all points in all trees
saveScoreToFile(scores,pathLength,metadata,output_name,savePathLength);



}

overloaded function
void buildForestPy(Forest &iff, util::doubleframe* test_dt, const double alpha,int stopLimit,float rho)

{
    if(iff.ntree>0)
      iff.fixedTreeForest() ;
    else
    {
     //int treeRequired = iff.adaptiveForest(ALPHA,stopLimit);
    	if(rho<0){
    	int treeRequired = iff.adaptiveForest(alpha,stopLimit);
    	std::cout<<"\n# of Tree required from k-agreement \n "<<treeRequired;
    	}else{
    		const int initial_tree=50; //need to remove the constant term
    		int treeRequired = iff.confTree(alpha,rho,initial_tree);
    		std::cout<<"\n# of Tree required from rho based stopping\n "<<treeRequired;
    	}

    }

    //return iff;

    //vector<double> scores = iff.AnomalyScore(test_dt); //generate anomaly score
   	//vector<vector<double> > pathLength = iff.pathLength(test_dt); //generate Depth all points in all trees

//saveScoreToFile(scores,pathLength,metadata,output_name,savePathLength);

}
*/
/*
 * Display vector data
 */

void displayVec(vector<double> &data)
{
    for(double row : data)
    {
        std::cout<<row<<"\t";
    }
}

void displayVec(vector<vector<double> > data){
	for(auto row : data)
	{
		displayVec(row);
	}
	std::cout<<"\n";
}


/* Generate 2-D data
 *
 */

vector<vector<double> > syntheticData(int D, int N)
	{
		vector<vector<double> > data;
	     for (int k=0;k<N;k++)
	     {
	    	 vector<double> row(D);
	       for(int j=0;j<D;j++)
	        row.push_back(util::randomD(0,2));
			data.push_back(row);
	     }
	     return data;
	}


/* Static variable 
 */
//bool Tree::rangeCheck ;  //range check for Tree score calculation.

/* Static variable 
 */
/*
void parseInput(int argc, char* argv[])
{
    // bool Tree::rangeCheck ;  //range check for Tree score calculation. 

    parse argument from command line
	parsed_args* pargs = parse_args(argc, argv);
	ntstring input_name = pargs->input_name;
	ntstring output_name = pargs->output_name;
    ntstring test_name = pargs->test_name;
    d(int)* metacol = pargs->metacol;
	int ntree = pargs->ntrees;
	int nsample = pargs->sampsize;
	int maxheight = pargs->maxdepth;
	bool header = pargs->header;
	bool verbose = pargs->verbose;
	verbose = verbose; //Clears warning for now.
	bool rsample = nsample != 0;
	bool stopheight = maxheight != 0;
	int  stopLimit = pargs->adaptive;
	bool rangecheck = pargs->rangecheck;	
    bool rotate = pargs->rotate;
    bool pathlength = pargs->pathlength;
    float rho  = pargs->precision;
    float alpha = pargs->alpha;
       //Input file to dataframe
    ntstringframe* csv = read_csv(input_name, header, false, false);
    ntstringframe* metadata = split_frame(ntstring, csv, metacol,true);
	doubleframe* dt = conv_frame(double, ntstring, csv); //read data to the global variable
    
   
    
    //Test file to data frame 
  ntstringframe* csv_test = read_csv(test_name, header, false, false);
  metadata = split_frame(ntstring, csv_test, metacol,true);
  doubleframe* test_dt =dt;
  
  if(test_name==input_name)
       test_dt = dt;
  else
      test_dt = conv_frame(double, ntstring, csv_test); //read data to the global variable
   
    nsample = nsample==0?dt->nrow:nsample;
    //const double ALPHA=0.01;
   Tree::rangeCheck = rangecheck; 
   

   * Test for pyForest
   * TODO: Synthetic data genrating class
   *
  int N=30;
  int D=5;
 vector<vector<double> > data = syntheticData(N,D);
std::string ss("hello world\n");
 PyForest pforest;
//pforest.saveModel(ss);
pforest.trainForest(data,ntree, nsample,maxheight,rotate,stopLimit==0,
		     	rangecheck,rho,stopLimit);
 pforest.testForest(data);
 //pforest.testForest(data);
 vector<double> scores = pforest.getScore();
 for(double sc : scores)
 {
	 std::cout<<sc<<"\n";
 }

*/
/*

 IsolationForest iff(ntree,dt,nsample,maxheight,stopheight,rsample); //build iForest
 buildForest(iff,test_dt,alpha,stopLimit,rho,output_name,metadata,pathlength);
    
 if(rotate)  //check for rotation forest
 {
    RForest rff(ntree,dt,nsample,maxheight,stopheight,rsample);
    string rot_output(output_name); 
    buildForest(rff,test_dt,alpha,stopLimit,rho,"rotate_"+rot_output,metadata,pathlength);
 }

  //Anomaly score and path length


}
*/
namespace data {
	util::dataset *makeDataset(std::vector<std::vector<double> > &data) {
		util::dataset *dt = new util::dataset();
		dt->data = data;
		dt->ncol = (int) data[0].size();
		dt->nrow = (int) data.size();
		return dt;
	}
}




int main(int argc, char* argv[]) 
{
   //parseInput(argc,argv);
	//Tree::rangeCheck = true;
   std::string filename = util::filename();
   std::vector<std::vector<double> > data = util::readcsv((char*) &filename[0],',',true);
    
   // std::cout<<data.size()<<","<<data[0].size()<<" Row/column"<<std::endl;

 // From facadeForest
   FacadeForest ff;

//   std::vector<std::vector<double> > &traindf,int _ntree,
//       		int _nsample,int _maxheight, bool _rotate, bool _adaptive,
//       		    		bool _rangecheck,double _rho,int _stopLimit);
   ff.trainForest(data,100,256,0,false,false,false,0.01,0);
   std::cout<<ff.getNSample()<<" =="<<ff.getNTree()<<std::endl;
   std::cout<<"Size of training set"<<ff.getTraindf()->nrow<<endl;
   ff.testForest(data);
   std::vector<double> score  = ff.getScore();
  /** checking from forest **/
    util::dataset *dataset;
    dataset = data::makeDataset(data);
    int i=2;
    std::cout<<dataset->ncol<<" Column \n";
    dataset->print(i);
    auto explan = ff.explanation(dataset->data[i]);
    std::cout<<"\n Explanations"<<std::endl;
    for(const auto &mpr : explan)
        std::cout<<mpr.first<<"\t"<<mpr.second<<std::endl;





    /* checking contributions  from trees **/
	//std::vector<std::vector<double> > data = util::readcsv((char*) &filename[0],',',true);

//	Tree *tr = new Tree();
//	std::vector<int> dataIndex;//(dataset->nrow);
//	for(int i=0;i<dataset->nrow;i++)
//		dataIndex.push_back(i);
//	tr->iTree(dataIndex,dataset,0,0,false);
//	std::cout<<tr->pathLength(dataset->data[4])<<" Depth\n";
//	std::cout<<"Feature explanations\n";
//
//	auto feature = tr->featureContribution(dataset->data[2]);
//	std::cout<<feature.contributions.size()<<std::endl;
//	dataset->print(2);
//    for(const auto & mpr : feature.featureContribution())
//		std::cout<<mpr.first<<"\t"<<mpr.second<<std::endl;
//
//    std::cout<<" Second anomalies";
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
   util::logfile.close();
   	return 0;
}












