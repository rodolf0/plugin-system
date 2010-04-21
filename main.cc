#include <iostream>
#include <Plugin.h>
#include <Widget.h>

int main(int argc, char *argv[]) {

  Plugin *p;

  Plugin::scandir("./plugins");
  p = Plugin::loadPlugin("./plugins", "StaticWidget");

  std::cout << "Plugin: " << p << std::endl;

  Widget *w = (Widget*)p->getFactory("StaticWidget")->create();
  
  std::cout << w->width() << std::endl;

  return 0;
}

/* vim: set sw=2 sts=2 : */
