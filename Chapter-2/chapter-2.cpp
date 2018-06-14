//
//  chapter-1.cpp
//  OpenCV-Tutorails
//
//  Created by Logan Farr on 6/11/18.
//  Copyright © 2018 Logan Farr. All rights reserved.
//

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

int displayImage(int argc, char** argv) {
    Mat img = cv::imread(argv[1], -1);
    if(img.empty()) return -1;
    namedWindow("Example1", cv::WINDOW_AUTOSIZE);
    imshow("Example1", img);
    waitKey(0);
    destroyWindow("Example1");
    
    return 0;
}

int displayVideo(int argc, char** argv) {
    namedWindow("Example3", WINDOW_AUTOSIZE);
    VideoCapture cap;
    cap.open(string(argv[1]));
    
    Mat frame;
    
    for(;;) {
        cap >> frame;
        if(frame.empty()) break; // If no more film
        
        // Show the frame in the window
        imshow("Example3", frame);
        
        // Wait 33 milliseconds, and if the user hits a key, then break
        if(waitKey(33) >= 0) break;
    }
}
