//Exercises at end of Chapter 14

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void help(const char **argv) {
	cout << "\n\n"
		<< "This program solves the Exercises at the end of Chapter 14 \n"
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
	/* 1. We can find the extremal points (i.e., the two points that are farthest apart) in a
	closed contour of N points by comparing the distance of each point to every
	other point.
	a. What is the complexity of such an algorithm?
	b. Explain how you can do this faster.                                      */
	/************************************************************************/
	
	//a、O(N*N)
    //b、Finding the convex hull of  the contour,and then do the algorithm above at the convex hull .  
	/************************************************************************/
	/*2. What is the maximal closed contour length that could fit into a 4 × 4 image?
	What is its contour area?                                     */
	/************************************************************************/
	
	//the maximal closed contour length  is 12
	//the contour area is  16
	/************************************************************************/
	/* 3. Describe an algorithm for determining whether a closed contour is convex—
	without using cv::isContourConvex().                               */
	/************************************************************************/
	
	//connect each point with every other point,we can get a bunch of lines
    //Check each line  whether through the closed contour itself
	//if none line through the closed contour,it is convex.
	
	/************************************************************************/
	/* 4. Describe algorithms:
	a. for determining whether a point is above a line.
	b. for determining whether a point is inside a triangle.
	c. for determining whether a point is inside a polygon—without using
	cv::pointPolygonTest().                               */
	/************************************************************************/
	
	//a、in opencv,we often use two points(eg pa,pb)to describe a line.
    //   SO, when we have a point:" p"
	//   if   ( (p.y - pa.y)/(p.x - pa.x)  == (pb.y-p.y)/(pb.x - p.x))
	//   the point is above the line

    //b. at lease 3 points describe a triangle (eg pa,pb,pc)
	//     and the target point is "p"
	//     we will build a function GetArea(p1,p2,p3) which will return the area of triangle(p1,p2,p3)
	//     if ( GetArea(pa,pb,c) == GetArea(pa,pb,p) + GetArea(pa,pc,p) + GetArea(pb,pc,p))
	//	   the point is in he triangle(pa,pb,pc);

	//c. very like solution b
	//	to a polygon(p1,p2,...,pn)
	//	if( contourArea（polygon) ==  GetArea(p1,p2,p) + GetArea(p2,p3,p) +……+ GetArea(pn-1,pn,p)+ GetArea(pn,p1,p))
	//		the point is in he polygon(p1,p2,...,pn)

	/************************************************************************/
	/* 5. Using PowerPoint or a similar program, draw a white circle of radius  20 on a black background (the circle’s circumference will thus be 2 π 20 ≈ 125.7. Save
	your drawing as an image.
	a. Read the image in, turn it into grayscale, threshold, and find the contour. What is the contour length? Is it the same (within rounding) or different from the calculated length?
	b. Using 125.7 as a base length of the contour, run cv::approxPolyDP() using as parameters the following fractions of the base length: 90%, 66%, 33%, 10%.
	Find the contour length and draw the results.
	/************************************************************************/
	
	//a. result is contours 132.57.
	//   the result is large than the calculated length
   
	//read image,make gray,make bin
	Mat src = imread("20circle.png",0);
	Mat gray;
	Mat bin;
	cvtColor(src,gray,COLOR_BGR2GRAY);
	threshold(src, bin, 0, 255, CV_THRESH_BINARY);
	//find contours
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(bin, contours, hierarchy, CV_RETR_TREE, CHAIN_APPROX_NONE, Point(0,0));
	//get the arc of the circle 
	float arc  =(float)arcLength(contours[0],true);
	printf("contours %.2f\n",arc);


	//b dont kown "using as parameters the following fractions of the base length: 90%, 66%, 33%, 10%"
	//  just use approxPolyDP to get the contours_poly
    vector<vector<Point>> contours_poly(contours.size());
	Mat draw = src.clone();
	for (int i = 0; i<contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), contours_poly[i], 15, true);
		drawContours(draw, contours_poly, i, Scalar(0, 0, 255), 2, 8);  //绘制
		arc  =(float)arcLength(contours_poly[0],true);
		printf("contours %.2f\n",arc);
	}
	imshow("result", draw);
	waitKey();
	return 0;

}
