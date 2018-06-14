//
//  chapter-1.cpp
//  OpenCV-Tutorails
//
//  Created by Logan Farr on 6/11/18.
//  Copyright © 2018 Logan Farr. All rights reserved.
//

#include <opencv2/opencv.hpp>

using namespace cv;

// Example 2-2
// Show in a image
int displayImage(int argc, char** argv) {
    Mat img = cv::imread(argv[1], -1);
    if(img.empty()) return -1;
    namedWindow("Example1", cv::WINDOW_AUTOSIZE);
    imshow("Example1", img);
    waitKey(0);
    destroyWindow("Example1");
    
    return 0;
}

// Example 2-3
// Show a video
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

// Example 2-4
// Navigating a video with a slider
// (leading g_ to denote global variables)
int g_slider_position = 0; // Current trackbar position
int g_run = 1;
int g_dontset = 0; // Start out in single step mode
VideoCapture g_cap;

/**
 * Callback to update the global variables
 * and relocates read position in the video.
 */
void onTrackbarSlide(int pos, void *) {
    g_cap.set(cv::CAP_PROP_POS_FRAMES, pos);
    
    // To avoid confusion, pause video while user moves slidebar
    if(!g_dontset)
        g_run = 1;
    
    g_dontset = 0;
}

int trackbarSlide(int argc, char** argv) {
    namedWindow("Example2_4", cv::WINDOW_AUTOSIZE);
    g_cap.open(std::string(argv[1]));
    int frames  = (int) g_cap.get(cv::CAP_PROP_FRAME_COUNT);
    int tmpw    = (int) g_cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int tmph    = (int) g_cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    
    std::cout << "Video has " << frames << " frames of dimensions("
    << tmpw << ", " << tmph << ")." << std::endl;
    
    //             Label     , Window name,  Bound variable,  max value, callback function
    createTrackbar("Position", "Example2_4", &g_slider_position, frames, onTrackbarSlide);
    
    Mat frame;
    
    // For as long as we have frames in the video
    for(;;) {
        // If the video is not stopped
        if(g_run != 0) {
            g_cap >> frame;
            if(frame.empty())
                break;
            
            int current_pos = (int) g_cap.get(cv::CAP_PROP_POS_FRAMES);
            
            g_dontset = 1;
            
            // For each new frame, we need to set the trackbar's
            // position to correspond with where we are in the video
            setTrackbarPos("Position", "Example2_4", current_pos);
            imshow("Example2_4", frame);
            
            // Play video in continuous mode
            g_run -= 1;
        }
        
        // Wait 10 ms for keystroke
        char c = (char) waitKey(10);
        if(c == 's') { // Single step through video
            g_run = 1;
            std::cout << "Single step, run = " << g_run << std::endl;
        }
        
        if(c == 'r') { // Resume normal playback
            g_run = -1;
            std::cout << "Run mode, run = " << g_run << std::endl;
        }
        
        if(c == 27) // If the esc key is pressed, exit
            break;
    }
    
    destroyWindow("Example2_4");
    return 0;
}
