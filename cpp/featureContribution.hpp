//
// Created by tadeze on 8/9/17.
//

#ifndef PYIFOREST_FEATURECONTRIBUTION_HPP
#define PYIFOREST_FEATURECONTRIBUTION_HPP

#include <vector>
#include <map>

/* Defines feature contribution of a given point
 */
struct Contrib{
    int feature;
    std::map<int,std::vector<double> > contributions;
    void addcont(int index, double depth){
        if(contributions.count(index)<1) {
            std::vector<double> contr;
            contr.push_back(depth);
            contributions.insert({index,contr});
        }
        else{
            contributions[index].push_back(depth);
        }
    }
    std::map<int,double> featureContribution(){
        std::map<int,double> explanation;
        for(const auto & contr : contributions){
            double expl=0.0;
            expl = 1.0/contr.second[0]; //This consider the top most cut.
            //for(auto depth : contr.second) // if we consider all cuts
            //   expl += 1.0/depth;
            explanation.insert({contr.first,expl});

        }
        return explanation;
    }

};
typedef  struct Contrib contrib;

#endif //PYIFOREST_FEATURECONTRIBUTION_HPP
