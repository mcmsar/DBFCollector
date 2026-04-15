#ifndef INC_LEO600DEVICES
#define INC_LEO600DEVICES

//Door 
const unsigned long DOOR_RACK_FRONT = 0x40000;	//Rittal front
const unsigned long DOOR_RACK_BACK = 0x40001;	//Rittal back

//Switch
const unsigned long SWITCH_RACK_FRONT_DOOR = 0x30002;	//Rittal front
const unsigned long SWITCH_RACK_BACK_DOOR = 0x30001;	//Rittal back
const unsigned long SWITCH_AGC = 0x30003;	//Switch to turn on Antenna Gain Control
const unsigned long SWITCH_SYSTEM_TEST_HORN = 0x30004;	//Turn on the signal source for system test
const unsigned long SWITCH_POLARIZATIOM = 0x30005;	
const unsigned long SWITCH_FREQ_1 = 0x30006;
const unsigned long SWITCH_FREQ_2 = 0x30007;

//Temperature
const unsigned long TEMP_RACK_1 = 0x10001;	//Rittal 1
const unsigned long TEMP_RACK_2 = 0x10002;	//Rittal 2
const unsigned long TEMP_ACU_INTERNAL = 0x10003;	//ACU (Omega 5131)
const unsigned long TEMP_ACU_EXTERNAL = 0x10004;	//Omega 5331 1
const unsigned long TEMP_MOTOR = 0x10005;	//Omega 5331 2
const unsigned long TEMP_LNC = 0x10006;	//Omega 5331 3
const unsigned long TEMP_RAYDOME = 0x10007;	//Omega 5331 4
const unsigned long TEMP_OUTDOOR = 0x10008;		//Omega ENV50
const unsigned long TEMP_INDOORWW3 = 0x10009;	// WeatherWizard3 Internal Sensor
const unsigned long TEMP_OUTDOORWW3 = 0x1000a;	// WeatherWizard3 External Sensor


//Humidity
const unsigned long HUMIDITY_ACU = 0x20001;	//ACU (Omega 5131)
const unsigned long HUMIDITY_INDOORWW3 = 0x20002;	// WeatherWizard3 Internal Sensor
const unsigned long HUMIDITY_OUTDOORWW3 = 0x20003;	// WeatherWizard3 External Sensor

//Voltage
const unsigned long VOLTAGE_AGC = 0x50001;	//AGC Voltage Level

//System Test Interface
const unsigned long SYSTEM_TEST_SOURCE = 0x60001;

//AntennaDevice Interface
const unsigned long ANTENNA_DEVICE = 0x70000;

//WindDirection
const unsigned long WINDDIR_1 = 0x80000;
const unsigned long WINDDIR_WW3 = 0x80001;

//WindSpeed
const unsigned long WINDSPD_1 = 0x90000;
const unsigned long WINDSPD_WW3 = 0x90001;

//UPS
const unsigned long LOCAL_UPS = 0xA0000;

#endif