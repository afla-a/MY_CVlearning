

#include "DR.h"
#include<iostream>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<cmath>
using namespace std;
using namespace cv;

int main (){
    
    Mat src,dst,NOZ,nbr,nbr0;
    
    src=imread("einstein.jpg",CV_LOAD_IMAGE_GRAYSCALE);
//    for (int i=0; i<3; i++) {
//        for (int j=0; j<src.cols-10; j++) {
//            cout<<(int)src.at<uchar>(i,j);
//            cout<<" ";
//        }
//        cout<<endl;
//    }
    
    double PI =3.141592653589793;
    double ei =2.71;

    float sigma=1.0;
    dst=src.clone();
    nbr=src.clone();
    int mask_size=9;
    int F=floor(mask_size/2);
    double **m=new double *[mask_size];
    for (int i=0; i<mask_size; i++) {
        m[i]=new double[mask_size];
    }
   
    
    
/////////////////////////////////////////////////// Gaussian ////
    
//    for (int y=-1; y<2; y++) {
//        for (int x=-1; x<2; x++) {
//            
//            m[F+x][F+y]=(1.0/(2.0*PI*(sigma*sigma)))*(exp((x*x+y*y)/(-2.0*sigma*sigma)));
//            
//        }
//    }
//    
//    double filtersum=0;
//    for (int y=0; y<3; y++) {
//        for (int x=0; x<3; x++) {
//            
//           cout<< m[x][y]<<endl;
//            
//        }
//    }
/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////// Laplacian   ////
    for (int y=-F; y<F+1; y++) {
        for (int x=-F; x<F+1; x++) {
            
            m[F+x][F+y]=(((-1.0)/(PI*sigma*sigma*sigma*sigma))*(1.0-((x*x+y*y)/(2.0*sigma*sigma))))*(exp((x*x+y*y)/(-2.0*sigma*sigma)));
            
//             m[F+x][F+y]=(((x*x+y*y)-(2.0*sigma*sigma))/(sigma*sigma*sigma*sigma))*(exp((x*x+y*y)/(2.0*sigma*sigma)));
        }
    }
    
////////////////////////////////////////////////////////////////////
    
//    for (int y=0; y<mask_size; y++) {
//        for (int x=0; x<mask_size; x++) {
//            
//            cout<< m[x][y]<<endl;
//            
//        }
//    }
//
//    
 
  

    
//    
//    m[0][0]=(0.0625);
//    m[0][1]=(0.125);
//    m[0][2]=(0.0625);
//    m[1][0]=(0.125);
//    m[1][1]=(0.25);
//    m[1][2]=(0.125);
//    m[2][0]=(0.0625);
//    m[2][1]=(0.125);
//    m[2][2]=(0.0625);
//    
//    m[0][0]=(1);
//    m[0][1]=(0);
//    m[0][2]=(-1);
//    m[1][0]=(2);
//    m[1][1]=(0);
//    m[1][2]=(-2);
//    m[2][0]=(1);
//    m[2][1]=(0);
//    m[2][2]=(-1);
    
//    m[0][0]=(0);
//    m[0][1]=(1);
//    m[0][2]=(0);
//    m[1][0]=(1);
//    m[1][1]=(-4);
//    m[1][2]=(1);
//    m[2][0]=(0);
//    m[2][1]=(1);
//    m[2][2]=(0);
    
   // cout<<m[0][0]<<endl;
    
    
    
//    double mask[]= {0.0545, 0.2442, 0.4026, 0.2442, 0.0545};
//////////////////////////////////////////////////////////////////
//    nbr0=src.clone();
//    
//    for ( int i = 1; i < mask_size; i = i + 2 )
//    { GaussianBlur( nbr0, nbr, Size( i, i ), 0, 0 );
//    }
    
//    for (int i=0; i<src.rows; i++) {
//        for (int j=0; j<src.cols;j++) {
//            
//            double sum=0.0;
//            for (int k=-2; k<3; k++) {
//                
//            if (j+k<0 || j-k==src.cols) {
//                dst.at<uchar>(i,j)=0;
//                break;
//            }
//            else{
//                sum=mask[k+1]*(double)src.at<uchar>(i,j+k)+sum;
//            }
//            
//            }
//            dst.at<uchar>(i,j)=sum;
//        }
//    }
    
//////////////////////////////////////////////////////////////////
    
//    for (int j=0; j<src.cols; j++) {
//        for (int i=0; i<src.rows;i++) {
//            
//            double sum=0.0;
//            for (int k=-1; k<2; k++) {
//                
//                if (i+k<0 || i-k==src.rows) {
//                    dst.at<uchar>(i,j)=0;
//                    break;
//                }
//                else{
//                    sum=mask[k+1]*(double)src.at<uchar>(i+k,j)+sum;
//                }
//                
//            }
//            dst.at<uchar>(i,j)=sum;
//        }
//    }
    
///////////////////////////////////////////////////////////////////
    
    for (int i=0; i<src.rows; i++) {
        for (int j=0; j<src.cols;j++) {
            
            double sum=0.0;
            for (int k=-(F); k<(F+1); k++) {
               for (int k2=-(F); k2<(F+1); k2++) {
                if (j+k2<0 || j-k2>=src.cols || i+k2<0 || i-k2>=src.rows) {
                    dst.at<uchar>(i,j)=0;
                    break;
                }
                else{
                    sum=m[k+F][k2+F]*(double)src.at<uchar>(i+k,j+k2)+sum;
                }
                
            }
            }
            
//            if (sum < 0) sum = 0;
//            if (sum > 255) sum = 255;
            if (-13 <sum & sum< 13) {
                sum =255;
            }
            else
                sum =0;
            dst.at<uchar>(i,j) = sum;
            
        }
    }
//
//    m[0][0]=(1);
//    m[0][1]=(2);
//    m[0][2]=(1);
//    m[1][0]=(0);
//    m[1][1]=(0);
//    m[1][2]=(0);
//    m[2][0]=(-1);
//    m[2][1]=(-2);
//    m[2][2]=(-1);
//    
    for (int j=0; j<src.cols; j++) {
        for (int i=0; i<src.rows;i++) {
            
            double sum=0.0;
            for (int k=-(F); k<(F+1); k++) {
                for (int k2=-(F); k2<(F+1); k2++) {
                    if (j+k2<0 || j-k2>=src.cols || i+k2<0 || i-k2>=src.rows) {
                        nbr.at<uchar>(i,j)=0;
                        break;
                    }
                    else{
                        sum=m[k+F][k2+F]*(double)src.at<uchar>(i+k,j+k2)+sum;
                    }
                    
                }
            }
            
//           if (sum < 0) sum = 0;
//			if (sum > 255) sum = 255;
            
            if (-13 <sum & sum< 13) {
                sum =255;
            }
            else
                sum =0;
                
            nbr.at<uchar>(i,j) = sum;
        }
    }
    
   
    
    nbr0=nbr+dst;
    
    
    
    
    
    
//    for (int i=0; i<2; i++) {
//        for (int j=0; j<src.cols; j++) {
//           cout<<(double)dst.at<uchar>(i,j);
//            cout<<" ";
//        }
//        cout<<endl;
//    }
//    
    
    
    
    
    
//    imshow("pictureblur",nbr);
    imshow("picture0",dst);
    imshow("picture1",nbr);
    
    imshow("newpicture",nbr0);
  //  imshow("picture",src);
    waitKey();
    return 0;
}
