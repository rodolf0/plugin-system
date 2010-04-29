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
};

static OptionParser::Option Options[] = {
  OptionParser::Option("help"       , false, ""           , "this help"),
  OptionParser::Option("config"     ,  true, "-"          , "config file"),
  OptionParser::Option("layer"      ,  true, ""           , "[above|bellow] choose at wich layer to run"),
  OptionParser::Option("above-desk" , false, ""           , "run over desktop manager (ie: nautilus)"),
  OptionParser::Option("isize"      ,  true, "32"         , "icon normal size"),
  OptionParser::Option("idist"      ,  true, "1"          , "icon spacing"),
  OptionParser::Option("zoomf"      ,  true, "1.8"        , "icon grow factor"),
  OptionParser::Option("jumpf"      ,  true, "1"          , "icon jump factor"),
  OptionParser::Option("pos"        ,  true, "bottom"     , "wbar position (top / bottom / +x+y)"),
  OptionParser::Option("balfa"      ,  true, "-1"         , "bar alpha value"),
  OptionParser::Option("falfa"      ,  true, "-1"         , "lost focus bar alpha"),
  OptionParser::Option("dblclk"     ,  true, "200"        , "double click time in ms"),
  OptionParser::Option("bpress"     , false, ""           , "3D press simulation"),
  OptionParser::Option("vbar"       , false, ""           , "vertical wbar"),
  OptionParser::Option("filter"     ,  true, "0"          , "filter designation (0:none, 1:hovered, 2:others)"),
  OptionParser::Option("fc"         ,  true, "0xff00c800" , "filter color 0xAARRGGBB"),
  OptionParser::Option("nanim"      ,  true, "7"          , "number of animated icons"),
  OptionParser::Option("nofont"     , false, ""           , "disable font rendering"),
  OptionParser::Option("startdelay" ,  true, "15"         , "startup delay"),
};

#endif /* _OPTION_PARSER_H_ */
