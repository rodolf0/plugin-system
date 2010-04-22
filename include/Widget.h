#ifndef _WIDGET_H_
#define _WIDGET_H_

#include <Plugin.h>

class Widget : public Plugin::Object {
  public:

    virtual int x() const = 0;
    virtual int y() const = 0;
    virtual int height() const = 0;
    virtual int width() const = 0;

    virtual void render() const = 0;
    virtual ~Widget() = 0;
};

Widget::~Widget() {};

typedef Plugin::Factory<Widget> WidgetFactory;

#endif /* _WIDGET_H_ */

/* vim: set sw=2 sts=2 : */
