/*!
 * \file
 * \brief
 * \author Tomek
 */

#include <memory>
#include <string>

#include "DcFindSquares.hpp"
#include "Common/Logger.hpp"

#include <boost/bind.hpp>

namespace Processors {
namespace DcFindSquares {

DcFindSquares::DcFindSquares(const std::string & name) :
		Base::Component(name) , 
		p_min("p_min", 55), 
		p_max("p_max", 1400) {
	registerProperty(p_min);
	registerProperty(p_max);

}

DcFindSquares::~DcFindSquares() {
}

void DcFindSquares::prepareInterface() {
	// Register data streams, events and event handlers HERE!
	registerStream("in_img", &in_img);
	registerStream("out_img", &out_img);
	registerStream("out_contours", &out_contours);
	// Register handlers
	h_ProcessImage.setup(boost::bind(&DcFindSquares::ProcessImage, this));
	registerHandler("ProcessImage", &h_ProcessImage);
	addDependency("ProcessImage", &in_img);

}

bool DcFindSquares::onInit() {

	return true;
}

bool DcFindSquares::onFinish() {
	return true;
}

bool DcFindSquares::onStop() {
	return true;
}

bool DcFindSquares::onStart() {
	return true;
}

void DcFindSquares::ProcessImage() {

    LOG(LTRACE) << "DcFindSquare::onNewImage\n";
	
	int err = 0;    
	try {
        	

	// Read image from input data stream.
        Mat img = in_img.read();
	Mat cpy = img.clone();
	Mat drawing = Mat::zeros(img.size(), CV_8UC3);

	err++;

	// ContoursDetection {
	vector<vector<Point> > contours;
	vector<vector<Point> > out;
	vector<Vec4i> hierarchy;
	vector<Point> approx;
	vector<Point> square;
	err++;

	// Find Contours
	cv::findContours(cpy, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
	err++;
	
	// Draw square
	
	for(int i=0; i<=50; i++)
	{	
		square.push_back(Point(0,i));
	}
	for(int i=1; i<=50; i++)
	{	
		square.push_back(Point(i,50));
	}
	for(int i=49; i>=0; i--)
	{	
		square.push_back(Point(50,i));
	}
	for(int i=49; i>=1; i--)
	{	
		square.push_back(Point(i,0));
	}	
		
	
	double match;

	// Select contours
  	for(int i = 0; i< contours.size(); i++)
     	{
		approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.08, true);
		match = matchShapes(Mat(approx), Mat(square), CV_CONTOURS_MATCH_I1, 0);
 		if (fabs(contourArea(Mat(approx))) > p_min && fabs(contourArea(Mat(approx))) < p_max && match<0.05)
            	{
			drawContours(drawing, contours, i, cv::Scalar(255.0,0.0,0.0), 0, 8, hierarchy, 0, Point());			
			out.push_back(contours[i]);
		}
		else 
		{
			drawContours(drawing, contours, i, cv::Scalar(128.0,128.0,128.0), 0, 8, hierarchy, 0, Point());			
		}
	}
	err++;
	
		

        // Write image to output data stream.
        out_contours.write(out);
	out_img.write(drawing);       
	err++;

	// Raise event.
        //newContours->raise();
	//newImage->raise();
	err++;

    } catch (...) {
        LOG(LERROR) << "DcFindSquare::onNewImage failed \n" << endl << err << endl;
    }

}



} //: namespace DcFindSquares
} //: namespace Processors
