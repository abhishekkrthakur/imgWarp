//
//  main.cpp
//  imgWarp
//
//  Created by Abhishek Kumar Thakur on 1/14/13.
//  Copyright (c) 2013 Abhishek Kumar Thakur. All rights reserved.
//

#define PI 3.14159265359

#include <iostream>
#include "math.h"
#include "vector"
#include <iomanip>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <sys/time.h>
#include <ctime>

using namespace cv;
using namespace std;


// Function to Warp Image
// Input:
//          input = input image
//          out = output image
//          amplitude1 = amplitude of first sinusoid
//          tPeriod1 = time period of the first sinusoid
//          phi1 = phase of first sinusoid
//          amplitude1 = amplitude of second sinusoid
//          tPeriod1 = time period of the second sinusoid
//          phi1 = phase of the second sinusoid
//          direction - direction of warp. 1 for x-direction, 2 for y-direction and 3 for both x and y
//
void warpFunc(Mat input, Mat &out, double amplitude1, double tPeriod1, double phi1, double amplitude2, double tPeriod2, double phi2, int direction)
{
    int height = input.rows;
    int width = input.cols;
    
    double xo, yo;
    input.convertTo(input, CV_32FC1); // Convert image to float
    out = Mat(height, width, input.type());
    
    // data as array
    float *outdata = (float*)out.data;
    float *indata = (float*)input.data;
    
    
    //switch direction of warp
    switch(direction)
    {
        case 1:
            for(int j = 0; j < height; j++){
                for(int i =0; i < width; i++){
                    xo = amplitude1 * sin((2.0 * PI * (j/tPeriod1)) + phi1) ;
                    yo = amplitude2 * (sin(2.0 * PI* (i/tPeriod2)) + phi2);
                    int ix = min(width-1, max(0, (int) (i + xo)));
                    int iy = min(height-1, max(0, (int) (j)));
                    outdata[j*width + i] = indata[iy* width + ix];
                    
                }
            }
            break;
        case 2:
            for(int j = 0; j < height; j++){
                for(int i =0; i < width; i++){
                    xo = amplitude1 * sin((2.0 * PI * (j/tPeriod1)) + phi1) ;
                    yo = amplitude2 * (sin(2.0 * PI* (i/tPeriod2)) + phi2);
                    int ix = min(width-1, max(0, (int) (i)));
                    int iy = min(height-1, max(0, (int) (j + yo )));
                    outdata[j*width + i] = indata[iy* width + ix];
                    
                }
            }
            break;
        case 3:
            for(int j = 0; j < height; j++){
                for(int i =0; i < width; i++){
                    xo = amplitude1 * sin((2.0 * PI * (j/tPeriod1)) + phi1) ;
                    yo = amplitude2 * (sin(2.0 * PI* (i/tPeriod2)) + phi2);
                    int ix = min(width-1, max(0, (int) (i + xo)));
                    int iy = min(height-1, max(0, (int) (j + yo )));
                    outdata[j*width + i] = indata[iy* width + ix];
                    
                }
            }
            break;
    }
    
    // normalize image
    normalize(out, out,0,255,NORM_MINMAX,CV_8UC1);
    
}

int main(int argc, const char * argv[])
{

    Mat input = imread("/Users/abhishek/Documents/image\ processing/bauckhage.jpg",CV_LOAD_IMAGE_GRAYSCALE);
    
    Mat out1, out2, out3;
    
    warpFunc(input, out1, 30.0, 128.0, 0.0,30.0, 128.0, 0.0, 1);
    imshow("1", out1);

    waitKey();
    
    return 0;
    
    
}

