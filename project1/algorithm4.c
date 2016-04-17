#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

typedef struct {
	int start;
	int end;
	int value;
} tTuple;

struct timeval time_start, time_stop, run_time;



/* ***************************************************************
*					  FUNCTION DECLARATIONS						 *
*************************************************************** */


tTuple max_sum_subArray_4(int* array);
int* parseArray(char* line);
void getLine(FILE* inFile, FILE* outFile);
FILE* openFile(const char* filname);
void timeRightNow(FILE* outFile);
int arraySize;



/* ***************************************************************
*						  MAIN FUNCTION							 *
*************************************************************** */


 int main(){
 
	const char* fileIn = "MSS_TestProblems.txt";
	const char* fileOut = "MSS_TestResults.txt";
	FILE *fpIn, *fpOut;
	
	fpIn = openFile(fileIn);
	fpOut = openFile(fileOut);
	
	getLine(fpIn, fpOut);
	
	fclose(fpIn);
	fclose(fpOut);
	   
	return 0;
}



/* ***************************************************************
*						SUPPLEMENTAL FUNCTION					 *
*************************************************************** */
 
 
tTuple max_sum_subArray_4(int* array){
	
	int min = 32767;
	tTuple result;
	result.value, result.start = 0;
	result.end = arraySize;
	
	int temp_max, current_max = 0;
 
	for (int i = 0; i < arraySize; i++){
		min = min < array[i] ? min : array[i];
		if (array[i] > (current_max + array[i])){
			result.start = i;
			current_max = array[i];
		}
		else{
			current_max = current_max + array[i];
		}

		if (result.value <= current_max){
			result.value = current_max;
			result.end = i;
		}
	}
	return result;
}


int* parseArray(char* passedLine){
	
	char* token;
	char line[256];
	int nextNum, i = 0;
	int* parsedArray = malloc(256);
	
	memset(&line, 0, sizeof(line));
	memcpy(&line, passedLine, 256);
	line[0] = ' ';
	token = strtok(line, ",");
	
	while(token != NULL){
		sscanf(token, "%d", &nextNum);
		printf("\nNumber: %d", nextNum);
		parsedArray[i] = nextNum;
		i++;
		token = strtok(NULL,",");
	}
	arraySize = i;
	return parsedArray;
}


void getLine(FILE* inFile, FILE* outFile){
	
	char lineIn[256];
	int* parsedArray, max;
	tTuple subArray;
	while ( fgets(lineIn, sizeof(lineIn), inFile) != NULL ){
		
		printf("\n*********** ALGORITHM 4 ***********\n");
		fprintf(outFile, "\n*********** ALGORITHM 4 ***********\n");
		parsedArray = parseArray(lineIn);
		gettimeofday(&time_start, NULL);
		subArray = max_sum_subArray_4(parsedArray);
		gettimeofday(&time_stop, NULL);		
		printf("\nThe max sub array is: %d\nStart: %d\nEnd: %d", subArray.value, subArray.start, subArray.end);
		fprintf(outFile, "\nThe max sub array is: %d\nStart: %d\nEnd: %d", subArray.value, subArray.start, subArray.end);
		timeRightNow(outFile);
	}
	free(parsedArray);
}


FILE* openFile(const char* filename){
	
	FILE *file = fopen(filename, "a+");
	
	if(file != NULL){
		return file;
	}
	else{
		printf("\nFailed to open %s", filename);
	}	
}


void timeRightNow(FILE* outFile){
		
	timersub(&time_stop, &time_start, &run_time);
	printf("\nComputed in %ld.%06ld\n", (long int)run_time.tv_sec, (long int)run_time.tv_usec);
	fprintf(outFile, "\nComputed in %ld.%06ld\n", (long int)run_time.tv_sec, (long int)run_time.tv_usec);
}


