/*!
 * \file
 * \brief
 * \author Tomek
 */

#include <memory>
#include <string>

#include "DcCountDots.hpp"
#include "Common/Logger.hpp"

#include <boost/bind.hpp>

namespace Processors {
namespace DcCountDots {

DcCountDots::DcCountDots(const std::string & name) :
		Base::Component(name) , 
		x_limit("x_limit", 280), 
		y_limit("y_limit", 200), 
		mask_size("mask_size", 80) {
	registerProperty(x_limit);
	registerProperty(y_limit);
	registerProperty(mask_size);

}

DcCountDots::~DcCountDots() {
}

void DcCountDots::prepareInterface() {
	// Register data streams, events and event handlers HERE!
	registerStream("in_img", &in_img);
	registerStream("out_img", &out_img);
	registerStream("out_dots", &out_dots);
	// Register handlers
	h_ProcessImage.setup(boost::bind(&DcCountDots::ProcessImage, this));
	registerHandler("ProcessImage", &h_ProcessImage);
	addDependency("ProcessImage", &in_img);

}

bool DcCountDots::onInit() {

	return true;
}

bool DcCountDots::onFinish() {
	return true;
}

bool DcCountDots::onStop() {
	return true;
}

bool DcCountDots::onStart() {
	return true;
}

void DcCountDots::ProcessImage() {
	try {

	// Read image from input data stream.
        Mat img = in_img.read();
	Mat cpy = img.clone();
	Mat drawing = Mat::zeros(img.size(), CV_8UC3);

	vector<vector<Point> > contours;
	vector<vector<Point> > dots;
	vector<Vec4i> hierarchy;
	vector<Point> approx;
	Moments mm;

	/*int x_limit = 320-40; //465;
	int y_limit = 240-40; //255;
	int mask_size = 80; //85;*/


/*
	rectangle(cpy, cv::Point(0,0), cv::Point(x_limit,480), cv::Scalar(0.0,0.0,0.0), -1, 8, 0);
	rectangle(cpy, cv::Point(x_limit,0), cv::Point(x_limit+mask_size,y_limit), cv::Scalar(0.0,0.0,0.0), -1, 8, 0);
	rectangle(cpy, cv::Point(x_limit,y_limit+mask_size), cv::Point(x_limit+mask_size,480), cv::Scalar(0.0,0.0,0.0), -1, 8, 0);
	rectangle(cpy, cv::Point(x_limit+mask_size,0), cv::Point(640,480), cv::Scalar(0.0,0.0,0.0), -1, 8, 0);
*/

	cv::findContours(cpy, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
	
	// Select contours
  	for(int i = 0; i< contours.size(); i++)
     	{
		approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.08, true);
		mm = moments(Mat(approx), true);
 		if (fabs(contourArea(Mat(approx))) > 5 && fabs(contourArea(Mat(approx))) < 50 &&
			mm.m10/mm.m00 < x_limit+mask_size-20 && mm.m10/mm.m00 > x_limit+20 &&
			mm.m01/mm.m00 < y_limit+mask_size-20 && mm.m01/mm.m00 > y_limit+20)
            	{
			drawContours(drawing, contours, i, cv::Scalar(0.0,255.0,0.0), 0, 8, hierarchy, 0, Point());			
			dots.push_back(contours[i]);
		}
		else 
		{
			drawContours(drawing, contours, i, cv::Scalar(128.0,128.0,128.0), 0, 8, hierarchy, 0, Point());			
		}
	}
	        
	
	rectangle(drawing, cv::Point(x_limit,y_limit), cv::Point(x_limit+mask_size,y_limit+mask_size), cv::Scalar(255.,255.0,255.), 2, 8, 0);
	
	string str, tmp;

	sprintf((char*)tmp.c_str(), "%d", (dots.size()));
	str = tmp.c_str();

	putText(drawing, str, Point(100,100), FONT_HERSHEY_DUPLEX, 0.8, cv::Scalar(0,255,0));
	
	int send = dots.size();	

	//Write outputs
	out_img.write(drawing);       
	out_dots.write(send);

	// Raise event.
	//newImage->raise();
	//newDots->raise();



    } catch (exception& ex) {
        LOG(LERROR) << "DcDecision::onNewContours \n"  << ex.what() << endl;
    }
}



} //: namespace DcCountDots
} //: namespace Processors
