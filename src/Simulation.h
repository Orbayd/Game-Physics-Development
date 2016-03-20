#ifndef SIMULATION_H
#define SIMULATION_H

#include "AzulStopWatch.h"

#define SIM_NUM_WAKE_CYCLES     10
#define SIM_SINGLE_TIME_STEP	0.016666f

enum SimulationEnum
{
	WakeUp,
	Realtime,
	FixedStep,
	SingleStep,
	Pause
};

// singleton class
class Simulation
{
public:
	// singleton access
	static Simulation *Instance();
	static void Create();
	static void Update();

	// Get time in Seconds
	float getTimeStep();

	// Get totalTime
	float getTotalTime();

	// Get / Set state
	void setState(SimulationEnum simState);
	SimulationEnum getState() const;


private:
	// cannot create without going through singleton
	Simulation();

	// Special functions for wakeup state
	void privUpdateWakeUp();

private:  // data
	SimulationEnum  state;
	int				wakeupCount;
	AzulStopWatch	stopWatch;
	AzulStopWatch	totalWatch;
	float			timeStep;
};


#endif