#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	FILE* fp;
	FILE* fp1;
	FILE* fp2;
	int rval;
	char *str;
	int tval1, tval2;
	size_t num_of_bytes = 1;
	float percentage=1;
	int temp;
	int temp1;
	long int period = 2000;
//	sscanf(argv[1],"%f",&percentage);
	while(1) 
	{

		fp1=fopen("/sys/class/gpio/gpio956/value", "r");
		if(fp1==NULL)
			puts("Problem prvi otvaranju 1. fajla");

		str=(char*)malloc(num_of_bytes+1);
		getline(&str, &num_of_bytes+1, fp1);

		if(fclose(fp1))
			puts("Problem pri zatvaranju 1. fajla");

		sscanf(str, "%d", &tval1);
		free(str);

		fp2=fopen("/sys/class/gpio/gpio957/value", "r");
		if(fp2==NULL)
			puts("Problem prvi otvaranju 2. fajla");

		str=(char*)malloc(num_of_bytes+1);
		getline(&str, &num_of_bytes+1, fp2);

		if(fclose(fp2))
			puts("Problem pri zatvaranju 2. fajla");

		sscanf(str, "%d", &tval2);
		free(str);


		fp = fopen("/proc/myled", "w");
		if(fp == NULL)
		{
			printf("Cannot open /proc/myled for write\n");
			return -1;
		}
		fputs("0xff\n", fp);
		fclose(fp);
		if(tval1==1 && temp==1 ){

			temp=0;
			percentage=percentage-0.2;
				if(percentage<0){
					percentage=0;
				}

		}
		else if(tval1==0){
		temp=1;
		}
		usleep(percentage*period);


		fp = fopen("/proc/myled", "w");
		if(fp == NULL)
		{
		printf("Cannot open /proc/myled for write\n");
			return -1;
		}
		fputs("0x00\n", fp);
		fclose(fp);
		if(tval2==1 && temp1==1){
			temp1=0;
			percentage=percentage+0.2;
			if(percentage>1){
				percentage=1;
			}
		}
		else if(tval2==0){
			temp1=1;
		}

		usleep((1-percentage)*period);
	}
	return 0;
}

