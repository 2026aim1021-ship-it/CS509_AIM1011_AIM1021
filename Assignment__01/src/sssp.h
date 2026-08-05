#ifndef SSSP_H
#define SSSP_H

#define mV 100
#define mE 100
#define INF 1000000000

extern int V, E, source;

void readGraph(char *filename);
void makeCSR();
void dijkstra();
void printDistance();

#endif