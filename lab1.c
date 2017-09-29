//
//  Lab 1.c
//  Lab 1
//
//  Created by Gabe Saleh on 9/27/17.
//  Copyright © 2017 Gabe Saleh. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void updateOnHit();
void updateOnMiss();
int whichSet(unsigned int address);
int tagBits(unsigned int address, int numberOfTag);
int hitWay();
int getNumberOfSets(int cacheSize, int blockSize, int associativity);
int numberOfBlocks(int cacheSize, int blockSize);
unsigned int OffsetLength(int blockSize);
unsigned int setIndexLength(int numberOfSets);
int getNumberOfTagBits(int lengthOfAddress, int blockOffset, int setIndex);



int main(void)
{
    FILE *fp;
    int i;
    unsigned int retVal;
    // open trace file for reading
    
    fp = fopen("sampleTrace.txt", "r");
    
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
        
        printf("%x\n",i);

    }
    fclose(fp);
    
    
    
    
}

int whichSet(unsigned int address)
{
    return 1;
}

int tagBits(unsigned int address, int numberOfTag)
{
    return 1;
}

int hitWay()
{
    int a = 1;
    if (a == 1)
    {
        updateOnHit();
        return a;
    }
    else
    {
        updateOnMiss();
        return 0;
    }
    
    
    return 1;
}

void updateOnHit()
{
    
}

void updateOnMiss()
{
    
}

//helper functions
int getNumberOfSets(int cacheSize, int blockSize, int associativity)
{
    return cacheSize/(associativity*blockSize);
}

int numberOfBlocks(int cacheSize, int blockSize)
{
    return cacheSize/blockSize;
}

unsigned int OffsetLength(int blockSize)
{
    return (unsigned)(blockSize >> 1);
}

unsigned int setIndexLength(int numberOfSets)
{
    return (unsigned)(numberOfSets >> 1);
}

int getNumberOfTagBits(int lengthOfAddress, int blockOffset, int setIndex)
{
    return lengthOfAddress - OffsetLength(blockOffset) - setIndexLength(setIndex);
}


