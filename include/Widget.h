#ifndef _WIDGET_H_
#define _WIDGET_H_

#include <Plugin.h>

class Widget : public Object {
  public:

    virtual int x() const = 0;
    virtual int y() const = 0;
    virtual int height() const = 0;
    virtual int width() const = 0;

    virtual void render() const = 0;

  protected:

    virtual ~Widget() = 0;

};

#endif /* _WIDGET_H_ */

/* vim: set sw=2 sts=2 : */
