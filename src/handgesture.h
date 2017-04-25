#ifndef HANDGESTURE_H
#define HANDGESTURE_H

//add QT head
#include <QWidget>
#include <QTimer>
#include <QImage>
#include <QInputDialog>
#include <QDebug>
#include <QDir>
#include <QMessageBox>
#include <QFileDialog>
#include <QPalette>

#include "common.h"
#include "database_api.h"


namespace Ui {
class handGesture;
}

class handGesture : public QWidget
{
    Q_OBJECT

public:
    explicit handGesture(QWidget *parent = 0);
    ~handGesture();
    void GetFeature(IplImage* src,Point2f center,float radius,SGestureFeature &feature);
private slots:
    void on_pushButton_openCamera_clicked();
    void readFrame();
    void handGestureDrawing();
    void sourceImagePreprocessing(Mat original);
    void ComputeHandGestureCenterPoint(vector<Point2f> & center);
    void ComputeHandGestureMaxCenterRadius(vector<Point2f> center,float &radius);
    void RecogniseHandGestureSeq(vector<Point2f> &ptArr, float width, float height, string &result);
    void getCurrentFilePath();
    QDir SetFolderPath(int num);//return image path
    void saveImageWithDialog();
    void on_pushButton_captureImage_clicked();
    void findConvexityDefects(vector<Point>& contour, vector<int>& hull, vector<ConvexityDefect>& convexDefects);
    void init_hand_template(void);
    void hand_template_match(void);
    int RecogniseResult(vector<int> iArray);
    void binary_image_process(Mat src);
    void on_pushButton_startRecognize_clicked();
    void on_pushButton_DirectionRecognize_clicked();
    void handRecogniseResult();
    void judgeCurrentDrawingColor(Point curPoint);
    void on_pushButton_ClearDrawing_clicked();
    void on_pushButton_StartDrawing_clicked();
private:
    Ui::handGesture *ui;

    QTimer *timer;

    VideoCapture cap;
    cv::Mat frame;
    cv::Mat captureframe;
    cv::Mat binImage;
    cv::Mat dstImage;
    cv::Mat maskImage;
    int centerNum=0;
    int recResult;
    vector< vector<Point> > contours;
    vector< vector<Point> > filterContours;
    vector< Vec4i > hierarchy;
    vector< Point > hull;

    vector<Point2f> centerArray;
    vector<Point2f> cornerArray;
    string sCurrentFilepPath;
    vector<Point> approxCurve;
    Scalar sColor;
    vector <DrawPointAttribute> DPA;
    vector< vector<Point> > mContoursTemp;
    vector<int> mResultArray;
    vector< Mat > tempImage;
    enum operation{ENOTHING=0,ESTARTDRAWING,ECLEARDRAWING,EDIGITRECOGNIZE,EDIRRECOGNIZE,ELAST}EOperation;
};

#endif // HANDGESTURE_H
