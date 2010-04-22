#include <iostream>
#include <Plugin.h>
#include <Widget.h>

int main(int argc, char *argv[]) {

  Plugin *p = Plugin::loadPlugin("./plugins", "StaticWidget");

  std::cout << "Plugin: " << p << std::endl;

  Widget *w = (Widget*)p->getFactory()->create();
  
  std::cout << w->width() << "x" << w->height() << std::endl;

  p->getFactory()->destroy(w);

  Plugin::unloadPlugin(p);

  return 0;
}

/* vim: set sw=2 sts=2 : */
