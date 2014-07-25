/*!
 * \file
 * \brief 
 * \author Tomek
 */

#ifndef DCFINDSQUARES_HPP_
#define DCFINDSQUARES_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "Property.hpp"
#include "EventHandler2.hpp"

#include <opencv2/opencv.hpp>


namespace Processors {
namespace DcFindSquares {

using namespace cv;

/*!
 * \class DcFindSquares
 * \brief DcFindSquares processor class.
 *
 * 
 */
class DcFindSquares: public Base::Component {
public:
	/*!
	 * Constructor.
	 */
	DcFindSquares(const std::string & name = "DcFindSquares");

	/*!
	 * Destructor
	 */
	virtual ~DcFindSquares();

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
	Base::DataStreamOut<vector<vector<Point> > > out_contours;

	// Handlers
	Base::EventHandler2 h_ProcessImage;

	// Properties
	Base::Property<double> p_min;
	Base::Property<double> p_max;

	
	// Handlers
	void ProcessImage();

};

} //: namespace DcFindSquares
} //: namespace Processors

/*
 * Register processor component.
 */
REGISTER_COMPONENT("DcFindSquares", Processors::DcFindSquares::DcFindSquares)

#endif /* DCFINDSQUARES_HPP_ */
