//Exercises at end of Chapter 10,《learning OpenCV3》
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

void help(const char **argv) {
	cout << "\n\n"
		<< "This program solves the Exercises at the end of Chapter 10 \n"
		<< "Call:\n"
		<< argv[0] << " <path/image_name>\n\n"
		<< "For example: " << argv[0] << " / test.jpg\n"
		<< endl;
}

//p.s to all questions below
//the smoothing functions are now:
//cv::blur
//cv::GaussianBlur
//cv::medianBlur
//cv::bilateralFilter

int main( int argc, const char** argv )
{
	help(argv);
	if(argc < 2) {
		cout << "\nERROR: You had too few parameters.\n" << endl;
		return -1;
	}
	/************************************************************************/
	/*1. Load an image with interesting textures. Smooth the image in several ways using
	cv::smooth() with smoothtype=cv::GAUSSIAN.
	a. Use a symmetric 3 × 3, 5 × 5, 9 × 9, and 11 × 11 smoothing window size and display the results.
	b. Are the output results nearly the same by smoothing the image twice with a
	5 × 5 Gaussian filter as when you smooth once with two 11 × 11 filters? Why or why not?     */
	/************************************************************************/

	Mat src = imread("e:/sandbox/texture.jpg",0);
	Mat tmp;
	//a
	GaussianBlur(src,tmp,Size(3,3),0);
	imshow("question 1 :3 * 3",tmp);
	GaussianBlur(src,tmp,Size(5,5),0);
	imshow("question 1 :5 * 5",tmp);
	GaussianBlur(src,tmp,Size(9,9),0);
	imshow("question 1 :9 * 9",tmp);
	GaussianBlur(src,tmp,Size(11,11),0);
	imshow("question 1 :11 * 11",tmp);
	//b
	//the answer is :no ,they are not the same.I believe the reseaon is they have difference kernel.
	GaussianBlur(src,tmp,Size(5,5),0);
	GaussianBlur(tmp,tmp,Size(5,5),0);
	imshow("5 * 5 twice",tmp);

	/************************************************************************/
	/*2. Create a 100 × 100 single-channel image. Set all pixels to 0. Finally, set the center pixel equal to 255.
	a. Smooth this image with a 5 × 5 Gaussian filter and display the results. What did you find?
	b. Do this again but with a 9 × 9 Gaussian filter.
	c. What does it look like if you start over and smooth the image twice with the 5 × 5 filter? Compare this with the 9 × 9 results. 
	Are they nearly the same? Why or why not?  */
	/************************************************************************/
	Mat src2(Size(100,100),CV_8UC1,Scalar::all(0));
	src2.at<char>(50,50) = 255;
	//a
	GaussianBlur(src2,tmp,Size(5,5),0);
	imshow("question 2 : 5 * 5",tmp);
	//b
	GaussianBlur(src2,tmp,Size(9,9),0);
	imshow("question 2 : 9 * 9",tmp);
	//c
	Mat tmp2;
	GaussianBlur(src2,tmp2,Size(5,5),0);
	GaussianBlur(tmp2,tmp2,Size(5,5),0);
	imshow("question 2 : 5 * 5 twice",tmp2);
	//it is hard to figure out whether the result of b and c is different or not,some code will help
	tmp2 = tmp - tmp2;
	//minmaxit
	double minc[1], maxc[1];
	Mat mask = tmp2>0;
	minMaxLoc(tmp2, minc, maxc,NULL,NULL,mask);
	//the result of c is:the difference between  result of b and c is like a circle ,which all made by 1
	//so ,they are nearyl the same;

	/************************************************************************/
	/*3. Load an interesting image, and then blur it with cv::smooth() using a Gaussian filter.
	a. Set param1=param2=9. Try several settings of param3 (e.g., 1, 4, and 6). Display the results.
	b. Set param1=param2=0 before setting param3 to 1, 4, and 6. Display the results.
	Are they different? Why?
	c. Use  param1=param2=0 again, but this time set  param3=1 and  param4=9.
	Smooth the picture and display the results.
	d. Repeat Exercise 3c but with param3=9 and param4=1. Display the results.
	e. Now smooth the image once with the settings of Exercise 3c and once with
	the settings of Exercise 3d. Display the results.
	f. Compare the results in Exercise 3e with smoothings that use
	param3=param4=9 and param3=param4=0 (i.e., a 9 × 9 filter). Are the results the same? Why or why not?
	/************************************************************************/
    //we dont have function cv::smooth() and it's param1,param2,param3 any more
	//so i pass question 3

	/************************************************************************/
	/*4. Use a camera to take two pictures of the same scene while moving the camera as
	little as possible. Load these images into the computer as src1 and src1.
	a. Take the absolute value of  src1 minus  src1 (subtract the images); call it
	diff12 and display. If this were done perfectly, diff12 would be black. Why isn’t it?
	b. Create cleandiff by using cv::erode() and then cv::dilate() on diff12.
	Display the results.
	c. Create  dirtydiff by using  cv::dilate() and then  cv::erode() on  diff12
	and then display.
	d. Explain the difference between cleandiff and dirtydiff.
	/************************************************************************/
	Mat src_4_1 = imread("e:/sandbox/OpticalFlow0.jpg");
	Mat src_4_2 = imread("e:/sandbox/OpticalFlow1.jpg");
	//a 
	Mat diff12;
	absdiff(src_4_1,src_4_2,diff12);
	imshow("diff12",diff12);
	// I use OpticalFlow.jpg as my src1,the result is pretty cool:the background of this image is black,we can get hands clearly;
	// I believe the reseaon is "two pictures of the same scene" is very similarity.
	//b. 
	Mat cleandiff;
	erode(diff12,cleandiff,Mat());
	dilate(cleandiff,cleandiff,Mat());
	imshow("cleandiff",cleandiff);
	//c
	Mat dirtydiff;
	dilate(diff12,dirtydiff,Mat());
	erode(dirtydiff,dirtydiff,Mat());
	imshow("dirtydiff",dirtydiff);
	//the difference between b and c is the difference of "open" and "close"
    //Open:  erode  - > dilate ,smooth the outline of the object, break the narrower area, remove the fine protrusion.
    //Close: dilate - > erode, bridging narrow gaps to fill slender gullies;
	/************************************************************************/

	/*5. Create an outline of an object. Take a picture of a scene. Then, without moving
	the camera, put a coffee cup in the scene and take a second picture. Load these
	images and convert both to 8-bit grayscale images.
	a. Take the absolute value of their difference. Display the result, which should
	look like a noisy mask of a coffee mug.
	b. Do a binary threshold of the resulting image using a level that preserves most
	of the coffee mug but removes some of the noise. Display the result. The “on”
	values should be set to 255.
	c. Do a cv::MOP_OPEN on the image to further clean up noise.
	/************************************************************************/
	//read scene with and without coffe cup ,gray it
	Mat mug = imread("e:/template/mug.jpg",0);
	Mat noMug=imread("e:/template/nomug.jpg",0);
	//a
	absdiff(mug,noMug,mug);
	imshow("absdiff",mug);
	//b ,50 looks nice
	threshold(mug,mug,50,255,THRESH_BINARY);
	//c the result is really better
	Mat element = getStructuringElement(MORPH_RECT,Size(13,13));
	morphologyEx(mug,mug,CV_MOP_OPEN,element);

	/*6. High dynamic range: go into a room with strong overhead lighting and tables
	that shade the light. Take a picture. With most cameras, either the lighted parts
	of the scene are well exposed and the parts in shadow are too dark, or the lighted
	parts are overexposed and the shadowed parts are OK. Create an adaptive filter
	to help balance out such an image; that is, in regions that are dark on average,
	boost the pixels up some, and in regions that are very light on average, decrease
	the pixels somewhat.
	/************************************************************************/
	//a  Laplace kernel will work
	Mat image = imread("e:/sandbox/nogood.jpg", 1);
	imshow("original image", image);
	Mat imageEnhance;
	Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, 0, 5, 0, 0, -1, 0);
	filter2D(image, imageEnhance, CV_8UC3, kernel);
	imshow("Laplace enhance", imageEnhance);

	/*7. Sky filter: create an adaptive “sky” filter that smooths only bluish regions of a
	scene so that only the sky or lake regions of a scene are smoothed, not ground regions.
	/************************************************************************/
	//don't know how to make it
	//Actually,I can segment "sky or lake" from the back scence,but don't know how to smooth it with a filter
	
	/*8. Create a clean mask from noise. After completing Exercise 5, continue by keep‐
	ing only the largest remaining shape in the image. Set a pointer to the upper left
	of the image and then traverse the image. When you find a pixel of value  255
	(“on”), store the location and then flood-fill it using a value of 100. Read the con‐
	nected component returned from flood fill and record the area of filled region. If
	there is another larger region in the image, then flood-fill the smaller region
	using a value of 0 and delete its recorded area. If the new region is larger than the
	previous region, then flood-fill the previous region using the value 0 and delete
	its location. Finally, fill the remaining largest region with 255. Display the results.
	We now have a single, solid mask for the coffee mug.
	/************************************************************************/
	//the point is "keep only the largest remaining shape in the image"
	//by floodfill and connect component 
	//Actually,a better way to "find the biggest region" should be using contours,I don't tink "floodfill" is good enough.

	/*9. Use the mask created in Exercise 8 or create another mask of your own (perhaps
	by drawing a digital picture, or simply use a square). Load an outdoor scene.
	Now use this mask with copyTo() to copy an image of a mug into the scene.
	/************************************************************************/
	//the point of this quesiton is copyto() with "mask"
	//pay attention at this :if the backImage and the scenceImage are not the same size,you should use ROI
	Mat backImage = imread("e:/template/lena.jpg", 1);
	pyrDown(image,image);
	pyrDown(image,image);
	Mat Copymask(image.size(),CV_8UC1,Scalar(0));
	Mat roi=backImage(Rect(0,0,image.cols,image.rows)); // pay attention at this
	//make a square,and copyto() will just copy these part where mask is white
	rectangle(Copymask,Rect(0,0,Copymask.cols/2,Copymask.rows/2),Scalar(255),-1);
	//Operation mask of the same size as *this. Its non-zero elements indicate 
	//which matrix elements need to be copied. The mask has to be of type CV_8U and can have 1 or multiple channels. 
	image.copyTo(roi,Copymask);

	/*10. Create a low-variance random image (use a random number call such that the
	numbers don’t differ by much more than three and most numbers are near zero).
	Load the image into a drawing program such as PowerPoint, and then draw a
	wheel of lines meeting at a single point. Use bilateral filtering on the resulting
	image and explain the results.
	/************************************************************************/
	//是用来说明双边滤波的，说实话我真不知道是为什么
	//它想体现的，应该是双边滤波的保边能力
	Mat n_mat(Size(100,100), CV_8UC1 ,Scalar(0));
	RNG rng;
	rng.fill( n_mat, cv::RNG::UNIFORM, 0,3);
	//draw a wheel of lines meeting at a single point
	line(n_mat,Point(50,50),Point(50,0),Scalar(255));
	line(n_mat,Point(50,50),Point(100,0),Scalar(255));
	line(n_mat,Point(50,50),Point(100,50),Scalar(255));
	line(n_mat,Point(50,50),Point(100,100),Scalar(255));
	line(n_mat,Point(50,50),Point(50,100),Scalar(255));
	line(n_mat,Point(50,50),Point(0,100),Scalar(255));
	line(n_mat,Point(50,50),Point(0,50),Scalar(255));
	line(n_mat,Point(50,50),Point(0,0),Scalar(255));
	//do bilateral,the result is all "noise" will disappear 
	Mat dst;
	bilateralFilter(n_mat,dst,5,10.0,2.0);

	/*11. Load an image of a scene and convert it to grayscale.
	a. Run the morphological Top Hat operation on your image and display the results.
	b. Convert the resulting image into an 8-bit mask.
	c. Copy a grayscale value into the original image where the Top Hat mask (from
	Part b of this exercise) is nonzero. Display the results.
	/************************************************************************/
	Mat scene = imread("e:/sandbox/scenetext01.jpg");
	Mat sceneGray;
	cvtColor(scene,sceneGray,COLOR_BGR2GRAY);
	//a
	element = getStructuringElement(MORPH_ELLIPSE,Size(5,5));
	morphologyEx(sceneGray,dst,CV_MOP_TOPHAT,element);
	imshow("CV_MOP_TOPHAT",dst);
	//b
	dst.convertTo(dst,CV_8UC1);//The mask has to be of type CV_8U and can have 1 or multiple channels. 
	//c
	cvtColor(sceneGray,sceneGray,COLOR_GRAY2BGR);
	sceneGray.copyTo(scene,dst);

	/*12. Load an image with many details.
	a. Use resize() to reduce the image by a factor of 2 in each dimension (hence
	the image will be reduced by a factor of 4). Do this three times and display the results.
	b. Now take the original image and use cv::pyrDown() to reduce it three times,
	and then display the results.
	c. How are the two results different? Why are the approaches different?
	/************************************************************************/
	src = imread("e:/template/lena.jpg");
	Mat matResize;
	Mat matPyrdown;
	//a resize
	resize(src,src,Size(),0.5,0.5);
	resize(src,src,Size(),0.5,0.5);
	resize(src,matResize,Size(),0.5,0.5);
	imshow("src resize ",matResize);
	//b pyrdown
	src = imread("e:/template/lena.jpg");
	pyrDown(src,src);
	pyrDown(src,src);
	pyrDown(src,matPyrdown);
	imshow("pyrdown",matPyrdown);
	//c ,we can find the differenct,by don't know Why are the approaches different……
	absdiff(matResize,matPyrdown,dst);
	imshow("q12 find the differenct",dst);
	//I dont know "Why are the approaches different"

	/*13. Load an image of an interesting or sufficiently “rich” scene. Using  cv::threshold(), 
	set the threshold to  128. Use each setting type in  Figure 10-4  on the
	image and display the results. You should familiarize yourself with thresholding
	functions because they will prove quite useful.
	a. Repeat the exercise but use cv::adaptiveThreshold() instead. Set param1=5.
	b. Repeat part a of this exercise using param1=0 and then param1=-5.
	/************************************************************************/
	src = imread("E:/template/lena.jpg",0);//we love lena
	threshold(src,dst,128,255,cv::THRESH_BINARY);
	threshold(src,dst,128,255,cv::THRESH_BINARY_INV );
	threshold(src,dst,128,255,cv::THRESH_TRUNC);
	threshold(src,dst,128,255,cv::THRESH_TOZERO);
	threshold(src,dst,128,255,cv::THRESH_TOZERO_INV);
	//a b as we don't kown which param of adaptiveThreshold is param1,I just adaptiveThreshold it.
	int maxVal = 255;
	int blockSize = 41;
	double C = 0;
	cv::adaptiveThreshold(src, dst, maxVal, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, blockSize, C);

	/*
	15. Use  cv::filter2D() to create a filter that detects only 60-degree lines in an
	image. Display the results on a sufficiently interesting image scene.*/
	//dont know how to create a 60-degree kenrel,ask at answer@opencv
	Mat srcLines(100,100,CV_8UC1,Scalar::all(0));//draw lines
	line(srcLines,Point(0,0),Point(100,100),Scalar(255),1);
	line(srcLines,Point(50,50),Point(100,0),Scalar(255),1);//45 - degree
	line(srcLines,Point(0,100),Point(50,0),Scalar(255),1);//60 - degree
	Mat srcH(3,3,CV_8UC1,Scalar::all(0));
	
	srcH.at<char>(0,0) = 255;
	srcH.at<char>(1,1) = 255;
	srcH.at<char>(2,2) = 255;
	
	filter2D(srcLines,dst,srcLines.depth(),srcH);
	/*
	16. Separable kernels: create a 3 × 3 Gaussian kernel using rows [(1/16, 2/16, 1/16),
	(2/16, 4/16, 2/16), (1/16, 2/16, 1/16)] and with anchor point in the middle.
	a. Run this kernel on an image and display the results.
	b. Now create two one-dimensional kernels with anchors in the center: one
	going “across” (1/4, 2/4, 1/4), and one going down (1/4, 2/4, 1/4). Load the
	same original image and use  cv::filter2D() to convolve the image twice,
	once with the first 1D kernel and once with the second 1D kernel. Describe
	the results.
	c. Describe the order of complexity (number of operations) for the kernel in
	part a and for the kernels in part b. The difference is the advantage of being
	able to use separable kernels and the entire Gaussian class of filters—or any
	linearly decomposable filter that is separable, since convolution is a linear
	operation.*/
	//the point of this question is sepFilter2D VS Filter2D
	src = imread("e:/template/lena.jpg",0);
	//a
	//build 3 × 3 Gaussian
	Mat Gaussian33(3,3,CV_32FC1,Scalar::all(0));
	Gaussian33.at<float>(0,0) = 1.0/16;
	Gaussian33.at<float>(0,1) = 2.0/16;
	Gaussian33.at<float>(0,2) = 1.0/16;
	Gaussian33.at<float>(1,0) =2.0/16;
	Gaussian33.at<float>(1,1) = 4.0/16;
	Gaussian33.at<float>(1,2) = 2.0/16;
	Gaussian33.at<float>(2,0) = 1.0/16;
	Gaussian33.at<float>(2,1) = 2.0/16;
	Gaussian33.at<float>(2,2) = 1.0/16;
	filter2D(src,dst,src.depth(),Gaussian33);
	imshow("Gaussian33 on lena",dst);
	//b
	Mat KernelDown(3,1,CV_32FC1,Scalar::all(0));
	Mat KernelAcross(1,3,CV_32FC1,Scalar::all(0));
	KernelDown.at<float>(0,0) = 1.0/4;
	KernelDown.at<float>(1,0) = 2.0/4;
	KernelDown.at<float>(2,0) = 1.0/4;
	KernelAcross.at<float>(0,0) = 1.0/4;
	KernelAcross.at<float>(0,1) = 2.0/4;
	KernelAcross.at<float>(0,2) = 1.0/4;
	filter2D(src,dst,src.depth(),KernelAcross);
	filter2D(dst,dst,dst.depth(),KernelDown);
	imshow("across and down on lena",dst);
	//p.s we can use sepfileter2d. 
	sepFilter2D(src,dst,src.depth(),KernelAcross,KernelDown);
	imshow("sepFilter2D on lena",dst);
	// all of the above three look simailary,actually
	//c
	// i believe gaussian is easy to understand than separable filter.
	/*
	17. Can you make a separable kernel from the Scharr filter shown in Figure 10-15? If
	so, show what it looks like.*/
	// the result is
	//   3
	//   10    and   -1 0 1
	//   3
	/*
	18. In a drawing program such as PowerPoint, draw a series of concentric circles
	forming a bull’s-eye.
	a. Make a series of lines going into the bull’s-eye. Save the image.
	b. Using a 3 × 3 aperture size, take and display the first-order x- and y-
	derivatives of your picture. Then increase the aperture size to 5 × 5, 9 × 9, and
	13 × 13. Describe the results.*/
	//a
	//we make a bull's eye using opencv itslef,white on black
	Mat bullEyes = Mat(Size(512,512),CV_8UC1,Scalar(0));
	circle(bullEyes,Point(150,250),100,Scalar(255),5);
	circle(bullEyes,Point(350,250),100,Scalar(255),5);
	line(bullEyes,Point(150,350),Point(250,250),Scalar(255),5);
	imshow("bullbullEyes",bullEyes);
	//b the point of this question is funciton "sobel"
	Sobel(bullEyes,dst,bullEyes.depth(),1,0,3);
	imshow("bullEyes-3-x_derivatives",dst);
	Sobel(bullEyes,dst,bullEyes.depth(),0,1,3);
	imshow("bullEyes-3-y_derivatives",dst);
	Sobel(bullEyes,dst,bullEyes.depth(),1,0,5);
	imshow("bullEyes-5-x_derivatives",dst);
	Sobel(bullEyes,dst,bullEyes.depth(),0,1,5);
	imshow("bullEyes-5-y_derivatives",dst);
	Sobel(bullEyes,dst,bullEyes.depth(),1,0,9);
	imshow("bullEyes-9-x_derivatives",dst);
	Sobel(bullEyes,dst,bullEyes.depth(),0,1,9);
	imshow("bullEyes-9-y_derivatives",dst);
	Sobel(bullEyes,dst,bullEyes.depth(),1,0,13);
	imshow("bullEyes-13-x_derivatives",dst);
	Sobel(bullEyes,dst,bullEyes.depth(),0,1,13);
	imshow("bullEyes-13-y_derivatives",dst);

	/*
	19. Create a new image that is just a 45-degree line, white on black. For a given series
	of aperture sizes, we will take the image’s first-order x-derivative (dx) and first-
	order y-derivative (dy). We will then take measurements of this line as follows.
	The (dx) and (dy) images constitute the gradient of the input image. The magni‐
	tude at location (i, j) is  mag(i, j) = d x 2
	(i, j) + d y 2
	(i, j) and the angle is
	Θ(i, j) = atan2(dy(i, j), dx(i, j)). Scan across the image and find places where
	the magnitude is at or near maximum. Record the angle at these places. Average
	the angles and report that as the measured line angle.
	a. Do this for a 3 × 3 aperture Sobel filter.
	b. Do this for a 5 × 5 filter.
	c. Do this for a 9 × 9 filter.
	d. Do the results change? If so, why?
	*/
	Mat _45_degreedline = Mat(Size(512,512),CV_8UC1,Scalar(0));
	line(_45_degreedline,Point(0,512),Point(512,0),Scalar(255),5);
	//a
	Sobel(_45_degreedline,dst	,_45_degreedline.depth(),1,0,3);
	//b
	Sobel(_45_degreedline,dst	,_45_degreedline.depth(),1,0,5);
	//c
	Sobel(_45_degreedline,dst	,_45_degreedline.depth(),1,0,9);
	// the result of sobel must be something with the gradient of the input image.

	//That is a kernel for a theoretic angle of 62.5 degree.

	//	cv::Mat1f k = (cv::Mat1f(9,9)<<
	//	0,0,0,0,0,0,1,0,0,
	//	0,0,0,0,0,0,0,0,0,
	//	0,0,0,0,0,1,0,0,0,
	//	0,0,0,0,0,0,0,0,0,
	//	0,0,0,0,1,0,0,0,0,
	//	0,0,0,0,0,0,0,0,0,
	//	0,0,0,1,0,0,0,0,0,
	//	0,0,0,0,0,0,0,0,0,
	//	0,0,1,0,0,0,0,0,0);




	return 0;
}
