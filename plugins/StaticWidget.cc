#include <Plugin.h>
#include "StaticWidget.h"

class StaticWidgetFactory : 
    public Object,
    public Plugin::Factory<Object> {

  public:
    bool init();
    StaticWidget * create();
};

bool StaticWidgetFactory::init() { return true; }

StaticWidget * StaticWidgetFactory::create() {
  return new StaticWidget();
}

StaticWidgetFactory *myStaticWidgetFactory = 0;

extern "C" {
  StaticWidgetFactory * getStaticWidgetFactory() {
    if (!myStaticWidgetFactory) {
      myStaticWidgetFactory = new StaticWidgetFactory;
    }
    return myStaticWidgetFactory;
  }
}



StaticWidget::StaticWidget() :
  _x(0), _y(0), _width(1), _height(1), _scale(1.0) {}

StaticWidget::~StaticWidget() {}

int StaticWidget::x() const {
  return _x;
}
int StaticWidget::y() const {
  return _y;
}
int StaticWidget::width() const {
  return _width;
}
int StaticWidget::height() const {
  return _height;
}

void StaticWidget::move(int x, int y) {
  _x = x;
  _y = y;
}
void StaticWidget::scale(float f) {
  _scale = f;
}

void StaticWidget::render() const {
  return;
}

/* vim: set sw=2 sts=2 : */
