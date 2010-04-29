#include <iostream>
#include <cstring>
#include <getopt.h>
#include "OptionParser.h"

int OptionParser::optionCount() {
  return sizeof(Options) / sizeof(Option);
}

OptionParser::OptionParser(int argc, char *argv[]) {
  struct option longOpts[OptionParser::optionCount()];
  int i, ret = -1;

  memset(longOpts, 0x00, sizeof(longOpts));

  for (i = 0; i < OptionParser::optionCount(); i++) {
    longOpts[i].name = Options[i].name();
    longOpts[i].has_arg = Options[i].takesArgument();
  }

  while ((ret = getopt_long_only(argc, argv, "h", longOpts, &i)) == 0)
    Options[i].setArgument(optarg);

  if (ret != -1)
    throw "Error parsing options";
}


OptionParser::Option::Option(const char *name, bool takes_arg,
                             const char *defarg, const char *descrip) :
  name_val(name), takes_arg(takes_arg), is_set(false),
  default_val(defarg), descrip_val(descrip) {} 

void OptionParser::Option::setArgument(const char *arg) {
  is_set = true;
  if(arg) {
    strncpy(argument_val, arg, ARG_SIZE-1);
    argument_val[ARG_SIZE-1] = '\0';
  }
}

bool OptionParser::Option::isSet() const { return is_set; }
bool OptionParser::Option::takesArgument() const { return takes_arg; }
const char * OptionParser::Option::DefArgument() const { return default_val; }
const char * OptionParser::Option::argument() const { return argument_val; }
const char * OptionParser::Option::name() const { return name_val; }
const char * OptionParser::Option::description() const { return descrip_val; }


void OptionParser::printOptions() const {
  int i;

  std::cout << "Usage: wbar [options]" << std::endl;
  std::cout << "Options:" << std::endl << std::endl;

  std::cout.width(12);

  for (i = 0; i < OptionParser::optionCount(); i++){
    std::cout.width(14);
    std::cout.setf(std::ios::left);
    std::cout << Options[i].name();
    std::cout.width(0);
    std::cout << ": " << Options[i].description() << std::endl;
  }
}

const OptionParser::Option * OptionParser::getOption(const char *name) const {
  size_t namelen = strlen(name);
  for (int i = 0; i < OptionParser::optionCount(); i++) {
    if (strncmp(Options[i].name(), name, namelen) == 0)
      return Options+i;
  }
  return NULL;
}

#define _TEST_PARSER_
#ifdef _TEST_PARSER_
int main(int argc, char *argv[]) {

  OptionParser op(argc, argv);

  op.printOptions();

  if (op.getOption("zoomf")) {
    std::cout << op.getOption("zoomf")->isSet() << std::endl;
    std::cout << op.getOption("zoomf")->name() << std::endl;
    std::cout << op.getOption("zoomf")->description() << std::endl;
    std::cout << op.getOption("zoomf")->argument() << std::endl;
    std::cout << op.getOption("zoomf")->DefArgument() << std::endl;
    std::cout << op.getOption("zoomf")->takesArgument() << std::endl;
  }

  return 0;
}
#endif
