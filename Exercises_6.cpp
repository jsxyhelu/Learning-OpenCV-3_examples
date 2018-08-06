//Exercises at end of Chapter 6,《learning OpenCV3》
#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void help(const char **argv) {
	cout << "\n\n"
		<< "This program solves the Exercises at the end of Chapter 6 \n"
		<< "Call:\n"
		<< argv[0] << " <path/image_name>\n\n"
		<< "For example: " << argv[0] << " / test.jpg\n"
		<< endl;
}

int main( int argc, const char** argv )
{
	help(argv);
	if(argc < 2) {
		cout << "\nERROR: You had too few parameters.\n" << endl;
		return -1;
	}
	/************************************************************************/
	/*5.1. Drawing practice: load or create and display a color image. Draw one example of
	every shape and line that OpenCV can draw.                           */
	/************************************************************************/
	Mat src = imread(argv[1]);
	cv::circle(src,Point(100,100),100,Scalar(255,255,255),2); //circle
	cv::rectangle(src,Point(0,0),Point(300,300),Scalar(255,255,255),2);//rectangle
	cv::line(src,Point(0,0),Point(300,300),Scalar(255,255,255),2);//line
	cv::ellipse(src,cv::Point(100,100),Size(100,100),45,0,180,Scalar(255,0,0),2);//ellipse
    /************************************************************************/
	/*5.2. Grayscale: load and display a color image.
	a. Turn it into three-channel grayscale (it is still an BGR image, but it looks gray
	to the user).   
	b. Draw color text onto the image.*/
	/************************************************************************/
    //a
	Mat tmp;
    cvtColor(src,tmp,COLOR_BGR2GRAY);
	cvtColor(tmp,src,COLOR_GRAY2BGR);
	//b
	putText(src,"puttext",Point(50,30),CV_FONT_HERSHEY_DUPLEX,1.0f,Scalar(0,255,0));
	/************************************************************************/
	/*5.5. Use cv::LineIterator to count pixels on different line segments in, say, a 300 × 300 image.
	a. At what angles do you get the same number of pixels for 4-connected and
	8-connected lines?
	b. For line segment angles other than the above, which counts more pixels:
	4-connected or 8-connected lines?
	c. For a given line segment, explain the difference in the length of the line compared 
	to the number of pixels you count iterating along the line for
	both 4-connected and 8-connected? Which connectedness is closer to the true
	line length?
	/************************************************************************/
	//a、
	LineIterator it_4_x(src, Point(0,0), Point(0,100), 4);
	LineIterator it_8_x(src, Point(0,0), Point(0,100), 4);
	LineIterator it_4_y(src, Point(0,0), Point(100,0), 4);
	LineIterator it_8_y(src, Point(0,0), Point(100,0), 4);
	cout << "it_4_x " <<it_4_x.count<<" it_8_x "<<it_8_x.count<<endl;
	cout << "it_4_y " <<it_4_y.count<<" it_8_y "<<it_8_y.count<<endl;
	//b the answer is: 4-connected counts more pixels than 8-connected counts
	LineIterator it_4(src, Point(0,0), Point(100,100), 4);
	LineIterator it_8(src, Point(0,0), Point(100,100), 8);
	cout << "it_4 " <<it_4.count<<" large than it_8 "<<it_8.count<<endl;
	//c 
	// the difference is the same as the difference between 4-connected and 8-connected
	// I veleve the 8-connected is closer to the true line length. 
	waitKey();
	return 0;

}
