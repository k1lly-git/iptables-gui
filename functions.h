#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#define CONF_DIR "/opt/iptables-gui/"
#define CONF_FILE "/opt/iptables-gui/default_rules.conf"

#include <includes.h>

bool checkRoot();
bool dirExists(const std::string &dirname);
void getDefaultRules();
void changeToDefaultRules();

#endif
