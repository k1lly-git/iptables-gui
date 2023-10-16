#include <functions.h>

bool checkRoot()
{
  bool flag = true;
  if (getuid() != 0)
  {
    QMessageBox *msgBox = new QMessageBox(QMessageBox::Warning, "Error", "Run program with root");
    msgBox->setAttribute(Qt::WA_DeleteOnClose);
    msgBox->show();
    flag = false;
  }
  return flag;
}

bool dirExists(const std::string &dirname)
{
  bool flag = false;
  DIR* dir = opendir(dirname.c_str());
  if (dir)
  {
    closedir(dir);
    flag = true;
  }
  return flag;
}

void getDefaultRules()
{
  if (!dirExists("/opt/iptables-gui"))
  {
    system("sudo mkdir /opt/iptables-gui");
    FILE* fileCheck = fopen("/opt/iptables-gui/default_rules.conf", "r");
    if (fileCheck == NULL)
    {
      system("sudo touch /opt/iptables-gui/default_rules.conf");
      FILE* file = fopen("/opt/iptables-gui/default_rules.conf", "w");
      FILE* pipe = popen("sudo iptables -S", "r");

      char buff[1024];
      while (fgets(buff, sizeof(buff), pipe) != NULL)
      {
        fprintf(file, "%s", buff);
      }
      pclose(pipe);
      fclose(file);
    }
    else
    { fclose(fileCheck); }
  }
}
