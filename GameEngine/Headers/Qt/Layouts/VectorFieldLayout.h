#pragma once

#include <QHBoxLayout>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QWidget>

class VectorFieldLayout : public QHBoxLayout {
public:
    VectorFieldLayout(const QString& label, double min, double max, double step, double defaultValue, int fields, QWidget* parent = nullptr);

    QVector<QDoubleSpinBox*> getSpinBoxes() const;

private:
    QVector<QDoubleSpinBox*> mSpinBoxes;

    QDoubleSpinBox* createDoubleSpinBox(double min, double max, double step, double value);
};