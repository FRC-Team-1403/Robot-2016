/*
 * CougarCougarCANTalon.cpp
 *
 *	Created on: Feb 27, 2016
 *			Author: Thejas
 */

#include "CougarCANTalon.h"

/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2014-2016. All Rights Reserved.						  */
/* Open Source Software - may be modified and shared by FRC teams. The code	  */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.										   						  */
/*----------------------------------------------------------------------------*/


namespace cougar {

std::string CougarCANTalon::toString()  {
	std::string str = "CougarCANTalon " + this->name_ + "\n";
	str += "Sensor value: " + std::to_string(this->Get()) + "\n";
	return str;
}

std::string CougarCANTalon::dumpState()  {
	std::string str =  this->toString();
	str += "Sensor value: " + std::to_string(this->Get()) + "\n";
	return str;
}

} // namespace cougar

