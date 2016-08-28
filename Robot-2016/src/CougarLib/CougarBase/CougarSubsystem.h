/*
 * CougarCougarSubsystem.h
 *
 *	Created on: Mar 8, 2016
 *			Author: Thejas
 */

#ifndef SRC_COUGARLIB_COUGARBASE_COUGARSUBSYSTEM_H_
#define SRC_COUGARLIB_COUGARBASE_COUGARSUBSYSTEM_H_

/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2011-2016. All Rights Reserved.						  */
/* Open Source Software - may be modified and shared by FRC teams. The code	  */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.															   	  */
/*----------------------------------------------------------------------------*/

#include "WPILib.h"
#include "Dumpable.h"
#include "StateManager.h"

namespace cougar {

class CougarSubsystem : public Subsystem {
public:
	CougarSubsystem(const std::string name);
	virtual ~CougarSubsystem() = default;

	void addObject(std::shared_ptr<Dumpable> obj);
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARBASE_COUGARSUBSYSTEM_H_ */
