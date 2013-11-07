#ifndef _TRAIN_H_
#define _TRAIN_H_

void *my_malloc(long t);

float dot_rgb(float *x1,float *x2);
float dot_linear(float *x1,float *x2,int);
float (*dot_poduct)(float *,float *);

typedef struct problem_parameter{
	float **data_vector;   // pointer to the datavector
	int *label;
	int 	dimension;
	int 	size;
	float C;
	float tolerance;
	float *w;
	float *b;
	
	float *Erroi;
	float *alpha; 

}problem_parameter;
  
int examineExample(int i1,problem_parameter *prob_para);
int  takeStep(int i1,int i2,problem_parameter *prob_para);

problem_parameter init_Prob_Para(float **data_vector,int *label,int dimension,int size,
	float C,float tolerance);
void svm_train(problem_parameter *prob_para);

#endif 