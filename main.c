#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "data_parse.h"
#include "print_model.h"
#include "modelv1.h"

int main(int argc, char const *argv[])
{
	int ii=0;
	char *fname=NULL;
	float value=0;
	problem_parameter prob_para;
	float C=1,tolerance=0.0001;

	if(argc==1){
		printf("Please specify the intput data file\nPress enter to exit");
		getchar();
		exit(0);
	}
	for(ii=1;(ii<argc) && (argv[ii][0]=='-');ii++){
		switch(argv[ii][1])
		{case 'f':ii++;fname=argv[ii];break;
		default: printf("No such command argument\n");
				 exit(0);
		}				 
	}

	if (ii>argc){
		printf("Not enough input argument\n");
		exit(0);
	}

	prob_para=data_read(fname,C,tolerance);
	svm_train(&prob_para);
    print_model(&prob_para);
    value=predict(prob_para.data_vector[0]);
    	
    printf("%d\n",predict(prob_para.data_vector[1]));

    printf("Trainning is successfull,press enter to exit\n");
    getchar();
    return 0;
}

