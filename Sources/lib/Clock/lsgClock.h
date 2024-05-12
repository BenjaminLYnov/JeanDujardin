#ifndef SLGCLOCK_H
#define SLGCLOCK_H

#include <GLFW/glfw3.h>

class slgClock
{
public:
	slgClock();
	~slgClock() = default;

	double getEllapsedTime() const;
	double restart();

private:
	double startTime;
};

#endif // !SLGCLOCK_H
