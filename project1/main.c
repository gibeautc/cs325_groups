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


int size=100;//size of array
FILE *fd_in;
FILE *fd_out; //file discriptors for input and output files
char buffer[100];//buffer for reading from file



void max_sum_subArray_4(int array[])
{
	//for each starting location n, sum from n to count
	//track largest value of sum in sum array
	printf("Starting Sum\n");
	int count=sizeof(array);//actual count of elements
	int i;
	int sum_Array[count];//create sum array
	int n;
	for(n=0;n<count;n++)
	{
		int sum=0;
		int max=0;
		for(i=n;i<count;i++)
		{
			//printf("Made it here i=%d n=%d\n",i,n);fflush(NULL);
			sum=sum+array[i];
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
	printf("Max index is: %d with a sum of: %d\n",index,max);
}




			
//used for doubling array size
void double_array()
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
			printf("Number: %d\n",var);
			data[i]=var;
			i++;
			token=strtok(NULL,",");
		}
	
		
		
		
		//Calls to summing fuctions here
		max_sum_subArray_4(data);
		//Add calls to other problems using the same data set
		
		printf("***************\n\n");
	}//loop back and grab next line (data set)
	
	
	
}//end load_array()

void output_file()
{
	printf("COMPLETE!  Outputting file.....\n");
	fd_out=fopen("MSS_Results.txt","w");
			

	
}





int main()
{

	
	
	
//lod array from file
load_array();
//preform test
//iter_sum();
//output to file
output_file();
fclose(fd_in);
fclose(fd_out);
}
