//
// Created by tadeze on 9/15/17.
//

#ifndef PYIFOREST_COMMANDPARSER_HPP
#define PYIFOREST_COMMANDPARSER_HPP
class Parser{
public:
    std::string input_name;
    std::string output_name;
    //std::string test_name;
    int metacols;
    int ntrees;
    int nsample;
    int maxdepth;
    bool header;
    bool adaptive;
    bool rotate;
    bool pathlength;
    bool rangecheck;
    double precision;
    double alpha;
    int epoch;
    int seed;
    bool explain;
    bool oob;
    std::string savepath;
    std::string loadpath;
    bool help;
    void parse_argument(int argc, char* argv[]);
    Parser(){
        input_name = std::string();
        output_name = std::string();
        metacols = 0;
        ntrees = 0;
        nsample = 0;

    }
};
#endif //PYIFOREST_COMMANDPARSER_HPP
