#include "pch.h"
#include "ShapeInfinity.h"

void ShapeInfinity::Finish()
{
	finished = true;
}

bool ShapeInfinity::isFinished()
{
	return finished;
}
