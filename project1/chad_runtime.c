//Writen by Chad Gibeaut
//Iterative version of algorthm 
//Includes parsing and file helper functions
// Written from the happiest place in the work (unless you have HW to do)


#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>


//int size=100;//size of array
FILE *fd_in;
FILE *fd_out; //file discriptors for input and output files
char buffer[300];//buffer for reading from file


//still need to do
//add timing functions so each problem can be tracked for time based on size of array
//dynamic array functions so large arrays can be used
//ability to generate large arrays


//creates random array of size and returns it
void random_array(int size)
{
	srand( (unsigned)time( NULL ) );
    int rand_array[size];
	int index;
	for(index=0;index<size;index++)
	{
	    rand_array[index]=((rand() % 200)-100);//create random number from -100 to 100
		//printf("Random Number is: %d\n",rand_array[index]);
		
	}
	
	max_sum_subArray_4(rand_array,size);
	
}



void max_sum_subArray_4(int array[],int s)
{
	//for each starting location n, sum from n to count
	//track largest value of sum in sum array
	printf("Starting Sum\n");
	//printf("Made it here");fflush(NULL);
	int count=s;//actual count of elements
	printf("Size of array: %d\n",count);
	int i;
	int sum_Array[count];//create sum array
	int n;
	time_t start,end;
	start=time(NULL);
	for(n=0;n<count;n++)
	{
		int sum=0;
		int max=0;
		for(i=n;i<count;i++)
		{
			
			sum=sum+array[i];
			//printf("Made it here i=%d n=%d\n",i,n);fflush(NULL);
			if(sum>max){max=sum;}
		}
		sum_Array[n]=max;
	}
	int max=0;
	int index=0;
	for(n=0;n<count;n++)
	{
		if(sum_Array[n]>max){max=sum_Array[n];index=n;}
		//printf("Sum of index:%d is:%d\n",n,sum_Array[n]);	
	}
	
	end=time(NULL);
	printf("Max index is: %d with a sum of: %d\n",index,max);
	printf("In time: %d\n",((int) end-(int)start));
}




			
//used for doubling array size
void double_array(int array[],int size)
{
	printf("Doubling array size");
	int temp[2*size];
	int i;
	for(i=0;i<size;i++)
	{
	//temp[i]=data[i];	
	}
	//data=temp;
	size=size*2;
	
}//end double_array()
			
			
void load_array()
{
		
	//Open input file
	fd_in=fopen("MSS_TestProblems-1.txt","r");
	
	
	//while there is another line in file
	while(fgets(buffer,100,(FILE*) fd_in)!=NULL)
	{
		printf("Loading Array....\n");
		printf("%s\n",buffer);//prints the array  ****can be removed after testing for correctness
		buffer[0]=' ';//removes the first [ 
		int data[100]; //Data array   //ONLY WORKS on arrays of 100 or less********
		
		//parse buffer into data array
		char* token;
		token=strtok(buffer,",");
		int var;
		int i=0;
		while(token !=NULL)
		{
			sscanf(token, "%d", &var);
			//printf("Number: %d\n",var);
			data[i]=var;
			i++;
			token=strtok(NULL,",");
		}
	
		//Calls to summing fuctions here
		max_sum_subArray_4(data,i);//Check this.....************************
		//Add calls to other problems using the same data set
		
		printf("***************\n\n");
	}//loop back and grab next line (data set)
	
	
	
}//end load_array()

void output_file(int array[],int max)
{
	//printf("COMPLETE!  Outputting file.....\n");
	
			

	
}





int main()
{
//testing the random function
int test_num=100000;
random_array(test_num);
return 0;//exit out	
//Stops here for runtime testing************************************	
	
fd_out=fopen("MSS_Results.txt","w");	
//lod array from file
load_array();
//preform test
//iter_sum();
//output to file
//output_file();
fclose(fd_in);
fclose(fd_out);
}
