/*
 * utitlity.h
 *
 *  Created on: Mar 27, 2015
 *      Author: Tadeze
 */

#include "utility.hpp"

using namespace std;
using namespace osu::ad;
    //default_random_engine gen(400);  //Debugging

    default_random_engine gen(time(NULL));  //Production
    template<typename T>
    T util::randomT(T min, T max) {
        uniform_real_distribution<T> dist(min, max);
        return dist(gen);

    }

    double util::randomD(double min, double max) {
        uniform_real_distribution<double> dist(min, max);
        return dist(gen);
    }

    int util::randomI(int min, int max) {

        uniform_int_distribution<unsigned> dist(min, max);
        return dist(gen);
    }

    int util::randomEx(int min, int max, set<int> &exlude) {
        int num;
        num = randomI(min, max);            //(int) (min + (rand() % (max - min+1)));
        return exlude.find(num) != exlude.end() ? randomEx(min, max, exlude) : num;

    }

    void util::sampleI(int min, int max, int nsample, vector<int> &samples) {
        int cnt = 0;
        int rndI;
        set<int> duplicate;
        while (cnt < nsample) {
            rndI = randomEx(min, max, duplicate);
            samples.push_back(rndI);
            duplicate.insert(rndI);
            cnt++;

        }

    }

    double util::avgPL(int n) {

        return (((n - 1) <= 0) ?
                0.0 :
                ((2.0 * (log((double) (n - 1)) + 0.5772156649))
                 - (2.0 * (double) (n - 1)) / (1.0 + (double) (n - 1))));

    }
    double util::score(double depth, int n) {
        return pow(2, -depth / avgPL(n));
    }
    template<typename T>
    void util::swapInt(int a, int b, T *x) {
        int hold;
        hold = x[a];
        x[a] = x[b];
        x[b] = hold;
    }

//template<typename T>
/*
 * Sample mean of points
 */
    double util::mean(vector<double> points) {
        double sum = 0;
        for (int f = 0; f < (int) points.size(); f++)
            sum += points[f];
        return sum / (double) points.size();
    }

/*
 * Calculate sample variance from vector of doublen numbers
 */
    double util::variance(vector<double> &x) {
        double sum = 0.0;
        double mn = mean(x);
        for (double elem : x) {
            sum += pow(elem - mn, 2);
        }
        return sum / (double) (x.size() - 1);
    }

/* T-confidence interval
 *
 */
    double util::tconf(vector<double> &points, double sigma = 0.95) {
        double sd = sqrt(variance(points));
        double tvalue = 1.64 * sd / (double) sqrt(points.size());
        return tvalue;
    }


/*
 * Read csv file into vector,
 * used for testing
 */

    vector<vector<double> > util::readcsv(const char *filename, char delim = ',',
                                    bool header = true) {
        vector<vector<double> > values;
        vector<double> valueline;
        ifstream fin(filename);
        string item;
        if (header)  //if header available
            getline(fin, item);

        for (string line; getline(fin, line);) {
            istringstream in(line);
            while (getline(in, item, delim)) {
                valueline.push_back(atof(item.c_str()));
            }
            values.push_back(valueline);
            valueline.clear();
        }
        return values;
    }

/*
 * Calculate the cumulative distribution function
 */
    map<double, double> util::ecdf(vector<double> points) {
        map<double, double> cdfm;

        sort(points.begin(), points.end());
        int j = -1;
        double len = (double) points.size();
        for (unsigned i = 0; i < points.size(); ++i) {
            if (i == 0 || points[i - 1] != points[i]) {
                j++;
                cdfm.insert({points.at(i), (double) (i + 1) / len});
            } else {
                cdfm[points.at(i)] = (double) (i + 1) / len;
            }
        }
        return cdfm;

    }


    template<typename T>
    vector<T> flatten(const vector<vector<T>> &v) {
        size_t total_size = 0;
        for (const auto &sub : v)
            total_size += sub.size();
        vector<T> result;
        result.reserve(total_size);
        for (const auto &sub : v)
            result.insert(result.end(), sub.begin(), sub.end());
        return result;
    }



/*
 * Compute the Anderson-Darling distance for the depth distribution of each point
 * input: 2-d depth row X tree_depth
 * return 1-D score of each point
 */

    vector<double> ADdistance(vector<vector<double> > depths, bool weightToTail =
    false) {
        //flatten 2-d to 1-d and compute alldepth ECDF of using all points depths
        vector<double> alldepth = flatten(depths);
        map<double, double> Fxm = util::ecdf(alldepth); //all depth cdf

        vector<double> scores;
        /*
         * compute score of each point
         * sort the depth, compute its ECDF
         */
        for (vector<double> x : depths) {
            sort(x.begin(), x.end());
            map<double, double>::iterator iter = Fxm.begin();
            map<double, double> fxn = util::ecdf(x);  //empirical cdf of the point
            double sum = 0;
            for (double elem : x) {
                double val;
                while (iter != Fxm.end()) {
                    //cout<<elem<<"\t"<<iter->first<<"\t"<<iter->second<<endl;
                    if (iter->first > elem) //x.at(i))
                    {

                        val = (--iter)->second; //= ((i==0)?.0:(--iter)->second);
                        break;
                    }
                    ++iter;
                }
                if (iter == Fxm.end())
                    val = 0.99999999; //close to 1 at the end of the distribution
                double cdfDiff = max((fxn[elem] - val), 0.0);
                sum += weightToTail ? cdfDiff / sqrt(val) : cdfDiff; //distance of each point in the vector


            }
            scores.push_back(sum);
        }
        return scores;

    }

    /* Logging functions
     * /
     */

/*
    void init_log(std::string filename){
        logfile.open(filename);

    }
    void write_log(std::string &msg){
        logfile<<msg;
    }
    void close_log(){
        logfile.close();
    }

void convertVtoDf(std::vector<std::vector<double> > &sourceVec,doubleframe* df)
{
	int _ncol =(int) sourceVec[0].size();
	int _nrow =(int) sourceVec.size();

	for(int i=0;i<_nrow;i++)
	{
		for(int j=0;j<_ncol;j++)
		{
			df->data[i][j] = sourceVec[i][j];

		}
	}
	df->ncol = _ncol;
	df->nrow = _nrow;

}
*/


    std::string util::filename() {
        std::string filename("/home/tadeze/projects/iForestCodes/pyiForest/test/unittest/synthetic5d34.csv");
        return filename;
    }

    std::shared_ptr<util::dataset> util::makeDataset(std::vector<std::vector<double> > &data) {
        std::shared_ptr<util::dataset> dt = std::make_shared<util::dataset>(); //new util::dataset();
        dt->data = data;
        dt->ncol = (int) data[0].size();
        dt->nrow = (int) data.size();
        return dt;
    }

    void util::displayVec(std::vector<double> &data) {
        for (double row : data) {
            std::cout << row << "\t";
        }
    };

    void util::displayVec(std::vector<std::vector<double> > data) {
        for (auto row : data) {
            displayVec(row);
        }
        std::cout << "\n";
    }


    std::vector<std::vector<double> > util::syntheticData(int D, int N) {
        std::vector<std::vector<double> > data;

        for (int k = 0; k < N; k++) {
            std::vector<double> row;
            for (int j = 0; j < D; j++)
                row.push_back(util::randomD(0, 2));
            data.push_back(row);
        }
        return data;
    }







/* UTITLITY_H_ */

