/* Plugin.h
 *
 * A plugin object keeps track of a dynamically linked library.
 * Its expected that each plugin provides a factory for some class
 * of object it will provide.
 *
 * */

#ifndef _PLUGIN_H_
#define _PLUGIN_H_

#include <map>
#include <cstring>

#define FACTORY_REGISTRATION_ABI00(factoryClass) \
  Plugin::BaseFactory *my##factoryClass = 0;     \
  extern "C" {                                   \
    Plugin::BaseFactory * get##factoryClass() {  \
      if (!my##factoryClass) {                   \
        my##factoryClass = new factoryClass();   \
      }                                          \
      return my##factoryClass;                   \
    }                                            \
  }

class Plugin {
  public:
    static bool load(const char *path, const char *name);
    static bool unload(const char *name);

    static bool loadAll(const char *path);
    static bool unloadAll();

  public:
    class BaseFactory {
      public:
        virtual ~BaseFactory() {};
        virtual bool init() = 0;
        virtual void fini() {};
    };

    template <typename Interface>
    class Factory : public BaseFactory {
      public:
        // factory initialization and shutdown
        virtual bool init() = 0;
        virtual void fini() {};
        // creation and destruction of objects
        virtual Interface * create() const = 0;
        // let derived clases their objects
        //virtual Interface * create() { return new Interface(); }
        virtual void destroy(Interface *w) const { delete w; }
        // get a dynamic casted derived factory according to name
        static const Factory<Interface> * get(const char *name);
    };

    const char * name() const;
    const BaseFactory * factory() const;

  private:
    // Users are not allowed to manage plugins directly
    Plugin(const char *name, void *dlhand, BaseFactory *factory);
    Plugin & operator=(const Plugin &); // don't define this: dissallowed.
    ~Plugin();

  private:
    // dynamic loader handling functions
    static Plugin * create(const char *name,
                           const char *lib, const char *sym);
    static void destroy(Plugin *p);
    typedef BaseFactory* (*FactoryProc)(void);

    // track loaded plugins
    struct cmpStr {
      bool operator() (const char *a, const char *b) const {
        return strcmp(a, b) < 0;
      }
    };
    typedef std::map<const char *, Plugin *, cmpStr> PluginMap;
    static PluginMap loadedPlugins;

  public:
    static const Plugin * get(const char *name);

  private:
    // plugin information
    char *_name;
    void *_dlhandle;
    BaseFactory *_factory;
};

template <typename T>
const Plugin::Factory<T> * Plugin::Factory<T>::get(const char *name) {
  if (const Plugin *p = Plugin::get(name)) {
    if (const Plugin::BaseFactory *bf = p->factory()) {
      if (const Plugin::Factory<T> *f =
                dynamic_cast<const Plugin::Factory<T> *>(bf)) {
        return f;
      }
    }
  }
  return NULL;
}

// describe plugable types
#include "Widget.h"
typedef Plugin::Factory<Widget> WidgetFactory;

#endif /* _PLUGIN_H_ */

/* vim: set sw=2 sts=2 : */
