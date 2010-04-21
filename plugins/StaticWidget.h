#ifndef _STATIC_WIDGET_H_
#define _STATIC_WIDGET_H_

#include "Widget.h"


class StaticWidget : public Widget {
  public:

    StaticWidget();

    int x() const;
    int y() const;
    int height() const;
    int width() const;

    void scale(float f);
    void move(int x, int y);

    void render() const;

  protected:
    ~StaticWidget();

    int _x, _y, _width, _height;
    float _scale;

};



#endif /* _STATIC_WIDGET_H_ */

/* vim: set sw=2 sts=2 : */
