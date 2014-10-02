/*!
 * \file
 * \brief 
 * \author Tomek
 */

#ifndef DCCOUNTDOTS_HPP_
#define DCCOUNTDOTS_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "Property.hpp"
#include "EventHandler2.hpp"

#include <opencv2/opencv.hpp>


namespace Processors {
namespace DcCountDots {

using namespace cv;

/*!
 * \class DcCountDots
 * \brief DcCountDots processor class.
 *
 * 
 */
class DcCountDots: public Base::Component {
public:
	/*!
	 * Constructor.
	 */
	DcCountDots(const std::string & name = "DcCountDots");

	/*!
	 * Destructor
	 */
	virtual ~DcCountDots();

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

	// Output data streams
	Base::DataStreamOut<cv::Mat> out_img;
	Base::DataStreamOut<int> out_dots;

	// Handlers
	Base::EventHandler2 h_ProcessImage;

	// Properties
	Base::Property<int> x_limit;
	Base::Property<int> y_limit;
	Base::Property<int> mask_size;
	Base::Property<int> min_size;
	Base::Property<int> max_size;

	
	// Handlers
	void ProcessImage();

};

} //: namespace DcCountDots
} //: namespace Processors

/*
 * Register processor component.
 */
REGISTER_COMPONENT("DcCountDots", Processors::DcCountDots::DcCountDots)

#endif /* DCCOUNTDOTS_HPP_ */
