# Face-Recognition
### 开发环境
* IDE：Qt Creator 4.11.1<br>
* Qt Version：Qt 5.14.2
* Compiler：Microsoft Visual C++ 2017（x64）<br>
* OpenCV：OpenCV 4.2
---------
### 项目介绍 
* 这是一个基于 `OpenCV 4` 和 `Qt 5` 的人脸识别小demo，核心功能是由 `cv::CascadeClassifier::detectMultiScale` 分类器实现。希望能够帮到大家，也请各位大佬多多指教。<br>
---------
### 运行说明
* 由于 `OpenCV 4` 的DLL体积过大，不方便上传，所以需要自行补齐DLL。（也可以换算自己的OpenCV库）

|  DLL名称              |
|  -------------------  |
|  opencv_world420.dll  |
|  opencv_world420d.dll |

* `haarcascade_frontalface_alt.xml` 和 `haarcascade_frontalface_alt2.xml` 都是官方训练好的模型，demo中默认使用第一个，可以根据自己需要更换。
---------
### 关于作者
* QQ：2189684957<br>
* E-mail：2189684957@qq.com<br>