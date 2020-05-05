#include <iostream>
#include "ImageProcessing.h"
#include "Image.h"
#include <cctype>
#include <fstream>


using ZMMALE001::ImageProcessing;
using ZMMALE001::Image;
using std::string;

int main(int argc, char *argv[]) {

    std::cout << "start proses.\n";

    std::string format= "clusterer <dataset> [-o output] [-k n] [-bin b] [-color] [-otherMethod]";

    std::string baseName;
    //default
    std::string output ="noOutputLoctation";
    int clusters=10;
    int bin=1;
    bool colour=false;
    bool otherMethod = false;

    try {
        baseName = argv[1];
        int i = 1;
        while (argv[i] != NULL) {
            if (std::string(argv[i])=="-o") {
                output = argv[i + 1];
                i++;
            } else if (std::string(argv[i])=="-k") {
                clusters = std::stoi(argv[i + 1]);
                i++;
            } else if (std::string(argv[i])=="-bin") {
                bin = std::stoi(argv[i + 1]);
                i++;
            } else if (std::string(argv[i])=="-colour") {
                colour = true;
            }else if (std::string(argv[i])=="-otherMethod") {
                otherMethod = true;
            }
            i++;
        }

        ImageProcessing driver(string(baseName), clusters, bin ,colour ,otherMethod);

        // processes and print histogram (DEBUG)
        driver.processAllHist();

        // kills if otherMethod is run
        if(otherMethod==true) {
            exit(0);
        }
        // classify the images
        driver.classify();
        //Out put of clusters
        if(output=="noOutputLoctation"){
            std::cout<<driver;
        } else{
            std::ofstream ofs(output);
            ofs<<(driver);
        }

    }
    catch( std::invalid_argument& e)
            {
                std::cerr << e.what() << std::endl;
                std::cout << format << std::endl;
                return -1;
            }
// end program
return 0;
}
std::ostream &ZMMALE001::operator<<(std::ostream &os, const ImageProcessing& kt) {

    for (int j = 0; j < kt.getNumClusters(); ++j) {
        os<<"Cluster "<< j <<": ";
        for (const Image& i: kt.images){
            if(i.getClusterValue()==j) {
                os<< i.getFilename()+", ";
            }
        }
        os<<std::endl;
    }
    return os;
}