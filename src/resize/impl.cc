#include "impls.h"


cv::Mat my_resize(const cv::Mat& input, float scale) {
    /**
     * 要求：
     *      实现resize算法，只能使用基础的语法，比如说for循环，Mat的基本操作。不能
     * 用cv::resize。resize算法的内容自行查找学习，不是很难。
     * 
     * 提示：
     * 无。
     * 
     * 通过条件：
     * 运行测试点，你的结果跟答案长的差不多就行。
     */
    //stage1:计算新图的宽高大小
    int old_rows = input.rows;
    int old_cols = input.cols;
    int new_rows = static_cast<int>(old_rows*scale+0.5f);
    int new_cols = static_cast<int>(old_cols*scale+0.5f);
    int chs = input.channels();

     cv::Mat dst(new_rows,new_cols,input.type());
   
    //stage2：遍历新图的每一个点，找到原图对应的坐标
    for (int i=0;i<new_rows;++i)
    {
        float src_y=i/scale;  //找原图对应的y坐标
        int y1 = static_cast<int>(src_y);
        int y2 = std::min(y1+1,old_rows-1);
        float dy = src_y-y1;

        for (int j=0;j<new_cols;++j)
        {
            float src_x = j/scale;  //同理
            int x1 = static_cast<int>(src_x);
            int x2 = std::min(x1+1,old_cols-1);
            float dx = src_x-x1;
    //这里我用algorithm中的min进行边界检查，不用三目运算符了！！！！
    //stage3:再找四个邻居点
            for (int c = 0;c<chs;++c)
            {
                uchar q1 = input.at<uchar>(y1,x1*chs+c);
                uchar q2 = input.at<uchar>(y1,x2*chs+c);
                uchar q3 = input.at<uchar>(y2,x1*chs+c);
                uchar q4 = input.at<uchar>(y2,x2*chs+c);

                float r1 = q1*(1-dx)+q2*dx;
                float r2 = q3*(1-dx)+q4*dx;//套套公式，先各自做一次单线性插法
                dst.at<uchar>(i, j*chs+c) = (r1*(1-dy)+r2*dy);//再做一次单线性插值
            }
        }
    }
    return dst;
}
