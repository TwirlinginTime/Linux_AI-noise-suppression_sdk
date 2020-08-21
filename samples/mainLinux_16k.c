#include "../include/TwirlingCapture.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

//#define FRAMElEN (160)
#define MAX16S (32767)
#define MIN16S (-32768)
#define MAXABS16S (32768)
#ifndef PI
#define PI (3.1415926)
#endif

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("ERROR: arguments number is wrong!\n");
		printf("App.exe inputFilename outputFilename\n");
		return 0;
	}

	char appId[50] = "a5633d85883eccab4a073e44a75bf524";
	char passwrd[50] = "123";
	captureAuthInit(appId, passwrd);

	FILE *fpInput = NULL;
	FILE *fpOutput = NULL;
	// void *vadObj = NULL;
	// void *rnnObj = NULL;
	// char header[44];

	/** Ans parameters. */
	int sampleRate = 16000;
	int inChannels = 1;
	int frameLength = 256;
	int samplesNum = 0;
	int k;

	short inputData16s[frameLength * inChannels];
	short outData16s[frameLength * inChannels];
	float inputData32f[frameLength * inChannels];
	float outputData32f[frameLength * inChannels];

	/** Head rotation parameters. */
	// float heading = 0.f;
	// float pitch = 0.f;
	// float bank = 0.f;

	if ((fpInput = fopen(argv[1], "rb")) == NULL)
	{
		printf("Error: input audio file %s could not be opened.\n", argv[1]);
		// goto end;
		exit(1);
	}
	if ((fpOutput = fopen(argv[2], "wb")) == NULL)
	{
		printf("Error: output audio file %s could not be opened.\n", argv[2]);
		// goto end;
		exit(1);
	}

	void *rnnObj = dnnoiseInit();

	// struct timeval us1;
	// struct timeval us2;
	// long total_cost = 0;
	// int count = 0;

	static const float scale = 1.f / (float)(MAXABS16S);
	while ((k = fread(inputData16s, sizeof(short), frameLength * inChannels, fpInput)) > 0)
	{
		// gettimeofday(&us1, NULL);

		/** Convert input data from 16s to 32f. */
		for (int i = 0; i < frameLength; i++)
		{
			inputData32f[i] = (float)inputData16s[i] * scale * 1.0;
		}

		/**
		* dnn process .
		*/
		dnnoiseProcess(rnnObj, inputData32f);

		/** Convert input data from 32f to 16s. */
		for (int i = 0; i < frameLength; i++)
		{
			int val = (int)(inputData32f[i] * (float)MAXABS16S);
			if (val > (int)MAX16S)
			{
				outData16s[i] = MAX16S;
			}
			else if (val < (int)MIN16S)
			{
				outData16s[i] = MIN16S;
			}
			else
			{
				outData16s[i] = (short)val;
			}
		}

		// for (int i = 0; i < frameLength; i++)
		// {
		// 	outData16s[i] = (short)inputData32f[i];
		// }

		// gettimeofday(&us2, NULL);
		// printf("INFO: TWIR_TIME=%ld us ,counts = %ld us \n", ((us2.tv_sec * 1000000 + us2.tv_usec) - (us1.tv_sec * 1000000 + us1.tv_usec)), count);
		// total_cost += ((us2.tv_sec * 1000000 + us2.tv_usec) - (us1.tv_sec * 1000000 + us1.tv_usec));
		// count++;

		/** Write data to output file. */
		fwrite(outData16s, sizeof(short), frameLength, fpOutput);
		fflush(fpOutput);
	}

	// printf("INFO: total cost time = %ld us, average cost per framelens = %ld us \n", total_cost, total_cost / count);
end:
	captureAuthRelease();
	if (NULL != rnnObj)
	{
		dnnoiseRelease(rnnObj);
		rnnObj = NULL;
	}
	if (NULL != fpOutput)
	{
		fclose(fpOutput);
		fpOutput = NULL;
	}
	if (NULL != fpInput)
	{
		fclose(fpInput);
		fpInput = NULL;
	}

	return 0;
}
