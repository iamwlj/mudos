#include "spec.h"

    mixed abs(int | float);
    string base_name(string | object default: F__THIS_OBJECT);
    string ansi(string);
    string ansi_part(string);
    string remove_ansi(string);
    string remove_bg_ansi(string);
    string kill_repeat_ansi(string);
    int noansi_strlen(string);
    mixed count(mixed, string, mixed);
    string B2G(string);
    string G2B(string);
    string bg5cc(string);
    string cwrap(string, void | int, void | int);
#ifdef NO_ADD_ACTION
    object find_player(string);
#endif
    void remove_input_to(void | object);
    string remove_fringe_blanks(string);
    string buftostr(buffer);
    buffer strtobuf(string);
    int milli_clock();

