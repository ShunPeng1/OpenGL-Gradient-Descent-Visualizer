#include <QPropertyAnimation>

#include "Qt/Widgets/SectionWidget.h"
#include <QDebug>


SectionWidget::SectionWidget(const QString& title, const int animationDuration, QWidget* parent)
    : QWidget(parent), mAnimationDuration(animationDuration)
{
    mToggleButton = new QToolButton(this);
    mHeaderLine = new QFrame(this);
    mToggleAnimation = new QParallelAnimationGroup(this);
    mContentArea = new QScrollArea(this);
    mMainLayout = new QGridLayout(this);

    mToggleButton->setStyleSheet("QToolButton {border: none;}");
    mToggleButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    mToggleButton->setArrowType(Qt::ArrowType::RightArrow);
    mToggleButton->setText(title);
    mToggleButton->setCheckable(true);
    mToggleButton->setChecked(false);

    mHeaderLine->setFrameShape(QFrame::HLine);
    mHeaderLine->setFrameShadow(QFrame::Sunken);
    mHeaderLine->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

    mContentArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // start out collapsed
    mContentArea->setMaximumHeight(0);
    mContentArea->setMinimumHeight(0);

    // let the entire widget grow and shrink with its content
    mToggleAnimation->addAnimation(new QPropertyAnimation(this, "maximumHeight"));
    mToggleAnimation->addAnimation(new QPropertyAnimation(this, "minimumHeight"));
    mToggleAnimation->addAnimation(new QPropertyAnimation(mContentArea, "maximumHeight"));

    mMainLayout->setVerticalSpacing(0);
    mMainLayout->setContentsMargins(0, 0, 0, 0);

    int row = 0;
    mMainLayout->addWidget(mToggleButton, row, 0, 1, 1, Qt::AlignLeft);
    mMainLayout->addWidget(mHeaderLine, row++, 2, 1, 1);
    mMainLayout->addWidget(mContentArea, row, 0, 1, 3);
    setLayout(mMainLayout);

    connect(mToggleButton, &QToolButton::toggled, this, &SectionWidget::toggle);
}

void SectionWidget::toggle(bool expanded)
{
    mToggleButton->setArrowType(expanded ? Qt::ArrowType::DownArrow : Qt::ArrowType::RightArrow);
    mToggleAnimation->setDirection(expanded ? QAbstractAnimation::Forward : QAbstractAnimation::Backward);
    mToggleAnimation->start();

    this->mIsExpanded = expanded;

    //qDebug() << "MV: toggle: isExpanded " << mIsExpanded;
}

void SectionWidget::setContentLayout(QLayout& contentLayout)
{
    delete mContentArea->layout();
    mContentArea->setLayout(&contentLayout);
    mCollapsedHeight = sizeHint().height() - mContentArea->maximumHeight();

    updateHeights();
}

void SectionWidget::setTitle(QString title)
{
    mToggleButton->setText(std::move(title));
}

void SectionWidget::updateHeights()
{
    int contentHeight = mContentArea->layout()->sizeHint().height();

    for (int i = 0; i < mToggleAnimation->animationCount() - 1; ++i)
    {
        QPropertyAnimation* SectionAnimation = static_cast<QPropertyAnimation*>(mToggleAnimation->animationAt(i));
        SectionAnimation->setDuration(mAnimationDuration);
        SectionAnimation->setStartValue(mCollapsedHeight);
        SectionAnimation->setEndValue(mCollapsedHeight + contentHeight);
    }

    QPropertyAnimation* contentAnimation = static_cast<QPropertyAnimation*>(mToggleAnimation->animationAt(mToggleAnimation->animationCount() - 1));
    contentAnimation->setDuration(mAnimationDuration);
    contentAnimation->setStartValue(0);
    contentAnimation->setEndValue(contentHeight);

    mToggleAnimation->setDirection(mIsExpanded ? QAbstractAnimation::Forward : QAbstractAnimation::Backward);
    mToggleAnimation->start();
}
