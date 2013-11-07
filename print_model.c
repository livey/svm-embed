#include <stdio.h>
#include "train.h"
void print_model(problem_parameter *prob_para){
	int N;
	float b;
	FILE *fp;
	int ii;
	b=*prob_para->b;
	N=prob_para->dimension;
	fp=fopen("model.h","w+");
	fprintf(fp,"#ifndef _MODEL_H\n#define _MODEL_H\n");
	fprintf(fp,"int predict(float *vector){\n");
	fprintf(fp, "const int dimension=%d;\n",N);
	fprintf(fp, "const float weight[%d]={\n",N);
	for(ii=0;ii<N-1;ii++)
		fprintf(fp,"%f,",prob_para->w[ii]);

    // printf("%f\n",prob_para->w[1]);
    // printf("ii is %d\n",ii );
	fprintf(fp, "%f};\n",prob_para->w[ii]);
	fprintf(fp,"const float biase=%f;\n",b );

	
	fprintf(fp, "int kk=0;\n");
	// fprintf(fp, "int label;\n");
	fprintf(fp, "float value=0;\n");
	fprintf(fp, "int NN=%d;\n",N);
	fprintf(fp, "for(kk=0;kk<%d;kk++)\n",N );
	fprintf(fp, " value+=weight[kk]*vector[kk];\n");
	fprintf(fp, "value=value-biase;\n");
	fprintf(fp, "if (value>0) \n" );
	fprintf(fp, "return 1;\n" );
	fprintf(fp, "else return -1;}\n" );
	fprintf(fp,"#endif\n");
	fclose(fp);
}