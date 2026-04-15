
#ifndef __FREQ_CONSTANTS_H__
#define __FREQ_CONSTANTS_H__


	// Moved From SitGenServ.h.  Need to share these values with MTL.
	// BIAS check range, set to meet the spec (-25KHz to 75KHz), can be change later
	#define MAX_121_BIAS			(double) 75000.00		//Hz
	#define MIN_121_BIAS			(double) -25000.00		//Hz
	#define MAX_243_BIAS			(double) 75000.00		//Hz
	#define MIN_243_BIAS			(double) -25000.00		//Hz
	#define MAX_406_BIAS			(double) 75000.00		//Hz
	#define MIN_406_BIAS			(double) -25000.00		//Hz
	#define MAX_FREQ_BIAS			(double) 75000.00		//Hz
	#define MIN_FREQ_BIAS			(double) -25000.00		//Hz
	#define FREQ_OFF_121			(double) 121500000.00	//Hz
	#define FREQ_OFF_243			(double) 243000000.00	//Hz
	#define FREQ_OFF_406			(double) 406025000.00	//Hz

#endif	// __FREQ_CONSTANTS_H__