#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "genann.h"

double *input, *output;
int samples;

const char *emily_data = "example/emily.data";

void load_data() {
  FILE *in=fopen("example/emily.data","r");
  if(!in) {
    printf("Could not open file: %s\n",emily_data);
    exit(1);
  }

  char line[1024];
  while(!feof(in)&&fgets(line,1024,in)) {
    samples++;
  }
  fseek(in,0,SEEK_SET);

  printf("Loading %d data points from %s\n",samples,emily_data);

  // Allocate memory for input and output data
  input=malloc(sizeof(double)*samples*12);
  output=malloc(sizeof(double)*samples*8);

  int i,j;
  for (i=0;i<samples;i++) {
    double *p=input+i*12;
    double *o=output+i*8;
    o[0]=o[1]=o[2]=o[3]=o[4]=o[5]=o[6]=o[7]=0.0;

    if (fgets(line,1024,in)==NULL) {
      perror("fgets");
      exit(1);
    }

    char *split=strtok(line,",");
    for (j=0;j<12;j++) {
      p[j]=atof(split);
      split=strtok(0,",");
    }
    for(j=0;j<8;j++) {
      o[j]=atof(split);
      split=strtok(0,",");
    }
  }
  
  fclose(in);
}

int main(int argc, char *argv[]) {
  printf("GENANN example 5.\n");
  printf("Train an ANN to predict multiple floats\n");

  load_data();

  /* 12 inputs
   * 1 hidden layer of 6 neurons
   * 8 outputs
   */
  genann *ann=genann_init(12,1,6,8);

  int i,j;
  int loops=1000;
  /* Train with backprop */
  printf("Training for %d loops over data.\n",loops);
  for (i=0;i<loops;i++) {
    for (j=0;j<samples;j++) {
      genann_train(ann,input+j*12,output+j*8,.01);
    }
  }

#define EPS 0.01f
  int correct[8]={0,0,0,0,0,0,0,0};
  for (j=0;j<samples;j++) {
    const double *guess=genann_run(ann,input+j*12);
    for (i=0;i<8;i++) {
      if (output[j*8+i]-guess[i]<EPS) ++correct[i];
    }
  }

  printf("%d/%d,%d/%d,%d/%d,%d/%d,%d/%d,%d/%d,%d/%d,%d/%d correct.\n",
      correct[0],samples,correct[1],samples,correct[2],samples,
      correct[3],samples,correct[4],samples,correct[5],samples,
      correct[6],samples,correct[7],samples);

  genann_free(ann);
}
