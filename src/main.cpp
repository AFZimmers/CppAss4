#include <iostream>
#include "ImageProcessing.h"
#include "Image.h"
#include "ClusterProcess.h"
#include <cctype>



using ZMMALE001::ImageProcessing;
using ZMMALE001::Image;
using std::string;

int main(int argc, char *argv[]) {

    std::cout << "start proses.\n";

    std::string format= "clusterer <dataset> [-o output] [-k n] [-bin b] [-color]";

    std::string baseName;
    std::string output;
    //default
    int clusters=10;
    int bin=1;
    bool colour=false;
    try {
        int i = 0;
        while (argv[i] != NULL) {
            if (std::string(argv[i]).compare("-o")) {
                output = argv[i + 1];
                i++;
            } else if (std::string(argv[i]).compare("-k")) {
                output = argv[i + 1];
                i++;
            } else if (std::string(argv[i]).compare("-bin")) {
                output = argv[i + 1];
                i++;
            } else if (std::string(argv[i]).compare("-colour")) {
                colour = true;
            }
            i++;
        }

        ImageProcessing driver(string(baseName), clusters, bin);

        // print histogram (DEBUG)
        driver.printHist();

        // classify the images
        // driver.classify();
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
