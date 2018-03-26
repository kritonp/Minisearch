#ifndef POSTINGLIST_H
#define POSTINGLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>		    //for log(x)
#include <unistd.h> 	  //for ioclt
#include <sys/ioctl.h> 	//for ioclt


struct postingList* initList();
void pushList(struct postingList*,int);
void printList(struct postingList*);

int get_freq(struct postingList*);
int get_list_data(struct postingList*,int*,int*);

void destroyList(struct postingList* );

#endif
