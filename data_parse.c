#include <stdio.h>
#include "train.h"
int *data_parse(char *fname,int *pp){
	FILE *fp;
	char ch;
	int dimension=0;
	int size=0;
	int label;
	float dat;
	char pop;
	if(fname==NULL) fname="data";
	fp=fopen(fname,"r");
	if(fp==NULL){
		printf("this is no such a file named \" %s\",press any key to exit\n", fname);
		fclose(fp);
		getchar();
		exit(0);
	}
	
		fscanf(fp,"%d",&label);
		
		if ((ch=fgetc(fp))!=':'){
			printf("there is a erro in line %d\n",size+1);
			fclose(fp);
			printf("press any key to exit\n");
			getchar();
			exit(0);
		}		
		for(int kk=0;;kk++){
			
			fscanf(fp,"%f",&dat);
			dimension++;
			ch=fgetc(fp);
			if(ch == '\n')
				break;
			else if (ch==':')
				;
		 	else{ printf("there is a erro in line %d\n",size+1);
		 		  printf("press any key to exit\n");
		 		  fclose(fp);
		 		  getchar();
		 		  exit(0);
		 		}
		}
		size++;
	

	while(!feof(fp)){
		fscanf(fp,"%d",&label);
		
		if ((ch=fgetc(fp))!=':'){
			printf("there is a erro in line %d\n",size+1);
			fclose(fp);
			exit(0);}

		for(int kk=1;kk<=dimension;kk++){
			fscanf(fp,"%f",&dat);
			ch=fgetc(fp);
			if(kk<dimension) 
			{  
				if(ch !=':'){
					printf("there is a erro in line %d\n",size+1);
					printf("press any key to exit\n");
					fclose(fp);
					getchar();
			 		exit(0);
				}
		 	}
		 	else if (kk==dimension){
		 		if(ch=='\n')
		 			break ;

		 		else if(ch==EOF){
		 			size ++;
		 			fclose(fp);
   					*pp=dimension;
    				*(pp+1)=size;
    				return;
		 		    }
		 		else {
		 			printf("there is a erro in line %d\n",size+1);
			 		fclose(fp);
			 		printf("press any key to exit\n");
			 		getchar();
		 		  	exit(0);
		 		}
		 	}
		}
		size++;

	}

	
}

problem_parameter data_read(char *fname,float C,float tolerance){
	problem_parameter prob_para;
	int data_dim[2];
	int dimension=0;
	int size=0;
	float *data_vector;
	int *label;
	int kk=0;
	float **ptarray;
    FILE *fp;
	data_parse(fname,data_dim);
	// printf("flag 1 ddebgu pace %d\n",data_dim[1] );

	fp=fopen(fname,"r");
	dimension=data_dim[0];
	size=data_dim[1];

	// printf("dim is %d\n",dimension);
	// printf("size is %d\n", size);

    data_vector=(float *)my_malloc(dimension*size*sizeof(float));
    label=(int *)my_malloc(size*sizeof(int));
	
	for(kk=0;kk<size;kk++){
		fscanf(fp,"%d",label+kk);
		for(int ii=0;ii<dimension;ii++){
			fscanf(fp,":");
			fscanf(fp,"%f",data_vector+kk*dimension+ii);
			fscanf(fp,":");
		}
		if(kk==size-1)
			break;
		else fscanf(fp,"\n");
	}	

	fclose(fp);

	ptarray=(float **)my_malloc(size*sizeof(float *));
	for(int ii=0;ii<size;ii++)
		ptarray[ii]=data_vector+ii*dimension;

 	// for (int ii=0;ii<size;ii++)
 	// 	for(int kk=0;kk<dimension;kk++)
 	// 		printf("%f\n",ptarray[ii][kk]);

	 for(int ii=0;ii<size;ii++){
	 	if(label[ii]*label[ii]!=1){
	 		printf("there is a label not in range{-1,+1} in line %d\n",ii);
	 		printf("Please press any key to exit\n");
	 		getchar();
	 		exit(0);
	 	}
	 }
	 prob_para=init_Prob_Para(ptarray,label,dimension,size,C,tolerance);

	 return prob_para;

}
