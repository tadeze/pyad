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

#include "main.hpp"
using namespace std;
//log file
ofstream util::logfile("treepath.csv");

//Save score to flat file
void saveScoreToFile(std::vector<double> &scores,std::vector<std::vector<double> > &pathLength,const ntstringframe* metadata, string fName,bool savePathLength=false)
{

    ofstream outscore(fName);
    if(!savePathLength)
	outscore << "groundtruth,score\n";
	for (int j = 0; j < (int) scores.size(); j++)
    {
        if (metadata)
        {
            outscore<<metadata->data[j][0]<<",";
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

  void buildForest(Forest &iff,const double ALPHA,int stopLimit,string output_name,ntstringframe* metadata,bool savePathLength)
 {
    if(iff.ntree>0)
       iff.fixedTreeForest() ;
    else
    {
     int treeRequired = iff.adaptiveForest(ALPHA,stopLimit);
     std::cout<<"\n# of Tree required "<<treeRequired;
    }
    vector<double> scores = iff.AnomalyScore(iff.dataset); //generate anomaly score
   	vector<vector<double> > pathLength = iff.pathLength(iff.dataset); //generate Depth all points in all trees
    saveScoreToFile(scores,pathLength,metadata,output_name,savePathLength);



 }
    



int main(int argc, char* argv[]) {

    /*parse argument from command line*/
	parsed_args* pargs = parse_args(argc, argv);
	ntstring input_name = pargs->input_name;
	ntstring output_name = pargs->output_name;
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
    bool rotate = pargs->rotate;
    bool pathlength = pargs->pathlength;
    ntstringframe* csv = read_csv(input_name, header, false, false);
	ntstringframe* metadata = split_frame(ntstring, csv, metacol,true);
	doubleframe* dt = conv_frame(double, ntstring, csv); //read data to the global variable
    nsample = nsample==0?dt->nrow:nsample;
    const double ALPHA=0.01;
  
    IsolationForest iff(ntree,dt,nsample,maxheight,stopheight,rsample); //build iForest
    buildForest(iff,ALPHA,stopLimit,output_name,metadata,pathlength);
    
    if(rotate)  //check for rotation forest
    {
          RForest rff(ntree,dt,nsample,maxheight,stopheight,rsample);
          string rot_output(output_name); 
          buildForest(rff,ALPHA,stopLimit,"rotate_"+rot_output,metadata,pathlength);

    }
    util::logfile.close();
	return 0;
}












