#ifndef ISERIALIZABLE
#define ISERIALIZABLE

#include <QJsonObject>
#include <QJsonArray>
#include "Engine/Constants/SerializePath.h"

class ISerializable {
public:
	virtual void write(QJsonObject& json) const = 0;
	virtual void read(const QJsonObject& json) = 0;
};

#endif // !ISERIALIZABLE
