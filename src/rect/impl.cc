#include "impls.h"
std::pair<cv::Rect, cv::RotatedRect>get_rect_by_contours(const cv::Mat& input){
    /**
     * 要求：
     * 使用findCountours函数找出输入图像（彩色图像）中的矩形轮廓，并且返回它的外接矩形，以及
     * 最小面积外接矩形。所需要的函数自行查找。
     * 
     * 通过条件：
     * 运行测试点，你找到的矩形跟答案一样就行。
        */  
    
    //Stage1:单通道+二值化
    cv::Mat binary;
    if (input.channels() != 1)
        cv::cvtColor(input, binary,cv::COLOR_BGR2GRAY);
    else
        binary = input.clone();
    cv::threshold(binary, binary,127,255,cv::THRESH_BINARY);
    
    //Stage2:找轮廓,返回层次结构
    std::vector<std::vector<cv::Point>>contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(binary,contours,hierarchy,cv::RETR_TREE,cv::CHAIN_APPROX_SIMPLE);

    std::vector<std::vector<cv::Point>>leaf_contours;
    for (size_t i = 0;i< contours.size();++i)
        if (hierarchy[i][2] == -1)      // 若当前轮廓没有子轮廓（hierarchy[i][2] == -1)则为叶子节点
            leaf_contours.push_back(contours[i]);




    // 以下部分求助了ai，学习了对层次结构的遍历以及利用最大面积方法筛选        
    // 主函数：根据轮廓获取外接矩形和最小面积外接矩形
    contours = leaf_contours;           // 1. 获取所有叶子节点轮廓（复用同名变量）

    // 2. 筛选面积最大的轮廓（排除噪声小轮廓，聚焦主要目标）
    int max_idx = 0;
    double max_area = cv::contourArea(contours[0]);
    for (size_t i = 1; i < contours.size(); ++i) {
        double area = cv::contourArea(contours[i]);
        if (area > max_area) {
            max_area = area;
            max_idx = i;
        }
    }

    // 3. 计算两种外接矩形
    return {cv::boundingRect(contours[max_idx]),   // 轴对齐外接矩形
            cv::minAreaRect(contours[max_idx])};  // 最小面积外接旋转矩形
} 
