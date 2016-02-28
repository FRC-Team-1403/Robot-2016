/*
 * CougarGyro.h
 *
 *	Created on: Feb 9, 2016
 *			Author: Thejas
 *
 *	Currently just a copy of AnalogGyro with some logging added in.
 *	Might do something more interesting with it if I have time.
 */

/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008-2016. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/


#ifndef SRC_COUGARLIB_COUGARWPI_COUGARINPUT_COUGARGYRO_H_
#define SRC_COUGARLIB_COUGARWPI_COUGARINPUT_COUGARGYRO_H_

#include "WPILib.h"
#include "../../CougarDebug.h"

namespace cougar {

class CougarGyro : public GyroBase {
public:
	static const uint32_t kOversampleBits = 10;
	static const uint32_t kAverageBits = 0;
	static constexpr float kSamplesPerSecond = 50.0;
	static constexpr float kCalibrationSampleTime = 5.0;
	static constexpr float kDefaultVoltsPerDegreePerSecond = 0.007;

	explicit CougarGyro(int32_t channel);
	explicit CougarGyro(AnalogInput *channel);
	explicit CougarGyro(std::shared_ptr<AnalogInput> channel);
	CougarGyro(int32_t channel, uint32_t center, float offset);
	CougarGyro(std::shared_ptr<AnalogInput> channel, uint32_t center, float offset);
	virtual ~CougarGyro() = default;

	virtual float GetAngle() const override;
	virtual double GetRate() const override;
	virtual uint32_t GetCenter() const;
	virtual float GetOffset() const;
	virtual void SetSensitivity(float voltsPerDegreePerSecond);
	virtual void SetDeadband(float volts);
	virtual void Reset() override;
	virtual void InitGyro();
	virtual void Calibrate() override;

 protected:
	std::shared_ptr<AnalogInput> m_analog;

 private:
	float m_voltsPerDegreePerSecond;
	float m_offset;
	uint32_t m_center;
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARWPI_COUGARINPUT_COUGARGYRO_H_ */
