svm-embed support vector machine for embedded system. 

Svm_embed is a simplified vector machine for embedded systems. In such systems, the computing resources like RAM, ROM and Computing, are strictly constrained. Sometimes we attempt to do some simple classifications in such embedded systems. For example, we detect if the input signal is a sine wave or a square wave. Svm_embed is the right choice. Svm_embed performs in the off-line training stage, after that you will get an training model. That is, it is a vector indicating the separating hyper plane. In the final step, it automatically generates the model.h file, which has a predicting function. You just need to simply include the model.h file in your program and happily use it. In consideration of computing and memory resources, I just implement the linear kernel. I believe this is the best choice for embedded systems.

## Usage:
------
The command line -f data 
Here,data stands for the training datasets file. In the later version,some more features will be added in.

Data sets can be any name,the data form is specified as below.

Label:value1:value2:....:valueN 

each line ended up with a 'enter' symbol, except the last line.

Finally,just include the "model.h" file in your program. 
## Reference
[1]Cortes, Corinna, and Vladimir Vapnik. "Support vector machine." Machine learning 20.3 (1995): 273-297.     
[2]Suykens, Johan AK, and Joos Vandewalle. "Least squares support vector machine classifiers." Neural processing letters 9.3 (1999): 293-300.   
</br>[3]Keerthi, S. Sathiya, et al. "Improvements to Platt's SMO algorithm for SVM classifier design." Neural Computation 13.3 (2001): 637-649.
