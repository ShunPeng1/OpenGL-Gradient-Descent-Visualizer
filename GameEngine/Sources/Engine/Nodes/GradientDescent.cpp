#include "Engine/Nodes/GradientDescent.h"
#include "Engine/Loaders/ModelLoader.h"
#include "Engine/Interfaces/IScene.h"

GradientDescent::GradientDescent()
    : MeshRenderer(), mExpression("0"), mXFrom(0.0f), mXTo(1.0f), mXStep(0.1f),
    mYFrom(0.0f), mYTo(1.0f), mYStep(0.1f),
    mMaxIteration(1000), mLearningRate(0.01f),
	mPointCount(0), mSimulationFrequency(1), mSpheres(), mSphereMesh(nullptr)
{

}

GradientDescent::GradientDescent(QString expression, float xFrom, float xTo, float xStep, float yFrom, float yTo, float yStep, int maxIteration, float learningRate, int pointCount, float simulationFrequency)
    : MeshRenderer(), mExpression(expression), mXFrom(xFrom), mXTo(xTo), mXStep(xStep), 
    mYFrom(yFrom), mYTo(yTo), mYStep(yStep), 
    mMaxIteration(maxIteration), mLearningRate(learningRate), 
    mPointCount(pointCount), mSimulationFrequency(1), mSpheres(), mSphereMesh(nullptr)
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
    mScenePtr = scene;
    ReloadMesh();
    initializeSpheres();
}

void GradientDescent::update(float deltaTime)
{
    MeshRenderer::update(deltaTime);

    simulateGradientDescent(deltaTime);
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
    try {
        ModelLoader loader = ModelLoader::Builder().SetUseNormalColor(true).Build();

        ModelLoader::Range xRange(mXFrom, mXTo, mXStep);
        ModelLoader::Range yRange(mYFrom, mYTo, mYStep);

        Mesh* mesh = loader.loadPlane(mExpression, xRange, yRange, mResults);

        mesh->init();
        mesh->tryStart();


        setMesh(mesh, false);
	}
	catch (const std::exception& e) {
		qDebug() << e.what();
	}
    


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
        initializeSpheres();
		emit pointCountChanged(mPointCount);
    }
}

int GradientDescent::getPointCount() const
{
    return mPointCount;
}

void GradientDescent::setSimulationFrequency(float simulationFrequency)
{
	if (mSimulationFrequency != simulationFrequency) {
		mSimulationFrequency = simulationFrequency;
		emit simulationFrequencyChanged(mSimulationFrequency);
	}
}

float GradientDescent::getSimulationFrequency() const
{
    return mSimulationFrequency;
}

void GradientDescent::initializeSpheres()
{
	for (auto sphere : mSpheres) {
		mScenePtr->removeNode(sphere);
		delete sphere;
	}
	mSpheres.clear();

	if (mSphereMesh != nullptr) {
		delete mSphereMesh;
		mSphereMesh = nullptr;
	}

    ModelLoader loader = ModelLoader::Builder().SetUseNormalColor(true).Build();

    Mesh* mesh = loader.loadIcosphere(3);
    mesh->init();
    mesh->tryStart();
    for (int i = 0; i < mPointCount; ++i) {


        MeshRenderer* sphere = new MeshRenderer();
		sphere->setMesh(mesh, true);

		mScenePtr->addNode(sphere);

		sphere->init();

		mSpheres.push_back(sphere);
    }

	mSphereMesh = mesh;

    //QJSEngine engine;

    //int xStep = (int)((xRange.to - xRange.from) / xRange.step);
    //int yStep = (int)((yRange.to - yRange.from) / yRange.step);
    //float minZ = std::numeric_limits<float>::max();
    //float maxZ = std::numeric_limits<float>::lowest();

    //QString expression1 = expression;
    //QString expression2 = expression;
    //QString expression3 = expression;

    //// Precompute the results in JavaScript
    //QString jsCode = "var results = [];"
    //    "for (var i = 0; i <= " + QString::number(xStep) + "; i++) {"
    //    "    results[i] = [];"
    //    "    for (var j = 0; j <= " + QString::number(yStep) + "; j++) {"
    //    "        var x = " + QString::number(xRange.from) + " + i * " + QString::number(xRange.step) + ";"
    //    "        var y = " + QString::number(yRange.from) + " + j * " + QString::number(yRange.step) + ";"
    //    "        var z = " + expression1.replace("$x", "x").replace("$y", "y") + ";"
    //    "        var zX = " + expression2.replace("$x", "(x + 0.00001)").replace("$y", "y") + ";"
    //    "        var zY = " + expression3.replace("$x", "x").replace("$y", "(y + 0.00001)") + ";"
    //    "        results[i][j] = [x, y, z, zX, zY];"
    //    "    }"
    //    "}"
    //    "results;";
    //QJSValue jsResults = engine.evaluate(jsCode);
    //if (jsResults.isError()) {
    //    std::cerr << "JavaScript error: " << jsResults.toString().toStdString() << std::endl;
    //    return nullptr;
    //}

    //std::vector <std::vector<std::vector<float>>> results(xStep + 1, std::vector<std::vector<float>>(yStep + 1, std::vector<float>(5, 0.0f)));

    //int i = 0, j = 0;
    //QJSValueIterator it(jsResults);
    //while (it.hasNext()) {
    //    it.next();
    //    QJSValue row = it.value();
    //    QJSValueIterator rowIt(row);
    //    while (rowIt.hasNext()) {
    //        rowIt.next();
    //        QJSValue point = rowIt.value();
    //        float x = point.property(0).toNumber();
    //        float y = point.property(1).toNumber();
    //        float z = point.property(2).toNumber();
    //        float zX = point.property(3).toNumber();
    //        float zY = point.property(4).toNumber();


    //        if (std::isnan(x) || std::isnan(y) || std::isnan(z) || std::isnan(zX) || std::isnan(zY)) {
    //            continue;
    //        }


    //        results[i][j][0] = x;
    //        results[i][j][1] = y;
    //        results[i][j][2] = z;
    //        results[i][j][3] = zX;
    //        results[i][j][4] = zY;

    //        if (z < minZ) minZ = z;
    //        if (z > maxZ) maxZ = z;

    //        i = (i + 1) % (xStep + 1);

    //        if (i == 0)
    //        {
    //            j++;
    //        }
    //    }
    //}
    
}

void GradientDescent::simulateGradientDescent(float deltaTime)
{
	if (mResults.empty() || mSpheres.size() == 0) {
		return;
	}

    
    mTimeAccumulator += deltaTime;

    if (mTimeAccumulator >= mSimulationFrequency) {
        mTimeAccumulator = 0.0f; // Reset for the next step

        for (size_t i = 0; i < mSpheres.size(); ++i) {
            // Randomly choose a starting point if needed
            int xIndex = rand() % mResults.size();
            int yIndex = rand() % mResults[0].size();

            auto& vertexData = mResults[xIndex][yIndex]; // Access [x, y, z, dx, dy] data

            float currentX = vertexData[0];
            float currentY = vertexData[1];
            float currentZ = vertexData[2];

            float gradientX = vertexData[3];
            float gradientY = vertexData[4];

            // Update positions based on learning rate and gradients
            currentX -= mLearningRate * gradientX;
            currentY -= mLearningRate * gradientY;

            // Update sphere position (using setTransform or appropriate method)
            QVector3D newPosition(currentX, currentY, currentZ);
            mSpheres[i]->transform->setLocalPosition(newPosition);
        }
    }

}
