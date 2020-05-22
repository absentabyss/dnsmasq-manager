#ifndef TIME_H
#define TIME_H

#include <ctime>

struct TimeRange
{
	std::tm earlyEnd;
	std::tm lateEnd;
};

bool laterThan(const std::tm &late, const std::tm &early);
bool isBetweenPeriod(const std::tm &time, const std::tm &early, const std::tm &late);

std::tm getTM(int hour, int min, int sec);

#endif 
