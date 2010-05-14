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

class Plugin {
  // Plugin management
  public:

    static bool load(const char *path, const char *name);
    static bool unload(const char *name);

    static bool loadAll(const char *path);
    static bool unloadAll();

    // what if I dont have it ?
    static const Plugin * get(const char *name);

  private:
    static Plugin * create(const char *name,
                           const char *lib, const char *sym);
    static void destroy(Plugin *p);

    struct cmpStr {
      bool operator() (const char *a, const char *b) const {
        return strcmp(a, b) < 0;
      }
    };

    typedef std::map<const char *, Plugin *, cmpStr> PluginMap;
    static PluginMap loadedPlugins;

  // plugin definition
  public:

    // Factory definition
    template <typename Interface>
    class Factory {
      public:
        // factory initialization and shutdown
        virtual bool init() = 0;
        virtual void fini();
        // creation and destruction of objects
        virtual Interface * create() = 0;
        virtual void destroy(Interface *);
    };
    // Base class of whatever the factory makes
    class Object {};

    const char * name() const;
    Factory<Object> & getFactory() const;

  private:
    // Users are not allowed to make or destroy plugins directly
    Plugin(const char *name, void *dlhand, Factory<Object> *factory);
    ~Plugin();
    // DONT define this function: disallow plugin assignment
    Plugin & operator=(const Plugin &);

    typedef Plugin::Factory<Plugin::Object> * (*FactoryProc)(void);

    void *_dlhandle;
    char *_name;
    Factory<Object> *_factory;
};

template <typename Interface>
void Plugin::Factory<Interface>::destroy(Interface *w) {
  delete w;
}

template <typename Interface>
void Plugin::Factory<Interface>::fini() {}

// Let each type define its creation methods
#if 0
template <typename Interface>
Interface * Plugin::Factory<Interface>::create() {
  Interface *w = new Interface();
  return w;
}

template <typename Interface>
void Plugin::Factory<Interface>::init() {}
#endif

#endif /* _PLUGIN_H_ */

/* vim: set sw=2 sts=2 : */
