#ifndef SESSION_WIDGET_H
#define SESSION_WIDGET_H

#include "strategy.h"
#include "session.h"
#include "applicationsettings.h"
#include "colorprovider.h"

#include <QMap>
#include <QWidget>

class QTimeLine;

class SessionWidget : public QWidget, public ColorProvider {
Q_OBJECT

public:
    explicit SessionWidget(stg::session activitySession,
                           QWidget *parent = nullptr);


    bool isSelected() const;
    void setIsSelected(bool isSelected);

    void setActivitySession(const stg::session &newActivitySession);
    void setSlotHeight(int slotHeight);

    void setSelectBorder(bool isBorderSelected);

    static QColor borderColor();
private:
    int slotHeight = ApplicationSettings::defaultSlotHeight;
    bool _isSelected = false;
    bool isBorderSelected = false;

    stg::session activitySession;
    stg::session previousActivitySession = stg::session();

    stg::strategy::duration_t previousDuration = 0;
    stg::strategy::time_t previousEndTime = 0;

    void drawBorder(QPainter &painter);

    void updateUI();
    int expectedHeight();

    QColor selectedBackgroundColor() const;
    QColor sessionColor() const;

    void paintEvent(QPaintEvent *event) override;

    void drawSelection(QPainter &painter) const;
    void drawRulers(QPainter &painter) const;
    void drawLabel(QPainter &painter) const;
};


#endif // SESSION_WIDGET_H
