#include <stdio.h>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <string.h>
#include <ctime>
#include <time.h>
#include <iterator>
#include <math.h>
#include <vector>

#include "CMSketch.h"
#include "CUSketch.h"
#include "CSketch.h"
#include "ASketch.h"

#include "PCMSketch.h"
#include "PCUSketch.h"
#include "PCSketch.h"
#include "PASketch.h"

using namespace std;


char * filename_stream = "u1";

char insert[32000000][14];
char query[20000000][14];


unordered_map<string, int> unmp;

#define testcycles 10


int main(int argc, char** argv)
{
    if(argc > 2)
    {
        filename_stream = argv[1];
    }

    unmp.clear();
    int val;


    double memory = atoi(argv[2]) * 100;//KB
    int word_size = 64;


    int w = memory *  1024 * 8.0 / COUNTER_SIZE;
    int w_p = memory * 1024 * 8.0 / (word_size * 2);

    printf("\n******************************************************************************\n");
    printf("Evaluation starts!\n\n");

    
    CMSketch *cmsketch;
    CUSketch *cusketch;
    CSketch *csketch;
    ASketch *asketch;

    PCMSketch *pcmsketch;
    PCUSketch *pcusketch;
    PCSketch *pcsketch;
    PASketch *pasketch;



    char _temp[200], temp2[200];
    int t = 0;

    int package_num = 0;


    FILE *file_stream = fopen(filename_stream, "r");

    // while(fgets(insert[package_num], 100, file_stream) != NULL)
    while(fread(insert[package_num], 8, 1, file_stream))
    {
        unmp[string(insert[package_num])]++;

        package_num++;

        if(package_num == MAX_INSERT_PACKAGE)
            break;
    }
    fclose(file_stream);




    
    printf("dataset name: %s\n", filename_stream);
    printf("total stream size = %d\n", package_num);
    printf("distinct item number = %d\n", unmp.size());
    
    int max_freq = 0;
    unordered_map<string, int>::iterator it = unmp.begin();

    for(int i = 0; i < unmp.size(); i++, it++)
    {
        strcpy(query[i], it->first.c_str());

        int temp2 = it->second;
        max_freq = max_freq > temp2 ? max_freq : temp2;
    }
    printf("max_freq = %d\n", max_freq);
    
    printf("\n*************************************\n\n");



/********************************insert*********************************/

    timespec time1, time2;
    long long resns;




    clock_gettime(CLOCK_MONOTONIC, &time1);
    for(int t = 0; t < testcycles; t++)
    {
        cmsketch = new CMSketch(w / LOW_HASH_NUM, LOW_HASH_NUM);
        for(int i = 0; i < package_num; i++)
        {
            cmsketch->Insert(insert[i]);
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &time2);
    resns = (long long)(time2.tv_sec - time1.tv_sec) * 1000000000LL + (time2.tv_nsec - time1.tv_nsec);
    double throughput_cm = (double)1000.0 * testcycles * package_num / resns;
    printf("throughput of CM (insert): %.6lf Mips\n", throughput_cm);
    
/*

    clock_gettime(CLOCK_MONOTONIC, &time1);
    for(int t = 0; t < testcycles; t++)
    {
        pcmsketch = new PCMSketch(w_p, LOW_HASH_NUM, word_size);
        for(int i = 0; i < package_num; i++)
        {
            pcmsketch->Insert(insert[i]);
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &time2);
    resns = (long long)(time2.tv_sec - time1.tv_sec) * 1000000000LL + (time2.tv_nsec - time1.tv_nsec);
    double throughput_pcmsketch = (double)1000.0 * testcycles * package_num / resns;
    printf("throughput of PCM (insert): %.6lf Mips\n\n", throughput_pcmsketch);
    




    clock_gettime(CLOCK_MONOTONIC, &time1);
    for(int t = 0; t < testcycles; t++)
    {
        cusketch = new CUSketch(w / LOW_HASH_NUM, LOW_HASH_NUM);
        for(int i = 0; i < package_num; i++)
        {
            cusketch->Insert(insert[i]);
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &time2);
    resns = (long long)(time2.tv_sec - time1.tv_sec) * 1000000000LL + (time2.tv_nsec - time1.tv_nsec);
    double throughput_cu = (double)1000.0 * testcycles * package_num / resns;
    printf("throughput of CU (insert): %.6lf Mips\n", throughput_cu);
*/   

    clock_gettime(CLOCK_MONOTONIC, &time1);
    for(int t = 0; t < testcycles; t++)
    {
        pcusketch = new PCUSketch(w_p, LOW_HASH_NUM, word_size);
        for(int i = 0; i < package_num; i++)
        {
            pcusketch->Insert(insert[i]);
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &time2);
    resns = (long long)(time2.tv_sec - time1.tv_sec) * 1000000000LL + (time2.tv_nsec - time1.tv_nsec);
    double throughput_pcusketch = (double)1000.0 * testcycles * package_num / resns;
    printf("throughput of PCU (insert): %.6lf Mips\n\n", throughput_pcusketch);




/*
    clock_gettime(CLOCK_MONOTONIC, &time1);
    for(int t = 0; t < testcycles; t++)
    {
        csketch = new CSketch(w / LOW_HASH_NUM, LOW_HASH_NUM);
        for(int i = 0; i < package_num; i++)
        {
            csketch->Insert(insert[i]);
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &time2);
    resns = (long long)(time2.tv_sec - time1.tv_sec) * 1000000000LL + (time2.tv_nsec - time1.tv_nsec);
    double throughput_c = (double)1000.0 * testcycles * package_num / resns;
    printf("throughput of C (insert): %.6lf Mips\n", throughput_c);


    clock_gettime(CLOCK_MONOTONIC, &time1);
    for(int t = 0; t < testcycles; t++)
    {
        pcsketch = new PCSketch(w_p, LOW_HASH_NUM, word_size);
        for(int i = 0; i < package_num; i++)
        {
            pcsketch->Insert(insert[i]);
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &time2);
    resns = (long long)(time2.tv_sec - time1.tv_sec) * 1000000000LL + (time2.tv_nsec - time1.tv_nsec);
    double throughput_pcsketch = (double)1000.0 * testcycles * package_num / resns;
    printf("throughput of PC (insert): %.6lf Mips\n\n", throughput_pcsketch);


    



    clock_gettime(CLOCK_MONOTONIC, &time1);
    for(int t = 0; t < testcycles; t++)
    {
        asketch = new ASketch(w / LOW_HASH_NUM, LOW_HASH_NUM);
        for(int i = 0; i < package_num; i++)
        {
            asketch->Insert(insert[i]);
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &time2);
    resns = (long long)(time2.tv_sec - time1.tv_sec) * 1000000000LL + (time2.tv_nsec - time1.tv_nsec);
    double throughput_a = (double)1000.0 * testcycles * package_num / resns;
    printf("throughput of A (insert): %.6lf Mips\n", throughput_a);

    clock_gettime(CLOCK_MONOTONIC, &time1);
    for(int t = 0; t < testcycles; t++)
    {
        pasketch = new PASketch(w_p, LOW_HASH_NUM, word_size);
        for(int i = 0; i < package_num; i++)
        {
            pasketch->Insert(insert[i]);
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &time2);
    resns = (long long)(time2.tv_sec - time1.tv_sec) * 1000000000LL + (time2.tv_nsec - time1.tv_nsec);
    double throughput_pasketch = (double)1000.0 * testcycles * package_num / resns;
    printf("throughput of PA (insert): %.6lf Mips\n\n", throughput_pasketch);
*/
/********************************************************************************************/

    printf("*************************************\n\n");

    // printf("\n******************************************************************************\n");



/********************************query*********************************/
    int res_tmp=0;

    int flow_num = unmp.size();

    int sum = 0;

    clock_gettime(CLOCK_MONOTONIC, &time1);
    for(int t = 0; t < testcycles; t++)
    {
        for(int i = 0; i < flow_num; i++)
        {
            res_tmp = cmsketch->Query(query[i]);
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &time2);
    resns = (long long)(time2.tv_sec - time1.tv_sec) * 1000000000LL + (time2.tv_nsec - time1.tv_nsec);
    throughput_cm = (double)1000.0 * testcycles * flow_num / resns;
    printf("throughput of CM (query): %.6lf Mips\n", throughput_cm);
    // printf("%d\n", res_tmp);
    sum += res_tmp;
/* 
    clock_gettime(CLOCK_MONOTONIC, &time1);
    for(int t = 0; t < testcycles; t++)
    {
        for(int i = 0; i < flow_num; i++)
        {
            res_tmp = pcmsketch->Query(query[i]);
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &time2);
    resns = (long long)(time2.tv_sec - time1.tv_sec) * 1000000000LL + (time2.tv_nsec - time1.tv_nsec);
    throughput_pcmsketch = (double)1000.0 * testcycles * flow_num / resns;
    printf("throughput of PCM (query): %.6lf Mips\n\n", throughput_pcmsketch);
    // printf("%d\n", res_tmp);
    sum += res_tmp;




    
    clock_gettime(CLOCK_MONOTONIC, &time1);
    for(int t = 0; t < testcycles; t++)
    {
        for(int i = 0; i < flow_num; i++)
        {
            res_tmp = cusketch->Query(query[i]);
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &time2);
    resns = (long long)(time2.tv_sec - time1.tv_sec) * 1000000000LL + (time2.tv_nsec - time1.tv_nsec);
    throughput_cu = (double)1000.0 * testcycles * flow_num / resns;
    printf("throughput of CU (query): %.6lf Mips\n", throughput_cu);
    // printf("%d\n", res_tmp);
    sum += res_tmp;
*/    

    clock_gettime(CLOCK_MONOTONIC, &time1);
    for(int t = 0; t < testcycles; t++)
    {
        for(int i = 0; i < flow_num; i++)
        {
            res_tmp = pcusketch->Query(query[i]);
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &time2);
    resns = (long long)(time2.tv_sec - time1.tv_sec) * 1000000000LL + (time2.tv_nsec - time1.tv_nsec);
    throughput_pcusketch = (double)1000.0 * testcycles * flow_num / resns;
    printf("throughput of PCU (query): %.6lf Mips\n\n", throughput_pcusketch);
    // printf("%d\n", res_tmp);
    sum += res_tmp;
    



/*
    clock_gettime(CLOCK_MONOTONIC, &time1);
    for(int t = 0; t < testcycles; t++)
    {
        for(int i = 0; i < flow_num; i++)
        {
            res_tmp = csketch->Query(query[i]);
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &time2);
    resns = (long long)(time2.tv_sec - time1.tv_sec) * 1000000000LL + (time2.tv_nsec - time1.tv_nsec);
    throughput_c = (double)1000.0 * testcycles * flow_num / resns;
    printf("throughput of C (query): %.6lf Mips\n", throughput_c);
    // printf("%d\n", res_tmp);
    sum += res_tmp;


    clock_gettime(CLOCK_MONOTONIC, &time1);
    for(int t = 0; t < testcycles; t++)
    {
        for(int i = 0; i < flow_num; i++)
        {
            res_tmp = pcsketch->Query(query[i]);
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &time2);
    resns = (long long)(time2.tv_sec - time1.tv_sec) * 1000000000LL + (time2.tv_nsec - time1.tv_nsec);
    throughput_pcsketch = (double)1000.0 * testcycles * flow_num / resns;
    printf("throughput of PC (query): %.6lf Mips\n\n", throughput_pcsketch);
    // printf("%d\n", res_tmp);
    sum += res_tmp;





    clock_gettime(CLOCK_MONOTONIC, &time1);
    for(int t = 0; t < testcycles; t++)
    {
        for(int i = 0; i < flow_num; i++)
        {
            res_tmp = asketch->Query(query[i]);
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &time2);
    resns = (long long)(time2.tv_sec - time1.tv_sec) * 1000000000LL + (time2.tv_nsec - time1.tv_nsec);
    throughput_a = (double)1000.0 * testcycles * flow_num / resns;
    printf("throughput of A (query): %.6lf Mips\n", throughput_a);
    // printf("%d\n", res_tmp);
    sum += res_tmp;


    clock_gettime(CLOCK_MONOTONIC, &time1);
    for(int t = 0; t < testcycles; t++)
    {
        for(int i = 0; i < flow_num; i++)
        {
            res_tmp = pasketch->Query(query[i]);
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &time2);
    resns = (long long)(time2.tv_sec - time1.tv_sec) * 1000000000LL + (time2.tv_nsec - time1.tv_nsec);
    throughput_pasketch = (double)1000.0 * testcycles * flow_num / resns;
    printf("throughput of PA (query): %.6lf Mips\n\n", throughput_pasketch);
    // printf("%d\n", res_tmp);
    sum += res_tmp;
*/

/********************************************************************************************/
    // printf("\n******************************************************************************\n");
    printf("*************************************\n\n");

    //avoid the over-optimize of the compiler! 
    if(sum == (1 << 30))
        return 0;



    char temp[500];

    double re_cm = 0.0, re_cu = 0.0, re_c = 0.0, re_a = 0.0, re_pcmsketch = 0.0, re_pcusketch = 0.0, re_pcsketch = 0.0, re_pasketch = 0.0;
    double re_cm_sum = 0.0, re_cu_sum = 0.0, re_c_sum = 0.0, re_a_sum = 0.0, re_pcmsketch_sum = 0.0, re_pcusketch_sum = 0.0, re_pcsketch_sum = 0.0, re_pasketch_sum = 0.0;
    
    double ae_cm = 0.0, ae_cu = 0.0, ae_c = 0.0, ae_a = 0.0, ae_pcmsketch = 0.0, ae_pcusketch = 0.0, ae_pcsketch = 0.0, ae_pasketch = 0.0;
    double ae_cm_sum = 0.0, ae_cu_sum = 0.0, ae_c_sum = 0.0, ae_a_sum = 0.0, ae_pcmsketch_sum = 0.0, ae_pcusketch_sum = 0.0, ae_pcsketch_sum = 0.0, ae_pasketch_sum = 0.0;

    double val_cm = 0.0, val_cu = 0.0, val_c = 0.0, val_a = 0.0, val_pcmsketch = 0.0, val_pcusketch = 0.0, val_pcsketch = 0.0, val_pasketch = 0.0;
    


    for(unordered_map<string, int>::iterator it = unmp.begin(); it != unmp.end(); it++)
    {
        strcpy(temp, (it->first).c_str());
        val = it->second;
        

        val_cm = cmsketch->Query(temp);
        // val_cu = cusketch->Query(temp);
        // val_c = csketch->Query(temp);
        // val_a = asketch->Query(temp);
        // val_pcmsketch = pcmsketch->Query(temp);
        val_pcusketch = pcusketch->Query(temp);
        // val_pcsketch = pcsketch->Query(temp);
        // val_pasketch = pasketch->Query(temp);




        re_cm = fabs(val_cm - val) / (val * 1.0);
        // re_cu = fabs(val_cu - val) / (val * 1.0);
        // re_c = fabs(val_c - val) / (val * 1.0);
        // re_a = fabs(val_a - val) / (val * 1.0);
        // re_pcmsketch = fabs(val_pcmsketch - val) / (val * 1.0);
        re_pcusketch = fabs(val_pcusketch - val) / (val * 1.0);
        // re_pcsketch = fabs(val_pcsketch - val) / (val * 1.0);
        // re_pasketch = fabs(val_pasketch - val) / (val * 1.0);

        ae_cm = fabs(val_cm - val);
        // ae_cu = fabs(val_cu - val);
        // ae_c = fabs(val_c - val);
        // ae_a = fabs(val_a - val);
        // ae_pcmsketch = fabs(val_pcmsketch - val);
        ae_pcusketch = fabs(val_pcusketch - val);
        // ae_pcsketch = fabs(val_pcsketch - val);
        // ae_pasketch = fabs(val_pasketch - val);




        re_cm_sum += re_cm;
        // re_cu_sum += re_cu;
        // re_c_sum += re_c;
        // re_a_sum += re_a;
        // re_pcmsketch_sum += re_pcmsketch;
        re_pcusketch_sum += re_pcusketch;    
        // re_pcsketch_sum += re_pcsketch;
        // re_pasketch_sum += re_pasketch;

        ae_cm_sum += ae_cm;
        // ae_cu_sum += ae_cu;
        // ae_c_sum += ae_c;
        // ae_a_sum += ae_a;
        // ae_pcmsketch_sum += ae_pcmsketch;
        ae_pcusketch_sum += ae_pcusketch;
        // ae_pcsketch_sum += ae_pcsketch;
        // ae_pasketch_sum += ae_pasketch;
    }


    double a = package_num * 1.0;
    double b = unmp.size() * 1.0;


    printf("aae_cm = %lf\n", ae_cm_sum / b);
    // printf("aae_pcm = %lf\n\n", ae_pcmsketch_sum / b);

    // printf("aae_cu = %lf\n", ae_cu_sum / b);
    printf("aae_pcu = %lf\n\n", ae_pcusketch_sum / b);
    FILE *aae = fopen("aae.txt", "a");
    fprintf(aae, "%lf\n", ae_pcusketch_sum / b);
    fclose(aae);
    // printf("aae_c = %lf\n", ae_c_sum / b);
    // printf("aae_pc = %lf\n\n", ae_pcsketch_sum / b);

    // printf("aae_a = %lf\n", ae_a_sum / b);
    // printf("aae_pa = %lf\n\n", ae_pasketch_sum / b);
    
    printf("*************************************\n\n");


    printf("are_cm = %lf\n", re_cm_sum / b);
    // printf("are_pcm = %lf\n\n", re_pcmsketch_sum / b);

    // printf("are_cu = %lf\n", re_cu_sum / b);
    printf("are_pcu = %lf\n\n", re_pcusketch_sum / b);
    FILE *are = fopen("are.txt", "a");
    fprintf(are, "%lf\n", re_pcusketch_sum / b);
    fclose(are);

    // printf("are_c = %lf\n", re_c_sum / b);
    // printf("are_pc = %lf\n\n", re_pcsketch_sum / b);

    // printf("are_a = %lf\n", re_a_sum / b);
    // printf("are_pa = %lf\n\n", re_pasketch_sum / b);

    
    printf("Evaluation Ends!\n");
    printf("******************************************************************************\n\n");

    return 0;

}