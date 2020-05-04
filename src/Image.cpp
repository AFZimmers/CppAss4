//
// Created by User on 2020-03-27.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include "ImageProcessing.h"
#include "Image.h"

using ZMMALE001::ImageProcessing;
using ZMMALE001::Image;
using ZMMALE001::RGB;


void Image::addPixel (RGB pix){
    pixels.push_back(pix);
}

void Image::processHist(int bin_size, bool colour) {

    if (!colour) {
        int num_bins = ceil(255 / bin_size);
        for (int i = 0; i < num_bins + 1; ++i) {
            std::vector<int> v;
            hist_grey_bins.push_back(v);
        }
        for (RGB &pix : pixels) {
            // grey scale only
            int upper = bin_size-1;

            // bin_index = index of the bin in the histogram vector
            for (int bin_index = 0; bin_index < num_bins; ++bin_index) {
                if (pix.grey > upper) {
                    upper += bin_size;
                    continue;
                } else {
                    int greyValue = pix.grey;
                    hist_grey_bins[bin_index].push_back(greyValue);
                    break;
                }
            }// done with one pixel

        } // done with all pixels

        for (int pixel_bin = 0; pixel_bin < hist_grey_bins.size(); ++pixel_bin) {
            hist_grey_bins_count.push_back(hist_grey_bins[pixel_bin].size());
        }
        ////DEBUG CODE print the grey hist
//        for (int pixel_bin = 0; pixel_bin < hist_grey_bins.size(); ++pixel_bin) {
//            int amount = (bin_size + (pixel_bin * bin_size));
//            std::cout << "bin number = " << pixel_bin << " (" << pixel_bin * bin_size << "," << amount-1 << ") >> ";
////            for (int p : hist_grey_bins[pixel_bin]) {
//////                std::cout << p << " ";
////                std::cout << "*";
////            }
//
//            std::cout<<hist_grey_bins[pixel_bin].size();
//            std::cout << std::endl;
//        }
//
//        std::cout << std::endl << " ++++++ " << std::endl;

    } else {
        //If using colour hist
        int num_bins = ceil(255 / bin_size);
        for (int i = 0; i < num_bins + 1; ++i) {
            std::vector<int> v;
            hist_red_bins.push_back(v);
            hist_green_bins.push_back(v);
            hist_blue_bins.push_back(v);
        }
        for (RGB &pix : pixels) {
            // grey scale only
            int upper_red = bin_size-1;
            int upper_green = bin_size-1;
            int upper_blue = bin_size-1;

            // bin_index = index of the bin in the histogram vector
            for (int bin_index = 0; bin_index < num_bins; ++bin_index) {
                if (pix.red > upper_red) {
                    upper_red += bin_size;
                    continue;
                } else {
                    int redValue = pix.red;
                    hist_red_bins[bin_index].push_back(redValue);
                    break;
                }
            }// done with one pixel
            for (int bin_index = 0; bin_index < num_bins; ++bin_index) {
                if (pix.green > upper_green) {
                    upper_green += bin_size;
                    continue;
                } else {
                    int greenValue = pix.green;
                    hist_green_bins[bin_index].push_back(greenValue);
                    break;
                }
            }
            for (int bin_index = 0; bin_index < num_bins; ++bin_index) {
                if (pix.blue > upper_blue) {
                    upper_blue += bin_size;
                    continue;
                } else {
                    int blueValue = pix.blue;
                    hist_blue_bins[bin_index].push_back(blueValue);
                    break;
                }
            }


        } // done with all pixels
        // sets each count for each colour hist count bins
        for (int pixel_bin = 0; pixel_bin < hist_red_bins.size(); ++pixel_bin) {
            hist_red_bins_count.push_back(hist_red_bins[pixel_bin].size());
        }
        for (int pixel_bin = 0; pixel_bin < hist_green_bins.size(); ++pixel_bin) {
            hist_green_bins_count.push_back(hist_green_bins[pixel_bin].size());
        }
        for (int pixel_bin = 0; pixel_bin < hist_blue_bins.size(); ++pixel_bin) {
            hist_blue_bins_count.push_back(hist_blue_bins[pixel_bin].size());
        }
        //concatenates the count bins into a RGB histogram
        hist_RBG_counts.insert(hist_RBG_counts.end(),hist_red_bins_count.begin(),hist_red_bins_count.end());
        hist_RBG_counts.insert(hist_RBG_counts.end(),hist_green_bins_count.begin(),hist_green_bins_count.end());
        hist_RBG_counts.insert(hist_RBG_counts.end(),hist_blue_bins_count.begin(),hist_blue_bins_count.end());

        ////DEBUG CODE print each colour hist to see if values are correct in each bin of each colour
//        for (int pixel_bin = 0; pixel_bin < hist_red_bins.size(); ++pixel_bin) {
//            int amount = (bin_size + (pixel_bin * bin_size));
//            std::cout << "bin number = " << pixel_bin << " (" << pixel_bin * bin_size << "," << amount-1 << ") >> ";
//            for (int p : hist_red_bins[pixel_bin]) {
//                std::cout << p << " ";
//            }
//            std::cout << std::endl;
//        }
//        for (int pixel_bin = 0; pixel_bin < hist_green_bins.size(); ++pixel_bin) {
//            int amount = (bin_size + (pixel_bin * bin_size));
//            std::cout << "bin number = " << pixel_bin << " (" << pixel_bin * bin_size << "," << amount-1 << ") >> ";
//            for (int p : hist_green_bins[pixel_bin]) {
//                std::cout << p << " ";
//            }
//            std::cout << std::endl;
//        }
//        for (int pixel_bin = 0; pixel_bin < hist_blue_bins.size(); ++pixel_bin) {
//            int amount = (bin_size + (pixel_bin * bin_size));
//            std::cout << "bin number = " << pixel_bin << " (" << pixel_bin * bin_size << "," << amount-1 << ") >> ";
//            for (int p : hist_blue_bins[pixel_bin]) {
//                std::cout << p << " ";
//            }
//            std::cout << std::endl;
//        }
//        std::cout << std::endl << " ++++++ " << std::endl << std::endl;
    }
}

unsigned int &ZMMALE001::Image::getHeight() {
    return height;
}

unsigned int &ZMMALE001::Image::getWidth() {
    return width;
}

RGB &ZMMALE001::Image::get(unsigned int x, unsigned int y) {
    return pixels[(y*width)+x];
}

ZMMALE001::Image::Image() {
    width = 0;
    height = 0;
}

ZMMALE001::Image::Image(int w, int h, std::string fname) {
    width = w ;
    height = h;
    filename=fname;
}

const string &ZMMALE001::Image::getFilename() const {
    return filename;
}

void ZMMALE001::Image::setClusterValue(unsigned int clusterValue) {
    Image::clusterValue = clusterValue;
}


unsigned int ZMMALE001::Image::getClusterValue() const {
    return clusterValue;
}


