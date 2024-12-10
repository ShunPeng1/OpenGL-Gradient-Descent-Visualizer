#include "Engine/Nodes/Camera.h"

Camera::Camera()
{
	mFov = 45.0f;
	mNear = 0.1f;
	mFar = 1000.0f;
	mAspectRatio = 16.0f/9.0f;
	mIsOrtho = false;
	mDirty = true;
	mDrawFrustum = true;

	setObjectName("Camera");
}

Camera::~Camera() noexcept
{
}

void Camera::init()
{
	initializeOpenGLFunctions();
}

void Camera::start(IScene* scene)
{

}

void Camera::update(float deltaTime)
{

}

void Camera::render(ShaderProgram& shaderProgram)
{

	if (mDrawFrustum) {
		drawFrustum(shaderProgram);
	}

}


void Camera::drawFrustum(ShaderProgram& shaderProgram)
{
	QVector<QVector3D> frustumCorners = calculateFrustumCorners();
	QVector<Vertex> vertices;

	// Add the vertices for the frustum lines
	for (const auto& corner : frustumCorners) {
		Vertex vertex;
		vertex.position = corner;
		vertex.normal = QVector3D(0.0f, 0.0f, 0.0f);
		vertex.texCoord = QVector2D(0.0f, 0.0f);
		vertex.color = QVector4D(1.0f, 1.0f, 1.0f, 1.0f);
		vertices.append(vertex);
	}
	// Generate and bind the VAO
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	// Generate and bind the VBO
	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_DYNAMIC_DRAW);

	// Enable the vertex attribute array
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(3);

	// Set the world matrix to identity for the frustum lines
	QMatrix4x4 world = transform->getWorldMatrix();
	shaderProgram.setUniformValue("mWorld", world);

	// Draw the frustum lines
	glDrawArrays(GL_LINES, 0, vertices.size());

	// Unbind the VAO
	glBindVertexArray(0);

}

QVector<QVector3D> Camera::calculateFrustumCorners()
{
	QVector<QVector3D> corners(8);

	float nearHeight = 2.0f * tan(qDegreesToRadians(mFov) / 2.0f) * mNear;
	float nearWidth = nearHeight * mAspectRatio;
	float farHeight = 2.0f * tan(qDegreesToRadians(mFov) / 2.0f) * mFar;
	float farWidth = farHeight * mAspectRatio;

	QVector3D mPosition = transform->getWorldPosition();
	QVector3D mFront = transform->getWorldRotation() * QVector3D(0.0f, 0.0f, -1.0f);
	QVector3D mUp = transform->getWorldRotation() * QVector3D(0.0f, 1.0f, 0.0f);
	QVector3D mRight = QVector3D::crossProduct(mFront, mUp).normalized();

	QVector3D offset = mFront * 0.1f;  // Small offset forward
	QVector3D nearCenter = mPosition + mFront * mNear + offset;
	QVector3D farCenter = mPosition + mFront * mFar + offset;

	corners[0] = nearCenter - mRight * (nearWidth / 2.0f) + mUp * (nearHeight / 2.0f);
	corners[1] = nearCenter + mRight * (nearWidth / 2.0f) + mUp * (nearHeight / 2.0f);
	corners[2] = nearCenter + mRight * (nearWidth / 2.0f) - mUp * (nearHeight / 2.0f);
	corners[3] = nearCenter - mRight * (nearWidth / 2.0f) - mUp * (nearHeight / 2.0f);

	corners[4] = farCenter - mRight * (farWidth / 2.0f) + mUp * (farHeight / 2.0f);
	corners[5] = farCenter + mRight * (farWidth / 2.0f) + mUp * (farHeight / 2.0f);
	corners[6] = farCenter + mRight * (farWidth / 2.0f) - mUp * (farHeight / 2.0f);
	corners[7] = farCenter - mRight * (farWidth / 2.0f) - mUp * (farHeight / 2.0f);

	return corners;
}

void Camera::setFov(float fov)
{
	mFov = fov;
	mDirty = true;
	emit fovChanged(fov);
}

void Camera::setNear(float near)
{
	mNear = near;
	mDirty = true;
	emit nearChanged(near);
}

void Camera::setFar(float far)
{
	mFar = far;
	mDirty = true;
	emit farChanged(far);
}

void Camera::setAspectRatio(float width, float height)
{
	mAspectRatio = width / height;
	mDirty = true;
	emit aspectRatioChanged(mAspectRatio);
}

void Camera::setAspectRatio(float aspectRatio)
{
	mAspectRatio = aspectRatio;
	mDirty = true;
	emit aspectRatioChanged(aspectRatio);
}

void Camera::setIsOrtho(bool isOrtho)
{
	mIsOrtho = isOrtho;
	mDirty = true;
	emit isOrthoChanged(isOrtho);
}

void Camera::setWidth(float width)
{
	mWidth = width;
	mDirty = true;
	emit widthChanged(width);
}

void Camera::setDrawFrustum(bool drawFrustum)
{
	mDrawFrustum = drawFrustum;
	emit drawFrustumChanged(drawFrustum);
}

float Camera::getFov() const
{
	return mFov;
}

float Camera::getNear() const
{
	return mNear;
}

float Camera::getFar() const
{
	return mFar;
}

float Camera::getAspectRatio() const
{
	return mAspectRatio;
}

bool Camera::getIsOrtho() const
{
	return mIsOrtho;
}

float Camera::getWidth() const
{
	return mWidth;
}

bool Camera::getDrawFrustum() const
{
	return mDrawFrustum;
}

QMatrix4x4 Camera::getViewMatrix()
{
	QMatrix4x4 view;
	QVector3D mPosition = transform->getWorldPosition();
	QVector3D mFront = transform->getWorldRotation() * QVector3D(0.0f, 0.0f, -1.0f);
	QVector3D mUp = transform->getWorldRotation() * QVector3D(0.0f, 1.0f, 0.0f);

	view.lookAt(mPosition, mPosition + mFront, mUp);
	return view;
}

QMatrix4x4 Camera::getProjectionMatrix()
{
	if (!mDirty) {
		return mProjection;
	}

	mDirty = false;
	QMatrix4x4 projection;

	if (mIsOrtho) {
		// Create an orthographic projection matrix
		float orthoWidth = mWidth; // Define the width of the orthographic view
		float orthoHeight = orthoWidth / mAspectRatio;
		projection.ortho(-orthoWidth / 2, orthoWidth / 2, -orthoHeight / 2, orthoHeight / 2, mNear, mFar);
	}
	else {
		// Create a perspective projection matrix
		projection.perspective(mFov, mAspectRatio, mNear, mFar);
	}

	mProjection = projection;
	return projection;
}

void Camera::write(QJsonObject& json) const
{
}

void Camera::read(const QJsonObject& json)
{
}

void* Camera::accept(INodeVisitor* visitor)
{
	return visitor->visitCamera(this);
}