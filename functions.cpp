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

void initTheme()
{
  FILE* themeFile = fopen(THEME_FILE, "r");
  if (themeFile == NULL)
  {
    themeFile = fopen(THEME_FILE, "w");
    fprintf(themeFile, "%s", "light");
  }
  fclose(themeFile);
}

std::string getTheme()
{
  FILE* themeFile = fopen(THEME_FILE, "r");
  std::string themeName;
  if (themeFile != NULL)
  {
    char buff[128];
    while(fgets(buff, sizeof(buff), themeFile) != NULL)
    {
      themeName.append(buff);
    }
  }
  fclose(themeFile);
  return themeName;
}

void saveTheme(const std::string &themeName)
{
  FILE *themeFile = fopen(THEME_FILE, "w");
  if (themeFile != NULL)
  {
    fwrite(themeName.c_str(), sizeof(char), themeName.length(), themeFile);
  }
  fclose(themeFile);
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

void changeTheme(QApplication &app, QPalette &palette, const std::string &theme)
{
  if (strcmp(theme.c_str(), "light") == 0)
  {
    palette.setColor(QPalette::Window, QColor(240, 240, 240)); // Задний фон
    palette.setColor(QPalette::WindowText, Qt::black); // Цвет текста
    palette.setColor(QPalette::Base, QColor(240, 240, 240)); // Фон для виджетов
    palette.setColor(QPalette::AlternateBase, QColor(220, 220, 220)); // Альтернативный фон для виджетов
    palette.setColor(QPalette::ToolTipBase, Qt::white); // Фон подсказок
    palette.setColor(QPalette::ToolTipText, QColor(32, 41, 49)); // Цвет текста подсказок
    palette.setColor(QPalette::Text, Qt::black); // Цвет текста ввода
    palette.setColor(QPalette::Button, QColor(240, 240, 240)); // Цвет кнопок
    palette.setColor(QPalette::ButtonText, Qt::black); // Цвет текста кнопок
    palette.setColor(QPalette::BrightText, Qt::red); // Яркий цвет текста (для сообщений об ошибках)
    palette.setColor(QPalette::Link, QColor(42, 130, 218)); // Цвет ссылок
    palette.setColor(QPalette::Highlight, QColor(42, 130, 218)); // Цвет выделения
    palette.setColor(QPalette::HighlightedText, Qt::white); // Цвет текста выделения
    palette.setColor(QPalette::Disabled, QPalette::Text, QColor(127, 127, 127)); // Цвет отключенного текста
  }
  else if (strcmp(theme.c_str(), "dark") == 0)
  {
    palette.setColor(QPalette::Window, QColor(32, 41, 49)); // задний фон
    palette.setColor(QPalette::WindowText, Qt::white); // цвет текста
    palette.setColor(QPalette::Base, QColor(32, 41, 49)); // фон для виджетов
    palette.setColor(QPalette::AlternateBase, QColor(44, 54, 63)); // альтернативный фон для виджетов
    palette.setColor(QPalette::ToolTipBase, Qt::white); // фон подсказок
    palette.setColor(QPalette::ToolTipText, QColor(32, 41, 49)); // цвет текста подсказок
    palette.setColor(QPalette::Text, Qt::white); // цвет текста ввода
    palette.setColor(QPalette::Button, QColor(32, 41, 49)); // цвет кнопок
    palette.setColor(QPalette::ButtonText, Qt::white); // цвет текста кнопок
    palette.setColor(QPalette::BrightText, Qt::red); // яркий цвет текста (для сообщений об ошибках)
    palette.setColor(QPalette::Link, QColor(42, 130, 218)); // цвет ссылок
    palette.setColor(QPalette::Highlight, QColor(42, 130, 218)); // цвет выделения
    palette.setColor(QPalette::HighlightedText, Qt::white); // цвет текста выделения
    palette.setColor(QPalette::Disabled, QPalette::Text, QColor(127, 127, 127)); // цвет отключенного текста  
  }
  app.setPalette(palette);
}
