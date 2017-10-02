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
int hitWay(unsigned int tag, unsigned int set, unsigned int **tagArray, int **lruArray, unsigned int K);
void updateOnHit(unsigned int set, int index, unsigned int K, int **lruArray);
void updateOnMiss(unsigned int tag, unsigned int set, int index, unsigned int K, unsigned int **tagArray, int **lruArray);

double missRate;
double hitCount, missCount, totalCount;



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
    }
       
   while((retVal = fscanf(fp,"%x",&i))!=EOF)
    {
        
        set = whichSet(i, numOffsetBits, numIndexBits);
        tag = tagBits(i,numOffsetBits,numIndexBits);
        hitWay(tag, set, tagArray, lruArray, K);
        
        
    }
    
    fclose(fp);
    missRate = missCount/totalCount;
    printf("%s, %d, %d, %d, %f\n",argv[4], atoi(argv[3]), K, L, missRate);
    
    
    
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

//checks if there is a hit or miss and calls appropriate functions based on result
int hitWay(unsigned int tag, unsigned int set, unsigned int **tagArray, int **lruArray, unsigned int K)
{
    totalCount++;
    
    if(K==1)
    {
        if(tagArray[set][0] ==tag)
            hitCount++;
        else
            missCount++;
        
        tagArray[set][0]=tag;
        lruArray[set][0]=0;
    }
    
    int index = -2;
    int tagArrayIndex = 0;
   
    
    for(int a = 0; a < K; a++)
    {
        if(tagArray[set][a] == tag)
        {
            hitCount++;
            tagArrayIndex = a;
            updateOnHit(set,tagArrayIndex, K, lruArray);
            return a;
        }
    }
    
    
    
        for(int i = 0; i < K; i++)
        {
            if (lruArray[set][i] == -1)
            {
                index = i;
                break;
            }
        }
    
        if (index == -2)
        {
            int max = 0;
            for(int i = 0; i < K; i++)
            {
                if(lruArray[set][i] > max)
                {
                    max = lruArray[set][i];
                    index = i;
                }
            }
        }
    
        
    updateOnMiss(tag,set,index, K, tagArray, lruArray);
    return -1;

}

//updates lru array on a hit
void updateOnHit(unsigned int set, int index, unsigned int K, int **lruArray)
{
    for(int i = 0; i < K; i++)
    {
        if(lruArray[set][i] != -1)
        {
            lruArray[set][i]++;
        }
    
    }
    
    
    lruArray[set][index] = 0;
    
    
}

//updates tag array and lru array on a cache miss
void updateOnMiss(unsigned int tag, unsigned int set, int index, unsigned int K, unsigned int **tagArray, int **lruArray)
{
    missCount++;
    for(int i = 0; i < K; i++)
    {
        if(lruArray[set][i] != -1)
        {
            lruArray[set][i]++;
        }
        
    }

    lruArray[set][index] = 0;
    tagArray[set][index] = tag;
    
}


/******helper functions******/

//returns number of sets in cache
int getNumberOfSets(int cacheSize, int blockSize, int associativity)
{
    return cacheSize/(blockSize * associativity);
    
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

