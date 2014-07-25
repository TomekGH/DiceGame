/*!
 * \file
 * \brief 
 * \author Tomek
 */

#ifndef DCDICEREADING_HPP_
#define DCDICEREADING_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "Property.hpp"
#include "EventHandler2.hpp"



namespace Processors {
namespace DcDiceReading {

/*!
 * \class DcDiceReading
 * \brief DcDiceReading processor class.
 *
 * 
 */
class DcDiceReading: public Base::Component {
public:
	/*!
	 * Constructor.
	 */
	DcDiceReading(const std::string & name = "DcDiceReading");

	/*!
	 * Destructor
	 */
	virtual ~DcDiceReading();

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
	Base::DataStreamIn<double> in_angle;
	Base::DataStreamIn<int> in_dots;

	// Output data streams

	// Handlers
	Base::EventHandler2 h_NewAngle;

	// Properties

	
	// Handlers
	void NewAngle();

};

} //: namespace DcDiceReading
} //: namespace Processors

/*
 * Register processor component.
 */
REGISTER_COMPONENT("DcDiceReading", Processors::DcDiceReading::DcDiceReading)

#endif /* DCDICEREADING_HPP_ */
