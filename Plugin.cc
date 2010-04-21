#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <dlfcn.h>
#include <string>
#include <iostream>

#include <Plugin.h>

Plugin * Plugin::loadPlugin(const char *path, const char *name) {
  std::string file;
  struct stat finfo;
  void *dlhand = NULL;
  FactoryProc getFactory;
  bool loaded = false;
  Plugin *p = NULL;

  // check file existence
  file = std::string(path) + "/lib" + std::string(name) + ".so";
  if (stat(file.c_str(), &finfo) != 0) {
    std::cout << "Couldn't stat plugin: " << file << std::endl;
    return NULL;
  }

  // attempt to load library
  if ((dlhand = dlopen(file.c_str(), RTLD_LAZY))) {
    // clear out errors
    char *error = dlerror();
    // resolv plugin export symbol
    std::string sym = "get" + std::string(name) + "Factory";

    getFactory = (FactoryProc)dlsym(dlhand, sym.c_str());
    if ((error = dlerror())) {
      std::cout << "dlsym: " << error << std::endl;
      getFactory = NULL;
    }

    if (getFactory) {
      p = new Plugin();
      p->dlhand = dlhand;
      if ((p->factory = getFactory())) {
        loaded = true;
      } else {
        std::cout << "Couldn't load factory: " << name << std::endl;
        delete p;
        p = NULL;
      }
    } else {
      std::cout << "No Factory available: " << name << std::endl;
    }

  } else {
    std::cout << "Couldn't load plugin: " << name << std::endl;
  }

  // if loading failed, close handler
  if (dlhand && !loaded) {
    dlclose(dlhand);
  }

  return p;
}

int Plugin::scandir(const char *p) { 
  struct dirent *d;
  DIR *dp;

  dp = opendir(p);
  while ((d = readdir(dp))) {
    std::cerr << "Found Plugin: " <<  d->d_name << std::endl;
  }

  closedir(dp);

  return 0; 
}

Plugin::Factory<Object> * Plugin::getFactory(const char *f) const {
  return factory;
}

/* vim: set sw=2 sts=2 : */
