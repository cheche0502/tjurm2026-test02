#include "impls.h"


float compute_area_ratio(const std::vector<cv::Point>& contour) {
    /**
     * 要求：
     *      计算输入的轮廓的面积与它的最小外接矩形面积的比例。自行查找
     * 获得轮廓面积的函数。这个量可以用来判断一个轮廓到底有多靠近一个矩形。
     * 
     * 提示：
     * 无。
     * 
     * 通过条件:
     * 运行测试点，通过即可。
     */
    double contour_area = std::abs(cv::contourArea(contour));   //取绝对值，并求输入轮廓面积
    cv::RotatedRect rect = cv::minAreaRect(contour);  
    //minAreaRect不可以直接返回面积
    double rect_area =rect.size.width*rect.size.height;     

    if (rect_area < 1e-6)       
        return 0.f;
    return contour_area / rect_area;
}
