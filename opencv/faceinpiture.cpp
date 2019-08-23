#include<iostream>
#include"head.h"
using namespace cv;

void detectanddrow(Mat& img, CascadeClassifier& cascade,
	double scale);

void detectanddrow(Mat& img, CascadeClassifier& cascade,
	double scale)
{
	double t = 0;
	vector<Rect> face, face2;
	const static Scalar colors[] =
	{//��ͬ����ɫ��ʶ����
		Scalar(255,0,0),
		Scalar(255,128,0),
		Scalar(255,255,0),
		Scalar(0,255,0),
		Scalar(0,128,255),
		Scalar(0,255,255),
		Scalar(0,0,255),
		Scalar(255,0,255)
	};

	Mat gray, smallimg;
	cvtColor(img, gray, COLOR_BGR2GRAY); //ת��Ϊ�Ҷ�ͼ
	//resize(gray, smallimg, smallimg.size(), (double)(1 / scale), (double)(1 / scale), INTER_LINEAR_EXACT);
	//imshow("1", gray);
	resize(gray, smallimg, Size(), (double)(1 / scale), (double)(1 / scale), INTER_LINEAR_EXACT);
	
	//imshow("2", smallimg);
	equalizeHist(smallimg, smallimg); //��ֱ��ͼ��ֵ��
	t = (double)getTickCount();
	//�˴��������
	cascade.detectMultiScale(smallimg, face,
		1.1, 3, 0
		//|CASCADE_FIND_BIGGEST_OBJECT
		//|CASCADE_DO_ROUGH_SEARCH
		| CASCADE_SCALE_IMAGE,
		Size(30, 30)); //1.1ͼ��ߴ�ÿ����С1.1����
		//2 �ظ����2�Σ�CASCADE_SCALE_IMAGE ͨ������ͼ���⣬�����Ƿ���������
	
	t = (double)getTickCount();
	//cout << "detect time:" << t * 1000 / getTickFrequency() << "ms" << endl;
	//drow face
	for (size_t i = 0; i < face.size(); i++) {
		Rect r = face[i]; //x y ���Ͻǵ�����
		//Mat smallImgROI;
		Point center;
		Scalar color = colors[i % 8];
		int radius;

		double aspect_ratio = (double)r.width / r.height;
		//���ݳ������������Բ���ǻ�����
		if (aspect_ratio >= 0.75 && aspect_ratio <= 1.3) {
			center.x = cvRound((r.x + r.width * 0.5) * scale);
			center.y = cvRound((r.y + r.height * 0.5) * scale);
			radius = cvRound((r.width + r.height) * 0.25 * scale);
			circle(img, center, radius, color, 3, 8, 0); 
		}
		else {
			rectangle(img, Point(cvRound(r.x * scale), cvRound(r.y * scale)),
				Point(cvRound((r.x + r.width - 1) * scale), cvRound((r.y + r.height - 1) * scale)),
				color, 3, 8, 0);
		}
	}
	resize(img, img, Size(400, 500), 0, 0);
	return;
}

//main ����facedetect by camera or piture


/*
int main() {
	VideoCapture mycapture;
	Mat frame,image;
	//double scale;
	CascadeClassifier cascadeforhaar;
	CascadeClassifier cascadeforlbp;
	head header;
	if(!cascadeforhaar.load(header.haar)) {
		cout << "can not load haar classifier" << endl;
		return -1;
	}
	if (!cascadeforlbp.load(header.lbp)) {
		//������ͬ�ķ������Ƚ�
	
		cout << "can not load lbp classifler" << endl;
		return -1;
	}

	if (!mycapture.open(0)) { //detect from camera
		cout << "camera can not open" << endl;
		return -1;
	}
	
	*/



	 //first deal with camera  
	//blow using lbp to detect 
/*	cout << "start camera detect use haarclassifier,push q||Q to stop" << endl;
	if (mycapture.isOpened()) {
		while (1) {
			mycapture >> frame;

			if (frame.empty())
				break;

			Mat frame1 = frame.clone();
			detectanddrow(frame1, cascadeforhaar, 2);
			imshow("result", frame1);
			
			char c = (char)waitKey(50);
			if (c == 'q' || c == 'Q') {
				destroyWindow("result");
				break;
			}
		}
	}
	
//blow using haar to detect
/*
	cout << "start camera detect use lbpclassifier,push q||Q to stop";
	if (mycapture.isOpened()) { //lbp detect
		while (1) {
			mycapture >> frame;

			if (frame.empty())
				break;

			Mat frame1 = frame.clone();
			detectanddrow(frame1,cascadeforlbp, 2);
			imshow("result", frame1);
			char c = waitKey(10);
			if (c == 'q' || c == 'Q') {
				destroyWindow("result");
				break;
			}
				
		}
	}
	*/
	/*mycapture.release();

	image = imread(header.picture1, IMREAD_COLOR);//bgr��ȡ
	if (image.empty()) {
		cout << "can not read the image" << endl;
		return -1;
	}

	cout << "start detect image" << endl;
	if (!image.empty()) {
		detectanddrow(image, cascadeforhaar, 2);
		
		imshow("result", image);
		waitKey(0);
	}
	system("pause");
	return 0;
}

*/
