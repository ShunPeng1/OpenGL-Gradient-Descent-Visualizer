#include "Qt/Inspector/NodeWidgets/GradientDescentWidget.h"


GradientDescentWidget::GradientDescentWidget(GradientDescent* gradientDescent, QWidget* parent)
    : INodeWidget<GradientDescent>(parent) {

    QVBoxLayout* widgetLayout = new QVBoxLayout(this);
    mSection = new SectionWidget("Gradient Descent", 0, this);
    widgetLayout->addWidget(mSection);

    QVBoxLayout* mainLayout = new QVBoxLayout(mSection);

    // Expression
    QHBoxLayout* expressionLayout = new QHBoxLayout();
    QLabel* expressionLabel = new QLabel("Expression:");
    mExpressionEdit = new QLineEdit();
    expressionLayout->addWidget(expressionLabel);
    expressionLayout->addWidget(mExpressionEdit);
    mainLayout->addLayout(expressionLayout);

    // X From
    QHBoxLayout* xFromLayout = new QHBoxLayout();
    QLabel* xFromLabel = new QLabel("X From:");
    mXFromSpin = new QDoubleSpinBox();
    mXFromSpin->setRange(-1e6, 1e6);
    xFromLayout->addWidget(xFromLabel);
    xFromLayout->addWidget(mXFromSpin);
    mainLayout->addLayout(xFromLayout);

    // X To
    QHBoxLayout* xToLayout = new QHBoxLayout();
    QLabel* xToLabel = new QLabel("X To:");
    mXToSpin = new QDoubleSpinBox();
    mXToSpin->setRange(-1e6, 1e6);
    xToLayout->addWidget(xToLabel);
    xToLayout->addWidget(mXToSpin);
    mainLayout->addLayout(xToLayout);

    // X Step
    QHBoxLayout* xStepLayout = new QHBoxLayout();
    QLabel* xStepLabel = new QLabel("X Step:");
    mXStepSpin = new QDoubleSpinBox();
    mXStepSpin->setRange(0.0001, 1e3);
    xStepLayout->addWidget(xStepLabel);
    xStepLayout->addWidget(mXStepSpin);
    mainLayout->addLayout(xStepLayout);

    // Y From
    QHBoxLayout* yFromLayout = new QHBoxLayout();
    QLabel* yFromLabel = new QLabel("Y From:");
    mYFromSpin = new QDoubleSpinBox();
    mYFromSpin->setRange(-1e6, 1e6);
    yFromLayout->addWidget(yFromLabel);
    yFromLayout->addWidget(mYFromSpin);
    mainLayout->addLayout(yFromLayout);

    // Y To
    QHBoxLayout* yToLayout = new QHBoxLayout();
    QLabel* yToLabel = new QLabel("Y To:");
    mYToSpin = new QDoubleSpinBox();
    mYToSpin->setRange(-1e6, 1e6);
    yToLayout->addWidget(yToLabel);
    yToLayout->addWidget(mYToSpin);
    mainLayout->addLayout(yToLayout);

    // Y Step
    QHBoxLayout* yStepLayout = new QHBoxLayout();
    QLabel* yStepLabel = new QLabel("Y Step:");
    mYStepSpin = new QDoubleSpinBox();
    mYStepSpin->setRange(0.0001, 1e3);
    yStepLayout->addWidget(yStepLabel);
    yStepLayout->addWidget(mYStepSpin);
    mainLayout->addLayout(yStepLayout);

    // Max Iteration
    QHBoxLayout* maxIterationLayout = new QHBoxLayout();
    QLabel* maxIterationLabel = new QLabel("Max Iteration:");
    mMaxIterationSpin = new QSpinBox();
    mMaxIterationSpin->setRange(1, 1e6);
    maxIterationLayout->addWidget(maxIterationLabel);
    maxIterationLayout->addWidget(mMaxIterationSpin);
    mainLayout->addLayout(maxIterationLayout);

    // Learning Rate
    QHBoxLayout* learningRateLayout = new QHBoxLayout();
    QLabel* learningRateLabel = new QLabel("Learning Rate:");
    mLearningRateSpin = new QDoubleSpinBox();
    mLearningRateSpin->setRange(0.0001, 1.0);
    learningRateLayout->addWidget(learningRateLabel);
    learningRateLayout->addWidget(mLearningRateSpin);
    mainLayout->addLayout(learningRateLayout);

	// Point Count
	QHBoxLayout* pointCountLayout = new QHBoxLayout();
	QLabel* pointCountLabel = new QLabel("Point Count:");
	mPointCountSpin = new QSpinBox();
	mPointCountSpin->setRange(0, 1e6);
	pointCountLayout->addWidget(pointCountLabel);
	pointCountLayout->addWidget(mPointCountSpin);
	mainLayout->addLayout(pointCountLayout);

	// Simulation Frequency
	QHBoxLayout* simulationFrequencyLayout = new QHBoxLayout();
	QLabel* simulationFrequencyLabel = new QLabel("Simulation Frequency:");
	mSimulationFrequencySpin = new QSpinBox();
	mSimulationFrequencySpin->setRange(1, 1e6);
	simulationFrequencyLayout->addWidget(simulationFrequencyLabel);
	simulationFrequencyLayout->addWidget(mSimulationFrequencySpin);
	mainLayout->addLayout(simulationFrequencyLayout);

	// Reload Mesh
    QVBoxLayout* buttonLayout = new QVBoxLayout(this);
    mReloadMeshButton = new QPushButton("Reload Mesh", this);
    buttonLayout->addWidget(mReloadMeshButton);
	mainLayout->addLayout(buttonLayout);


    mSection->setContentLayout(*mainLayout);

    // Connect signals
    connect(mExpressionEdit, &QLineEdit::textChanged, this, &GradientDescentWidget::onExpressionSet);
    connect(mXFromSpin, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &GradientDescentWidget::onXFromSet);
    connect(mXToSpin, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &GradientDescentWidget::onXToSet);
    connect(mXStepSpin, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &GradientDescentWidget::onXStepSet);
    connect(mYFromSpin, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &GradientDescentWidget::onYFromSet);
    connect(mYToSpin, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &GradientDescentWidget::onYToSet);
    connect(mYStepSpin, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &GradientDescentWidget::onYStepSet);
    connect(mMaxIterationSpin, QOverload<int>::of(&QSpinBox::valueChanged), this, &GradientDescentWidget::onMaxIterationSet);
    connect(mLearningRateSpin, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &GradientDescentWidget::onLearningRateSet);
	connect(mPointCountSpin, QOverload<int>::of(&QSpinBox::valueChanged), this, &GradientDescentWidget::onPointCountSet);
	connect(mSimulationFrequencySpin, QOverload<int>::of(&QSpinBox::valueChanged), this, &GradientDescentWidget::onSimulationFrequencySet);
	connect(mReloadMeshButton, &QPushButton::clicked, this, &GradientDescentWidget::onReloadMeshClicked);

    setNode(gradientDescent);
}

GradientDescentWidget::~GradientDescentWidget() {
    clearNode();
}

void GradientDescentWidget::setNode(GradientDescent* gradientDescent) {
    disconnectSignals();
    mNode = gradientDescent;
    updateUI();
    connectSignals();
}

void GradientDescentWidget::clearNode() {
    disconnectSignals();
    mNode = nullptr;
}

void GradientDescentWidget::onExpressionChanged(const QString& expression) {
	mExpressionEdit->blockSignals(true);
    mExpressionEdit->setText(expression);
	mExpressionEdit->blockSignals(false);
}

void GradientDescentWidget::onXFromChanged(double xFrom) {
	mXFromSpin->blockSignals(true);
    mXFromSpin->setValue(xFrom);
	mXFromSpin->blockSignals(false);
}

void GradientDescentWidget::onXToChanged(double xTo) {
	mXToSpin->blockSignals(true);
    mXToSpin->setValue(xTo);
	mXToSpin->blockSignals(false);
}

void GradientDescentWidget::onXStepChanged(double xStep) {
	mXStepSpin->blockSignals(true);
    mXStepSpin->setValue(xStep);
	mXStepSpin->blockSignals(false);
}

void GradientDescentWidget::onYFromChanged(double yFrom) {
	mYFromSpin->blockSignals(true);
    mYFromSpin->setValue(yFrom);
	mYFromSpin->blockSignals(false);
}

void GradientDescentWidget::onYToChanged(double yTo) {
	mYToSpin->blockSignals(true);
    mYToSpin->setValue(yTo);
	mYToSpin->blockSignals(false);
}

void GradientDescentWidget::onYStepChanged(double yStep) {
	mYStepSpin->blockSignals(true);
    mYStepSpin->setValue(yStep);
	mYStepSpin->blockSignals(false);
}

void GradientDescentWidget::onMaxIterationChanged(int maxIteration) {
	mMaxIterationSpin->blockSignals(true);
    mMaxIterationSpin->setValue(maxIteration);
	mMaxIterationSpin->blockSignals(false);
}

void GradientDescentWidget::onLearningRateChanged(double learningRate) {
	mLearningRateSpin->blockSignals(true);
    mLearningRateSpin->setValue(learningRate);
	mLearningRateSpin->blockSignals(false);
}

void GradientDescentWidget::onPointCountChanged(int pointCount) {
	mPointCountSpin->blockSignals(true);
    mPointCountSpin->setValue(pointCount);
	mPointCountSpin->blockSignals(false);
}

void GradientDescentWidget::onSimulationFrequencyChanged(int simulationFrequency) {
	mSimulationFrequencySpin->blockSignals(true);
	mSimulationFrequencySpin->setValue(simulationFrequency);
	mSimulationFrequencySpin->blockSignals(false);
}

void GradientDescentWidget::onExpressionSet(const QString& expression) {
    if (mNode) {
        mNode->setExpression(expression);
    }
}

void GradientDescentWidget::onXFromSet(double xFrom) {
    if (mNode) {
        mNode->setXFrom(static_cast<float>(xFrom));
    }
}

void GradientDescentWidget::onXToSet(double xTo) {
    if (mNode) {
        mNode->setXTo(static_cast<float>(xTo));
    }
}

void GradientDescentWidget::onXStepSet(double xStep) {
    if (mNode) {
        mNode->setXStep(static_cast<float>(xStep));
    }
}

void GradientDescentWidget::onYFromSet(double yFrom) {
    if (mNode) {
        mNode->setYFrom(static_cast<float>(yFrom));
    }
}

void GradientDescentWidget::onYToSet(double yTo) {
    if (mNode) {
        mNode->setYTo(static_cast<float>(yTo));
    }
}

void GradientDescentWidget::onYStepSet(double yStep) {
    if (mNode) {
        mNode->setYStep(static_cast<float>(yStep));
    }
}

void GradientDescentWidget::onMaxIterationSet(int maxIteration) {
    if (mNode) {
        mNode->setMaxIteration(maxIteration);
    }
}

void GradientDescentWidget::onLearningRateSet(double learningRate) {
    if (mNode) {
        mNode->setLearningRate(static_cast<float>(learningRate));
    }
}

void GradientDescentWidget::onPointCountSet(int pointCount) {
    if (mNode) {
        mNode->setPointCount(pointCount);
    }
}

void GradientDescentWidget::onSimulationFrequencySet(int simulationFrequency) {
    if (mNode) {
        mNode->setSimulationFrequency(static_cast<float>(simulationFrequency));
    }
}

void GradientDescentWidget::onReloadMeshClicked()
{
    if (mNode) {
        mNode->ReloadMesh();
    }
}

void GradientDescentWidget::updateUI() {
    blockSignals(true);
    if (mNode) {
        mExpressionEdit->setText(mNode->getExpression());
        mXFromSpin->setValue(mNode->getXFrom());
        mXToSpin->setValue(mNode->getXTo());
        mXStepSpin->setValue(mNode->getXStep());
        mYFromSpin->setValue(mNode->getYFrom());
        mYToSpin->setValue(mNode->getYTo());
        mYStepSpin->setValue(mNode->getYStep());
        mMaxIterationSpin->setValue(mNode->getMaxIteration());
        mLearningRateSpin->setValue(mNode->getLearningRate());
    }
    else {
        mExpressionEdit->clear();
        mXFromSpin->setValue(0.0);
        mXToSpin->setValue(0.0);
        mXStepSpin->setValue(0.1);
        mYFromSpin->setValue(0.0);
        mYToSpin->setValue(0.0);
        mYStepSpin->setValue(0.1);
        mMaxIterationSpin->setValue(100);
        mLearningRateSpin->setValue(0.01);
    }
    blockSignals(false);
}

void GradientDescentWidget::connectSignals() {
    if (!mNode) return;

    connect(mNode, &GradientDescent::expressionChanged, this, &GradientDescentWidget::onExpressionChanged);
    connect(mNode, &GradientDescent::xFromChanged, this, &GradientDescentWidget::onXFromChanged);
    connect(mNode, &GradientDescent::xToChanged, this, &GradientDescentWidget::onXToChanged);
    connect(mNode, &GradientDescent::xStepChanged, this, &GradientDescentWidget::onXStepChanged);
    connect(mNode, &GradientDescent::yFromChanged, this, &GradientDescentWidget::onYFromChanged);
    connect(mNode, &GradientDescent::yToChanged, this, &GradientDescentWidget::onYToChanged);
    connect(mNode, &GradientDescent::yStepChanged, this, &GradientDescentWidget::onYStepChanged);
    connect(mNode, &GradientDescent::maxIterationChanged, this, &GradientDescentWidget::onMaxIterationChanged); 
    connect(mNode, &GradientDescent::learningRateChanged, this, &GradientDescentWidget::onLearningRateChanged);
	connect(mNode, &GradientDescent::pointCountChanged, this, &GradientDescentWidget::onPointCountChanged);
}

void GradientDescentWidget::disconnectSignals() {
    if (!mNode) return;

    disconnect(mNode, &GradientDescent::expressionChanged, this, &GradientDescentWidget::onExpressionChanged);
    disconnect(mNode, &GradientDescent::xFromChanged, this, &GradientDescentWidget::onXFromChanged);
    disconnect(mNode, &GradientDescent::xToChanged, this, &GradientDescentWidget::onXToChanged);
    disconnect(mNode, &GradientDescent::xStepChanged, this, &GradientDescentWidget::onXStepChanged);
    disconnect(mNode, &GradientDescent::yFromChanged, this, &GradientDescentWidget::onYFromChanged);
    disconnect(mNode, &GradientDescent::yToChanged, this, &GradientDescentWidget::onYToChanged);
    disconnect(mNode, &GradientDescent::yStepChanged, this, &GradientDescentWidget::onYStepChanged);
    disconnect(mNode, &GradientDescent::maxIterationChanged, this, &GradientDescentWidget::onMaxIterationChanged);
    disconnect(mNode, &GradientDescent::learningRateChanged, this, &GradientDescentWidget::onLearningRateChanged);
	disconnect(mNode, &GradientDescent::pointCountChanged, this, &GradientDescentWidget::onPointCountChanged);
}

void GradientDescentWidget::blockSignals(bool block) { 
    mExpressionEdit->blockSignals(block); 
    mXFromSpin->blockSignals(block); 
    mXToSpin->blockSignals(block); 
    mXStepSpin->blockSignals(block); 
    mYFromSpin->blockSignals(block); 
    mYToSpin->blockSignals(block); 
    mYStepSpin->blockSignals(block); 
    mMaxIterationSpin->blockSignals(block); 
    mLearningRateSpin->blockSignals(block); 
	mPointCountSpin->blockSignals(block);
}

