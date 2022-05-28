#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdlib.h>
#include <stdio.h>
#include <list>


double Volt;
/*
struct Measure						//structure that stores data about a single point
{
	int x, y, z, voltage;
};
*/
class SignalPi
{
private:
	const int adrD = 0x48;						//device address Data, X, Y, Z
	const int adrX = 0x00;
	const int adrY = 0x00;
	const int adrZ = 0x00;
	int setWiring, setD, setX, setY, setZ;

	
public:
	int ADCreadD, ADCreadX, ADCreadY, ADCreadZ;
	void startWiring();
	void startI2CD();
	void startI2CX();
	void startI2CY();
	void startI2CZ();
	void liveprint();
};



void SignalPi::startWiring()
{
	setWiring = wiringPiSetup();					/*This initialises wiringPi and assumes that the calling program is going to be using the wiringPi pin numbering scheme. 
													This is a simplified numbering scheme which provides a mapping from virtual pin numbers 0 through 16 to the real underlying Broadcom GPIO pin numbers.
													WiringPi returns zero or -1 if any error.
													One of the setup functions must be called at the start of your program or your program will fail to work correctly.*/
	if (setWiring == -1)					
	{
		printf("wiringPi doesn't work.");
		exit(1);
	}
}

//----------------------------------------------------------------------------------------------------------

void SignalPi::startI2CD()
{
	setD = wiringPiI2CSetup(adrD);						/*This initialises the I2C system with your given device identifier. The ID is the I2C number of the device and you can use the i2cdetect program to find this out. 
														wiringPiI2CSetup() will work out which revision Raspberry Pi you have and open the appropriate device in /dev.
														The return value is the standard Linux filehandle, or -1 if any error – in which case, you can consult errno as usual.
														Setup functions must be called at the start of your program or your program will fail to work correctly.*/
	if (setD == -1)         
	{
		printf("I2C for Data device doesn't work.");
		exit(1);
	}
}

//----------------------------------------------------------------------------------------------------------

void SignalPi::startI2CX()
{
	setX = wiringPiI2CSetup(adrX);						//start I2C X device
	if (setX == -1)         
	{
		printf("I2C for X device doesn't work.");
		exit(1);
	}
}

//----------------------------------------------------------------------------------------------------------

void SignalPi::startI2CY()
{
	setY = wiringPiI2CSetup(adrY);						//start I2C Y device
	if (setY == -1)        
	{
		printf("I2C for Y device doesn't work.");
		exit(1);
	}
}

//----------------------------------------------------------------------------------------------------------

void SignalPi::startI2CZ()
{
	setZ = wiringPiI2CSetup(adrZ);						//start I2C Z device
	if (setZ == -1)         
	{
		printf("I2C for Z device doesn't work.");
		exit(1);
	}
}

void SignalPi::liveprint()
{
	ADCreadD = wiringPiI2CReadReg8(setD, adrD);               /*for PCF8591 adr+0=IN0, adr+1=IN1, adr+2=IN3, adr+3=IN3, adr+4=OUT
															  These read an 8-bit value from the device register indicated.*/
	Volt = ADCreadD * 3.3 / 255;
	printf("Voltage from the needle: %f \n", Volt);

	delay(100);
}


int main(void)
{
	SignalPi inicialize;
	inicialize.startWiring();
	inicialize.startI2CD();
	inicialize.startI2CX();
	inicialize.startI2CY();
	inicialize.startI2CZ();
	
	// W tym miejscu pojawią się odpowiednie pętle po stworzeniu funkcji sterowania.

	while (true)
	{
		inicialize.liveprint();
	}

	return 0;
	
}



/*
//----------------------------------------------------------------------------------------------------------

void savedata()
{
	std::list<Measure> dataset;                                                        //a list of read point structures 
	dataset.emplace_back(Measure({ADCreadX, ADCreadY, ADCreadZ, ADCreadD}));
}

//----------------------------------------------------------------------------------------------------------

void collectdata()
{
	ADCreadD = wiringPiI2CReadReg8(setD, adrD);

	ADCreadX = wiringPiI2CReadReg8(setX, adrX);

	ADCreadY = wiringPiI2CReadReg8(setY, adrY);

	ADCreadZ = wiringPiI2CReadReg8(setZ, adrZ);
}

//----------------------------------------------------------------------------------------------------------

*/