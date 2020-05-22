#include "time.h"

#include <ctime>

bool laterThan(const std::tm &late, const std::tm &early)
{
	if (late.tm_hour > early.tm_hour)
		return true;
	else if (late.tm_hour == early.tm_hour)
	{
		if (late.tm_min > early.tm_min)
			return true;
		else if (late.tm_min == early.tm_min)
		{
			if (late.tm_sec > early.tm_sec)
				return true;
		}
	}
	return false;
}

bool isBetweenPeriod(const std::tm &time, const std::tm &early, const std::tm &late)
{
	if (laterThan(late, time) && laterThan(time, early))
		return true;
	return false;
}

std::tm getTM(int hour, int min, int sec)
{
	std::tm date{};
	date.tm_hour = hour;
	date.tm_min = min;
	date.tm_sec = sec;
	return date;
}

