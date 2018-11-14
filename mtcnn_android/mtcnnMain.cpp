//
// Created by liuhui on 18-10-15.
//
#include "mtcnn.h"
static float getElapse(struct timeval *tv1,struct timeval *tv2)
{
    float t = 0.0f;
    if (tv1->tv_sec == tv2->tv_sec)
        t = (tv2->tv_usec - tv1->tv_usec)/1000.0f;
    else
        t = ((tv2->tv_sec - tv1->tv_sec) * 1000 * 1000 + tv2->tv_usec - tv1->tv_usec)/1000.0f;
    return t;
}
static long get_current_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
int main(int argc, char** argv)
{
    const char* imagepath = argv[1];

    cv::Mat cv_img = cv::imread(imagepath, CV_LOAD_IMAGE_COLOR);
    if (cv_img.empty())
    {
        fprintf(stderr, "cv::imread %s failed\n", imagepath);
        return -1;
    }
    std::vector<Bbox> finalBbox;
    MTCNN mm;
    ncnn::Mat ncnn_img = ncnn::Mat::from_pixels(cv_img.data, ncnn::Mat::PIXEL_BGR2RGB, cv_img.cols, cv_img.rows);

    long start,end;
    start=get_current_time();

    struct timeval  tv1,tv2;
    struct timezone tz1,tz2;

    gettimeofday(&tv1,&tz1);
    mm.detect(ncnn_img, finalBbox);
    cout<<"finalBbox size"<<finalBbox.size()<<endl;
    gettimeofday(&tv2,&tz2);
    printf( "%s = %g ms \n ", "Detection All time", getElapse(&tv1, &tv2) );

    end=get_current_time();
    printf( "mtcnn_android Detection All time %g ms", (end-start) );
    for(vector<Bbox>::iterator it=finalBbox.begin(); it!=finalBbox.end();it++){
            rectangle(cv_img, cv::Point((*it).x1, (*it).y1), cv::Point((*it).x2, (*it).y2), cv::Scalar(0,0,255), 2,8,0);
            for(int num=0;num<5;num++)circle(cv_img,cv::Point((int)*(it->ppoint+num), (int)*(it->ppoint+num+5)),3,cv::Scalar(0,255,255), -1);
    }
    imwrite("/home/liuhui/Desktop/result.jpg",cv_img);
    return 0;
}
//void MTCNN::detection(const cv::Mat& img, std::vector<cv::Rect>& rectangles){
//    ncnn::Mat ncnn_img = ncnn::Mat::from_pixels(img.data, ncnn::Mat::PIXEL_BGR2RGB, img.cols, img.rows);
//    std::vector<Bbox> finalBbox;
//    detect(ncnn_img, finalBbox);
//    const int num_box = finalBbox.size();
//    rectangles.resize(num_box);
//    for(int i = 0; i < num_box; i++){
//        rectangles[i] = cv::Rect(finalBbox[i].x1, finalBbox[i].y1, finalBbox[i].x2 - finalBbox[i].x1 + 1, finalBbox[i].y2 - finalBbox[i].y1 + 1);
//    }
//}
