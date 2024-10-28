// MainWindow.h
#include <QMainWindow>
#include <QDockWidget>
#include <QTabWidget>
#include <QTreeWidget>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();


private:
    void createDockWidgets();
    void populateHierarchyView();
    void updateInspectorView(QTreeWidgetItem* item);
    QDockWidget* hierarchyDock;
    QDockWidget* cameraViewDock;
    QDockWidget* inspectorDock;
    QTreeWidget* hierarchyView;
    QWidget* inspectorView;
};