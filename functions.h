#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#define CONF_DIR "/opt/iptables-gui/"
#define CONF_FILE "/opt/iptables-gui/default_rules.conf"
#define THEME_FILE "/opt/iptables-gui/theme.conf"

#include <includes.h>

bool checkRoot();
bool dirExists(const std::string &dirname);
void initTheme();
std::string getTheme();
void saveTheme(const std::string &themeName);
void getDefaultRules();
void changeToDefaultRules();
void changeTheme(QApplication &app, QPalette &palette, const std::string &theme);

#endif
