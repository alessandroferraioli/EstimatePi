#ifndef ESTIMATEPI_H
#define ESTIMATEPI_H

#include <QWidget>
#include <QRandomGenerator>
#include <QTimer>
#include <QDateTime>
#include <QDebug>
#include "qcustomplot-source/qcustomplot.h"

#define DEFAULT_MAX_STEP 1000
#define CLOCK_TIMER 50
#define RES_RAND 1000


namespace Ui {
class EstimatePi;
}

class EstimatePi : public QWidget
{
    Q_OBJECT

public:
    explicit EstimatePi(int maxStep = DEFAULT_MAX_STEP,QWidget *parent = nullptr);
    void Estimate(unsigned int batchSize = 50);

    ~EstimatePi();

private:

    float UpdateEstimate();
    Ui::EstimatePi *ui;

    float mPointIn{0};
    float mPointOut{0};
    unsigned int mBatchSize{50};
    float mEstimatedPi{0};
    int mEstimationStep{0};
    int mMaxStep{DEFAULT_MAX_STEP};

    std::shared_ptr<QCustomPlot> mPlot;
};

#endif // ESTIMATEPI_H
