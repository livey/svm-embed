main:data_parse.c data_parse.h print_model.c print_model.h train.c train.h main.c
	gcc train.c print_model.c main.c data_parse.c -o main -w -std=c99