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
//          
//
void warpFunc(Mat input, Mat &out, double amplitude1, double tPeriod1, double phi1, double amplitude2, double tPeriod2, double phi2)
{
    int height = input.rows;
    int width = input.cols;
    int c;
    double xo, yo;
    input.convertTo(input, CV_32FC1); // Convert image to float
    out = Mat(height, width, input.type());
    
    // data as array
    float *outdata = (float*)out.data;
    float *indata = (float*)input.data;
    
    
   
            for(int j = 0; j < height; j++){
                for(int i =0; i < width; i++){
                    xo = round(i + amplitude1 * sin(2.0 * PI * (j / tPeriod1) + (phi1*PI/180)));
                    yo = round(j + amplitude2 * cos(2.0 * PI * (i / tPeriod2) + (phi2*PI/180)));
                    if(xo >= width || xo < 0 ||
                       yo >= height || yo < 0)
                        c = 0;
                    else
                        c = indata[int(yo* width + xo)];
                    outdata[j*width+i] = c;
                    //                    outdata[int(yo*width + xo)] = indata[j* width + i];
                    
                }
            }
                
    
    // normalize image
    normalize(out, out,0,255,NORM_MINMAX,CV_8UC1);
    
}

int main(int argc, const char * argv[])
{
    
    Mat input = imread("/Users/abhishek/Documents/image\ processing/bauckhage.jpg",CV_LOAD_IMAGE_GRAYSCALE);
    
    Mat out1,out2;
    
    warpFunc(input, out1, 0.0, 128.0, 0.0, 15.0, 256.0, 0.0);
    imshow("res", out1);
    
    waitKey();
    
    return 0;
    
    
}

