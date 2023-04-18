#include "logger.h"
#include <iostream>

void log(const char* msg, unsigned int type){
	const char* types[2] = {
			"[ERROR]",
			"[INFO]"
	};

	std::cout << types[type] << msg << std::endl;
}
