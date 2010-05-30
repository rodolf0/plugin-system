#ifndef _OPTION_PARSER_H_
#define _OPTION_PARSER_H_

#define ARG_SIZE 64

class OptionParser {
  public:

    class Option {
      public:
        Option(const char *name, bool takes_arg,
               const char *defarg, const char *descrip);

        bool isSet() const;
        bool takesArgument() const;
        void setArgument(const char *arg);
        const char * DefArgument() const;
        const char * name() const;
        const char * argument() const;
        const char * description() const;

      private:
        const char *name_val;
        bool takes_arg;
        bool is_set;
        const char *default_val;
        const char *descrip_val;
        char argument_val[ARG_SIZE];
    };

    OptionParser(int argc, char *argv[]);
    void printOptions() const;

    const Option * getOption(const char *name) const;

    static int optionCount();

  private:
    static Option Options[];
};

// This implementation needs to move into another header that
// only OptionParser.cc includes
OptionParser::Option OptionParser::Options[] = {
  Option("help"       , false, ""           , "this help"),
  Option("config"     ,  true, "-"          , "config file"),
  Option("layer"      ,  true, ""           , "[above|bellow] choose at wich layer to run"),
  Option("above-desk" , false, ""           , "run over desktop manager (ie: nautilus)"),
  Option("isize"      ,  true, "32"         , "icon normal size"),
  Option("idist"      ,  true, "1"          , "icon spacing"),
  Option("zoomf"      ,  true, "1.8"        , "icon grow factor"),
  Option("jumpf"      ,  true, "1"          , "icon jump factor"),
  Option("pos"        ,  true, "bottom"     , "wbar position (top / bottom / +x+y)"),
  Option("balfa"      ,  true, "-1"         , "bar alpha value"),
  Option("falfa"      ,  true, "-1"         , "lost focus bar alpha"),
  Option("dblclk"     ,  true, "200"        , "double click time in ms"),
  Option("bpress"     , false, ""           , "3D press simulation"),
  Option("vbar"       , false, ""           , "vertical wbar"),
  Option("filter"     ,  true, "0"          , "filter designation (0:none, 1:hovered, 2:others)"),
  Option("fc"         ,  true, "0xff00c800" , "filter color 0xAARRGGBB"),
  Option("nanim"      ,  true, "7"          , "number of animated icons"),
  Option("nofont"     , false, ""           , "disable font rendering"),
  Option("startdelay" ,  true, "15"         , "startup delay"),
};

#endif /* _OPTION_PARSER_H_ */
