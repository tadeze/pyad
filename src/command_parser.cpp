//
// Created by tadeze on 9/15/17.
//
#include "include/parser/parser.hh"
#include "command_parser.hpp"
/*
 * /*Options:
	-i FILE, --infile=FILE
		Specify path to input data file. (Required).
	-o FILE, --outfile=FILE
		Specify path to output results file. (Required).
	-m COLS, --metacol=COLS
		Specify columns to preserve as meta-data. (Separated by ',' Use '-' to specify ranges).
	-t N, --ntrees=N
		Specify number of trees to build.(Value 0 indicates to use adaptive tree growing)
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
		Toggle verbose output.
		Default value is false.
	-a (null), --adaptive=(null)
		Number of common successive top K for adaptive process.
		Default value is 5.
	-r, --rotate
		Toggle whether to rotate data or not.
		Default value is false.
	-c N, --columns=N
		specify number of columns to use.
		Default value is 0.
	-p, --pathlength
		Toggle whether to display  depth of all trees (Default is false)
		Default value is false.
	-x FILE, --testfile=FILE
		Specify path to test file. (optional).
	-g, --rangecheck
		Toggle whether to use range check or not during testing (Default false)
		Default value is false.
	-j P, --precision=P
		Specify rho precision confidence interval for stopping criteria Value (0.01 to 0.08) works
		Default value is -3.0.
	-q Q, --alpha=Q
		Anomaly proportion. Default 0.01
		Default value is 0.01.
	-e E, --epoch=E
		Specify number of epoch when batch mode training is selected. Default 30
		Default value is 0.
	-z seed, --seed=seed
		Specify seed for randomization. Default random seed
		Default value is -1.
	-l, --explain
		Toggle whether to output feature explanation or not.
		Default value is false.
	-k, --oob
		Check if you want use out of bag estimate for scoring. Default false.
		Default value is false.
	-b FILE, --save=FILE
		Specify path to save iforest model.
	-f FILE, --load=FILE
		Specify path to load saved iforest model, if you want to load from saved forest.
	-h, --help
		Print this help message and exit.
 *
 *
 */


void Parser::parse_argument(int argc, char **argv) {


    optionparser::parser p("IsolationForest commandline options ");

    p.add_option("--ntree", "-t").help("Number of trees.")
            .mode(optionparser::store_value)
            .default_value(100);
    p.add_option("--nsample","-s").help("Sample size. Default 512.")
            .mode(optionparser::store_value)
            .required(false)
            .default_value(512);
    p.add_option("--input","-i").help("Input csv file required.")
            .mode(optionparser::store_value);
    p.add_option("--output","-o").help("Number of synthetic cluster to use. Defualt 3")
            .mode(optionparser::store_value);

    p.add_option("--metacols","-m").help("Metacolumn to skip. ")
            .mode(optionparser::store_mult_values);

    p.add_option("--maxheight", "-d").help("Input data. 3D data with X, Y,Z value separated by comma")
            .mode(optionparser::store_value);
    p.add_option("--pathlenght","-p")
            .help("Toggle whether to display depth of all trees or not. Default false")
            .mode(optionparser::store_true);

    p.eat_arguments(argc, argv);


    if (p.get_value("input")) {
        input_name = p.get_value<std::string>("input");
        //input_name = names;

    }
    if(p.get_value("nsample")) {
        nsample = p.get_value<int>("nsample");
    }

    if(p.get_value("ntree")) {
        ntrees =p.get_value<int>("tree");
    }

    if(p.get_value("output")) {
        output_name = p.get_value<std::string>("output");
    }
/*
    if (p.get_value("metacols")) {
        auto names = p.get_value<int>("metacols");
        gComponent = names;
    }
*/

//    if (p.get_value("knn")){
//        auto names = p.get_value<int>("knn");
//        k = names;
//
//    }

}