#pragma once

#include "MeshRenderer.h"


class GradientDescent : public MeshRenderer
{
	Q_OBJECT
public:
	GradientDescent();
	GradientDescent(QString mExpression, float mXFrom, float mXTo, float mXStep, float mYFrom, float mYTo, float mYStep, int mMaxIteration, float mLearningRate, int mPointCount);
	virtual ~GradientDescent() noexcept;

	virtual void init() override;

	virtual void start(IScene* scene) override;
	virtual void update(float deltaTime) override;
	virtual void render(ShaderProgram& shaderProgram) override;

public:
	void* accept(INodeVisitor* visitor) override;

public:
	void ReloadMesh();

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

signals:
	void expressionChanged(QString expression);
signals:
	void xFromChanged(float xFrom);
signals:
	void xToChanged(float xTo);
signals:
	void xStepChanged(float xStep);
signals:
	void yFromChanged(float yFrom);
signals:
	void yToChanged(float yTo);
signals:
	void yStepChanged(float yStep);
signals:
	void maxIterationChanged(int maxIteration);
signals:
	void learningRateChanged(float learningRate);
signals:
	void pointCountChanged(int pointCount);

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

	int mPointCount;
	std::vector <std::vector<std::vector<float>>> mResults;

};


