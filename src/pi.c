#include <stdio.h>

#define N 7200

int main(int argc, char* argv[])
{
    int const M=10000;
    int const B=10000;
    int const L=4;
    // Machin公式 计算pi到一万位
    int s[M/L];
    int r1[N]={0},r2[N]={0},d1[N]={0},d2;
    int r3[N]={0},r4[N]={0},d3[N]={0},d4;
    int i,k,t,p=0,mp=M/L/20;

    r1[0]=1;
    r1[1]=3;
    r3[0]=4;

    printf("正在计算,请等待\n____________________\n");

    for(k=0;k<M/L;++k)
    {
        t=r1[0]*B;
        d1[0]=t/0x5;
        r1[0]=t%0x5;
        //
        t=r3[0]*B;
        d3[0]=t/0xEF;
        r3[0]=t%0xEF;
        s[k]=d1[0]-d3[0];
        int tag=0;
        for(i=1;i<N;++i)
        {
            t=r1[i]*B+d1[i-1];
            d1[i]=t/0x19;
            r1[i]=t%0x19;
            t=r2[i]*B+d1[i];
            d2=t/(2*i+1);
            r2[i]=t%(2*i+1);
            //
            t=r3[i]*B+d3[i-1];
            d3[i]=t/0xDF21;
            r3[i]=t%0xDF21;
            t=r4[i]*B+d3[i];
            d4=t/(2*i+1);
            r4[i]=t%(2*i+1);
            if(tag)
            {
                s[k]+=(d2-d4);
                tag=0;
            }
            else
            {
                s[k]+=(d4-d2);
                tag=1;
            }
        }
        if(p==mp)
        {
            printf(">");
            p=0;
        }
        else
          p++;
    }
    for(i=M/L-1;i>=0;i--)
    {
        while(s[i]>=B)
        {
            s[i-1]++;
            s[i]-=B;
        }
        while(s[i]<0)
        {
            s[i-1]--;
            s[i]+=B;
        }
    }
    printf("\npi=3.\n");
    for(i=0;i<M/L;++i)
      printf("%04d",s[i]);
    return 0;
}
