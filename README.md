---
### 日志
1. 针对mtcnn的col-major模型添加了caffe2ncnn_mtcnn.cpp, 生成row-major模型
2. 添加void resize_image(ncnn::Mat& srcImage, ncnn::Mat& dstImage)，无arm优化
3. 前面都是用BGR图像做的，导致很多漏检，改过来了。
4. 3519编译：在CMakelist.txt的17行下面手动添加如下代码
```
set(CMAKE_C_COMPILER   arm-hisiv500-linux-gcc) 
set(CMAKE_CXX_COMPILER arm-hisiv500-linux-g++)
add_definitions(-D__ARM_NEON)
add_definitions("-O3 -mfloat-abi=softfp -mfpu=neon-vfpv4 -ffunction-sections") 
```
5. 在非手机的arm环境下，需要修改CMakeLists.txt才能把arm编译进去，如CMakeLists_arm.txt
6. 如果使用opencv2，需要将examples/CmakeLists.txt里的imgcodecs去掉，否则可能编译不过去
7. 在tx1下make时可能会出现"can't find -lopencv_dep_cudart"，重新cmake，"cmake -D CUDA_USE_STATIC_CUDA_RUNTIME=OFF .."
8. 新版本ncnn,使用mtcnn/mtcnn_new.cpp 
---
![image](https://github.com/ElegantGod/ncnn/blob/master/mtcnn/result.jpg)
