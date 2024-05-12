#include "logger.h"

#include <iostream>

void KLog(const char* str)
{
	std::cout << "KLOG: " << str << std::endl;
}

void KErr(const char* str)
{
	std::cerr << "KERR: " << str << std::endl;
}
