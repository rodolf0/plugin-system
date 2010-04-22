#ifndef _STATIC_WIDGET_H_
#define _STATIC_WIDGET_H_

#include "Widget.h"


class StaticWidget :
    public Widget {
  public:

    StaticWidget();

    int x() const;
    int y() const;
    int height() const;
    int width() const;

    void scale(float f);
    void move(int x, int y);

    void render() const;

    ~StaticWidget();

  protected:
    int _x, _y, _width, _height;
    float _scale;

};

class StaticWidgetFactory : public WidgetFactory {
  public:
    bool init();
    StaticWidget * create();
};

#endif /* _STATIC_WIDGET_H_ */

/* vim: set sw=2 sts=2 : */
