#include "activitygroupwidget.h"
#include <QPainter>
#include <QStyleOption>
#include <QLayout>
#include <QDebug>

ActivityGroupWidget::ActivityGroupWidget(QWidget *parent) : QWidget(parent)
{
    label = new QLabel();
    label->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    label->setMaximumWidth(30);

    titleLabel = new QLabel();
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-weight: bold;");

    setLayout(new QHBoxLayout());
    layout()->addWidget(label);
    layout()->addWidget(titleLabel);

    selectionWidget = new QWidget(this);
    selectionWidget->setGeometry(geometry());
    selectionWidget->hide();
/*    selectionWidget->setLayout(new QVBoxLayout());
    selectionWidget->layout()->setMargin(0);
    selectionWidget->layout()->setSpacing(0)*/;

    updateStyleSheet();
}

void ActivityGroupWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void ActivityGroupWidget::updateStyleSheet()
{
    if (title().length()) {
        setStyleSheet("ActivityGroupWidget { "
                      "background-color: white;"
                      "border-bottom: 1px solid gray;"
                      "}");
    } else {
        setStyleSheet("ActivityGroupWidget { "
                      "background-color: #ccc;"
                      "border-bottom: 1px solid gray;"
                      "}");
    }
}

bool ActivityGroupWidget::isSelected() const
{
    return _isSelected;
}

void ActivityGroupWidget::setIsSelected(bool isSelected)
{
    _isSelected = isSelected;

    if (isSelected) {
        setStyleSheet("ActivityGroupWidget { "
                      "background-color: #eee;"
                      "border-bottom: 1px solid gray;"
                      "}");
    } else {
        updateStyleSheet();
    }
}

void ActivityGroupWidget::setSlotHeight(int height)
{
    setFixedHeight(height);
}

void ActivityGroupWidget::selectSlotAtIndex(int slotIndex)
{
    if (!selectionSlots.contains(slotIndex)) {
        auto *selectionSlot = new QWidget(selectionWidget);
        selectionSlot->setFixedHeight(50);
        selectionSlot->setStyleSheet("background-color: rgba(255, 255, 0, 0.5)");
        selectionSlot->setGeometry(QRect(0,
                                         slotIndex * 50,
                                         geometry().width(),
                                         50));
        selectionSlot->show();

        selectionSlots.insert(slotIndex, selectionSlot);
    } else {
        deselectSlotAtIndex(slotIndex);
    }

    if (selectionWidget->isHidden()) {
        selectionWidget->show();
    }
}

void ActivityGroupWidget::deselectSlotAtIndex(int slotIndex)
{
    if (selectionSlots[slotIndex] != nullptr) {
        delete selectionSlots[slotIndex];
    }

    if (selectionSlots.contains(slotIndex)) {
        selectionSlots.remove(slotIndex);
    }
}

void ActivityGroupWidget::deselectAllSlots()
{
    for (auto selectionIndex : selectionSlots.keys()) {
        deselectSlotAtIndex(selectionIndex);
    }
}

bool ActivityGroupWidget::hasSelection()
{
    return selectionSlots.count() > 0;
}

int ActivityGroupWidget::length() const
{
    return _length;
}

void ActivityGroupWidget::setLength(int length)
{
    _length = length;
}

void ActivityGroupWidget::grow()
{
    setLength(length() + 1);
}

void ActivityGroupWidget::shrink()
{
    auto newLength = length() - 1;
    if (newLength < 1) {
        newLength = 1;
    }

    setLength(newLength);
}

QString ActivityGroupWidget::title() const
{
    return _title;
}

void ActivityGroupWidget::setTitle(QString title)
{
    _title = title;
    titleLabel->setText(title);
    updateStyleSheet();
}

int ActivityGroupWidget::number() const
{
    return _number;
}

void ActivityGroupWidget::setNumber(int number)
{
    _number = number;
    label->setText(QString::number(number));
}
