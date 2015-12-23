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
	//bool rotate = pargs->rotate;
	ntstringframe* csv = read_csv(input_name, header, false, false);
	ntstringframe* metadata = split_frame(ntstring, csv, metacol,true);
	doubleframe* dt = conv_frame(double, ntstring, csv); //read data to the global variable
    	nsample = nsample==0?dt->nrow:nsample;
    	const double ALPHA=0.01;
	string treereq(output_name);


	 //treereq<input_name;
  	ofstream treeReq(treereq+"_treerequired.csv"); 
        treeReq<<"benchmark,iforest,rforest"<<"\n";
   
         /* Basic IsolationForest  */
 	 IsolationForest iff(ntree,dt,nsample,maxheight,stopheight,rsample); //build iForest
 	 RForest rff(ntree,dt,nsample,maxheight,stopheight,rsample);
	 	
	 if(ntree!=0) //build with specified number of trees  
	{ 
	 	iff.buildForest();
     		rff.rForest();

	}
 	else   //Build trees with adaptive method 
	{ 	
		int ifntree= iff.adaptiveForest(ALPHA,stopLimit);  //use convergence
		int nt= rff.adaptiveForest(ALPHA,stopLimit); 
		treeReq<<input_name<<","<<ifntree<<","<<nt;
	}
	
	

	vector<double> scores = iff.AnomalyScore(dt); //generate anomaly score
   	vector<vector<double> > pathLength = iff.pathLength(dt); //generate Depth all points in all trees
	vector<double> rscores = rff.AnomalyScore(dt);
	ofstream outscore(output_name);
     /*if (metadata!=NULL) {
        if (header) {
            for_each_in_vec(i,cname,metadata->colnames,{
                outscore << *cname << ",";
            })
        } else {
            forseq(c,0,metadata->ncol,{
                outscore << "meta" << c << ",";
            })
        }
         }
    */
	outscore << "indx,ifscore,rfscore\n";
	for (int j = 0; j < (int) scores.size(); j++) {
        if (metadata) {
            forseq(m,0,metadata->ncol,{
                 //outscore << metadata->data[j][m] << ",";
                })
            }
		
		outscore << j << "," << scores[j]<<"," ; //<<util::mean(pathLength[j])<<","<<rscores[j];
		outscore<<rscores[j];
/* //for generating all depth 
		for(int i=0;i<(int)pathLength[1].size();i++)
	{	
		outscore<<','<<pathLength[j][i];
	//	rfscore<<','<<rpathLength[j][i];
	}
*/
	outscore<<"\n"; // << "," << mean(pathLength[j]) << "\n";
    	//logfile

	}
	treeReq.close();
	outscore.close();
   	 util::logfile.close();
	return 0;
}












