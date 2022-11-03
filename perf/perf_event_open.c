#define _GNU_SORCE
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/syscall.h>
#include <linux/perf_event.h>
//#include <linux/cpufreq.h>
#include <sys/ioctl.h>
#include <math.h>
//#define pid_id 4476
//#define pid_id 19091
//#define cpu  -1
struct cpufreq_policy *policy;

//目前perf_event_open在glibc中没有封装，需要手工封装一下
__attribute__((contructor)) static
int perf_event_open(struct perf_event_attr *attr,pid_t pid,int cpu,int group_fd,unsigned long flags)
{
    return syscall(__NR_perf_event_open,attr,pid,cpu,group_fd,flags);
}

struct read_format
{
    uint64_t nr;        //numbers of counter
    
    uint64_t values[4]; //value of counter
};

int main(int argc,const char *argv[])
{ 
 //read specify pid----------------------------
    char line[50];   // time_t start = time(NULL)
    FILE *command = popen("pidof main","r");
    //FILE *command = popen("pidof detectnet","r");
    fgets(line,50,command);

    pid_t pid_id = strtoul(line, NULL,10);
    pclose(command);
//--------------------------------------------

    char cmd_buf[5];
    char cpu_freq_buf[8];
    int test_sec;

    if(argc >1) {
        strcpy(cmd_buf, argv[1]);
        test_sec = atoi(cmd_buf);
    }
    //printf("test_sec = %d\n",test_sec);
 
    FILE *data = fopen("camera_mar_data.txt","a+");
  //FILE *data = fopen("gyro_mar_data.txt","a+");
  //FILE *mar_file = fopen("mar_data.txt", "w");

//mornitor_1--------------------------------------------------------- 
    struct perf_event_attr attr;
    memset(&attr,0,sizeof(struct perf_event_attr));
    attr.size=sizeof(struct perf_event_attr);
    //attr.type=PERF_TYPE_HARDWARE;
    attr.type=PERF_TYPE_HW_CACHE;
    
    //attr.config=PERF_COUNT_HW_CPU_CYCLES;
    //attr.config=PERF_COUNT_HW_CACHE_RESULT_MISS;
    attr.config=PERF_COUNT_HW_CACHE_L1D |
                PERF_COUNT_HW_CACHE_OP_READ << 8 |
                PERF_COUNT_HW_CACHE_RESULT_MISS << 16;
    
    attr.disabled=1;
    
    attr.read_format=PERF_FORMAT_GROUP;
    
    int fd=perf_event_open(&attr,pid_id,-1,-1,0);
    if(fd<0){
        perror("Cannot open perf fd!");
        return 1;
    }

//monitor_2---------------------------------------------------------

    memset(&attr,0,sizeof(struct perf_event_attr));
    
    attr.size=sizeof(struct perf_event_attr);
    attr.type=PERF_TYPE_HW_CACHE;
    //attr.config=PERF_COUNT_HW_CACHE_RESULT_ACCESS;
    attr.config=PERF_COUNT_HW_CACHE_L1D |
                PERF_COUNT_HW_CACHE_OP_READ << 8 |
                PERF_COUNT_HW_CACHE_RESULT_ACCESS << 16;

    //attr.config=PERF_COUNT_HW_CACHE_MISSES;
    //attr.config=PERF_COUNT_HW_CACHE_L1D;
    attr.disabled=1;
    
    int fd2=perf_event_open(&attr,pid_id,-1,fd,0);
    if(fd2<0){
        perror("Cannot open perf fd2!");
        return 1;
    }

//monitor_3--------------------------------------------------------
    memset(&attr,0,sizeof(struct perf_event_attr));
    
    attr.size=sizeof(struct perf_event_attr);
    attr.type=PERF_TYPE_HARDWARE;
    attr.config=PERF_COUNT_HW_CACHE_L1D;
    attr.disabled=1;
    
    int fd3=perf_event_open(&attr,pid_id,-1,fd,0);
    if(fd3<0)
    {
        perror("Cannot open perf fd2!");
        return 1;
    }

//monitor_4--------------------------------------------------------
    memset(&attr,0,sizeof(struct perf_event_attr));
    
    attr.size=sizeof(struct perf_event_attr);
    //attr.type=PERF_TYPE_HARDWARE;
    attr.type=PERF_TYPE_HW_CACHE;
    //attr.config=PERF_COUNT_HW_INSTRUCTIONS;
    attr.config=PERF_COUNT_HW_CACHE_L1I |
                PERF_COUNT_HW_CACHE_OP_READ << 8 |
                PERF_COUNT_HW_CACHE_RESULT_ACCESS << 16;
    attr.disabled=1;
    
    int fd4=perf_event_open(&attr,pid_id,-1,fd,0);
    if(fd4<0)
    {
        perror("Cannot open perf fd2!");
        return 1;
    }

//-----------------------------------------------------------------    
    char buf[2020];
    int pmu = open("/dev/pmuctl",O_RDONLY);
    read(fd,buf,sizeof(buf));


//start counter
    ioctl(fd,PERF_EVENT_IOC_ENABLE,PERF_IOC_FLAG_GROUP);
   
    int cnt = 0;
    while(cnt<test_sec)
    {/*
  //read specify pid----------------------------
    char line[50];   // time_t start = time(NULL)
    FILE *command = popen("pidof detectnet","r");
    //FILE *command = popen("pidof detectnet","r");
    fgets(line,50,command);

    pid_t pid_nid = strtoul(line, NULL,10);
    pclose(command);
    
    if(pid_nid != pid_id) 
        pid_id = pid_nid;
//--------------------------------------------
*/
       int freq,cpi;
        cnt++;
        float mar,mar2,cs;
        struct read_format aread;
        
        read(fd,&aread,sizeof(struct read_format));
    
        mar = (float)aread.values[0]/(float)aread.values[3];
        mar2 = (float)aread.values[2]/(float)aread.values[3];
        cpi = (int)aread.values[0] / (int)aread.values[3];
        cs = pow(mar,3)*(-30474.04)+pow(mar,2)*1855.97-mar*37.82+0.797;
        //float cmiss_rate = (float)aread.values[0]/(float)aread.values[1];
        float cmiss_rate = (float)aread.values[0] / (float)aread.values[1];
        float creference_percycle = (float)aread.values[2]/(float)aread.values[0];
   
//reset counter        
        ioctl(fd,PERF_EVENT_IOC_RESET,PERF_IOC_FLAG_GROUP);
//------------

        FILE *fq = fopen("/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_cur_freq","r");
    
        fscanf(fq, "%d", &freq);
        //freq = atoi(cpu_freq_buf);
        printf("pid = %d MAR = %f MAR_2 = %f cmiss_rate = %f  cache_misses=%ld instruction = %ld \n",pid_id,mar,mar2,cmiss_rate,aread.values[0],aread.values[1],aread.values[3]);
        printf("\naread[0] = %ld\naread[1] = %ld\n",aread.values[0],aread.values[1]);
        if(cs > 0)
            fprintf(data, "%f %d\n",mar,freq);
        //fprintf(mar_file,"%f\n",mar);	

        //fclose(fd);
        sleep(1);
    }
    fclose(data);
}
