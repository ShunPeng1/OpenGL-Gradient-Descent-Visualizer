#include "Qt/Layouts/VectorFieldLayout.h"

VectorFieldLayout::VectorFieldLayout(const QString& label, double min, double max, double step, double defaultValue, int fields, QWidget* parent) {
    addWidget(new QLabel(label, parent));
    for (int i = 0; i < fields; ++i) {
        QDoubleSpinBox* spinBox = createDoubleSpinBox(min, max, step, defaultValue);
        mSpinBoxes.push_back(spinBox);
        addWidget(spinBox);
    }
}

QVector<QDoubleSpinBox*> VectorFieldLayout::getSpinBoxes() const {
    return mSpinBoxes;
}

QDoubleSpinBox* VectorFieldLayout::createDoubleSpinBox(double min, double max, double step, double value) {
    QDoubleSpinBox* spinBox = new QDoubleSpinBox();
    spinBox->setRange(min, max);
    spinBox->setSingleStep(step);
    spinBox->setValue(value);
    return spinBox;
}