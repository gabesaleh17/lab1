//
//  Lab 1.c
//  Lab 1
//
//  Created by Gabe Saleh and Cameron Weiss on 9/27/17.
//  Copyright © 2017 Gabe Saleh and Cameron Weiss. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void updateOnHit();
void updateOnMiss();
int whichSet(unsigned int address, unsigned int offsetLength, unsigned int setLength);
int tagBits(unsigned int address, unsigned int offsetLength, unsigned int setIndexLength);
int getNumberOfSets(int cacheSize, int blockSize, int associativity);
int numberOfBlocks(int cacheSize, int blockSize);
unsigned int offsetLength(int blockSize);
unsigned int setIndexLength(int numberOfSets);
int getNumberOfTagBits(int lengthOfAddress, int blockOffset, int setIndex);
unsigned int logTwo(unsigned int num);



int main(int argc, char* argv[])
{
    unsigned int **tagArray;
    int **lruArray;
    FILE *fp;
    int i;
    unsigned int retVal, K, L, C, set, offset, numberOfSets, numOffsetBits, numIndexBits, numOfTagBits, tag;
    
    //int count = 0;
    // open trace file for reading
    // K, L, and C are assigned to the 3 arguements entered
    K = atoi(argv[1]);
    L = atoi(argv[2]);
    C = logTwo(atoi(argv[3])*1000) * 2;
    fp = fopen(argv[4], "r"); //sample trace should be used as 4th arguement
    
    //getting correct numbers for sets,offset bits, and index bits
    numberOfSets = getNumberOfSets(C, L, K);
    numOffsetBits= offsetLength(L);
    numIndexBits = setIndexLength(numberOfSets);
    
    //initializign and allocating memory for tag and lru array
    tagArray = malloc(numberOfSets*sizeof(int*));
    for(int x = 0; x<numberOfSets; x++)
    {
        tagArray[x] = malloc(sizeof(int*)*K);
    }
    
    lruArray = malloc(numberOfSets*sizeof(int*));
    for(int x = 0; x<numberOfSets; x++)
    {
        lruArray[x] = malloc(sizeof(int*)*K);
    }
    
    for (int i = 0; i < numberOfSets; i++) {
        for(int j = 0; j < K; j++) {
            lruArray[i][j] = -1;
        }
        printf("\n");
    }
    
    /*for (int i = 0; i < numberOfSets; i++) {
        for(int j = 0; j < K; j++) {
            printf("%d\t",tagArray[i][j]);
        }
        printf("\n");
    }*/

    
    
   
   while((retVal = fscanf(fp,"%x",&i))!=EOF)
    {
        // read 1 line of trace file
        // output virtual address in hex
        
        //Code where we evaluate every trace line and its bits
        //
        //
        //
        //
        //
        //
        //
        ////////////////////////////////////////////////////////
        set = whichSet(i, numOffsetBits, numIndexBits);
        printf("address = %x\n",i);
        printf("in set %d \n", set);
        tag = tagBits(i,numOffsetBits,numIndexBits);
        printf("tag bits are %d \n", tag);
        
        
        
    }
    
 
    
    fclose(fp);
    printf("K=%d, L= %d, C=%d", K, L, C);
    
    
    
}
//returns index/set bits of address
int whichSet(unsigned int address, unsigned int offsetLength, unsigned int setLength)
{
    unsigned int mask = 1;
    unsigned int count = 1;
    while(count<setLength)
    {
        mask = mask + pow(2,count);
        count++;
    }
    address = address>>offsetLength;
    return address&mask;
}

//returns tag bits of address
int tagBits(unsigned int address, unsigned int offsetLength, unsigned int setIndexLength)
{
    return address >> (offsetLength + setIndexLength);
}

int hitWay(unsigned int set, unsigned int way, int *tagArray)
{
    
    if ()
    {
        
        return way;
    }
    else
    {
        
        return -1;
    }
    
    
    
}

void updateOnHit()
{
    
    
}

void updateOnMiss()
{
    
}

//helper functions

//returns number of sets in cache
int getNumberOfSets(int cacheSize, int blockSize, int associativity)
{
    return cacheSize/(blockSize * associativity);
    
}

//returns number of blocks/lines in cache
int numberOfBlocks(int cacheSize, int blockSize)
{
    return cacheSize/blockSize;
}

//returns number of offset bits
unsigned int offsetLength(int blockSize)
{
    unsigned int x = 1;
    unsigned int length = 1;
    while(x<blockSize)
    {
        x = x + pow(2,length);
        length++;
    }
    return length-1;
}

//returns number of index/set bits
unsigned int setIndexLength(int numberOfSets)
{
    unsigned int x = 1;
    unsigned int length = 1;
    while(x<numberOfSets)
    {
        x = x + pow(2,length);
        length++;
    }
    return length - 1;
}

unsigned int logTwo(unsigned int num)
{
    num |= num >> 1;
    num |= num >> 2;
    num |= num >> 4;
    num |= num >> 8;
    num |= num >> 16;
    
    return (unsigned int)(num - (num >> 1));
    
}

int getNumberOfTagBits(int lengthOfAddress, int blockOffset, int setIndex)
{
    return lengthOfAddress - offsetLength(blockOffset) - setIndexLength(setIndex);
}
