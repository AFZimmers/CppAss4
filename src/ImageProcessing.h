//
// Created by User on 2020-03-27.
//

#ifndef ASSIGNMENT_4_IMAGEPROCESSING_H
#define ASSIGNMENT_4_IMAGEPROCESSING_H

#include <vector>
#include <string>
#include "Image.h"
#include "clustering.h"
#include <iostream>

using std::string;
using std::vector;

namespace ZMMALE001{
    class ImageProcessing {

friend class clustering;

    private:
        string baseName;
        int numClusters, binSize;
        bool colour, otherMethod;
        vector<Image> images;
        Image readImage(string baseName, string fname);
        bool readImages(string baseName);

        int mksize=15;
        int mkside=(mksize-1)/2;
        int segma=2;
        float xSqrtDervMask [15][15];
        float ySqrtDervMask [15][15];
        float xyDervMask [15][15];


    public:
        ImageProcessing();
        ImageProcessing(string, int, int, bool, bool);
        int getNumClusters() const;
        void processAllHist();
        void classify();
        friend std::ostream& operator<<(std::ostream& os, const ImageProcessing& kt);

        void calRvalue(Image &temp);
        void NonMaximalSuppression( float globalMaxRvalue, Image &temp);
        float GlobalMaxR( Image &temp);
   };
}

#endif //ASSIGNMENT_4_IMAGEPROCESSING_H
