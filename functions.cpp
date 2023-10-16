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
  if (!dirExists(CONF_DIR))
  {
    std::string dirname = "sudo mkdir ";
    dirname.append(CONF_DIR);
    qDebug() << dirname.c_str();
    system(dirname.c_str());
    FILE* fileCheck = fopen(CONF_FILE, "r");
    if (fileCheck == NULL)
    {
      std::string filename = "sudo touch ";
      filename.append(CONF_FILE);
      qDebug() << filename.c_str();
      system(filename.c_str());
      FILE* file = fopen(CONF_FILE, "w");
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

void changeToDefaultRules()
{
  system("sudo iptables -F");
  system("sudo iptables -X");
  FILE* file = fopen(CONF_FILE, "r");
  
  char buff[1024];
  while (fgets(buff, sizeof(buff), file) != NULL)
  {
    std::string resRule = "sudo iptables ";
    std::string fullRule = resRule + buff;
    if (fullRule[fullRule.length() - 1] == '\n') { fullRule[fullRule.length() - 1] = ' '; }
    system(fullRule.c_str());
  }
  fclose(file);
}
