#ifndef SPECINFO_H
#define SPECINFO_H

typedef struct specInfo{ // to be filled at compile time see comments for our/Bruker's conventions
		long si; // number of reals --changed from int 03May2024
		float offset; //high ppm
		double sf;  //400.1300104
		double sw_p; //sw in Hz
		double left; //high ppm
		double right; //low ppm
} SPI;	//PUT SI and other stuff in here!!!!!!!!!!!

//double leftHz(SPI spi);
//double rightHz(SPI spi);
#endif