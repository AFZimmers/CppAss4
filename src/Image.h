//
// Created by User on 2020-03-27.
//

#ifndef ASSIGNMENT_4_IMAGE_H
#define ASSIGNMENT_4_IMAGE_H

#include <vector>
#include <string>

using std::vector;

namespace ZMMALE001{

    struct RGB {

        unsigned char red;
        unsigned char green;
        unsigned char blue;
        unsigned char grey;
        double R;
        bool corner;

        RGB(): red(0),blue(0),green(0),grey(0),R(0),corner(false){};

    };

    class Image{
        friend class ImageProcessing;
        friend class clustering;
        friend class centroid;
    private:
        unsigned int width,height;
        vector<RGB> pixels;
        unsigned int clusterValue;

        vector< vector<int> > hist_red_bins;
        vector< vector<int> > hist_green_bins;
        vector< vector<int> > hist_blue_bins;
        vector< vector<int> > hist_grey_bins;
        std::string filename;
        vector<int> hist_grey_bins_count;
        vector<int> hist_red_bins_count;
        vector<int> hist_green_bins_count;
        vector<int> hist_blue_bins_count;
        vector<int> hist_RBG_counts;

    public:
        Image();
        Image(int w, int h, std::string fname);

        void addPixel(RGB pix);
        void processHist(int bin_size, bool colour);
        const std::string &getFilename() const;
        unsigned int &getHeight();
        unsigned int &getWidth();
        RGB &get(unsigned int a, unsigned int b);
        void setClusterValue(unsigned int clusterValue);
        unsigned int getClusterValue() const;
    };
}
#endif //ASSIGNMENT_4_IMAGE_H