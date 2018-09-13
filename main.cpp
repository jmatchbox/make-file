#include <iostream>
#include <direct.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define ONE_FILE_SIZE  1024*10//1024*1024
unsigned char buffer[ONE_FILE_SIZE];
#define cTOTAL_SIZE 100*1024  // 200GB

/* C:\Users\matchboxkuo\Desktop\1MB.JPG (2018/5/3 ¤U¤È 02:14:54)
   StartOffset: 00000000, EndOffset: 000FE385, Length: 000FE386 */

/* C:\Users\matchboxkuo\Desktop\4MB.JPG (2017/1/1)
   StartOffset: 00000000, EndOffset: 003E7F82, Length: 003E7F83 */


void random_buff(void)
{
	unsigned long i;
	
	for(i = 0; i < ONE_FILE_SIZE; i++)
    {
    	buffer[i] = (unsigned char)(rand() & 0xFF);
	}
}
int main(int argc, char** argv) {
	
    unsigned long i,j,k,l,sizeCnt;
    unsigned int foldernumber[30];
    unsigned char folderNameLength[30];
    char folderpathTemp[256];
    char folderpathTemp2[256];
    char folderpathInit[256];
    unsigned int EachFolderFileNumber;
    unsigned long TotalFileNumber;
    unsigned int TotalFolderNumber=0,FloderCnt;
    char name[64];
    int fileSize;
    
    FILE *fp;
    
    unsigned char folder[256];
    
    //folderpath[0] = argv[1][0]; // device 
    i = 3;
    printf("argc=%d\r\n",argc);
    while(i < argc)
    {
    	//printf("argv[i] = %s",argv[i]);
		foldernumber[i-3] = atoi(argv[i]);
		printf("foldernumber[i-3] = %d",foldernumber[i-3]);
    	i++;
	}
	i = 0;
	while(i < argc-3)
	{
		TotalFolderNumber += foldernumber[i];
		i++;
	}
	fileSize = atoi(argv[2]);
	TotalFileNumber = cTOTAL_SIZE/fileSize;
	printf("Total Folder Number=%d\r\n",TotalFolderNumber);
	printf("file Size=%dMB\r\n",fileSize);
	printf("Total file number=%d\r\n",TotalFileNumber);
	srand(time(NULL));
	if(TotalFolderNumber != 0)
	{
		EachFolderFileNumber = TotalFileNumber/TotalFolderNumber;
	}
	else
	{
		EachFolderFileNumber = TotalFileNumber;
	}
    printf("Each Folder File Number=%d\r\n",EachFolderFileNumber);
    sprintf(folderpathInit, "%c:\\folder",argv[1][0]);
    //random_buff();
	l = 0;
	FloderCnt = 0;
	if(TotalFolderNumber != 0)
	{
    	for(i=0; i< argc-3; i++)
    	{
    		if(i == 0)
    		{
    			strcpy(folderpathTemp, folderpathInit);
    	    	sprintf(folderpathTemp2, "_%X",i);
			}
			else
			{
				//strcat(folderpathTemp, "\\folder");
				sprintf(folderpathTemp2, "_%X",i);
			}
			
    	    strcat(folderpathTemp, folderpathTemp2);
    	    for(j=0; j < foldernumber[i]; j++)
    	    {
    	        k = strlen(folderpathTemp);
    	        sprintf(folderpathTemp2, "_%03X",FloderCnt);
    	        if(j == 0)
    	        {
    	        	strcat(folderpathTemp, folderpathTemp2);
				}
				else
				{
					strcpy(&folderpathTemp[k-4], folderpathTemp2);
				}
				//printf("k=%d",k);
    	        //folderpathTemp[k-1] = j + '0';
    	        //strcpy(folderpath[i*j],folderpathTemp);
    			_mkdir(folderpathTemp);
    			FloderCnt++;
    			printf("%s\r\n",folderpathTemp);
    	        for(k=0; k < EachFolderFileNumber; k++)
    	        {
    	            sprintf(name, "\\file_%08d.bin", l);
    	            strcpy(folderpathTemp2, folderpathTemp);
    	            strcat(folderpathTemp2, name);
    	            printf("%s\r\n",folderpathTemp2);
    	            fp = fopen(folderpathTemp2, "wb");
    	            sizeCnt = 0;
    	            for(sizeCnt = 0; sizeCnt<fileSize; sizeCnt++)
    	        	{
    	        		fwrite(buffer, sizeof(buffer), 1, fp);
    				}
                    fclose(fp);
                    l++;
    	        }
    	        random_buff();
    	    }
    	    strcat(folderpathTemp, "\\folder");
    	}
    }
    else
    {
        /*if(fileSize == 1)
        {
        	buffer = data1mb;
            i = sizeof(data1mb);
		}
		else
		{
			buffer = data4mb;
			i = sizeof(data4mb);
		}*/
		for(k=0; k < EachFolderFileNumber; k++)
        {
            sprintf(folderpathTemp, "%c:\\",argv[1][0]);
            sprintf(name, "file_%08d.jpg", l);
            strcat(folderpathTemp, name);
            printf("%s\r\n",folderpathTemp);
            fp = fopen(folderpathTemp, "wb");
            sizeCnt = 0;
            for(sizeCnt = 0; sizeCnt<fileSize; sizeCnt++)
        	{
        		fwrite(buffer, sizeof(buffer), 1, fp);
			}
            fclose(fp);
            l++;
        }
    }
//	sprintf(folderpath[0], "%c:\\folder_%d",argv[1][0] ,rand());
//	_mkdir(folderpath[0]);
//	strcat(folderpath[0], "\\floder");
//	//sprintf(folderpath[0], "%c:\\folder_%d\bbc",argv[1][0] ,rand());
//	_mkdir(folderpath[0]);
//	sprintf(name, "\\file_%08d.bin", 33);
//	strcat(folderpath[0], name);
//	fp = fopen(folderpath[0], "wb");
//	fwrite(buffer, 1, sizeof(buffer), fp);
//    fclose(fp);
/*	
	l = 0;
	for(i=0; i< argc; i++)
	{
	    for(j=0; j < foldernumber[i]; j++)
	    {
	        for(k=0; k < EachFolderFileNumber; k++)
	        {
	            sprintf(name, "file_%08d.bin", l);
	            strcat(folderpathTemp, name);
	            fp = fopen(folderpathTemp, "wb");
	            fwrite(buffer, 1, sizeof(buffer), fp);
                fclose(fp);
	        }
	        random_buff();
	    }
	}*/
/*    
    for(i=0; i<1024*128; i++)
    {
        sprintf(name, "file_%08d.bin", i);
        fp = fopen(name, "wb");
        fwrite(buffer, 1, sizeof(buffer), fp);
        fclose(fp);
    }  
 */   
    printf("gen end \n");
    system("pause");
	return 0;
}
