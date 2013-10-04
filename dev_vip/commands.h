#define SIGNAL_FINISH "isoend"
#define SIGNAL_SETFILTER "setfilter"
#define SIGNAL_ENDLIST "endlist"
#define SIGNAL_SETFILTERMODE "setfiltermode"
#define SIGNAL_FILTER_BLOCK "block"
#define SIGNAL_FILTER_ALLOW "allow"

void scan(char * addr);
Settings * command_listen(Settings * st , const char * a);
