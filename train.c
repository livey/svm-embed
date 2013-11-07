#include <stdio.h>
#include <math.h> 
#include "train.h"
float learned_fun(float *w,float b,float *x,int );
int try_argmaxE1_E2(int i1,float E1,problem_parameter *prob_para);
void *my_malloc(long t ){

	void *ptr;
	ptr=(void *)malloc(t);
	if(ptr==NULL)
		{printf("erro,out of memery!\n");
		exit(1);
		}
	else return ptr;	
}

float dot_rgb(float *x1,float *x2){
	float y;
	
	return 0;
}

float dot_linear(float *x1,float *x2,int m){
	float y=0,kk=0;
	for (kk=0;kk<m;kk++,x1++,x2++)
		y+=(*x1)*(*x2);
	return y;
}

int examineExample(int i1,problem_parameter *prob_para){
	float y1,alpha1,E1,r1;
	y1=prob_para->label[i1];
	alpha1=prob_para->alpha[i1];

	if (alpha1>0 && alpha1<prob_para->C)
		E1=prob_para->Erroi[i1];
	else
		E1=learned_fun(prob_para->w,*prob_para->b,prob_para->data_vector[i1],
            prob_para->dimension)-y1;

	r1=y1*E1;

	if((r1 < -prob_para->tolerance && alpha1 < prob_para->C)
		|| (r1>prob_para->tolerance && alpha1>0)){

		if(try_argmaxE1_E2(i1,E1,prob_para)) 
			return 1;
		else if (try_iter_non_boundary(i1,prob_para))
			return 1;
		else if (try_iter_all(i1,prob_para))
			return 1;

	}

	return 0; // all failed 

}

float learned_fun(float *w,float b,float *x,int m){

	  float y=0;
	  for(int kk=0;kk<m;kk++)
	  	y+=w[kk]*x[kk];
	  return y-b;
}

int try_argmaxE1_E2(int i1,float E1,problem_parameter *prob_para){

	int k,i2;
	float tmax;
    
	for(i2=-1,tmax=0,k=0;k<prob_para->size;k++)
		if(prob_para->alpha[k]>0 && prob_para->alpha[k]<prob_para->C){
			float E2,temp;
			E2=prob_para->Erroi[k];
			temp=fabs(E1-E2);
			if(temp>tmax){
				tmax=temp;
				i2=k;
			}
		}

	if(i2>=0){
		if(takeStep(i1,i2,prob_para))
			return 1;
	}	
	return 0;
}


int try_iter_non_boundary(int i1,problem_parameter *prob_para){
	int k,k0;
	int i2;
	srand((unsigned)time(NULL));
	for (k0=rand()%prob_para->size,k=k0;k<prob_para->size+k0;k++){
		i2=k%prob_para->size;
		if(prob_para->alpha[i2]>0 && prob_para->alpha[i2]<prob_para->C){
			if(takeStep(i1,i2,prob_para))
				return 1;
		}
	}
	return 0;
}
int try_iter_all(int i1,problem_parameter *prob_para){
	int k,k0;
	int i2;
	srand((unsigned)time(NULL));
	for (k0=rand()%prob_para->size,k=k0;k<prob_para->size+k0;k++){
		i2=k%prob_para->size;
		if(takeStep(i1,i2,prob_para))
				return 1;
	}
	
	return 0;
}


int  takeStep(int i1,int  i2,problem_parameter *prob_para){
	int y1,y2,s;
	float alpha1,alpha2;
	float a1,a2;
	float E1,E2,L,H,k11,k22,k12,eta,Lobj,Hobj;
	float delta_b;
    float tolerance;
    tolerance=prob_para->tolerance;
	if(i1==i2) return 0;

	// initial
	// look up alpha1,y1,alpha2,y2,e1,e2.
	alpha1=prob_para->alpha[i1];
 	y1=prob_para->label[i1];

 	if(alpha1>0 && alpha1<prob_para->C)
 		E1=prob_para->Erroi[i1];
 	else E1=learned_fun(prob_para->w,*prob_para->b,prob_para->data_vector[i1],prob_para->dimension)-y1;
 	alpha2=prob_para->alpha[i2];
 	y2=prob_para->label[i2];
 	if(alpha2>0 && alpha2<prob_para->C)
 		E2=prob_para->Erroi[i2];
 	else 
 		E2=learned_fun(prob_para->w,*prob_para->b,prob_para->data_vector[i2],prob_para->dimension)-y2;
  
   	s=y1*y2;

    // compute L,H
    if(y1==y2){
    	float gamma = alpha1+alpha2;
    	if(gamma>prob_para->C){
    		L=gamma-prob_para->C;
    		H=prob_para->C;
    	}
    	else {L=0;H=gamma;}
    }
    else {
    	float gamma=alpha1-alpha2;
    	if(gamma>0){
    		L=0;
    		H=prob_para->C-gamma;
    	}
    	else {L=-gamma;H=prob_para->C;}
    }	
    

    // compute eta
    k11=dot_linear(prob_para->data_vector[i1],prob_para->data_vector[i1],
                    prob_para->dimension);  
    k12=dot_linear(prob_para->data_vector[i1],prob_para->data_vector[i2],
                    prob_para->dimension);
    k22=dot_linear(prob_para->data_vector[i2],prob_para->data_vector[i2],
                    prob_para->dimension);
    eta=2*k12-k11-k22;

    if(eta<0){
    	a2=alpha2+y2*(E2-E1)/eta;
    	if(a2<L)
    		a2=L;
    	else if(a2>H)
    		a2=H;
    }
    else{
    	// compute Lobj,Hobj;
    	float c1=eta/2;
    	float c2=y2*(E2-E1)-eta*alpha2;
    	Lobj= c1*L*L+c2*L;
    	Hobj= c1*H*H+c2*H;
    	if(Lobj>Hobj+tolerance)
    	a2=L;
    	else if (Lobj<Hobj-tolerance)
    	a2=H;
    	else a2=alpha2;	
    }
    if(fabs(a2-alpha2)<tolerance*(a2+alpha2+tolerance))
    	return 0;
    a1=alpha1 - s*(a2-alpha2);
    if(a1<0){
    	a2+=s*a1;
    	a1=0;
    }
    else if (a1>prob_para->C){
    	float t=a1-prob_para->C;
    	a2+=s*t;
    	a1=prob_para->C;
    }


    // update threshold 
    if(1){
    	float b1,b2,bnew;
    	if(a1>0 && a1<prob_para->C)
    		bnew=*prob_para->b+E1+y1*(a1-alpha1)*k11 + y2*(a2-alpha2)*k12;
    	else {
    		if(a2>0 && a2<prob_para->C)
    			bnew = *prob_para->b+E2+y1*(a1-alpha1)*k12+y2*(a2-alpha2)*k22;
    		else {
    			b1=*prob_para->b+E1+y1*(a1-alpha1)*k11 + y2*(a2-alpha2)*k12;
    			b2=*prob_para->b+E2+y1*(a1-alpha1)*k12 + y2*(a2-alpha2)*k22;
    			bnew=(b1+b2)/2;
    		}
    	}
    	delta_b=bnew-*prob_para->b;
    	*prob_para->b = bnew;
    }

   // update weight vector 
    // for linear kenner
    if(1) {
    	float t1=y1*(a1 - alpha1);
    	float t2=y2*(a2 - alpha2);
    	for(int ii=0;ii<prob_para->dimension;ii++){
    		prob_para->w[ii]=t1*prob_para->data_vector[i1][ii]+
            t2*prob_para->data_vector[i2][ii]+prob_para->w[ii]; 
    	}
    }
    
    if(1){
    	float t1=y1*(a1-alpha1);
    	float t2=y2*(a2-alpha2);
    	for(int kk=0;kk<prob_para->dimension;kk++){
    		if(0<prob_para->alpha[kk] && prob_para->alpha[kk]<prob_para->C)
    			prob_para->Erroi[kk]=t1*dot_linear(prob_para->data_vector[i1],prob_para->data_vector[kk],
                                                    prob_para->dimension)
    		+t2*dot_linear(prob_para->data_vector[i2,kk],prob_para->data_vector[i2,kk],
                            prob_para->dimension)-delta_b;

    	prob_para->Erroi[i1]=0;
    	prob_para->Erroi[i2]=0;	
    	}
    }

    prob_para->alpha[i1]=a1;
    prob_para->alpha[i2]=a2;
    return 1;
}


 problem_parameter init_Prob_Para(float **data_vector,int *label,int dimension,int size,
    float C,float tolerance ){
    
    problem_parameter prob_para;
    prob_para.data_vector  =data_vector;
    prob_para.label        =label;
    prob_para.dimension    =dimension;
    prob_para.size         =size;
    prob_para.w            =(float *)my_malloc(dimension*sizeof(float));
    prob_para.b            =(float *)my_malloc(sizeof(float));
    prob_para.C            =C;
    prob_para.tolerance    =tolerance;
    prob_para.Erroi        =(float *)my_malloc(size*sizeof(float));
    prob_para.alpha        =(float *)my_malloc(size*sizeof(float));

    *prob_para.b=0;
    for (int jj=0;jj<size;jj++){
       prob_para.w[jj]=0;
       prob_para.Erroi[jj]=0;
       prob_para.alpha[jj]=0;

   }

   return prob_para;
}


void svm_train(problem_parameter *prob_para){
 int examineall=1;
 int numChanged=0;
    while(numChanged||examineall){
        numChanged=0;

        if(examineall){
            // printf("goes flag 1 \n");
            for(int k=0;k<prob_para->size;k++){
                numChanged+=examineExample(k,prob_para);

                // printf("flag2\n");
            }
            // printf("numChanged %d examineall %d \n",numChanged,examineall );
        }
        else {
            for(int k=0;k<prob_para->size;k++){
                if(prob_para->alpha[k]!=0 && 
                    prob_para->alpha[k]!=prob_para->C)
                    numChanged+=examineExample(k,prob_para);
        }       }

        if(examineall)
            examineall=0;
        else if(numChanged==0)
            examineall=1;   
        
        
    }

    // free the space // not free the alpha space ,because of later version
    free(prob_para->Erroi);
    prob_para->Erroi=NULL;
}