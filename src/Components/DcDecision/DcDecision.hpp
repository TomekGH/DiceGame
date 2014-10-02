/*!
 * \file
 * \brief 
 * \author Tomek
 */

#ifndef DCDECISION_HPP_
#define DCDECISION_HPP_

#include "Types/HomogMatrix.hpp"
#include "Types/Dices.hpp"
#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "Property.hpp"
#include "EventHandler2.hpp"

#include <opencv2/opencv.hpp>


namespace Processors {
namespace DcDecision {

using namespace cv;

/*!
 * \class DcDecision
 * \brief DcDecision processor class.
 *
 * 
 */
class DcDecision: public Base::Component {
public:
	/*!
	 * Constructor.
	 */
	DcDecision(const std::string & name = "DcDecision");

	/*!
	 * Destructor
	 */
	virtual ~DcDecision();

	/*!
	 * Prepare components interface (register streams and handlers).
	 * At this point, all properties are already initialized and loaded to 
	 * values set in config file.
	 */
	void prepareInterface();

protected:

	/*!
	 * Connects source to given device.
	 */
	bool onInit();

	/*!
	 * Disconnect source from device, closes streams, etc.
	 */
	bool onFinish();

	/*!
	 * Start component
	 */
	bool onStart();

	/*!
	 * Stop component
	 */
	bool onStop();


	// Input data streams
	Base::DataStreamIn<cv::Mat> in_img;
	Base::DataStreamIn<vector<vector<Point> > > in_contours;

	// Output data streams
	Base::DataStreamOut<cv::Mat> out_img;
	//Base::DataStreamOut<Types::HomogMatrix> out_homogMatrix;
	Base::DataStreamOut<float> out_pos_x;
	Base::DataStreamOut<float> out_pos_y;
	Base::DataStreamOut<float> out_angle;

	// Handlers
	Base::EventHandler2 h_ProcessingImage;

	// Properties
	Base::Property<double> dilation_size;
	
	// Handlers
	void ProcessingImage();

};

} //: namespace DcDecision
} //: namespace Processors

/*
 * Register processor component.
 */
REGISTER_COMPONENT("DcDecision", Processors::DcDecision::DcDecision)

#endif /* DCDECISION_HPP_ */
