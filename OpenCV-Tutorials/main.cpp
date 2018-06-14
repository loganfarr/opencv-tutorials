//
//  main.cpp
//  OpenCV-Tutorails
//
//  Created by Logan Farr on 6/11/18.
//  Copyright © 2018 Logan Farr. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, const char * argv[]) {
    cv::Mat img = cv::imread(argv[1], -1);
    if(img.empty()) return -1;
    cv::namedWindow("Example1", cv::WINDOW_AUTOSIZE);
    cv::imshow("Example1", img);
    cv::waitKey(0);
    cv::destroyWindow("Example1");
    
    return 0;
}
