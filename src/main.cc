#include <iostream>

#include "Plugin.h"
#include "Widget.h"

typedef Plugin::Factory<Widget> WidgetFactory;

int main(int argc, char *argv[]) {

  if (Plugin::load("../plugins", "StaticWidget")) {
    if (const WidgetFactory *wf = WidgetFactory::get("StaticWidget")) {
      Widget *w = wf->create();
      std::cout << w->width() << "x" << w->height() << std::endl;
      wf->destroy(w);
    }

    Plugin::unload("StaticWidget");
  }

  return 0;
}

/* vim: set sw=2 sts=2 : */
