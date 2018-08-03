//Exercises at end of Chapter 4,《learning OpenCV3》
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void help(const char **argv) {
	cout << "\n\n"
		<< "This program solves the Exercises at the end of Chapter 4 \n"
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
	/*4.1. Find and open  .../opencv/cxcore/include/cxtypes.h. Read through and find the
	many conversion helper functions.
	a. Choose a negative floating-point number.
	b. Take its absolute value, round it, and then take its ceiling and floor.
	c. Generate some random numbers.
	d. Create a floating-point cv::Point2f and convert it to an integer cv::Point.
	Convert a cv::Point to a cv::Point2f.                              */
	/************************************************************************/
	// cxtypes.h is no longer used in opencv3
	// have reported this to gray

    /************************************************************************/
	/*4.2. Compact matrix and vector types:
	a. Using the  cv::Matx33f and  cv::Vec3f objects (respectively), create a 3 × 3
	matrix and 3-row vector.
	b. Can you multiply them together directly? If not, why not?                       */
	/************************************************************************/
	//a.just create
	cv::Matx33f M(1, 2, 3,
		          4, 5, 6,
		          7, 8, 9); 

	cv::Vec3f V (1,2,3);
	//b.we can just multiply them by type-casting Mat33f and vector to Mat
	Mat A = Mat(M);
	Mat B = Mat(V);
	Mat AB1 = A*B;      //vector multiplication
	Mat AB2 = A.mul(B); //multiplication

	 /************************************************************************/
	/*4.3. Compact matrix and vector template types:
	a. Using the cv::Mat<> and cv::Vec<> templates (respectively), create a 3 × 3
	matrix and 3-row vector.
	b. Can you multiply them together directly? If not, why not?
	c. Try type-casting the vector object to a 3 × 1 matrix, using the cv::Mat<> tem‐
	plate. What happens now?                      */
	/************************************************************************/
	//a.just create
	cv::Mat_<float> M2(3,3);
	//init M2
	M2.at<float>(0,0)=1;  
	M2.at<float>(0,1)=2;  
	M2.at<float>(0,2)=3;  
	M2.at<float>(1,0)=4;  
	M2.at<float>(1,1)=5;  
	M2.at<float>(1,2)=6;  
	M2.at<float>(1,0)=4;  
	M2.at<float>(1,1)=5;  
	M2.at<float>(1,2)=6;
	cv::Vec<float,3> V2(1,2,3);
    //b.we can not,becase M2 and V2 are not in the same type
	//c.we can  multiply them by type-casting the vector object to a 3 × 1 matrix(becasue Mat_ is just a type of Mat)
	B = Mat(V2);
	Mat AB3 = M2*B;      //vector multiplication
	Mat AB4 = M2.mul(B); //multiplication
	waitKey();
	return 0;
}
