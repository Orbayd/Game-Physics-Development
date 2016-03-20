#include "Simulation.h"

Simulation *Simulation::Instance()
{
	// This is where its actually stored (BSS section)
	static Simulation instance;
	return &instance;
}

// default constructor
Simulation::Simulation()
{
	this->state = SimulationEnum::WakeUp;
	this->wakeupCount = 0;
	this->timeStep = 0.0f;

	AzulStopWatch::initStopWatch();
	this->totalWatch.tic();
	this->stopWatch.tic();
}

void Simulation::Create()
{
	Simulation *pSim = Simulation::Instance();

	pSim->totalWatch.tic();
	pSim->stopWatch.tic();
}

void Simulation::Update()
{
	Simulation *pSim = Simulation::Instance();

	// Time update.
	//      Get the time that has passed.
	//      Feels backwards, but its not, need to see how much time has passed
	pSim->stopWatch.toc();
	pSim->stopWatch.tic();
	pSim->totalWatch.toc();

	if (pSim->getState() == SimulationEnum::WakeUp)
	{
		pSim->timeStep = SIM_SINGLE_TIME_STEP;
		pSim->privUpdateWakeUp();
	}
	else if (pSim->getState() == SimulationEnum::FixedStep)
	{
		pSim->timeStep = SIM_SINGLE_TIME_STEP;
	}
	else if (pSim->getState() == SimulationEnum::Realtime)
	{
		pSim->timeStep = pSim->stopWatch.timeInSeconds();
	}
	else if (pSim->getState() == SimulationEnum::SingleStep)
	{
		pSim->timeStep = SIM_SINGLE_TIME_STEP;
		pSim->setState(SimulationEnum::Pause);
	}
	else //  pSim->getState() == SimulationEnum::Pause
	{
		pSim->timeStep = 0.0f;
	}

}

float Simulation::getTimeStep()
{
	return this->timeStep;
}

float Simulation::getTotalTime()
{
	return this->totalWatch.timeInSeconds();
}

void Simulation::privUpdateWakeUp()
{
	this->wakeupCount++;

	if (this->wakeupCount > SIM_NUM_WAKE_CYCLES)
	{
		this->state = SimulationEnum::Pause;
	}
}

void Simulation::setState(SimulationEnum simState)
{
	this->state = simState;
}

SimulationEnum Simulation::getState() const
{
	return this->state;
}

