//Exercises 6-10 at end of Chapter 14
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
	/*6. Suppose we are building a bottle detector and wish to create a “bottle” feature.We have many images of 
	bottles that are easy to segment and find the contours of, but the bottles are rotated and come in various sizes. 
	We can draw the contours and then find the Hu moments to yield an invariant bottle-feature vector.
	So far, so good—but should we draw filled-in contours or just line contours?Explain your answer.                                     */
	/************************************************************************/
	
	//the answer : I think  line contours is enough。
  
	/************************************************************************/
	/*7. When using  cv::moments() to extract bottle contour moments in Exercise 6,how should we set isBinary? Explain your answer.
	binaryImage 	If it is true, all non-zero image pixels are treated as 1's. The parameter is used for images only.                                    */
	/************************************************************************/
	
	//the answer: i think we should keep binaryImage 	=false,and use threshthord to get the bin image.
	/************************************************************************/
	/* 8.Take the letter shapes used in the discussion of Hu moments. Produce variant images of the shapes by rotating to several 
	different angles, scaling larger and smaller, and combining these transformations. Describe which Hu features respond to rotation,
	which to scale, and which to both.                              */
	/************************************************************************/
	
	//the answer :none of  the 7 Hu features respond to rotateion,but all to scale.
	//read image,make gray,make bin
	Mat src = imread(argv[0]);
	Mat gray;
	Mat tmp;
	double hu[7]; 
	Moments mts;
	cvtColor(src,gray,COLOR_BGR2GRAY);

	//original image
	tmp = gray.clone();
	mts = moments(tmp); 
	HuMoments(mts, hu); 
	for (int i=0; i<7; i++) 
	{ 
		cout << log(abs(hu[i])) <<" "; 
	} 
	cout<<endl;
	imshow("original image",tmp);
	//90_CLOCKWISE
	rotate(gray,tmp,cv::ROTATE_90_CLOCKWISE);
	mts = moments(tmp); 
	HuMoments(mts, hu); 
	for (int i=0; i<7; i++) 
	{ 
		cout << log(abs(hu[i])) <<" "; 
	} 
	cout<<endl;
	imshow("90_CLOCKWISE",tmp);
	//ROTATE_180
	rotate(gray,tmp,cv::ROTATE_180);
	mts = moments(tmp); 
	HuMoments(mts, hu); 
	for (int i=0; i<7; i++) 
	{ 
		cout <<log(abs(hu[i])) <<" "; 
	} 
	cout<<endl;
	imshow("ROTATE_180",tmp);
	//pyramid up
	pyrUp(gray,tmp);
	mts = moments(tmp); 
	HuMoments(mts, hu); 
	for (int i=0; i<7; i++) 
	{ 
		cout <<log(abs(hu[i])) <<" "; 
	} 
	cout<<endl;
	imshow("pyrup",tmp);
	//pyramid up and rotate 180
	pyrUp(gray,tmp);
	rotate(tmp,tmp,cv::ROTATE_180);
	mts = moments(tmp); 
	HuMoments(mts, hu); 
	for (int i=0; i<7; i++) 
	{ 
		cout <<log(abs(hu[i])) <<" "; 
	} 
	cout<<endl;
	imshow("pyrup and ROTATE_180 ",tmp);
	waitKey();
	//                h1	   h2     h3        	h4      	h5	       h6	      h7
	//origion	-6.92707	-18.025	 -23.4196	-30.2727	-57.5474	-43.7345	-57.395
	//rotate 90	-6.92707	-18.025	 -23.4196	-30.2727	-57.5474	-43.7345	-57.395
	//rotate180	-6.92707	-18.025	 -23.4196	-30.2727	-57.5474	-43.7345	-57.395
	//pyrup 	-6.92683	-18.0452 -23.4221	-29.9383	-56.6541	-39.3623	-57.9569
	//180&pyrup	-6.92683	-18.0452 -23.4221	-29.9383	-56.6541	-39.3623	-57.9569
	
	/************************************************************************/
	/* 9.Go to Google images and search for “ArUco markers.” Choose some larger ones.
	a. Are moments good for finding ArUco images?
	b. Are moments or Hu features good for reading ArUco codes?
	c. Is cv::matchShapes() good for reading ArUco codes?                           */
	/************************************************************************/
	//the anwer :none of the answer is yes.we have special method to read ArUco markers right.
	
	/************************************************************************/
	/* 10、Make a shape in PowerPoint (or another drawing program) and save it as an image.
	Make a scaled, a rotated, and a rotated and scaled version of the object,
	and then store these as images. Compare them using cv::matchShapes().
	/************************************************************************/
	
	//very like execrise 8,but use another fucntion.
	//	the result is "there are very like"
	//	scaled vs rotated is 1.14219e-005
	//	scaled vs matScaledRotated is 0
	//	matScaledRotated vs rotated is 1.14219e-005

	Mat matScaled;
	pyrUp(gray,matScaled);
	// a rotated,
	Mat matRotated;
	rotate(gray,matRotated,cv::ROTATE_180);
	//a rotated and scaled
	Mat matScaledRotated;
	pyrUp(gray,matScaledRotated);
	rotate(matScaledRotated,matScaledRotated,cv::ROTATE_180);
	double comres= 0;
	comres = matchShapes(matScaled, matRotated,CV_CONTOURS_MATCH_I1, 0.0); 
	cout<< "scaled vs rotated is "<<comres<<endl;
	comres = matchShapes(matScaled, matScaledRotated,CV_CONTOURS_MATCH_I1, 0.0); 
	cout<< "scaled vs matScaledRotated is "<<comres<<endl;
	comres = matchShapes(matScaledRotated, matRotated,CV_CONTOURS_MATCH_I1, 0.0); 
	cout<< "matScaledRotated vs rotated is "<<comres<<endl;
	waitKey();
	return 0;

}
