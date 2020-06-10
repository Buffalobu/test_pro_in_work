#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "msb/MsbIOPluginFunctions.h"
#include "msb/MsbSample.h"
#include "msb/MsbSampleSet.h"
#include "msb/MsbSpectrum.h"
#include "msb/MsbIO0202.h"

#include "cFileData.h"
#include "cconfigoms.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    long filesize(FILE *stream);

    bool isRestart = true;

    //about mass
    QByteArray mGraphBuffer;
    QByteArray mSegment;

    double Period = 1000;
    std::vector<qint64> pIndexArray;
    std::vector<double> pTicX;
    std::vector<double> pTicY;


    QByteArray pStreamHead , pStreamBody;
    QList<std::vector<double>> tmpThreadBuffX;
    QList<std::vector<double>> tmpThreadBuffY;
    QVector<qint64> mPageTIC;
    QList<_CONGIG_OMS::_STRUCT_DATA> listSTRUCT_DATA;


    int splitStreamHead(QByteArray& pStreamHead, cParamValue::_Segment*& pSegment);
    uint32_t dataDismantleFirst(QByteArray& pByteArray, cParamValue::_Segment* pSegment,
                                    QList<std::vector<double>>* pListX, QList<std::vector<double>>* pListY,
                                    QList<_CONGIG_OMS::_STRUCT_DATA>& pSTRUCT_DATA, bool restart);

//    cDataProcess* mDataProcess= nullptr;

    _CONGIG_OMS::_PARAM_FIT mCALIBRATE;
    QString mChartHead;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_UI_PB_CONVERT_clicked();

    void on_UI_PB_LOAD_clicked();

    void on_UI_PB_READMSB_clicked();

private:
    Ui::MainWindow *ui;
    kome::objects::Variant make_params(kome::objects::Parameters& params);
};
#endif // MAINWINDOW_H
