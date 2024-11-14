
#ifndef MESH_RENDERER_WIDGET_H
#define MESH_RENDERER_WIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "Engine/Nodes/MeshRenderer.h"
#include "Qt/Interfaces/INodeWidget.h"
#include "Qt/Widgets/SectionWidget.h"

class MeshRendererWidget : public INodeWidget<MeshRenderer> {
    Q_OBJECT

public:
    MeshRendererWidget(MeshRenderer* meshRenderer, QWidget* parent = nullptr);
    ~MeshRendererWidget();

    void setNode(MeshRenderer* meshRenderer) override;
    void clearNode() override;

private slots:
    //void onMeshChanged(Mesh* mesh, bool isInstance);
    void onPolygonModeChanged(PolygonMode polygonMode);
    void onDrawBufferModeChanged(DrawBufferMode drawBufferMode);

	//void onMeshSet(int);
	void onPolygonModeSet(int polygonMode);
	void onDrawBufferModeSet(int drawBufferMode);

private:
    void updateUI() override;
    void connectSignals() override;
    void disconnectSignals() override;
    void blockSignals(bool) override;

private:
	int getPolygonModeIndex(PolygonMode polygonMode);
	int getDrawBufferModeIndex(DrawBufferMode drawBufferMode);

	PolygonMode getPolygonMode(int index);
	DrawBufferMode getDrawBufferMode(int index);

private:
    SectionWidget* mSection;

    QComboBox* mPolygonMode;
    QComboBox* mDrawBufferMode;
};

#endif // MESH_RENDERER_WIDGET_H