#include <iostream>
#include <Plugin.h>
#include <Widget.h>
#include <Container.h>

int main(int argc, char *argv[]) {

  //Plugin *c = Plugin::loadPlugin("./plugins", "WaveContainer");
  if (Plugin::load("./plugins", "StaticWidget")) {
    Plugin::Factory<Plugin::Object> &wf = Plugin::get("StaticWidget")->getFactory();

    Widget *w = (Widget*)wf.create();
    std::cout << w->width() << "x" << w->height() << std::endl;
    wf.destroy(w);

    Plugin::unload("StaticWidget");
  }

  return 0;
}

/* vim: set sw=2 sts=2 : */
