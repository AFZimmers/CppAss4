//
// Created by User on 2020-03-27.
//
#include <iostream>
#include <fstream>
#include "ImageProcessing.h"
#include "Image.h"
#include <experimental/filesystem>
#include <iomanip>
#include <cmath>

namespace fs = std::experimental::filesystem;
using ZMMALE001::ImageProcessing;
using ZMMALE001::Image;
using ZMMALE001::RGB;
using ZMMALE001::clustering;

ImageProcessing::ImageProcessing(string base, int clusters, int bin , bool colour , bool otherMethod) : baseName(base), numClusters(clusters), binSize(bin), colour(colour) , otherMethod(otherMethod) {

    // load all the images from <basename> folder and add to this.images
    readImages(base);
}

// read all images from a given folder
bool ImageProcessing::readImages(std::string baseName) {
    std::cout<<"start reading in images"<<std::endl;
    // https://www.bfilipek.com/2019/04/dir-iterate.html#using-c17
    // iterate through all images in basename folder
    for (const auto& entry : fs::directory_iterator(baseName)) {
            const auto filenameStr = entry.path().filename().string();
            if (is_directory(entry)) {
                // ignore
                continue;
            }
            else if (is_regular_file(entry)) {
                // PPM file. read it  in as an image and add to this.images
                Image img_ = readImage( baseName, filenameStr);
                images.push_back( img_ );
            }
            else
                // ignore
                continue;
    }
}

// read a single image when given a filepath and return an image variable
Image ImageProcessing::readImage(string baseName,string fname){

    std::cout<<"read in new image :"<< fname << std::endl;

    // read header
    std::ifstream header_fs(baseName+"/"+fname);
    std::string magic_number,r,c,i;
    header_fs >> magic_number;
    if(magic_number!="P6") {
        header_fs.close();
        std::cerr << "Wrong image format";
        exit(1);
    }
    header_fs>> r;

    header_fs>> c;
    header_fs>> i;
    int h = (atoi(r.c_str()));
    int w = (atoi(c.c_str()));

    // create the image variable
    Image temp(w,h,fname);

    //header_fs.ignore(,'\n');

    RGB tmp_pix;
    char _r;
    char _g;
    char _b;
    int size = h*w;
    for (unsigned int j = 0; j < size; ++j) {
        header_fs>> _r;
        header_fs>> _g;
        header_fs>> _b;
        tmp_pix.red=char(_r);
        tmp_pix.green=char(_g);
        tmp_pix.blue=char(_b);
        tmp_pix.grey= (0.21 * tmp_pix.red + 0.72 * tmp_pix.green + 0.07 * tmp_pix.blue);
        temp.addPixel(tmp_pix);
    }
    header_fs.close();


    if(otherMethod==true){

//second derivative of Gaussian

        for (int y = -mkside; y <=mkside ; ++y) {
            for (int x = -mkside; x <=mkside ; ++x) {
                xSqrtDervMask[y+mkside][x+mkside]=(pow(x,2),-pow(segma,2))*exp(-(pow(x,2)+pow(y,2))/(2*pow(segma,2)))*1.0/pow(segma,4);
            }
        }
        for (int y = -mkside; y <=mkside ; ++y) {
            for (int x = -mkside; x <=mkside ; ++x) {
                ySqrtDervMask[y+mkside][x+mkside]=(pow(y,2),-pow(segma,2))*exp(-(pow(x,2)+pow(y,2))/(2*pow(segma,2)))*1.0/pow(segma,4);
            }
        }
        for (int y = -mkside; y <=mkside ; ++y) {
            for (int x = -mkside; x <=mkside ; ++x) {
                xyDervMask[y+mkside][x+mkside]=(x*y)*exp(-(pow(x,2)+pow(y,2))/(2*pow(segma,2)))*1.0/pow(segma,4);
            }
        }

        //std:: cout<< mksize;
        calRvalue(temp);
        double globalMaxR = GlobalMaxR(temp);
        NonMaximalSuppression(globalMaxR,temp);
        //std:: cout<< mksize;
    }
int count=0;
    //// DEBUG CODE prints out the images
    for (unsigned int y = 0; y < temp.getHeight(); ++y) {
        for (unsigned int x = 0; x < temp.getWidth(); ++x) {
                RGB &ref_colour = temp.get(x, y);
                //std::cout << std::setw(3) << ref_colour.corner << " ";
                //std::cout << "RGB {" <<std::setw (3) <<(int) ref_colour.red << ", " <<std::setw (3) << (int) ref_colour.green << ", "<<std::setw (3) << (int) ref_colour.blue << "}";
                if(ref_colour.corner== true) {
                    std::cout << std::setw(3) << "C ";
                    //count++;
                } else{std::cout<< std::setw (3) << (int)ref_colour.grey<<" ";}
//                if((int)ref_colour.grey>100)
//                {
//                    std::cout<< std::setw (3) << (int)ref_colour.grey;
//                } else{
//                    std::cout<<std::setw(3)<<" ";
//                }
        }
        std::cout<<std::endl;
    }
    std::cout<<count;

    std::cout<<std::endl;
    return temp;// todo why return this

}

void ZMMALE001::ImageProcessing::processAllHist() {

    for(int i=0;i<images.size();i++){
        std::cout<<"Image : "<< images.at(i).getFilename()<<std::endl;
        images.at(i).processHist(binSize,colour);
        std::cout<< std::endl;
    }
}

void ZMMALE001::ImageProcessing::classify() {

    clustering(numClusters,binSize,colour,images);
}

int ZMMALE001::ImageProcessing::getNumClusters() const {
    return numClusters;
}

void ZMMALE001::ImageProcessing::calRvalue(Image &temp) {
    float k= 0.05;
    for (int j = mkside; j < temp.getHeight()-mkside; ++j) {
        for (int i = mkside; i < temp.getWidth()-mkside; ++i) {
            double xx=0.0, yy=0.0,xy=0.0;
            for (int dy = -mkside; dy <=mkside ; ++dy) {
                for (int dx = -mkside; dx <=mkside ; ++dx) {
                    xx+= (xSqrtDervMask[dy + mkside][dx + mkside]) * temp.get(i + dx, j + dy).grey;
                    yy+= (ySqrtDervMask[dy + mkside][dx + mkside]) *temp.get(i+dx,j+dy).grey;
                    xy+= (xyDervMask[dy + mkside][dx + mkside]) *temp.get(i+dx,j+dy).grey;
                }
            }
            //R=detM -k(traceM)^2
            double trace= xx+yy;
            double det = (xx*yy)-(xy*xy);
            double x = det - k * (pow(trace, 2));
            temp.get(i,j).R=x;
            //std::cout<<x<< " ";
        }
    }
}

void ZMMALE001::ImageProcessing::NonMaximalSuppression(float globalMaxRvalue, Image &temp) {
    int gap =4;
    for (int j = gap; j < temp.getHeight()-gap; ++j) {
        for (int i = gap; i < temp.getWidth() - gap; ++i) {
            int maxi=i, maxj =j;
            float MaxR=-1000000000;
            for (int dy = -gap; dy <=gap ; ++dy) {
                for (int dx = -gap; dx <=gap ; ++dx) {
                    if(temp.get(i+dx,j+dy).R>MaxR){
                        MaxR=temp.get(i+dx,j+dy).R;
                        maxi=i+dx;
                        maxj=j+dy;
                    }
                }
            }
            if(maxi==i && maxj ==j && MaxR>0.01*globalMaxRvalue){
                temp.get(i,j).corner=true;
            }
        }
    }


}

float ZMMALE001::ImageProcessing::GlobalMaxR( Image &temp) {
    float Max =-100000000;
    for (int j = mkside; j < temp.getHeight()-mkside; ++j) {
        for (int i = mkside; i < temp.getWidth() - mkside; ++i) {
            if(temp.get(i,j).R>Max){
                Max=temp.get(i,j).R;
            }
        }
    }
    return Max;
}

