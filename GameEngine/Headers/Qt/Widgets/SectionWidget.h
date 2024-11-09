#ifndef SECTION_WIDGET_H
#define SECTION_WIDGET_H

#include <QFrame>
#include <QGridLayout>
#include <QParallelAnimationGroup>
#include <QScrollArea>
#include <QToolButton>
#include <QWidget>

class SectionWidget : public QWidget
{
    Q_OBJECT

private:
    QGridLayout* mMainLayout;
    QToolButton* mToggleButton;
    QFrame* mHeaderLine;
    QParallelAnimationGroup* mToggleAnimation;
    QScrollArea* mContentArea;
    int mAnimationDuration;
    int mCollapsedHeight;
    bool mIsExpanded = false;

public slots:
    void toggle(bool collapsed);

public:
    static const int DEFAULT_DURATION = 0;

    // initialize section
    explicit SectionWidget(const QString& title = "", const int animationDuration = DEFAULT_DURATION, QWidget* parent = 0);

    // set layout of content
    void setContentLayout(QLayout& contentLayout);

    // set title
    void setTitle(QString title);

    // update animations and their heights
    void updateHeights();
};


#endif // SECTION_WIDGET_H