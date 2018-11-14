//
// Created by liuhui on 18-10-15.
//
#include "mtcnn.h"
#include "rotateUtil.h"

static long get_current_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int main(int argc, char** argv)
{
    long start,end;
    start=get_current_time();

    float resizeParam=2;
    const char* imagepath = argv[1];

    cv::Mat cv_img = cv::imread(imagepath, CV_LOAD_IMAGE_COLOR);
    cv::Mat cv_img_backup;
    cv_img.copyTo(cv_img_backup);

    if (cv_img.empty())
    {
        fprintf(stderr, "cv::imread %s failed\n", imagepath);
        return -1;
    }
    std::vector<Bbox> finalBbox;
    mtcnn mm;
    ncnn::Mat ncnn_img = ncnn::Mat::from_pixels(cv_img.data, ncnn::Mat::PIXEL_RGB, cv_img.cols, cv_img.rows);
//    ncnn::Mat ncnn_img_affine = ncnn::Mat::from_pixels_resize(cv_img_backup.data, ncnn::Mat::PIXEL_RGB2BGR, cv_img_backup.cols, cv_img_backup.rows,cv_img_backup.cols/resizeParam,cv_img_backup.rows/resizeParam);

    RotateImg(ncnn_img,1);//0向右 1向左 2上下 3水平对称 其他不变
    cv::Mat rotateImg(ncnn_img.h,ncnn_img.w,CV_8UC3);
    ncnn_img.to_pixels(rotateImg.data,ncnn::Mat::PIXEL_RGB);
    imwrite("/home/liuhui/Desktop/rotateImg1.jpg",rotateImg);

////    RotateImg(ncnn_img,0);
//    cv::Mat oriRotateImg(ncnn_img.h,ncnn_img.w,CV_8UC3);
//    ncnn_img.to_pixels(oriRotateImg.data,ncnn::Mat::PIXEL_RGB);
//
//    mm.detect(ncnn_img_affine, finalBbox);
//    int num_face=1;
//    int out_size = 1+num_face*4;
//    //  LOGD("内部人脸检测完成,开始导出数据");
//    int *faceInfo = new int[out_size];
//    faceInfo[0] = num_face;
//    for(int i=0;i<num_face;i++){
////        faceInfo[4*i+1] = finalBbox[i].x1*resizeParam;//left
////        faceInfo[4*i+2] = finalBbox[i].y1*resizeParam;//top
////        faceInfo[4*i+3] = finalBbox[i].x2*resizeParam;//right
////        faceInfo[4*i+4] = finalBbox[i].y2*resizeParam;//bottom
////        faceInfo[4*i+1] = finalBbox[i].x1*resizeParam;//left
////        faceInfo[4*i+2] = finalBbox[i].y1*resizeParam;//top
////        faceInfo[4*i+3] = finalBbox[i].x2*resizeParam;//right
////        faceInfo[4*i+4] = finalBbox[i].y2*resizeParam;//bottom
//        faceInfo[4*i+1] = finalBbox[i].y1*resizeParam;//left                      x1
//        faceInfo[4*i+2] = ncnn_img.h-(finalBbox[i].x1*resizeParam);//top       y1
//        faceInfo[4*i+3] = finalBbox[i].y2*resizeParam;//right                      x2
//        faceInfo[4*i+4] = ncnn_img.h-(finalBbox[i].x2*resizeParam);//bottom     y2
//    }
////    cv::Mat reget_img(ncnn_img_affine.h,ncnn_img_affine.w,CV_8UC3);
////    ncnn_img_affine.to_pixels(reget_img.data,ncnn::Mat::PIXEL_RGB);
//    cout<<faceInfo[1]<<" "<<faceInfo[2]<<" "<<faceInfo[3]<<" "<<faceInfo[4]<<endl;
//    for(int i=0;i<num_face;i++){
//        rectangle(oriRotateImg, Point(faceInfo[4*i+1], faceInfo[4*i+2]), Point(faceInfo[4*i+3], faceInfo[4*i+4]), Scalar(0,0,255), 2,8,0);
//    }
//    std::vector<Bbox> finalBboxex;
//
////    int height_padding=0.2*(finalBbox[0].y2-finalBbox[0].y1)*resizeParam;
////    int width_padding=0.2*(finalBbox[0].x2-finalBbox[0].x1)*resizeParam;
////
////    int y1=finalBbox[0].y1*resizeParam-height_padding;
////    int y2=(ncnn_img.h-finalBbox[0].y2*resizeParam)-height_padding;
////    int x1=finalBbox[0].x1*resizeParam-width_padding;
////    int x2=(ncnn_img.w-finalBbox[0].x2*resizeParam)-width_padding;
////    if (y1<0) y1=0;
////    if (y2<0) y2=0;
////    if (x1<0) x1=0;
////    if (x2<0) x1=0;
//
////    ncnn::Mat ncnn_crop_img;
//    copy_cut_border(ncnn_img, ncnn_crop_img,y1,y2,x1,x2);
//    imwrite("/home/liuhui/Desktop/result.jpg",oriRotateImg);
//
//    end=get_current_time();
//    printf( "all process time %ld ms \n", (end-start) );
    return 0;
}
