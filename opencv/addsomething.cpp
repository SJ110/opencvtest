#include"head.h"

using namespace std;
using namespace cv;


int head::loaddetect() {
	CascadeClassifier cascade;

	if (!cascade.load(haar)) {
		cout << "haar detect can not load" << endl;
		return 0;
	}
	CascadeClassifier cascade1;
	if (!cascade1.load(lbp)) {
		cout << "lbp detect can not load" << endl;
		return 0;
	}
	CascadeClassifier cascade2;
	if (!cascade2.load(haareyes)) {
		cout << "haareyes detector can not load" << endl;
		return 0;
	}
	return 1;
}

int meltpicture(Mat& hat, Mat& person,Mat& hat2,int flag);

int meltpicture(Mat& hat, Mat& dst,Mat& hat2,int flag) {
	Mat person,hat_rgb;
	vector<Mat> mv;
	split(hat, mv);  //ȡalphaͨ��
	hat_rgb = hat2.clone();
	cout << hat_rgb.type() << endl;


	CascadeClassifier cascadeface;
	head header;
	if (header.loaddetect() == 0) return 0;
	cascadeface.load(header.haar);
	CascadeClassifier cascadeeyes;
	cascadeeyes.load(header.haareyes);

	cvtColor(dst, person, COLOR_BGR2GRAY);
	equalizeHist(person, person);//��֤��Сһ��
	vector<Rect> face;
	cascadeface.detectMultiScale(person, face, 1.1, 3, 0| CASCADE_SCALE_IMAGE, Size(40, 40));
	if (face.empty()) {
		cout << "can not find a face" << endl;
		return 0; //û������
	} 
	for (vector<Rect>::iterator it = face.begin(); it != face.end(); it++) {
		//ʶ���۾�������ƴͼ
		
		//face
		//�ҵ�����ü�ĵ�λ��
		//cout << hat_rgb.size().height << " " << hat_rgb.size().width << " " << it->width<<endl; //for debug
		int hathight = (int)(hat_rgb.size().height * it->width / hat_rgb.size().width ); //�ȱȷ��� ,�ȼ���˷���֤��Ϊ0
		//cout<<hathight; //for debug
		Point center;
		center.x = cvRound(it->x + it->width / 2);
		center.y = cvRound(it->y - 20); //ü������20����
		if (center.y - 40 < 0) {
			cout << "be sure person's head and upper has enough space" << endl;
			return 0;
		}
		
		int top=0;
		if (flag == 0) { //0 ͷ��
			top = center.y - 25 - hathight; //��Ҫ����ͷ�����
			if (top < 0) {
				top = 0;
			}
			if (hathight > (it->y - 20)) hathight = it->y - 20; //���ñ��Խ���ϱ߽�
		}
		if (flag == 1) {
			top = center.y;
			hathight = it->height;
;
		}


		
		Mat hat_rgbResize;
		resize(hat_rgb, hat_rgbResize, Size(it->width, hathight), 0, 0, INTER_LINEAR_EXACT); //ñ�Ӻ�ͷһ��width
		//Ȧ����Ȥ����
		Mat imgROI = dst(Rect(it->x,top, hat_rgbResize.size().width, hat_rgbResize.size().height));
		cout << dst.type() << endl;

		Mat mask,mask_inv;
		resize(mv[3], mask, Size(it->width, hathight)); //����mask
		bitwise_not(mask,mask_inv); //threshold ȡ��
	//	imshow("test4", mask);
	//	imshow("test3", mask_inv);
		Mat dstfirst = imgROI.clone();
		Mat dstsec = hat_rgbResize.clone();
		bitwise_and(imgROI, imgROI,dstfirst,mask_inv);  //��ñ��
		bitwise_and(hat_rgbResize, hat_rgbResize,dstsec, mask); //ȡñ��
		//�ϲ�
		resize(dstfirst, dstfirst , dstsec.size(),0,0); //��ֹ�������㵼�´�С��ͬ
		//imshow("test1", dstfirst);
		//imshow("test2", dstsec);
		Mat mydst;
		cout << dstfirst.size() << " " << dstsec.size() << endl;
		cout << dstfirst.type() << " "<<dstsec.type()<<endl;
		waitKey(0);
		cv::add(dstfirst,dstsec,mydst);
		imshow("test", mydst);
		waitKey(0);
		cout << dst.type() << " " << mydst.type() << endl;
		if ((mydst.size().width * mydst.size().height) != (imgROI.size().width * imgROI.size().height)) {
			resize(mydst, mydst, imgROI.size());
		}
		cout << mydst.type() << " " << dst.type() << endl;
		mydst.copyTo(imgROI); //�޸ĺ������Ż�ԭͼ


		//imshow("test2", mydst);
		//cv::addWeighted( mydst, 0.7,dst, 0.3, 1., dst);
		//imshow("test", dst);
		//waitKey(0);
		//cv::add(mydst, person ,person);	
	}
	return 1;
}
/*
int main() {
	Mat hat, person;
	Mat hat2;
	head header;
	hat = imread(header.hat,-1); //��ȡalpthaͨ��
	hat2 = imread(header.hat);
	cout << hat.type();	
	person = imread(header.person);
	if (hat.empty()) {
		cout << "can not load picture hat" << endl;
		return 0;
	}
	if (person.empty()) {
		cout << "can not load piture person" << endl;
		return 0;
	}
	resize(person, person, Size(400, 500), 0, 0);
	Mat person2 = person.clone();

	if (meltpicture(hat, person,hat2,0)) {
		imshow("test", person);
		waitKey(0);
	}
	
	Mat huaji,huaji2;
	huaji = imread(header.huaji,-1);
	huaji2 = imread(header.huaji);
	if (huaji.empty()) {
		cout << " can not load file" << endl;
		return 0;
	}
	if (meltpicture(huaji, person2, huaji2, 1)) {
		imshow("test", person2);
		waitKey(0);
	}
	system("pause");
	return 0;
}
*/