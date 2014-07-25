/*!
 * \file
 * \brief
 * \author Tomek
 */

#include <memory>
#include <string>

#include "DcDiceReading.hpp"
#include "Common/Logger.hpp"

#include <boost/bind.hpp>

namespace Processors {
namespace DcDiceReading {

DcDiceReading::DcDiceReading(const std::string & name) :
		Base::Component(name)  {

}

DcDiceReading::~DcDiceReading() {
}

void DcDiceReading::prepareInterface() {
	// Register data streams, events and event handlers HERE!
	registerStream("in_angle", &in_angle);
	registerStream("in_dots", &in_dots);
	// Register handlers
	h_NewAngle.setup(boost::bind(&DcDiceReading::NewAngle, this));
	registerHandler("NewAngle", &h_NewAngle);
	addDependency("NewAngle", &in_angle);

}

bool DcDiceReading::onInit() {

	return true;
}

bool DcDiceReading::onFinish() {
	return true;
}

bool DcDiceReading::onStop() {
	return true;
}

bool DcDiceReading::onStart() {
	return true;
}

void DcDiceReading::NewAngle() {

	try {	
		double angle = in_angle.read();
		int dots = in_dots.read();

		LOG(LWARNING) << "ANGLE:" << angle << endl;
		LOG(LWARNING) << "DOTS:" << dots << endl;

	} catch (exception& ex) {
		 LOG(LERROR) << "DcDiceReading::NewAngle \n" << ex.what() << endl;
    	}
}



} //: namespace DcDiceReading
} //: namespace Processors
