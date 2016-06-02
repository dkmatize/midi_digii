#include "Do_3.h"
#include "Re_3.h"
#include "Mi_3.h"
#include "Fa_3.h"
#include "Sol_3.h"
#include "La_3.h"
#include "Si_3.h"
#include "notas.h"

//************************************
//	Input Timer
//************************************

void counter(bool signal_input)
{
	clock_t start = clock();
	while (signal_input==true)
	{
		iteration++;	
	}
	clock_t diff = clock() - start;

	int msec = diff * 1000 / CLOCKS_PER_SEC;
	printf("Time taken %d seconds %d milliseconds (%d iterations)\n",msec/1000, msec%1000, iterations);

}


//************************************
//	Note Selector
//************************************

int selector(int pulse_length)
{
	unsigned char note[];
	if (100<=pulse_length<=200)
	{
		note[]=Do_3_wav;
	}
	else if (201<=pulse_length<=300)
	{
		note[]=Re_3_wav;
	}
	else if (301<=pulse_length<=400)
	{
		note[]=Mi_3_wav;
	}
	else if (401<=pulse_length<=500)
	{
		note[]=Fa_3_wav;
	}
	else if (501<=pulse_length<=600)
	{
		note[]=Sol_3_wav;
	}
	else if (601<=pulse_length<=700)
	{
		note[]=La_3_wav;
	}
	else if (701<=pulse_length<=800)
	{
		note[]=Si_3_wav;
	}
return note;
}

//****************************************
//	DAC transfer function
//***************************************



////////////////////

/*
int msec = 0, trigger = 10; 
clock_t before = clock();

do {
  
   //Do something to busy the CPU just here while you drink a coffee
   //Be sure this code will not take more than `trigger` ms
   

  clock_t difference = clock() - before;
  msec = difference * 1000 / CLOCKS_PER_SEC;
  iterations++;
} while ( msec < trigger );

printf("Time taken %d seconds %d milliseconds (%d iterations)\n",
  msec/1000, msec%1000, iterations);
*/
