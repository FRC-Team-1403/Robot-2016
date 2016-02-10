/*
 * CougarGyro.h
 *
 *	Created on: Feb 9, 2016
 *			Author: Thejas
 */

#ifndef SRC_COUGARLIB_COUGARWPI_COUGARINPUT_COUGARGYRO_H_
#define SRC_COUGARLIB_COUGARWPI_COUGARINPUT_COUGARGYRO_H_

#include "WPILib.h"

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

	float GetAngle() const override;
	double GetRate() const override;
	virtual uint32_t GetCenter() const;
	virtual float GetOffset() const;
	void SetSensitivity(float voltsPerDegreePerSecond);
	void SetDeadband(float volts);
	void Reset() override;
	virtual void InitGyro();
	void Calibrate() override;

 protected:
	std::shared_ptr<AnalogInput> m_analog;

 private:
	float m_voltsPerDegreePerSecond;
	float m_offset;
	uint32_t m_center;
};

} /* namespace cougar */

#endif /* SRC_COUGARLIB_COUGARWPI_COUGARINPUT_COUGARGYRO_H_ */
