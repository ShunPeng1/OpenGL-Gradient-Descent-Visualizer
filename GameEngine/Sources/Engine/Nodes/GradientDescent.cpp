#include "Engine/Nodes/GradientDescent.h"
#include "Engine/Loaders/ModelLoader.h"

GradientDescent::GradientDescent()
    : MeshRenderer(), mExpression("0"), mXFrom(0.0f), mXTo(1.0f), mXStep(0.1f),
    mYFrom(0.0f), mYTo(1.0f), mYStep(0.1f),
    mMaxIteration(1000), mLearningRate(0.01f),
    mPointCount(0)
{

}

GradientDescent::GradientDescent(QString expression, float xFrom, float xTo, float xStep, float yFrom, float yTo, float yStep, int maxIteration, float learningRate, int pointCount) 
    : MeshRenderer(), mExpression(expression), mXFrom(xFrom), mXTo(xTo), mXStep(xStep), 
    mYFrom(yFrom), mYTo(yTo), mYStep(yStep), 
    mMaxIteration(maxIteration), mLearningRate(learningRate), mPointCount(pointCount)
{


}

GradientDescent::~GradientDescent() noexcept
{
}

void GradientDescent::init()
{
    MeshRenderer::init();

}

void GradientDescent::start(IScene* scene)
{
    MeshRenderer::start(scene);

    ReloadMesh();
}

void GradientDescent::update(float deltaTime)
{
    MeshRenderer::update(deltaTime);

}

void GradientDescent::render(ShaderProgram& shaderProgram)
{
    MeshRenderer::render(shaderProgram);
}

void* GradientDescent::accept(INodeVisitor* visitor)
{
	return visitor->visitGradientDescent(this);
}

void GradientDescent::ReloadMesh()
{
    ModelLoader loader = ModelLoader::Builder().SetUseNormalColor(true).Build();

    ModelLoader::Range xRange(mXFrom, mXTo, mXStep);
    ModelLoader::Range yRange(mYFrom, mYTo, mYStep);

    Mesh* mesh = loader.loadPlane(mExpression, xRange, yRange, mResults);

    mesh->init();
    mesh->tryStart();
    
	setMesh(mesh, false);


}

void GradientDescent::setExpression(QString expression)
{
    if (mExpression != expression) {
        mExpression = expression;
        emit expressionChanged(mExpression);
    }
}

QString GradientDescent::getExpression() const
{
    return mExpression;
}

void GradientDescent::setXFrom(float xFrom)
{
    if (mXFrom != xFrom) {
        mXFrom = xFrom;
        emit xFromChanged(mXFrom);
    }
}

float GradientDescent::getXFrom() const
{
    return mXFrom;
}

void GradientDescent::setXTo(float xTo)
{
    if (mXTo != xTo) {
        mXTo = xTo;
        emit xToChanged(mXTo);
    }
}

float GradientDescent::getXTo() const
{
    return mXTo;
}

void GradientDescent::setXStep(float xStep)
{
    if (mXStep != xStep) {
        mXStep = xStep;
        emit xStepChanged(mXStep);
    }
}

float GradientDescent::getXStep() const
{
    return mXStep;
}

void GradientDescent::setYFrom(float yFrom)
{
    if (mYFrom != yFrom) {
        mYFrom = yFrom;
        emit yFromChanged(mYFrom);
    }
}

float GradientDescent::getYFrom() const
{
    return mYFrom;
}

void GradientDescent::setYTo(float yTo)
{
    if (mYTo != yTo) {
        mYTo = yTo;
        emit yToChanged(mYTo);
    }
}

float GradientDescent::getYTo() const
{
    return mYTo;
}

void GradientDescent::setYStep(float yStep)
{
    if (mYStep != yStep) {
        mYStep = yStep;
        emit yStepChanged(mYStep);
    }
}

float GradientDescent::getYStep() const
{
    return mYStep;
}

void GradientDescent::setMaxIteration(int maxIteration)
{
    if (mMaxIteration != maxIteration) {
        mMaxIteration = maxIteration;
        emit maxIterationChanged(mMaxIteration);
    }
}

int GradientDescent::getMaxIteration() const
{
    return mMaxIteration;
}

void GradientDescent::setLearningRate(float learningRate)
{
    if (mLearningRate != learningRate) {
        mLearningRate = learningRate;
        emit learningRateChanged(mLearningRate);
    }
}

float GradientDescent::getLearningRate() const
{
    return mLearningRate;
}

void GradientDescent::setPointCount(int pointCount)
{
    if (mPointCount != pointCount) {
        mPointCount = pointCount;
        // No signal for pointCount as it is not defined in the header
    }
}

int GradientDescent::getPointCount() const
{
    return mPointCount;
}