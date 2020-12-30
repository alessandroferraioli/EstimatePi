#include "estimatepi.h"
#include "ui_estimatepi.h"

EstimatePi::EstimatePi(int maxStep, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EstimatePi)
{
    if(maxStep>0)
        mMaxStep = maxStep;

    mPlot = std::make_shared<QCustomPlot>();
    mPlot->addGraph();//data

    mPlot->xAxis->setRange(0,maxStep);
    mPlot->yAxis->setRange(M_PI-0.5,M_PI+0.5);
    mPlot->setMinimumHeight(350);
    ui->setupUi(this);

    ui->plotLayout->addWidget(mPlot.get());
    ui->labelPi->setText(QString::number(M_PI));

    //Reference
    mPlot->addGraph();
    mPlot->graph(1)->addData(0,M_PI);
    mPlot->graph(1)->addData(mMaxStep,M_PI);
    mPlot->graph(1)->setPen(QPen(QColor(255, 0, 0)));

}

void EstimatePi::Estimate(unsigned int batchSize)
{
    mBatchSize = batchSize;
    UpdateEstimate();
}

EstimatePi::~EstimatePi()
{
    delete ui;
}

float EstimatePi::UpdateEstimate()
{
    QRandomGenerator gen;
    for(unsigned int i = 0; i<mBatchSize; i++)
    {
        gen.seed(quint32(QDateTime::currentMSecsSinceEpoch())+i);
        float x = float(gen.bounded(0,RES_RAND))/RES_RAND;
        float y = float(gen.bounded(0,RES_RAND))/RES_RAND;
        if(x*x+y*y<1)
            mPointIn++;
        else
            mPointOut++;

    }
    mEstimatedPi = 4*(mPointIn/(mPointIn+mPointOut));


    mPlot->graph(0)->addData(mEstimationStep,mEstimatedPi);
    mPlot->replot();
    //qDebug()<<"Estimation : "<<mEstimatedPi;
    mEstimationStep++;
    ui->labelEstimated->setText(QString::number(mEstimatedPi));
    ui->labelError->setText(QString::number(qAbs (M_PI-mEstimatedPi)));

    if(mEstimationStep<=mMaxStep)
        QTimer::singleShot(CLOCK_TIMER,this,&EstimatePi::UpdateEstimate);

    return mEstimatedPi;
}
