#ifndef GRADIENT_DESCENT_WIDGET_H
#define GRADIENT_DESCENT_WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QPushButton>
#include <QComboBox>
#include "Engine/Nodes/GradientDescent.h"
#include "Qt/Interfaces/INodeWidget.h"
#include "Qt/Widgets/SectionWidget.h"

class GradientDescentWidget : public INodeWidget<GradientDescent> {
    Q_OBJECT

public:
    GradientDescentWidget(GradientDescent* gradientDescent, QWidget* parent = nullptr);
    ~GradientDescentWidget();

    void setNode(GradientDescent* gradientDescent) override;
    void clearNode() override;

private slots:
    void onExpressionChanged(const QString& expression);
    void onXFromChanged(double xFrom);
    void onXToChanged(double xTo);
    void onXStepChanged(double xStep);
    void onYFromChanged(double yFrom);
    void onYToChanged(double yTo);
    void onYStepChanged(double yStep);

    void onMaxIterationChanged(int maxIteration);
    void onLearningRateChanged(double learningRate);
	void onPointCountChanged(int pointCount);
	void onPointSizeChanged(float pointSize);
	void onSimulationFrequencyChanged(int simulationFrequency);

	void onMethodChanged(GradientDescent::Method method);
    void onEpsilonChanged(double epsilon);
    void onDecayRateChanged(double decayRate);
    void onBeta1Changed(double beta1);
    void onBeta2Changed(double beta2);

    void onExpressionSet(const QString& expression);
	void onXFromSet(double xFrom);
	void onXToSet(double xTo);
	void onXStepSet(double xStep);
	void onYFromSet(double yFrom);
	void onYToSet(double yTo);
	void onYStepSet(double yStep);

	void onMaxIterationSet(int maxIteration);
	void onLearningRateSet(double learningRate);
	void onPointCountSet(int pointCount);
	void onPointSizeSet(double pointSize);
	void onSimulationFrequencySet(double simulationFrequency);

	void onMethodSet(int method);
    void onEpsilonSet(double epsilon);
    void onDecayRateSet(double decayRate);
    void onBeta1Set(double beta1);
    void onBeta2Set(double beta2);


    void onReloadMeshClicked(); 
	void onRandomizeSimulationClicked();


private:
    void updateUI() override;
    void connectSignals() override;
    void disconnectSignals() override;
    void blockSignals(bool) override;

private:
    SectionWidget* mSection;
    QLineEdit* mExpressionEdit;

    QDoubleSpinBox* mXFromSpin;
    QDoubleSpinBox* mXToSpin;
    QDoubleSpinBox* mXStepSpin;
    QDoubleSpinBox* mYFromSpin;
    QDoubleSpinBox* mYToSpin;
    QDoubleSpinBox* mYStepSpin;

    QSpinBox* mMaxIterationSpin;
    QDoubleSpinBox* mLearningRateSpin;
	QSpinBox* mPointCountSpin;
    QDoubleSpinBox* mPointSizeSpin;
    QDoubleSpinBox* mSimulationFrequencySpin;
	QComboBox* mMethodCombo;

    QDoubleSpinBox* mEpsilonSpin;
    QDoubleSpinBox* mDecayRateSpin;
    QDoubleSpinBox* mBeta1Spin;
    QDoubleSpinBox* mBeta2Spin;

    QPushButton* mReloadMeshButton;
	QPushButton* mRandomizeSimulationButton;
};

#endif // GRADIENT_DESCENT_WIDGET_H
