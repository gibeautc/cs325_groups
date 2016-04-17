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
int time_test;

//still need to do
//add timing functions so each problem can be tracked for time based on size of array
//dynamic array functions so large arrays can be used
//ability to generate large arrays



//Not being used************************************
void max_sum_subArray_2(int array[],int s)
{
	if(time_test==0)
	{
		printf("Starting Sum2\n");
	}
	else
	{
		fprintf(fd_out,"Running Algorthim 2\n");
	}
	int count=s;//actual count of elements
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
	//*************End of algorthm, following code is printing and timing 
	end=time(NULL);
	if(time_test==0)
	{
		printf("Starting index is: %d with a sum of: %d\n",index,max);
		printf("In time: %d\n",((int) end-(int)start));
	}
	else
	{
		fprintf(fd_out,"Starting index is: %d with a sum of: %d\n",index,max);
		fprintf(fd_out,"[");
		int checksum=max-array[index];
		while(checksum!=0)
		{
			index++;
			checksum-=array[index];
			fprintf(fd_out," %d,",array[index-1]);
		}
		fprintf(fd_out," %d]\n\n",array[index]);
	}
}


void max_sum_subArray_1(int array[],int s)
{
	//Sum entire array from index 0 to n-1
	//each iteration after that, subtract i
	int count=s;//actual count of elements
	if(time_test==0)
	{
		printf("Starting Sum1\n");
	}
	else
	{
		fprintf(fd_out,"Running Algorthim 1\n");
	}
	int i;
	int n;
	int j;
	time_t start,end;
	start=time(NULL);
	int max=0;
	int sum;
	int start_i,end_i;//index of start and end
	//sums entire array
		
	for(i=0;i<count-1;i++)
	{
		for(j=i;j<count;j++)
		{
			sum=0;
			for(n=i;n<=j;n++)
			{
				sum=sum+array[n];
				if(sum>max){max=sum;start_i=i;end_i=n;}
			}
		}
	}
	
	
	//************END of algorthm, following code is printing and time keeping*****
	end=time(NULL);
	
	if(time_test==0)
	{//Testing for time
	printf("Start: %d   End: %d   with a sum of: %d\n",start_i,end_i,max);
	printf("In time: %d\n",((int) end-(int)start));
	}
	else
	{//outputing to file
		fprintf(fd_out,"Start: %d   End: %d   with a sum of: %d\n",start_i,end_i,max);
		fprintf(fd_out,"[");
		for(n=start_i;n<end_i;n++)
		{
			fprintf(fd_out," %d,",array[n]);
		}
		fprintf(fd_out," %d]\n\n",array[end_i]);
	}
}


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
	
	max_sum_subArray_1(rand_array,size);
	//max_sum_subArray_2(rand_array,size);
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
	fprintf(fd_out,"********Algorthim 1 and 2***********\n\n");
	
	//while there is another line in file
	while(fgets(buffer,100,(FILE*) fd_in)!=NULL)
	{
		if(time_test==0)
		{
			printf("Loading Array....\n");
			printf("%s\n",buffer);//prints the array  ****can be removed after testing for correctness
		}
		else
		{
			fprintf(fd_out,"\n\nLoading Array....\n");
			fprintf(fd_out,"%s\n",buffer);//prints the array  ****can be removed after testing for correctness
		}
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
		max_sum_subArray_1(data,i);//Check this.....************************
		max_sum_subArray_2(data,i);
		//Add calls to other problems using the same data set
		
	}//loop back and grab next line (data set)
	
	
	
}//end load_array()

void output_file(int array[],int max)
{
	//printf("COMPLETE!  Outputting file.....\n");
	
			

	
}





int main()
{
//Used for time testing

//change to 0 for time testing, or 1 for file output
time_test=1;

if(time_test==0)
{
	int test;
	for(test=1;test<11;test++)
	{
		int test_num=(test*500)+1500;
		random_array(test_num);
		printf("\n\n");
	}
	return 0;//exit out	
}
	
fd_out=fopen("MSS_Results.txt","a+");	
//lod array from file
load_array();
fclose(fd_in);
fclose(fd_out);
}
