#include "orccontroller.hh"

OrcController::OrcController(Orc* orc)
{
	this->orc = orc;
	timeCounter = 0;
}

void OrcController::tick(float dt)
{
	timeCounter += dt;
	if(timeCounter >= walkdt)
	{
	}
}
