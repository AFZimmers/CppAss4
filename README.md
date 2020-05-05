# CppAss4
***
Run make in the home directory to compile the huffman code program.
Image Clustering program is run using the syntax's:
* for just a cout out put of cluster with grey histograms being used:
`./clusterer Gradient_Numbers_PPMS -k 10 -bin 25`
* Output of cluster with grey histograms being used to a file(you can name the file anything as it will be created for you so if -o newfile.txt it will create newfile.txt and output to that file):
`./clusterer Gradient_Numbers_PPMS -o output.txt -k 10 -bin 25`
* if wanting to use colour histograms, which can have the option as above to have the -o part or not:
`./clusterer Gradient_Numbers_PPMS -k 10 -bin 25 -colour`
`./clusterer Gradient_Numbers_PPMS -o output.txt -k 10 -bin 25 -colour`
* if no -k value or -bin value are used it will default them to 10 and 1 respectively.

## Explanation
* I implemented two different ways of getting the initial centroids you can run them on either one the results will differ as
 the centroid are initialized differently. To do this go to clustering.cpp and in the method
  ZMMALE001::clustering::clustering(int numClusters,int binSize,bool colour,vector<Image> &images) 
you can pick them the first one is a k-means ++ method (starts on line 29 - 156) of doing it which initializes each centroid based
 on the furthest image away from the other centroid therefor spreading the centroid over the full data. The second method 
 is picking a random unique image to start initiation (start on line 157 - 194). try using them both please they both do work, just comment out the one you not using or comment in the one you want to use.
 
* I implemented a new feature, which is using the harris corner detector algorithm to detect corners of my images. so when
 you run the program using `./clusterer Gradient_Numbers_PPMS -k 10 -bin 25 -colour -otherMethod` which will output my images
  in a visual form with the value "c" where its found a corner. due to the size of the image the image window used which can be found in ImageProcessing.cpp 
  int mksize if to small to many corners are found and if to big image it self is to small so not many accurate one are found. i do have a image filter so change up the images 
  background and so on one line 92 - 101 on ImageProcessing which variations in this do help with the corners.
  that's is as far as I managed with the extra extra implementation of a good feature. 

## Files and Folders
* **main** - Driver class for the program. Checks for valid arguments and carries out necessary functions specified in the arguments.
* **ImageProcessing** - class does all data processing of the images. 
* **clustering** - class sets my centroids and runs k-mean
* **Image** - class is my data on each image
* **centroid** - class is the centroid created for each cluster