#include <stdio.h>
#include <stdint.h>
#include "speck.h"


void Words16ToBytes(u16 words[],u8 bytes[],int numwords)
{
    int i,j=0;
    for(i=0;i<numwords;i++){
        bytes[j]=(u8)words[i];
        bytes[j+1]=(u8)(words[i]>>8);
        j+=2;
    }
}

void BytesToWords16(u8 bytes[],u16 words[],int numbytes)
{
    int i,j=0; for(i=0;i<numbytes/2;i++){
        words[i]=(u16)bytes[j] | ((u16)bytes[j+1]<<8);
        j+=2;
    }
}

void Speck3264KeySchedule(u16 K[],u16 rk[])
{
    u16 i,D=K[3],C=K[2],B=K[1],A=K[0];
    for(i=0;i<22;){
        rk[i]=A;
        ER16(B,A,i++);
        rk[i]=A;
        ER16(C,A,i++);
        rk[i]=A;
        ER16(D,A,i++);
    }
}


void Speck3264Encrypt(u16 Pt[],u16 Ct[],u16 rk[])
{
    u16 i;
    Ct[0]=Pt[0]; Ct[1]=Pt[1];

    // full 22  rounds
    // for(i=0;i<22;) ;
    //er16(ct[1],ct[0],rk[0]);
    for(i=0;i<22;) {
        //er16(ct[1],ct[0],0xdead);
        ER16(Ct[1],Ct[0],rk[i++]);
#ifndef ARM
        printf("( c1=0x%x, c0=0x%x, k=0x%x )\n", Ct[1], Ct[0], rk[i]);
#endif

    }
}


void Speck3264Decrypt(u16 Pt[],u16 Ct[],u16 rk[])
{
    int i;
    Pt[0]=Ct[0]; Pt[1]=Ct[1];

    for(i=21;i>=0;) DR16(Pt[1],Pt[0],rk[i--]);
}


void Speck3264_EncryptBlock(u8 pt[], u8 k[], u8 ct[]) {

    u16 Pt[2] = {0};
    u16 K[4] = {0};
    u16 rk[34] = {0};
    u16 Ct[2] = {0};

    BytesToWords16(pt,Pt,8);
    BytesToWords16(k,K,16);

    Speck3264KeySchedule(K,rk);

    // DEBUG
#ifndef ARM
    for (int i=0; i < 16; i++)
    {
        printf("Key: 0x%x\n", rk[i]);
    }
#endif
    Speck3264Encrypt(Pt,Ct,rk);
    Words16ToBytes(Ct,ct,2);
}


#ifndef ARM
int main() {


    u8 pt[4] = {0x4c, 0x69, 0x74, 0x65};
    u8 key[8] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};


    u8 ct[4] = {0x0};

    Speck3264_EncryptBlock(pt, key, ct);
    printf("[[ Speck 32/64  ]]\n");

    printf("The output: \n");
    for (int i = 0; i < 4; i++) {
        printf("- %08x\n", ct[i]);
    }
    return 0;
}
#endif
