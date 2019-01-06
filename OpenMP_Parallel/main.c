
#include <xdc/std.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Diags.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/IHeap.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Timestamp.h>
#include <ti/sysbios/knl/Clock.h>

#include <ti/omp/omp.h>
//#include <stdio.h>
#include <ti/ipc/MultiProc.h>
#include <ti/uia/events/UIABenchmark.h>
#include <ti/uia/events/UIAStatistic.h>
#include <ti/uia/runtime/LogSync.h>
#include <ti/sysbios/knl/Task.h>

#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

#include "left.h"
#include "right.h"

#define pi 3.14159265
#define DEG2RAD 0.01745

#define Height 375
#define Width 1242
#define Search_range 80
#define Radius 2
#define maxd 90
#define Rho_Max 386
#define Acu_height 772

#define MY_TIME_FUNCTION Timestamp_get32()


unsigned char Left[Height*Width]={left};
unsigned char Right[Height*Width]={right};

float Lookup_L[Height*Width*2];
float Lookup_R[Height*Width*2];

unsigned char VDisbin[Height*maxd];
unsigned char VDisbin1[Height*maxd];
unsigned char New_Dis[Height*Width];
unsigned char dil[Height*Width];
unsigned char ero[Height*Width];
short Acu[Acu_height *180];
unsigned char Edgeleft[Height*Width];
int Coedge[Height*Width];

#pragma DATA_SECTION(Disparity,".MSMC0")
unsigned char Disparity[Height*Width];

extern float Stereo_Vision_sa(unsigned char *Left, unsigned char *Right,float *numsp,float *Lookup_L,float *Lookup_R,int *h);
//extern float Stereo_Vision_sa(unsigned char *Left, unsigned char *Right,float *numsp,float *Lookup_L,float *Lookup_R);
extern unsigned char NCC_sa_last_line(unsigned char *Left, unsigned char *Right,unsigned char *Disparity,float *Lookup_L,float *Lookup_R);
extern unsigned char NCC_sa_all(unsigned char *Left, unsigned char *Right,unsigned char *Disparity,unsigned char *Disp,float *Lookup_L,float *Lookup_R,int *J1,int *J2,int *Search_Limit2,int *Search_Limit1);
extern int Edge_Histogram(unsigned char *Edgeleft,int *Coedge);
extern unsigned char Dilation(unsigned char *New_Dis, unsigned char *dil, unsigned char *ero);

int main()
{

	int i,j,t;
	float numsp[2] = {0.025,0};
	xdc_runtime_Types_Timestamp64 ts_start_stereo, ts_end_stereo, ts_end_stereo1;
	xdc_runtime_Types_FreqHz fh_freq;
	Timestamp_getFreq(&fh_freq);
	//unsigned int timeNoOpt,timeStart,timeEnd;

		for (i = 0; i < Height; i++)
			{
				for (j = 0; j < Width; j++)
				{
					Disparity[i*Width+j] = 0;
					Lookup_L[i*Width+2*j] = 0;
					Lookup_L[i*Width+2*j+1] = 0;
					Lookup_R[i*Width+2*j] = 0;
					Lookup_R[i*Width+2*j+1] = 0;
					New_Dis[i*Width+j] = 0;
					Coedge[i*Width+j] = 0;
					Edgeleft[i*Width+j] = 0;
					dil[i*Width+j] = 0;
					ero[i*Width+j] = 0;
				}
				for(j =0;j<maxd;j++)
				{
					VDisbin[i*maxd+j] = 0;
					VDisbin1[i*maxd+j] = 0;
				}
			}
		int start[8]={0};
		int h[8]={0};
		for(i = 0;i<7;i++)
		{
			h[i] = (i==0)?46:(Height/8+2);
			start[i] = (i==0)?0:(start[i-1]+h[i-1]-1);
		}
		h[7] = 45; start[7] = 327;

		int J[16] = {227,84,371,228,515,372,659,516,803,660,947,804,1091,948,1235,1092};

		float x1 = 66, y1 = 374, x2 = 397, y2 = 180;
		float x11 = 787, y11 = 374, x22 = 648, y22 = 180;
		float k1 = (y1 - y2) / (x1 - x2);
		float b1 = (y1-k1*x1);
		float k11 = (y11 - y22) / (x11 - x22);
		float b11 = (y11 - k11*x11);

		unsigned char Disp1[144] = { 0 };
		unsigned char Disp2[144] = { 0 };
		unsigned char Disp3[144] = { 0 };
		unsigned char Disp4[144] = { 0 };
		unsigned char Disp5[144] = { 0 };
		unsigned char Disp6[144] = { 0 };
		unsigned char Disp7[144] = { 0 };
		unsigned char Disp8[144] = { 0 };


		//timeStart = MY_TIME_FUNCTION;
		//Log_write1(UIABenchmark_start, (xdc_IArg)"main loop");
		Timestamp_get64(&ts_start_stereo);
//Lookup table establishment
#pragma omp parallel shared(Left,Right,Lookup_L,Lookup_R,start,h,numsp) num_threads(8)
		{
#pragma omp sections
		{
#pragma omp section
			{
				//printf("id = %d\n",omp_get_thread_num());
				Stereo_Vision_sa(&Left[start[0]*Width],&Right[start[0]*Width],numsp,&Lookup_L[2*start[0]*Width],&Lookup_R[2*start[0]*Width],&h[0]);
				//linear assembly function
			}
#pragma omp section
			{
				//printf("id = %d\n",omp_get_thread_num());
				Stereo_Vision_sa(&Left[start[1]*Width],&Right[start[1]*Width],numsp,&Lookup_L[2*start[1]*Width],&Lookup_R[2*start[1]*Width],&h[1]);
			}
#pragma omp section
			{
				//printf("id = %d\n",omp_get_thread_num());
				Stereo_Vision_sa(&Left[start[2]*Width],&Right[start[2]*Width],numsp,&Lookup_L[2*start[2]*Width],&Lookup_R[2*start[2]*Width],&h[2]);
			}
#pragma omp section
			{
				//printf("id = %d\n",omp_get_thread_num());
				Stereo_Vision_sa(&Left[start[3]*Width],&Right[start[3]*Width],numsp,&Lookup_L[2*start[3]*Width],&Lookup_R[2*start[3]*Width],&h[3]);
			}
#pragma omp section
			{
				//printf("id = %d\n",omp_get_thread_num());
				Stereo_Vision_sa(&Left[start[4]*Width],&Right[start[4]*Width],numsp,&Lookup_L[2*start[4]*Width],&Lookup_R[2*start[4]*Width],&h[4]);
			}
#pragma omp section
			{
				//printf("id = %d\n",omp_get_thread_num());
				Stereo_Vision_sa(&Left[start[5]*Width],&Right[start[5]*Width],numsp,&Lookup_L[2*start[5]*Width],&Lookup_R[2*start[5]*Width],&h[5]);
			}
#pragma omp section
			{
				//printf("id = %d\n",omp_get_thread_num());
				Stereo_Vision_sa(&Left[start[6]*Width],&Right[start[6]*Width],numsp,&Lookup_L[2*start[6]*Width],&Lookup_R[2*start[6]*Width],&h[6]);
			}
#pragma omp section
			{
				//printf("id = %d\n",omp_get_thread_num());
				Stereo_Vision_sa(&Left[start[7]*Width],&Right[start[7]*Width],numsp,&Lookup_L[2*start[7]*Width],&Lookup_R[2*start[7]*Width],&h[7]);
			}
		}
		}
//Disparity estimation on the bottom line
		NCC_sa_last_line(Left,Right,Disparity,Lookup_L,Lookup_R);//linear assembly function


//Disparity estimation on the rest of the image
		for(i = Height-4;i>=2;i--)
		{
			int Search_Limit2 = Search_range*i/Height;
			int Search_Limit1 = (Search_Limit2-40)>=0? (Search_Limit2-40):0;
			int k = 0;

#pragma omp parallel sections num_threads(8)
		{
#pragma omp section
			{//linear assembly function
			NCC_sa_all(&Left[i*Width],&Right[i*Width],&Disparity[i*Width],Disp1,&Lookup_L[2*i*Width],&Lookup_R[2*i*Width],&J[0],&J[1],&Search_Limit2,&Search_Limit1);
			}
#pragma omp section
			{
			NCC_sa_all(&Left[i*Width],&Right[i*Width],&Disparity[i*Width],Disp2,&Lookup_L[2*i*Width],&Lookup_R[2*i*Width],&J[2],&J[3],&Search_Limit2,&Search_Limit1);
			}
#pragma omp section
			{
			NCC_sa_all(&Left[i*Width],&Right[i*Width],&Disparity[i*Width],Disp3,&Lookup_L[2*i*Width],&Lookup_R[2*i*Width],&J[4],&J[5],&Search_Limit2,&Search_Limit1);
			}
#pragma omp section
			{
			NCC_sa_all(&Left[i*Width],&Right[i*Width],&Disparity[i*Width],Disp4,&Lookup_L[2*i*Width],&Lookup_R[2*i*Width],&J[6],&J[7],&Search_Limit2,&Search_Limit1);
			}
#pragma omp section
			{
			NCC_sa_all(&Left[i*Width],&Right[i*Width],&Disparity[i*Width],Disp5,&Lookup_L[2*i*Width],&Lookup_R[2*i*Width],&J[8],&J[9],&Search_Limit2,&Search_Limit1);
			}
#pragma omp section
			{
			NCC_sa_all(&Left[i*Width],&Right[i*Width],&Disparity[i*Width],Disp6,&Lookup_L[2*i*Width],&Lookup_R[2*i*Width],&J[10],&J[11],&Search_Limit2,&Search_Limit1);
			}
#pragma omp section
			{
			NCC_sa_all(&Left[i*Width],&Right[i*Width],&Disparity[i*Width],Disp7,&Lookup_L[2*i*Width],&Lookup_R[2*i*Width],&J[12],&J[13],&Search_Limit2,&Search_Limit1);
			}
#pragma omp section
			{
			NCC_sa_all(&Left[i*Width],&Right[i*Width],&Disparity[i*Width],Disp8,&Lookup_L[2*i*Width],&Lookup_R[2*i*Width],&J[14],&J[15],&Search_Limit2,&Search_Limit1);
			}
		}
			for (k = 227; k >= 84; k--)
			{
				Disparity[i*Width + k] = Disp1[k - 84];
			}
			for (k = 371; k >= 228; k--)
			{
				Disparity[i*Width + k] = Disp2[k - 228];
			}
			for (k = 515; k >= 372; k--)
			{
				Disparity[i*Width + k] = Disp3[k - 372];
			}
			for (k = 659; k >= 516; k--)
			{
				Disparity[i*Width + k] = Disp4[k - 516];
			}
			for (k = 803; k >= 660; k--)
			{
				Disparity[i*Width + k] = Disp5[k - 660];
			}
			for (k = 947; k >= 804; k--)
			{
				Disparity[i*Width + k] = Disp6[k - 804];
			}
			for (k = 1091; k >= 948; k--)
			{
				Disparity[i*Width + k] = Disp7[k - 948];
			}
			for (k = 1235; k >= 1092; k--)
			{
				Disparity[i*Width + k] = Disp8[k - 1092];
			}
		}
		//NCC_all_orin(Left, Right, Disparity, Lookup_L, Lookup_R);


		Timestamp_get64(&ts_end_stereo);
		//Log_write1(UIABenchmark_stop, (xdc_IArg)"main loop");
		//timeEnd = MY_TIME_FUNCTION;
		//timeNoOpt = timeEnd-timeStart;

		/***************************V-Disaprity**************************/
#pragma omp parallel for private(j,t) num_threads(8) schedule(static,1)
		/*************obtain v-map************/
		for (i = 374; i >=180; i--)
		{
			for (j = (i - b11) / k11; j >= (i - b1) / k1; j--)
			{
				int Disp = Disparity[i*Width + j];
				if (Disp>10)
					VDisbin[i * maxd + Disp]++;
			}
			for (t = maxd - 1; t >= 0; t--)   //***binarization***/
			{
				VDisbin[i*maxd + t] = (VDisbin[i*maxd + t] < 110) ? 0 : 1;
			}
		}

/**************************HT for lane elimination**************************/
#pragma omp parallel for private(j) num_threads(8) schedule(static,1)
		for(i = Acu_height-1;i>=0;i--)
		{
			for(j = 179;j>=0;j--)
			{
				Acu[i*180+j] = 0;
			}
		}

#pragma omp parallel for private(j,t) schedule(static,1) num_threads(8)
		for (i = Height-1; i >= 0; i--)
		{
			for (j = maxd-1; j >= 0; j--)
			{
				if (VDisbin[i*maxd + j] == 1)
				{
					for (t = 179; t >= 0; t--)
					{
						int rho = round(i*cos(DEG2RAD*t) + j*sin(DEG2RAD*t));
						Acu[(rho + Rho_Max) * 180 + t]++;
					}
				}
			}
		}
		int theta, r, ii, jj;
		int Max = 0;
#pragma omp parallel for private(j) shared(Max) schedule(static,1) num_threads(8)
		for (i = Acu_height-1; i >= 0; i--)
		{
			for (j = 179; j >= 0; j--)
			{
				if (Max < Acu[i * 180 + j])
				{
					Max = Acu[i * 180 + j];
					r = i - Rho_Max;
					theta = j;
				}
			}
		}
		/***********Lane removal***********/
		int T = 10;
#pragma omp parallel for private(j,jj) shared(T) schedule(static,1) num_threads(8)
		for (i = Height-1; i >= 0; i--)
		{
			int j = (r - i*cos(theta*DEG2RAD)) / sin(theta*DEG2RAD);
			int V_Disp_value = 0;
			if (j >= 0 && j < maxd)
			{
				VDisbin1[i*maxd + j] = 1;
				V_Disp_value = j;
			}
			for (jj = (i - b11) / k11; jj >= (i - b1) / k1; jj--)
			{
				New_Dis[i*Width + jj] = (Disparity[i*Width + jj] <= V_Disp_value + T) ? 0 : Disparity[i*Width + jj];
			}
		}

/*****************************Edge detection*******************************/
		int rad = 3;
		int i1, i2, i3, gx, gy, g;

		//for (i = 0 + rad; i < height - rad; i++)
		for (i = 374 - rad; i >= 180 + rad; i--)
		{
			i1 = (i - 1)*Width;
			i2 = i*Width;
			i3 = (i + 1)*Width;
			//for (j = 0 + rad; j < width - rad; j++)
			for (j = ((i - b11) / k11) - rad; j >= (i - b1) / k1 + rad; j--)
			{
				gx = -Left[i1 + j - 1] + Left[i3 + j - 1] - 2 * Left[i1 + j] + 2 * Left[i3 + j] - Left[i1 + j + 1] + Left[i3 + j + 1];
				gy = Left[i1 + j - 1] + 2 * Left[i2 + j - 1] + Left[i3 + j - 1] - Left[i1 + j + 1] - 2 * Left[i2 + j + 1] - Left[i3 + j + 1];
				g = abs(gx) + abs(gy);
				Edgeleft[i * Width + j] = (g >= 80) ? 1 : 0;
			}

		}
		/**************Histogram generation based on the edge image****************/
/*		int RAD = 4;
		int sum;
//#pragma omp parallel for private(j,ii,jj) num_threads(8) schedule(static,1)
		for (i = 374; i >= 180; i--)
		{
			for (j = 700; j >= (i- b1)/k1; j--)
			{
				sum = 0;
				for (ii = RAD; ii >= -RAD; ii--)
				{
					for (jj = RAD; jj >= -RAD; jj--)
					{
						sum += Edgeleft[(i + ii)*Width + j + jj];
						//if (Edgeleft[(i + ii)*Width + j + jj] == 1)
							//sum++;
					}
				}
				//Coedge[i*width + j] = sum;
				Coedge[i*Width + j] = (sum < 10) ? 0 : sum;
			}
		}

*/
		Edge_Histogram(Edgeleft,Coedge); //linear assembly function

/****************************Histogram to Disparity Mapping*********************************/
#pragma omp parallel for private(j) num_threads(8) schedule(static,1)
		for (i = 374; i >= 180; i--)
		{
			for (j = (i - b11) / k11; j >= (i-b1)/k1; j--)
			{
				New_Dis[i*Width + j] = (Coedge[i*Width + j] == 0) ? 0 : New_Dis[i*Width + j];
			}
		}
#pragma omp parallel for private(j) num_threads(8) schedule(static,1)
		///***************binarization*****************/
		for (i = 374; i >= 180; i--)
		{
			for (j = (i - b11) / k11; j >= (i-b1)/k1; j--)
			{
				New_Dis[i*Width + j] = (New_Dis[i*Width + j] == 0) ? 0 : 255;
			}
		}

/***************************Dilation and Erosion****************************/
		Dilation(New_Dis,dil,ero);  //linear assembly function
/*
		int dilation_size = 8;

//#pragma omp parallel for private(j,ii,jj) shared(New_Dis,dil,ero) schedule(dynamic) num_threads(8)
		for (i = 374; i >= 180; i--)
		{
			for (j = (i - b11) / k11; j >= (i - b1) / k1; j--)
			{
				for (ii = dilation_size; ii >= -dilation_size; ii--)
				{
					for (jj = dilation_size; jj >= -dilation_size; jj--)
					{
						if (New_Dis[(i + ii)*Width + j + jj] == 255)
						{
							dil[i*Width + j] = 255;
							ero[i*Width + j] = 255;
							break;
						}
					}
				}
			}
		}
		int erosion_size = 10;
//#pragma omp parallel for private(j,ii,jj) shared(dil,ero) schedule(dynamic) num_threads(8)
		for (i = 374; i >= 180; i--)
		{
			for (j = (i - b11) / k11; j >= (i - b1) / k1; j--)
			{
				for (ii = erosion_size; ii >= -erosion_size; ii--)
				{
					for (jj = erosion_size; jj >= -erosion_size; jj--)
					{
						if (dil[(i + ii)*Width + j + jj] == 0)
						{
							ero[i*Width + j] = 0;
							break;
						}
					}
				}
			}
		}
*/
		Timestamp_get64(&ts_end_stereo1);

		unsigned long long end1 = ((unsigned long long) ts_end_stereo.lo)|(((unsigned long long)ts_end_stereo.hi)<<32);
		unsigned long long start1 = ((unsigned long long) ts_start_stereo.lo)|(((unsigned long long)ts_start_stereo.hi)<<32);
		unsigned long long freq1 = ((unsigned long long) fh_freq.lo)|(((unsigned long long)fh_freq.hi)<<32);
		unsigned long long end2 = ((unsigned long long) ts_end_stereo1.lo)|(((unsigned long long)ts_end_stereo1.hi)<<32);

		double time_difference_total1 = (((double)end1) -((double)start1))/freq1;
		double time_difference_total2 = (((double)end2) -((double)end1))/freq1;
		double time_difference_total3 = (((double)end2) -((double)start1))/freq1;
		//printf("\nLinear Code w/o Disparity cycle:      %d cycles\n",timeNoOpt);
		printf("\n Time for disparity estimation = %0.11lf s\n",time_difference_total1);
		printf("\n Time for vehicle detection = %0.11lf s\n",time_difference_total2);
		printf("\n Time total = %0.11lf s\n",time_difference_total3);

		return 0;
}




