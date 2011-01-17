#include <cstring>
#include <cstdio>
#include <iostream>
#include <dlfcn.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#include "Plugin.h"

// Plugin management
Plugin::PluginMap Plugin::loadedPlugins;

bool Plugin::load(const char *path, const char *name) {
  // check if plugin is already loaded
  if (loadedPlugins[name]) {
    std::cout << "PM: Plugin " << name << " is already loaded.\n";
    return false;
  }

  // check plugin file existance
  struct stat finfo;
  char file[256];
  snprintf(file, sizeof(file), "%s/lib%s.so", path, name);
  if (stat(file, &finfo) != 0) {
    std::cout << "PM: Couldn't stat plugin: " << file << std::endl;
    return false;
  }

  char sym[256];
  snprintf(sym, sizeof(sym), "get%sFactory", name);
  Plugin *p = Plugin::create(name, file, sym);

  if (p) {
    // add the fresh new plugin to our map
    loadedPlugins[p->_name]= p;
    return true;
  }
  return false;
}

bool Plugin::unload(const char *name) {
  Plugin *p = loadedPlugins[name];

  if (!p) {
    std::cout << "PM: Cannont unload plugin: "
              << name << " not loaded.\n";
    return false;
  }

  Plugin::destroy(p);
  loadedPlugins.erase(name);

  return true;
}

// -------------------------------------------------------------- //

void Plugin::destroy(Plugin *p) {
  // destroy the factory created by the getFactory() call
  // we delete it since we provide the macro to build it.
  p->_factory->fini();
  // TODO: dlsym('CloseFactory')
  delete p->_factory;
  dlclose(p->_dlhandle);
  delete p;
}

Plugin * Plugin::create(const char *name,
                        const char *lib, const char *factsym) {
  // attempt to load library
  void *dlhand = NULL;
  if (!(dlhand = dlopen(lib, RTLD_LAZY))) {
    std::cout << "PM: Couldn't load plugin: " << lib << std::endl;
  } else {
    // clear out dl errors for next steps
    char *error = dlerror();
    // get a handle for a function in the loaded library:
    // we're expecting a function returning a specialized Factory type
    FactoryProc getFactory = (FactoryProc)dlsym(dlhand, factsym);
    if ((error = dlerror())) {
      std::cout << "PM: dlsym: " << error << std::endl;
      dlclose(dlhand);
    } else {
      // check that the library exports a factory instantiator
      if (!getFactory) {
        std::cout << "PM: No Factory available: " << lib << std::endl;
        dlclose(dlhand);
      } else {
        // get the factory that the plugin provides
        BaseFactory *factory = (*getFactory)();
        if (!factory) {
          std::cout << "PM: Couldn't load factory: " << lib << std::endl;
          dlclose(dlhand);
        } else {
          // initialize the factory
          if (!factory->init()) {
            std::cout << "PM: Couldn't initialize the factory: "
                      << lib << std::endl;
            delete factory;
            dlclose(dlhand);
          } else {
            return new Plugin(name, dlhand, factory);
          }
        }
      }
    }
  }
  return NULL;
}

// -------------------------------------------------------------- //

Plugin::Plugin(const char *name, void *dlhand, BaseFactory *factory)
  : _dlhandle(dlhand), _factory(factory) {

  size_t len = strlen(name);
  _name = new char[len + 1];
  strncpy(_name, name, len);
  _name[len] = '\0';
}

Plugin::~Plugin() { delete [] _name; }

// -------------------------------------------------------------- //

const char * Plugin::name() const { return _name; }
const Plugin::BaseFactory * Plugin::factory() const { return _factory; }

const Plugin * Plugin::get(const char *name) {
  return loadedPlugins[name];
}

#if 0
bool Plugin::scandir(const char *p) {
  struct dirent *d;
  DIR *dp;

  dp = opendir(p);
  while ((d = readdir(dp))) {
    std::cerr << "Found Plugin: " <<  d->d_name << std::endl;
  }

  closedir(dp);

  return 0;
}
#endif

/* vim: set sw=2 sts=2 : */
