#ifndef __ROTATEUTIL_H__
#define __ROTATEUTIL_H__
//#include <stdlib.h>
//#include <string.h>

extern "C" {
void RotationRight(ncnn::Mat  srcMat) {
    float *ptr[3];
    ptr[0]= srcMat.channel(0);
    ptr[1] = srcMat.channel(1);
    ptr[2] = srcMat.channel(2);

    float *tempSrc = NULL;
    int desW = srcMat.h;
    int desH = srcMat.w;
    int mSize = desW * desH * sizeof(float);
    tempSrc = (float *) malloc(sizeof(float) * desW * desH);
    for (int k = 0; k < 3; ++k) {
        memcpy(tempSrc, ptr[k], mSize);
        for (int i = 0; i < desH; i++) {
            for (int j = 0; j < desW; j++) {
                ptr[k][(i * desW + j)] = tempSrc[((desW - 1 - j) * desH + i)];
//                src[(i * desW + j) * channel + k] = tempSrc[((srcH - 1 - j) * srcW + i) * channel + k];
            }
        }
    }
    free(tempSrc);
}

void RotationLeft(ncnn::Mat srcMat) {
    float *ptr[3];
    ptr[0]= srcMat.channel(0);
    ptr[1] = srcMat.channel(1);
    ptr[2] = srcMat.channel(2);

    float *tempSrc = NULL;
    int desW = srcMat.h;
    int desH = srcMat.w;
    int mSize = desW * desH * sizeof(float);
    tempSrc = (float *) malloc(sizeof(float) * desW * desH);
    for (int k = 0; k < 3; ++k) {
        memcpy(tempSrc, ptr[k], mSize);
        for (int i = 0; i < desH; i++) {
            for (int j = 0; j < desW; j++) {
                ptr[k][(i * desW + j)] = tempSrc[(j * desH + i)];
//                src[(i * desW + j) * channel + k] = tempSrc[(j * srcW + i) * channel + k];
            }
        }
    }
    free(tempSrc);
}

void RotationDown(ncnn::Mat srcMat) {
    float *ptr[3];
    ptr[0]= srcMat.channel(0);
    ptr[1] = srcMat.channel(1);
    ptr[2] = srcMat.channel(2);

    float *tempSrc = NULL;
    int desW = srcMat.w;
    int desH = srcMat.h;
    int mSize = desW * desH * sizeof(float);
    tempSrc = (float *) malloc(sizeof(float) * desW * desH);
    for (int k = 0; k < 3; ++k) {
        memcpy(tempSrc, ptr[k], mSize);
        for (int i = 0; i < desH; i++) {
            for (int j = 0; j < desW; j++) {
                ptr[k][(i * desW + j)] = tempSrc[((desH - 1 - i) * desW + desW - 1 - j)];
//                src[(i * desW + j) * channel + k] = tempSrc[((srcH - 1 - i) * srcW + srcW - 1 - j) * channel + k];
//                src[(y * desW + x)] = tempSrc[(x * srcW + y)];
            }
        }
    }
    free(tempSrc);
}
void Right2Left(ncnn::Mat srcMat) {
    float *ptr[3];
    ptr[0] = srcMat.channel(0);
    ptr[1] = srcMat.channel(1);
    ptr[2] = srcMat.channel(2);

    float *tempSrc = NULL;
    int mSize = srcMat.w * srcMat.h * sizeof(float);
    tempSrc = (float *) malloc(sizeof(float) * srcMat.w * srcMat.h);
    for (int k = 0; k < 3; ++k) {
        memcpy(tempSrc, ptr[k], mSize);
        for (int i = 0; i < srcMat.h; i++) {
            for (int j = 0; j < srcMat.w; j++) {
                ptr[k][(i * srcMat.w + j)] = tempSrc[(i * srcMat.w +srcMat.w - j - 1)];
            }
        }
    }
    free(tempSrc);
}


void RotateImg(ncnn::Mat &srcMat,int flag) {
    switch (flag){
        case 0:{
            RotationRight(srcMat);
            int temph=srcMat.h;
            srcMat.h=srcMat.w;
            srcMat.w=temph;
            break;
        }
        case 1:{
            printf("向左90度");
            RotationLeft(srcMat);
            int temph=srcMat.h;
            srcMat.h=srcMat.w;
            srcMat.w=temph;
            break;
        }
        case 2:{
            RotationDown(srcMat);
            break;
        }
        case 3:{
            Right2Left(srcMat);
            break;
        }
        default:
            break;
    }
}

}
#endif