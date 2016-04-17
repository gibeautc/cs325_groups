#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

typedef struct {
	int start;
	int end;
	int value;
} tTuple;

struct timeval time_start, time_stop, run_time, t;



/* ***************************************************************
*					  FUNCTION DECLARATIONS						 *
*************************************************************** */


tTuple max_sum_subArray_4(int* array);
int* randomArray(int size);
int* parseArray(char* line);
void getLine(FILE* inFile, FILE* outFile);
FILE* openFile(const char* filname);
void timeRightNow(FILE* outFile);
void largeArrayLoop();
int n[10] = {25, 50, 100, 250, 500, 1000, 1500, 3500, 5000, 10000};
int arraySize;



/* ***************************************************************
*						  MAIN FUNCTION							 *
*************************************************************** */


 int main(){
 
	const char* fileIn = "MSS_TestProblems.txt";
	const char* fileOut = "MSS_TestResults.txt";
	FILE *fpIn, *fpOut;
	int i, j, *tempArray;
	
	fpIn = openFile(fileIn);
	fpOut = openFile(fileOut);
	
	getLine(fpIn, fpOut);
	
	fclose(fpIn);
	fclose(fpOut);
	
	largeArrayLoop();
	   
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


void largeArrayLoop(){
	
	int i, *tempArray;
	
	for (i = 0; i < 10; i++){
		
		printf("\n*********** ALGORITHM 4 ***********\n");
		printf("\nIteration %d: n = %d", i, n[i]);
		tTuple subArray;		
		tempArray = randomArray(n[i]);
		
		gettimeofday(&time_start, NULL);
		subArray = max_sum_subArray_4(tempArray);
		gettimeofday(&time_stop, NULL);
		
		timersub(&time_stop, &time_start, &run_time);
		printf("\nThe max sub array is: %d\nStart: %d\nEnd: %d", subArray.value, subArray.start, subArray.end);
		printf("\nComputed in %ld.%06ld seconds\n", (long int)run_time.tv_sec, (long int)run_time.tv_usec);
		
		free(tempArray);
	}
}


int* randomArray(int size){
	
	int i, random;
	int* randArray = malloc(size*10);
	arraySize = size;
	
	gettimeofday(&t, NULL);
	srand(t.tv_sec * t.tv_usec);
	
	for(i = 0; i < size; i++){
		random = rand() % 200 - 100;
		randArray[i] = random;
	}
	return randArray;
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
		parsedArray[i] = nextNum;
		i++;
		token = strtok(NULL,",");
	}
	arraySize = i;
	return parsedArray;
}


void getLine(FILE* inFile, FILE* outFile){
	
	char lineIn[256];
	int* parsedArray;
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


