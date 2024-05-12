#include "lsgClock.h"

#include "GLFW/glfw3.h"

slgClock::slgClock() : startTime(glfwGetTime())
{}

double slgClock::getEllapsedTime() const
{
	double time = glfwGetTime();
	double elapsedTime = time - startTime;
	return elapsedTime;
}

double slgClock::restart()
{
	double time = glfwGetTime();
	double elapsedTime = time - startTime;
	startTime = time;
	return elapsedTime;
}


