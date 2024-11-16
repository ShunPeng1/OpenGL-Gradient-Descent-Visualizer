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
    reloadMesh();
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

void GradientDescent::reloadMesh()
{
    try {
        Mesh* mesh = createMesh();

        mesh->init();
        mesh->tryStart();

        setMesh(mesh, false);

        reloadSpheres();
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
        reloadSpheres();
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


void GradientDescent::getHeatMapColor(float value, float* red, float* green, float* blue)
{
    const int NUM_COLORS = 4;
    static float color[NUM_COLORS][3] = { {0,0,1}, {0,1,0}, {1,1,0}, {1,0,0} };

    int idx1, idx2;
    float fractBetween = 0;

    if (value <= 0) {
        idx1 = idx2 = 0;
    }
    else if (value >= 1) {
        idx1 = idx2 = NUM_COLORS - 1;
    }
    else {
        value = value * (NUM_COLORS - 1);
        idx1 = floor(value);
        idx2 = idx1 + 1;
        fractBetween = value - float(idx1);
    }

    *red = (color[idx2][0] - color[idx1][0]) * fractBetween + color[idx1][0];
    *green = (color[idx2][1] - color[idx1][1]) * fractBetween + color[idx1][1];
    *blue = (color[idx2][2] - color[idx1][2]) * fractBetween + color[idx1][2];

}

Mesh* GradientDescent::createMesh()
{
    std::vector<QVector3D> positions;
    std::vector<QVector3D> normals;
    std::vector<QVector2D> texcoords;
    std::vector<QVector4D> normalColors;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    QJSEngine engine;

    int xStep = (int)((mXTo - mXFrom) / mXStep);
    int yStep = (int)((mYTo - mYFrom) / mYStep);
    float minZ = std::numeric_limits<float>::max();
    float maxZ = std::numeric_limits<float>::lowest();

    QString expression1 = mExpression;
    QString expression2 = mExpression;
    QString expression3 = mExpression;

    // Precompute the results in JavaScript
    QString jsCode = "var results = [];"
        "for (var i = 0; i <= " + QString::number(xStep) + "; i++) {"
        "    results[i] = [];"
        "    for (var j = 0; j <= " + QString::number(yStep) + "; j++) {"
        "        var x = " + QString::number(mXFrom) + " + i * " + QString::number(mXStep) + ";"
        "        var y = " + QString::number(mYFrom) + " + j * " + QString::number(mYStep) + ";"
        "        var z = " + expression1.replace("$x", "x").replace("$y", "y") + ";"
        "        var zX = " + expression2.replace("$x", "(x + 0.00001)").replace("$y", "y") + ";"
        "        var zY = " + expression3.replace("$x", "x").replace("$y", "(y + 0.00001)") + ";"
        "        results[i][j] = [x, y, z, zX, zY];"
        "    }"
        "}"
        "results;";
    QJSValue jsResults = engine.evaluate(jsCode);
    if (jsResults.isError()) {
        std::cerr << "JavaScript error: " << jsResults.toString().toStdString() << std::endl;
        return nullptr;
    }

    std::vector <std::vector<std::vector<float>>> results(xStep + 1, std::vector<std::vector<float>>(yStep + 1, std::vector<float>(5, 0.0f)));

    int i = 0, j = 0;
    QJSValueIterator it(jsResults);
    while (it.hasNext()) {
        it.next();
        QJSValue row = it.value();
        QJSValueIterator rowIt(row);
        while (rowIt.hasNext()) {
            rowIt.next();
            QJSValue point = rowIt.value();
            float x = point.property(0).toNumber();
            float y = point.property(1).toNumber();
            float z = point.property(2).toNumber();
            float zX = point.property(3).toNumber();
            float zY = point.property(4).toNumber();


            if (std::isnan(x) || std::isnan(y) || std::isnan(z) || std::isnan(zX) || std::isnan(zY)) {
                continue;
            }


            results[i][j][0] = x;
            results[i][j][1] = y;
            results[i][j][2] = z;
            results[i][j][3] = zX;
            results[i][j][4] = zY;

            if (z < minZ) minZ = z;
            if (z > maxZ) maxZ = z;

            i = (i + 1) % (xStep + 1);

            if (i == 0)
            {
                j++;
            }
        }
    }

    for (int i = 0; i <= xStep; i++) {
        for (int j = 0; j <= yStep; j++) {
            float x = results[i][j][0];
            float y = results[i][j][1];
            float z = results[i][j][2];
            float zX = results[i][j][3];
            float zY = results[i][j][4];

            positions.push_back(QVector3D(x, y, z));
            texcoords.push_back(QVector2D(x, y));

            float r, g, b;
            float normalizedZ = (z - minZ) / (maxZ - minZ);

            QVector3D normal = QVector3D::crossProduct(
                QVector3D(1.0f, 0.0f, zX - z),
                QVector3D(0.0f, 1.0f, zY - z)
            );
            normals.push_back(normal.normalized());

            getHeatMapColor(normalizedZ, &r, &g, &b);
            normalColors.push_back(QVector4D(r, g, b, 1.0f));
        }
    }

    for (int i = 0; i <= xStep; i++) {
        for (int j = 0; j <= yStep; j++) {
            int index = j + i * (yStep + 1);

            Vertex vertex = {};
            vertex.position = positions[index];
            vertex.normal = normals[index];
            vertex.texCoord = texcoords[index];
            vertex.color = normalColors[index];
            vertices.push_back(vertex);
        }
    }

    for (int i = 0; i < xStep; i++) {
        for (int j = 0; j <= yStep; j++) {
            int index1 = j + i * (yStep + 1);
            int index2 = j + (i + 1) * (yStep + 1);

            indices.push_back(index1);
            indices.push_back(index2);
        }

        if (i < xStep - 1) {
            indices.push_back(indices[indices.size() - 1]);
            indices.push_back((i + 1) * (yStep + 1));
        }
    }

	mMeshResults = results;
    return new Mesh(MODEL_PLANE, vertices, indices, {}, GL_TRIANGLE_STRIP);
}


void GradientDescent::reloadSpheres()
{
    for (auto sphere : mSpheres) {
        this->removeChild(sphere);
        //delete sphere;
    }
    mSpheres.clear();

    if (mSphereMesh != nullptr) {
        delete mSphereMesh;
        mSphereMesh = nullptr;
    }

    // Precompute the results in JavaScript
    QJSEngine engine;
    int xStep = static_cast<int>((mXTo - mXFrom) / mXStep);
    int yStep = static_cast<int>((mYTo - mYFrom) / mYStep);


    ModelLoader loader = ModelLoader::Builder().SetUseNormalColor(true).Build();
    Mesh* mesh = loader.loadIcosphere(3);
    mesh->init();
    mesh->tryStart();

    for (int i = 0; i < mPointCount; ++i) {
        MeshRenderer* sphere = new MeshRenderer();
        sphere->init();
        sphere->setMesh(mesh, true);

        float size = 0.1f;

        sphere->transform->setLocalScale(QVector3D(size, size, size));
        sphere->setParent(this);
        mSpheres.push_back(sphere);
    }

    mSphereMesh = mesh;



    QString expression1 = mExpression;
    QString expression2 = mExpression;
    QString expression3 = mExpression;

	expression1 = expression1.replace("$x", "x").replace("$y", "y");
	expression2 = expression2.replace("$x", "(x + 0.0001)").replace("$y", "y");
	expression3 = expression3.replace("$x", "x").replace("$y", "(y + 0.0001)");


    QString jsCode = "function gradientDescent(x0, y0, learningRate, iterations) {"
        "    var x = x0;"
        "    var y = y0;"
        "    var x_history = [x0];"
        "    var y_history = [y0];"
        "    var dx_history = [0];"
        "    var dy_history = [0];"
        "	 var z_history = [" + expression1 + "]; "
        "    for (var i = 0; i < iterations; i++) {"
		"		 var z = " + expression1 + ";"
        "        var df_dx = (" + expression1 + " - " + expression2 + ") / 0.0001;"
        "        var df_dy = (" + expression1 + " - " + expression3 + ") / 0.0001;"
        "        x_history.push(x);"
        "        y_history.push(y);"
        "        dx_history.push(df_dx);"
        "        dy_history.push(df_dy);"
		"		 z_history.push(z);"
        "        x = x - learningRate * df_dx;"
        "        y = y - learningRate * df_dy;"
        "    }"
        "    return [x_history, y_history, dx_history, dy_history, z_history];"
        "}"
        "function generateRandomPoints(n, xRange, yRange) {"
        "    var points = [];"
        "    for (var i = 0; i < n; i++) {"
        "        var x = Math.random() * (xRange[1] - xRange[0]) + xRange[0];"
        "        var y = Math.random() * (yRange[1] - yRange[0]) + yRange[0];"
        "        points.push([x, y]);"
        "    }"
        "    return points;"
        "}"
        "var results = [];"
		"var points = generateRandomPoints(" + QString::number(mPointCount) + ", [" + QString::number(mXFrom) + ", " + QString::number(mXTo) + "], [" + QString::number(mYFrom) + ", " + QString::number(mYTo) + "]);"
		"for (var i = 0; i < points.length; i++) {"
		"    var point = points[i];"
		"    var x0 = point[0];"
		"    var y0 = point[1];"
		"    var result = gradientDescent(x0, y0, " + QString::number(mLearningRate) + ", " + QString::number(mMaxIteration) + ");"
		"    results.push(result);"
		"}"
        "results;";

    QJSValue jsResults = engine.evaluate(jsCode);
    if (jsResults.isError()) {
        qDebug() << "JavaScript error:" << jsResults.toString();
        return;
    }

    mGradientDescentResults.clear();

    QJSValueIterator it(jsResults);
    while (it.hasNext()) {
        it.next();
        QJSValue result = it.value();
        std::vector<std::vector<float>> pointResults;
        QJSValueIterator resultIt(result);
        while (resultIt.hasNext()) {
            resultIt.next();
            QJSValue resultResult = resultIt.value();

			if (resultResult.isError()) {
				qDebug() << "JavaScript error:" << resultResult.toString();
				return;
			}

			if (resultResult.isArray() == false) {
				continue;
			}

            QJSValueIterator resultItIt(resultResult);

			std::vector<float> pointData;
			while (resultItIt.hasNext()) {
				resultItIt.next();
				float value = resultItIt.value().toNumber();

                if (std::isnan(value))
                    continue;
				pointData.push_back(value);
			}
        
            pointResults.push_back(pointData);
        }
        mGradientDescentResults.push_back(pointResults);
    }
    

    mIteration = 0;
}

void GradientDescent::simulateGradientDescent(float deltaTime)
{
	if (mGradientDescentResults.empty() || mSpheres.size() == 0) {
		return;
	}

    mTimeAccumulator += deltaTime;

    if (mTimeAccumulator >= 1 / (float) mSimulationFrequency) {
        mTimeAccumulator = 0.0f; // Reset for the next step
		mIteration = (mIteration + 1) % mMaxIteration;


    
        for (size_t i = 0; i < mSpheres.size(); ++i) {
            // Randomly choose a starting point if needed
            float x = mGradientDescentResults[i][0][mIteration];
			float y = mGradientDescentResults[i][1][mIteration];
			float z = mGradientDescentResults[i][4][mIteration];

            // Update sphere position (using setTransform or appropriate method)
            QVector3D newPosition(x,y,z);
            mSpheres[i]->transform->setLocalPosition(newPosition + transform->getLocalPosition());
        }
    }

}
