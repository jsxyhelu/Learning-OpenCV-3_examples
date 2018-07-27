//Exercises 11 at end of Chapter 14
/************************************************************************/
	/*11. Modify the shape context example or shape_example.cpp from OpenCV 3 to use
	Hausdorff distance instead of a shape context.                                   */
	/************************************************************************/
	
	/*
	very simple,just replace shape context with Hausdorff

	the result of the program is 

	name: ../data/shape_sample/2.png
	distance between ../data/shape_sample/1.png and ../data/shape_sample/2.png is: 25.0599
	name: ../data/shape_sample/3.png
	distance between ../data/shape_sample/1.png and ../data/shape_sample/3.png is: 37.5899
	name: ../data/shape_sample/4.png
	distance between ../data/shape_sample/1.png and ../data/shape_sample/4.png is: 543.774
	name: ../data/shape_sample/5.png
	distance between ../data/shape_sample/1.png and ../data/shape_sample/5.png is: 49.93
	name: ../data/shape_sample/6.png
	distance between ../data/shape_sample/1.png and ../data/shape_sample/6.png is: 75.5844
	name: ../data/shape_sample/7.png
	distance between ../data/shape_sample/1.png and ../data/shape_sample/7.png is: 115.521
	name: ../data/shape_sample/8.png
	distance between ../data/shape_sample/1.png and ../data/shape_sample/8.png is: 30.1496
	name: ../data/shape_sample/9.png
	distance between ../data/shape_sample/1.png and ../data/shape_sample/9.png is: 59.9083
	name: ../data/shape_sample/10.png
	distance between ../data/shape_sample/1.png and ../data/shape_sample/10.png is: 22.1359
	name: ../data/shape_sample/11.png
	distance between ../data/shape_sample/1.png and ../data/shape_sample/11.png is: 1.41421
	name: ../data/shape_sample/12.png
	distance between ../data/shape_sample/1.png and ../data/shape_sample/12.png is: 88.8876
	name: ../data/shape_sample/13.png
	distance between ../data/shape_sample/1.png and ../data/shape_sample/13.png is: 287.48
	name: ../data/shape_sample/14.png
	distance between ../data/shape_sample/1.png and ../data/shape_sample/14.png is: 265.017
	name: ../data/shape_sample/15.png
	distance between ../data/shape_sample/1.png and ../data/shape_sample/15.png is: 74.1687
	name: ../data/shape_sample/16.png
	distance between ../data/shape_sample/1.png and ../data/shape_sample/16.png is: 35.609
	name: ../data/shape_sample/17.png
	distance between ../data/shape_sample/1.png and ../data/shape_sample/17.png is: 115.317
	name: ../data/shape_sample/18.png
	distance between ../data/shape_sample/1.png and ../data/shape_sample/18.png is: 230.078
	name: ../data/shape_sample/19.png
	distance between ../data/shape_sample/1.png and ../data/shape_sample/19.png is: 14.2127
	name: ../data/shape_sample/20.png
	distance between ../data/shape_sample/1.png and ../data/shape_sample/20.png is: 210.95
	*/

#include "stdafx.h"
#include "opencv2/shape.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/core/utility.hpp>
#include <iostream>
#include <string>
using namespace std;
using namespace cv;
static void help()
{
	printf("\n"
		"This program demonstrates a method for shape comparisson based on Shape Context\n"
		"You should run the program providing a number between 1 and 20 for selecting an image in the folder ../data/shape_sample.\n"
		"Call\n"
		"./shape_example [number between 1 and 20, 1 default]\n\n");
}
static vector<Point> simpleContour( const Mat& currentQuery, int n=300 )
{
	vector<vector<Point> > _contoursQuery;
	vector <Point> contoursQuery;
	findContours(currentQuery, _contoursQuery, RETR_LIST, CHAIN_APPROX_NONE);
	for (size_t border=0; border<_contoursQuery.size(); border++)
	{
		for (size_t p=0; p<_contoursQuery[border].size(); p++)
		{
			contoursQuery.push_back( _contoursQuery[border][p] );
		}
	}
	// In case actual number of points is less than n
	int dummy=0;
	for (int add=(int)contoursQuery.size()-1; add<n; add++)
	{
		contoursQuery.push_back(contoursQuery[dummy++]); //adding dummy values
	}
	// Uniformly sampling
	random_shuffle(contoursQuery.begin(), contoursQuery.end());
	vector<Point> cont;
	for (int i=0; i<n; i++)
	{
		cont.push_back(contoursQuery[i]);
	}
	return cont;
}
int main(int argc, char** argv)
{
	string path = "../data/shape_sample/";
	cv::CommandLineParser parser(argc, argv, "{help h||}{@input|1|}");
	if (parser.has("help"))
	{
		help();
		return 0;
	}
	int indexQuery = parser.get<int>("@input");
	if (!parser.check())
	{
		parser.printErrors();
		help();
		return 1;
	}
	if (indexQuery < 1 || indexQuery > 20)
	{
		help();
		return 1;
	}
	//cv::Ptr <cv::ShapeContextDistanceExtractor> mysc = cv::createShapeContextDistanceExtractor();
	cv::Ptr <cv::HausdorffDistanceExtractor> hausdorff_ptr = cv::createHausdorffDistanceExtractor();
	Size sz2Sh(300,300);
	stringstream queryName;
	queryName<<path<<indexQuery<<".png";
	Mat query=imread(queryName.str(), IMREAD_GRAYSCALE);
	Mat queryToShow;
	resize(query, queryToShow, sz2Sh);
	imshow("QUERY", queryToShow);
	moveWindow("TEST", 0,0);
	vector<Point> contQuery = simpleContour(query);
	int bestMatch = 0;
	float bestDis=FLT_MAX;
	for ( int ii=1; ii<=20; ii++ )
	{
		if (ii==indexQuery) continue;
		waitKey(30);
		stringstream iiname;
		iiname<<path<<ii<<".png";
		cout<<"name: "<<iiname.str()<<endl;
		Mat iiIm=imread(iiname.str(), 0);
		Mat iiToShow;
		resize(iiIm, iiToShow, sz2Sh);
		imshow("TEST", iiToShow);
		moveWindow("TEST", sz2Sh.width+50,0);
		vector<Point> contii = simpleContour(iiIm);
		float dis = hausdorff_ptr->computeDistance(contQuery, contii );
		// float dis = mysc->computeDistance( contQuery, contii );
		if ( dis<bestDis )
		{
			bestMatch = ii;
			bestDis = dis;
		}
		std::cout<<" distance between "<<queryName.str()<<" and "<<iiname.str()<<" is: "<<dis<<std::endl;
	}
	destroyWindow("TEST");
	stringstream bestname;
	bestname<<path<<bestMatch<<".png";
	Mat iiIm=imread(bestname.str(), 0);
	Mat bestToShow;
	resize(iiIm, bestToShow, sz2Sh);
	imshow("BEST MATCH", bestToShow);
	moveWindow("BEST MATCH", sz2Sh.width+50,0);
	return 0;
}
