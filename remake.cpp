#include <opencv2/opencv.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;
enum e{r,b};
int main(){e e1;
    string path="resources/opencv小测试/light.mp4",b1;//补全路径
      VideoCapture cap(path);
      Mat img,outcol,coldone;
      int cont=0;
  
      
      do{
        cap.read(img);
       if(img.empty()){break;}
        //cvtColor(img,outcol,COLOR_BGR2HSV);
        cont++;
        if(cont<400){
        inRange(img,Scalar(0,0,150),Scalar(90,150,240),coldone);
        e1=r;
        }
        else if(cont>=400){
        inRange(img,Scalar(150,50,0),Scalar(255,120,50),coldone);
        e1=b;
        } 
     
     
     vector<vector<Point>> contours;
      vector<Vec4i> hierarchy;
      
      findContours(coldone, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
     
      for(int i=0;i<contours.size();i++){  vector<Rect> a(contours.size());   //遍历某一时刻的所有轮廓    
       vector<vector<Point>> con(contours.size());   if(contourArea(contours[i])>500){               
      if(!contours.empty()){float pericircle =arcLength(contours[i],true);
        approxPolyDP(contours[i],con[i],0.02*pericircle,true);
    a[i]=boundingRect(con[i]);};
          
  //drawContours(img, contours, -1, Scalar(255, 0, 255), 2);

if(e1==r){
 rectangle(img,a[i].tl(),a[i].br(),Scalar(0,0,255),4);
 putText(img,"RED LIght?",{a[i].x,a[i].y},FONT_HERSHEY_COMPLEX,1,Scalar(0,0,255));
}
else if(e1==b){
 rectangle(img,a[i].tl(),a[i].br(),Scalar(50,0,0),4);
 putText(img,"human",{a[i].x,a[i].y},FONT_HERSHEY_COMPLEX,3,Scalar(150,0,0));
}
     }


    }
       int fps=50;
       int wid=cap.get(CAP_PROP_FRAME_WIDTH);
      int hei=cap.get(CAP_PROP_FRAME_HEIGHT);
   VideoWriter OUT;
   int f=VideoWriter::fourcc('X','V','I','D');
  string outputPath="output.avi";
  OUT.open(outputPath,f,fps,Size(wid,hei),true);
  OUT.write(img);

       imshow("img",coldone);
        imshow("1",img);
        waitKey(20);//修改帧率
   } while(1);
    return 0;
}