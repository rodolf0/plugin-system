#include "StaticWidget.h"

FACTORY_REGISTRATION_ABI00(StaticWidgetFactory)

bool StaticWidgetFactory::init() {
  return true;
}
StaticWidget * StaticWidgetFactory::create() const {
  return new StaticWidget();
}

/*******************************************************/

StaticWidget::StaticWidget() :
  _x(0), _y(0), _width(1), _height(7), _scale(1.0) {}

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
