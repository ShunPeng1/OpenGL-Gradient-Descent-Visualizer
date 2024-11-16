#pragma once

#include "MeshRenderer.h"


class GradientDescent : public MeshRenderer
{
	Q_OBJECT
public:
	GradientDescent();
	GradientDescent(QString mExpression, float mXFrom, float mXTo, float mXStep, float mYFrom, float mYTo, float mYStep, int mMaxIteration, float mLearningRate, int mPointCount, float simulationFrequency = 1);
	virtual ~GradientDescent() noexcept;

	virtual void init() override;

	virtual void start(IScene* scene) override;
	virtual void update(float deltaTime) override;
	virtual void render(ShaderProgram& shaderProgram) override;

public:
	void* accept(INodeVisitor* visitor) override;

public:
	void reloadMesh();
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

	void setSimulationFrequency(float simulationFrequency);
	float getSimulationFrequency() const;


private:

	void getHeatMapColor(float value, float* red, float* green, float* blue);
	Mesh* createMesh();
	void simulateGradientDescent(float deltaTime);


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
	void simulationFrequencyChanged(float simulationFrequency);

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
	std::vector <std::vector<std::vector<float>>> mGradientDescentResults;
	std::vector <std::vector<std::vector<float>>> mMeshResults;

	std::vector<MeshRenderer*> mSpheres;
	Mesh* mSphereMesh;

	float mTimeAccumulator;
	int mIteration;
};


