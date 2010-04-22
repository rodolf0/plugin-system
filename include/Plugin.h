#ifndef _PLUGIN_H_
#define _PLUGIN_H_

#include <map>

class Plugin {
  public:
    // Factory definition
    template <typename Interface>
    class Factory {
      public:
        const char * name() const;

        // factory initialization and shutdown
        virtual bool init() = 0;
        virtual void fini();

        // creation and destruction of objects
        virtual Interface * create() = 0;
        virtual void destroy(Interface *);
      private:
        char * _name;
    };

    // Base class of what a factory makes
    class Object {};

  private:
    // The library handle for the linker
    void *dlhand;
    // pointer to factory implementation
    Factory<Object> *factory;

    static std::map<const char *, Plugin *> loadedPlugins;

  public:
    Factory<Object> * getFactory() const;

    // Plugin management
    static Plugin * getPlugin(const char *p);
    static bool scandir(const char *path);
    static Plugin * loadPlugin(const char *path, const char *name);
    static void unloadPlugin(Plugin *p);
};

/* // Let each type define its creation methods
template <typename Interface>
Interface * Plugin::Factory<Interface>::create() {
  Interface *w = new Interface();
  return w;
}

template <typename Interface>
void Plugin::Factory<Interface>::init() {}
*/

template <typename Interface>
void Plugin::Factory<Interface>::destroy(Interface *w) {
  if (w)
    delete w;
}

template <typename Interface>
void Plugin::Factory<Interface>::fini() {}


template <typename Interface>
const char * Plugin::Factory<Interface>::name() const {
  return _name;
}

typedef Plugin::Factory<Plugin::Object> * (*FactoryProc)(void);


#endif /* _PLUGIN_H_ */

/* vim: set sw=2 sts=2 : */
