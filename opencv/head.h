#pragma once
#include<iostream>
#include<opencv2/objdetect.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
using namespace std;
using namespace cv;
class head {
	public :
	 string haar = "D:\\opencv\\build\\etc\\haarcascades\\haarcascade_frontalface_alt.xml";
	 string  lbp = "D:\\opencv\\build\\etc\\lbpcascades\\lbpcascade_frontalface_improved.xml";
	 string haareyes = "D:\\opencv\\build\\etc\\haarcascades\\haarcascade_eye.xml";
	 string picture1 = "D:\\desktop\\ps\\33.jpg";
	 string picture2 = "D:\\desktop\\ps\\me.jpg";
	 

	 string hat = "D:\\desktop\\ps\\hat.png";
	 string person = "D:\\desktop\\ps\\cai.jpg";
	 string huaji = "D:\\desktop\\ps\\huaji2.png";
public:
	 int loaddetect();

};





