#include <iostream>
#include <chrono>
#include <ctime> //calendar time

#pragma warning(disable:4996) // disable warning for unsafe operation number 4996

using namespace std;


int main() {
	//Durations
	chrono::hours hr(1);
	chrono::minutes min(15);
	chrono::seconds sec(30);
	chrono::milliseconds mill(1440);
	chrono::nanoseconds nan(12);
	chrono::microseconds mic(19);

	chrono::nanoseconds t = chrono::duration_cast<chrono::nanoseconds>(mill); //casting durations



	chrono::system_clock::time_point tp = std::chrono::system_clock::now(); //timepoint

	// time one hour from now
	chrono::system_clock::time_point one_hour_from_now = tp + chrono::hours(1);

	std::cout << tp.time_since_epoch().count() << endl;

	time_t now = chrono::system_clock::to_time_t(tp);


	std::cout << "Current time: " << std::ctime(&now) << std::endl; //from timepoint to calendar date (unsafe)


	//from timepoint to calendar date
	char str[26];
	ctime_s(str, sizeof str, &now);
	std::cout << "Current time: " << str << endl;

}

/* Duration
*  rapresent a span of time in various units such second, minutes ecc
*/

/* Timepoint
*  rapresent a specific point in time.
* c++ provide 3 clock types:
* - system_clock: rapresent the system-wide real time wall clock
* - steady_clock: rapresent a monotonic clock that is guaranteed to never be asjusted, ensure that the time between ticks is constant so is usefull for measuring intervals
* - high_resolution_clock: shortest tick period clock
*/

/* ctime
* convertr a timepoint to a calendar rapresentation
*
*/