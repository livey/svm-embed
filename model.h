#ifndef _MODEL_H
#define _MODEL_H
int predict(float *vector){
const int dimension=2;
const float weight[2]={
-0.315388,-0.714645};
const float biase=-0.952848;
int kk=0;
float value=0;
int NN=2;
for(kk=0;kk<2;kk++)
 value+=weight[kk]*vector[kk];
value=value-biase;
if (value>0) 
return 1;
else return -1;}
#endif
