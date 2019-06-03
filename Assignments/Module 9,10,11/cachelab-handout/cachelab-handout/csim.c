#include "cachelab.h"
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <strings.h>
#include <math.h>

typedef unsigned long long int memoryAddress;

struct cacheParameter {      
		int s; 
		int b; 
		int E;  
		int hits;
		int misses;
		int evicts;
	};

struct setLine {
		int freq;
		int valid;
		memoryAddress tag;
		char *block;
	};

struct cacheSet{    
		struct setLine *lines;
	}; 

struct cache{      
		struct cacheSet *sets;
	};
	
int getEvictLine(struct cacheSet set, struct cacheParameter myParams, int *freqLines) {
	int minfreq = set.lines[0].freq;
	int maxfreq = set.lines[0].freq;
	int minIndex = 0;
	/*struct setLine line;*/
	for (int i = 1; i < myParams.E; i++) {
		if(set.lines[i].freq < minfreq) {
			/*printf("in if\n");*/
			minfreq = set.lines[i].freq;
			minIndex = i;
		}
		if(set.lines[i].freq > maxfreq) {
			/*printf("in if\n");*/
			maxfreq = set.lines[i].freq;
		}
	}
	freqLines[0] = minfreq;
	freqLines[1] = maxfreq;
	return minIndex;     
	
}
int getEmptyLine(struct cacheSet set, struct cacheParameter myParams) {
	
	struct setLine line;
	for (int i = 0; i < myParams.E; i++) {
		line = set.lines[i];
		if (line.valid == 0) {    
			return i;
		}
	}
	return -1;     
}
	
struct cache initializeCache(long numberOfSets, int numberOfLines, long sizeOfBlock) 
{    

	struct cache newCache;	 
	struct cacheSet set;
	struct setLine line;
	int i;
	int j;

	newCache.sets = (struct cacheSet*) malloc(numberOfSets * sizeof(struct cacheSet) );

	for (i = 0; i < numberOfSets; i++) 
	{        		
		set.lines =  (struct setLine *) malloc(sizeof(struct setLine) * numberOfLines);
		newCache.sets[i] = set;

		for (j = 0; j < numberOfLines; j++) 
		{	
			line.freq = 0;
			line.valid = 0;
			line.tag = 0; 
			set.lines[j] = line;	
		}
		
	} 

	return newCache;
	
}

struct cacheParameter calculateParams(struct cache myCache, struct cacheParameter myParams, memoryAddress address) {
		int i;
		int hits = myParams.hits;
		int isCacheFull = 1;
		int tagSize = (64 - (myParams.s + myParams.b));		
		unsigned long long temp = address << (tagSize);
		unsigned long long indexOfSet = temp >> (tagSize + myParams.b);
		
		memoryAddress inputTag = address >> (myParams.s + myParams.b);
		
  		struct cacheSet set = myCache.sets[indexOfSet];

		for (i = 0; i < myParams.E; i++) 	{
				
			if (set.lines[i].valid) {   					
				if (set.lines[i].tag == inputTag) { 
					myParams.hits++;
					set.lines[i].freq++;
					    
				}				


			} else if (!(set.lines[i].valid) && (isCacheFull)){
				isCacheFull = 0;
			}
			 
		}	
		if(hits == myParams.hits) {
			myParams.misses++;
		} else {
			return myParams;
		}
		
		int *freqLines = (int*) malloc(sizeof(int) * 2);
		int eLine = getEvictLine(set,myParams,freqLines);
		
		if(isCacheFull) {
			myParams.evicts++;
			
			//printf("%d\n",(eLine));
			set.lines[eLine].tag = inputTag;
			set.lines[eLine].valid = 1;
			set.lines[eLine].freq = freqLines[1] + 1;
			 
		} else {
			int emptyline = getEmptyLine(set,myParams);
			set.lines[emptyline].tag = inputTag;
			set.lines[emptyline].valid = 1;
			set.lines[emptyline].freq = freqLines[1] + 1;
		}
		free(freqLines);
		return myParams;
}

int main(int argc, char **argv)
{
    /*printSummary(0, 0, 0);
    	*/
	
	struct cacheParameter myParams;
	
	char c;
	
	char* file;
	
	while( (c=getopt(argc,argv,"s:E:b:t:")) != -1)
	{	/*printf("%c\n",c);*/
		switch(c)
		{
		case 's':
		    myParams.s = atoi(optarg);
		    break;
		case 'E':
		    myParams.E = atoi(optarg);
		    break;
		case 'b':
		    myParams.b = atoi(optarg);
		    break;
		case 't':
		    file = optarg;
		    break;
		default:
		    exit(1);
		}	
	}
	
	long numberOfSets = pow(2.0, myParams.s);
	long sizeOfBlock = pow(2.0, myParams.b);
	struct cache myCache;
	myCache = initializeCache (numberOfSets, myParams.E, sizeOfBlock);
	
	myParams.hits = 0;
	myParams.misses = 0;
	myParams.evicts = 0;
	
	char instruc;
	memoryAddress address;
	int val;
	FILE *openfile = fopen(file, "r");
	if (openfile != NULL) {
		/*printf("in if\n");*/
		while (fscanf(openfile, " %c %llx,%d", &instruc, &address, &val) == 3) {
			/*printf("in while\n");*/
			switch(instruc) {
				case 'L':
				case 'S':
					myParams = calculateParams(myCache, myParams, address);
					break;
				case 'M':
					myParams = calculateParams(myCache, myParams, address);
					myParams = calculateParams(myCache, myParams, address);	
					break;
				default:
					break;
			}
		}
	}

	/*printf("hits : %d, misses : %d, evicts : %d\n",myParams.hits, myParams.misses, myParams.evicts);*/
	printSummary(myParams.hits, myParams.misses, myParams.evicts);
	
	
    return 0;
}