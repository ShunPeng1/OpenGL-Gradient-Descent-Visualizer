#pragma once

#include "MeshRenderer.h"


class GradientDescent : public MeshRenderer
{
	Q_OBJECT
public:
	enum class Method
	{
		SGD,
		Momentum,
		NesterovMomentum,
		AdaGrad,
		RMSProp,
		Adam
	};

public:
	GradientDescent();
	GradientDescent(QString mExpression, float mXFrom, float mXTo, float mXStep, float mYFrom, float mYTo, float mYStep, int mMaxIteration = 1000, float mLearningRate = 0.01, int mPointCount = 10, float pointSize = 0.1, float simulationFrequency = 1000);
	virtual ~GradientDescent() noexcept;

	virtual void init() override;

	virtual void start(IScene* scene) override;
	virtual void update(float deltaTime) override;
	virtual void render(ShaderProgram& shaderProgram) override;

public:
	void* accept(INodeVisitor* visitor) override;

public:
	void reloadMesh();
	void randomizeSimulation();
	void reloadSpheres();


	void setExpression(QString expression);
	QString getExpression() const;

	void setXFrom(float xFrom);
	float getXFrom() const;

	void setXTo(float xTo);
	float getXTo() const;

	void setXStep(float xStep);
	float getXStep() const;

	void setYFrom(float yFrom);
	float getYFrom() const;

	void setYTo(float yTo);
	float getYTo() const;

	void setYStep(float yStep);
	float getYStep() const;

	void setMaxIteration(int maxIteration);
	int getMaxIteration() const;

	void setLearningRate(float learningRate);
	float getLearningRate() const;

	void setPointCount(int pointCount);
	int getPointCount() const;

	void setPointSize(float pointSize);
	float getPointSize() const;

	void setSimulationFrequency(float simulationFrequency);
	float getSimulationFrequency() const;

	void setMethod(Method method);
	Method getMethod() const;

	void setMomentum(float momentum);
	float getMomentum() const;

	void setDecayRate(float decayRate);
	float getDecayRate() const;

	void setBeta1(float beta1);  // For Adam optimizer
	float getBeta1() const;

	void setBeta2(float beta2);  // For Adam optimizer
	float getBeta2() const;

	void setEpsilon(float epsilon);  // Small value to prevent division by zero
	float getEpsilon() const;

private:

	void getHeatMapColor(float value, float* red, float* green, float* blue);
	Mesh* createMesh();
	void simulateGradientDescent(float deltaTime);
	QString getMethodString(Method method);

	QString getSGDString();
	QString getMomentumString();
	QString getNesterovMomentumString();
	QString getAdaGradString();
	QString getRMSPropString();
	QString getAdamString();

signals:
	void expressionChanged(QString expression);
	void xFromChanged(float xFrom);
	void xToChanged(float xTo);
	void xStepChanged(float xStep);
	void yFromChanged(float yFrom);
	void yToChanged(float yTo);
	void yStepChanged(float yStep);

	void maxIterationChanged(int maxIteration);
	void learningRateChanged(float learningRate);
	void pointCountChanged(int pointCount);
	void pointSizeChanged(float pointSize);
	void simulationFrequencyChanged(float simulationFrequency);
	void methodChanged(Method method);

	void momentumChanged(float momentum);
	void decayRateChanged(float decayRate);
	void beta1Changed(float beta1);
	void beta2Changed(float beta2);
	void epsilonChanged(float epsilon);

protected:
	QString mExpression;

	float mXFrom;
	float mXTo;
	float mXStep;

	float mYFrom;
	float mYTo;
	float mYStep;

	int mMaxIteration;
	float mLearningRate;
	float mSimulationFrequency;

	int mPointCount;
	float mPointSize;

	Method mMethod = Method::SGD;

	float mMomentum = 0.9f;
	float mDecayRate = 0.99f;
	float mBeta1 = 0.9f;
	float mBeta2 = 0.999f;
	float mEpsilon = 1e-8f;

	std::vector <std::vector<std::vector<float>>> mGradientDescentResults;
	std::vector <std::vector<std::vector<float>>> mMeshResults;

	std::vector<MeshRenderer*> mSpheres;
	Mesh* mSphereMesh;

	float mTimeAccumulator;
	int mIteration;
};


