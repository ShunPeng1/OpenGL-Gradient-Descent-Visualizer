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
    mXStepSpin->setRange(-1e6, 1e6);
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
    mLearningRateSpin->setRange(-1e6, 1e6);
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

	// Point Size
	QHBoxLayout* pointSizeLayout = new QHBoxLayout();
	QLabel* pointSizeLabel = new QLabel("Point Size:");
	mPointSizeSpin = new QDoubleSpinBox();
	mPointSizeSpin->setRange(0.01, 1e6);
	pointSizeLayout->addWidget(pointSizeLabel);
	pointSizeLayout->addWidget(mPointSizeSpin);
	mainLayout->addLayout(pointSizeLayout);


	// Simulation Frequency
	QHBoxLayout* simulationFrequencyLayout = new QHBoxLayout();
	QLabel* simulationFrequencyLabel = new QLabel("Simulation Frequency:");
	mSimulationFrequencySpin = new QDoubleSpinBox();
	mSimulationFrequencySpin->setRange(0.01, 1e6);
	simulationFrequencyLayout->addWidget(simulationFrequencyLabel);
	simulationFrequencyLayout->addWidget(mSimulationFrequencySpin);
	mainLayout->addLayout(simulationFrequencyLayout);

	// Method
	QHBoxLayout* methodLayout = new QHBoxLayout();
	QLabel* methodLabel = new QLabel("Method:");
	mMethodCombo = new QComboBox();
	mMethodCombo->addItem("SGD");
	mMethodCombo->addItem("Momentum");
	mMethodCombo->addItem("Nesterov Momentum");
	mMethodCombo->addItem("AdaGrad");
	mMethodCombo->addItem("RMSProp");
	mMethodCombo->addItem("Adam");
	methodLayout->addWidget(methodLabel);
	methodLayout->addWidget(mMethodCombo);
	mainLayout->addLayout(methodLayout);

	// Epsilon
	QHBoxLayout* epsilonLayout = new QHBoxLayout();
	QLabel* epsilonLabel = new QLabel("Epsilon:");
	mEpsilonSpin = new QDoubleSpinBox();
	mEpsilonSpin->setRange(0.00001, 1e6);
	epsilonLayout->addWidget(epsilonLabel);
	epsilonLayout->addWidget(mEpsilonSpin);
	mainLayout->addLayout(epsilonLayout);

	// Decay Rate
	QHBoxLayout* decayRateLayout = new QHBoxLayout();
	QLabel* decayRateLabel = new QLabel("Decay Rate:");
	mDecayRateSpin = new QDoubleSpinBox();
	mDecayRateSpin->setRange(0.00001, 1e6);
	decayRateLayout->addWidget(decayRateLabel);
	decayRateLayout->addWidget(mDecayRateSpin);
	mainLayout->addLayout(decayRateLayout);

	// Beta 1
	QHBoxLayout* beta1Layout = new QHBoxLayout();
	QLabel* beta1Label = new QLabel("Beta 1:");
	mBeta1Spin = new QDoubleSpinBox();
	mBeta1Spin->setRange(0.00001, 1e6);
	beta1Layout->addWidget(beta1Label);
	beta1Layout->addWidget(mBeta1Spin);
	mainLayout->addLayout(beta1Layout);

	// Beta 2
	QHBoxLayout* beta2Layout = new QHBoxLayout();
	QLabel* beta2Label = new QLabel("Beta 2:");
	mBeta2Spin = new QDoubleSpinBox();
	mBeta2Spin->setRange(0.00001, 1e6);
	beta2Layout->addWidget(beta2Label);
	beta2Layout->addWidget(mBeta2Spin);
	mainLayout->addLayout(beta2Layout);


	// Reload Mesh
    QVBoxLayout* buttonLayout = new QVBoxLayout(this);
    mReloadMeshButton = new QPushButton("Reload Mesh", this);
    buttonLayout->addWidget(mReloadMeshButton);
	mainLayout->addLayout(buttonLayout);

	// Randomize Simulation
	QVBoxLayout* randomizeSimulationLayout = new QVBoxLayout(this);
	mRandomizeSimulationButton = new QPushButton("Randomize Simulation", this);
	randomizeSimulationLayout->addWidget(mRandomizeSimulationButton);
	mainLayout->addLayout(randomizeSimulationLayout);


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
	connect(mPointSizeSpin, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &GradientDescentWidget::onPointSizeSet);
	connect(mSimulationFrequencySpin, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &GradientDescentWidget::onSimulationFrequencySet);
	connect(mMethodCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &GradientDescentWidget::onMethodSet);
	
    connect(mEpsilonSpin, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &GradientDescentWidget::onEpsilonSet);
	connect(mDecayRateSpin, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &GradientDescentWidget::onDecayRateSet);
	connect(mBeta1Spin, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &GradientDescentWidget::onBeta1Set);
	connect(mBeta2Spin, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &GradientDescentWidget::onBeta2Set);

    connect(mReloadMeshButton, &QPushButton::clicked, this, &GradientDescentWidget::onReloadMeshClicked);
	connect(mRandomizeSimulationButton, &QPushButton::clicked, this, &GradientDescentWidget::onRandomizeSimulationClicked);

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

void GradientDescentWidget::onPointSizeChanged(float pointSize)
{
	mPointSizeSpin->blockSignals(true);
	mPointSizeSpin->setValue(pointSize);
	mPointSizeSpin->blockSignals(false);
}

void GradientDescentWidget::onSimulationFrequencyChanged(int simulationFrequency) {
	mSimulationFrequencySpin->blockSignals(true);
	mSimulationFrequencySpin->setValue(simulationFrequency);
	mSimulationFrequencySpin->blockSignals(false);
}

void GradientDescentWidget::onMethodChanged(GradientDescent::Method method)
{
	mMethodCombo->blockSignals(true);
	mMethodCombo->setCurrentIndex(static_cast<int>(method));
	mMethodCombo->blockSignals(false);
}

void GradientDescentWidget::onEpsilonChanged(double epsilon)
{
	mEpsilonSpin->blockSignals(true);
	mEpsilonSpin->setValue(epsilon);
	mEpsilonSpin->blockSignals(false);
}

void GradientDescentWidget::onDecayRateChanged(double decayRate)
{
	mDecayRateSpin->blockSignals(true);
	mDecayRateSpin->setValue(decayRate);
	mDecayRateSpin->blockSignals(false);
}

void GradientDescentWidget::onBeta1Changed(double beta1)
{
	mBeta1Spin->blockSignals(true);
	mBeta1Spin->setValue(beta1);
	mBeta1Spin->blockSignals(false);
}

void GradientDescentWidget::onBeta2Changed(double beta2)
{
	mBeta2Spin->blockSignals(true);
	mBeta2Spin->setValue(beta2);
	mBeta2Spin->blockSignals(false);
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

void GradientDescentWidget::onPointSizeSet(double pointSize)
{
	if (mNode) {
		mNode->setPointSize(static_cast<float>(pointSize));
	}
}

void GradientDescentWidget::onSimulationFrequencySet(double simulationFrequency) {
    if (mNode) {
        mNode->setSimulationFrequency(static_cast<float>(simulationFrequency));
    }
}

void GradientDescentWidget::onMethodSet(int method)
{
	if (mNode) {
		mNode->setMethod(static_cast<GradientDescent::Method>(method));
	}
}

void GradientDescentWidget::onEpsilonSet(double epsilon)
{
	if (mNode) {
		mNode->setEpsilon(static_cast<float>(epsilon));
	}
}

void GradientDescentWidget::onDecayRateSet(double decayRate)
{
	if (mNode) {
		mNode->setDecayRate(static_cast<float>(decayRate));
	}
}

void GradientDescentWidget::onBeta1Set(double beta1)
{
	if (mNode) {
		mNode->setBeta1(static_cast<float>(beta1));
	}
}

void GradientDescentWidget::onBeta2Set(double beta2)
{
	if (mNode) {
		mNode->setBeta2(static_cast<float>(beta2));
	}
}

void GradientDescentWidget::onReloadMeshClicked()
{
    if (mNode) {
        mNode->reloadMesh();
    }
}

void GradientDescentWidget::onRandomizeSimulationClicked()
{
	if (mNode) {
		mNode->randomizeSimulation();
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
		mPointCountSpin->setValue(mNode->getPointCount());
		mPointSizeSpin->setValue(mNode->getPointSize());
        mMaxIterationSpin->setValue(mNode->getMaxIteration());
        mLearningRateSpin->setValue(mNode->getLearningRate());
		mMethodCombo->setCurrentIndex(static_cast<int>(mNode->getMethod()));
		mSimulationFrequencySpin->setValue(mNode->getSimulationFrequency());
		mEpsilonSpin->setValue(mNode->getEpsilon());
		mDecayRateSpin->setValue(mNode->getDecayRate());
		mBeta1Spin->setValue(mNode->getBeta1());
		mBeta2Spin->setValue(mNode->getBeta2());
    }
    else {
        mExpressionEdit->clear();
        mXFromSpin->setValue(0.0);
        mXToSpin->setValue(0.0);
        mXStepSpin->setValue(0.1);
        mYFromSpin->setValue(0.0);
        mYToSpin->setValue(0.0);
        mYStepSpin->setValue(0.1);
		mPointCountSpin->setValue(0);
		mPointSizeSpin->setValue(0.1);
        mMaxIterationSpin->setValue(100);
        mLearningRateSpin->setValue(0.01);
		mMethodCombo->setCurrentIndex(0);
		mSimulationFrequencySpin->setValue(0.1);
		mEpsilonSpin->setValue(1e-8);
		mDecayRateSpin->setValue(0.9);
		mBeta1Spin->setValue(0.9);
		mBeta2Spin->setValue(0.999);

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
	connect(mNode, &GradientDescent::pointSizeChanged, this, &GradientDescentWidget::onPointSizeChanged);
	connect(mNode, &GradientDescent::simulationFrequencyChanged, this, &GradientDescentWidget::onSimulationFrequencyChanged);
	connect(mNode, &GradientDescent::methodChanged, this, &GradientDescentWidget::onMethodChanged);
	connect(mNode, &GradientDescent::epsilonChanged, this, &GradientDescentWidget::onEpsilonChanged);
	connect(mNode, &GradientDescent::decayRateChanged, this, &GradientDescentWidget::onDecayRateChanged);
	connect(mNode, &GradientDescent::beta1Changed, this, &GradientDescentWidget::onBeta1Changed);
	connect(mNode, &GradientDescent::beta2Changed, this, &GradientDescentWidget::onBeta2Changed);
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
	disconnect(mNode, &GradientDescent::pointSizeChanged, this, &GradientDescentWidget::onPointSizeChanged);
	disconnect(mNode, &GradientDescent::simulationFrequencyChanged, this, &GradientDescentWidget::onSimulationFrequencyChanged);
	disconnect(mNode, &GradientDescent::methodChanged, this, &GradientDescentWidget::onMethodChanged);
	disconnect(mNode, &GradientDescent::epsilonChanged, this, &GradientDescentWidget::onEpsilonChanged);
	disconnect(mNode, &GradientDescent::decayRateChanged, this, &GradientDescentWidget::onDecayRateChanged);
	disconnect(mNode, &GradientDescent::beta1Changed, this, &GradientDescentWidget::onBeta1Changed);
	disconnect(mNode, &GradientDescent::beta2Changed, this, &GradientDescentWidget::onBeta2Changed);
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
	mPointSizeSpin->blockSignals(block);
	mSimulationFrequencySpin->blockSignals(block);
	mMethodCombo->blockSignals(block);
	mEpsilonSpin->blockSignals(block);
	mDecayRateSpin->blockSignals(block);
	mBeta1Spin->blockSignals(block);
	mBeta2Spin->blockSignals(block);

}

