#include <includes.h>

class Edit : public QWidget
{
public:
  Edit()
  {
    QLabel *label1 = new QLabel("EditText", this);
    label1->show();
  }
};

class Rules : public QWidget
{
public:
  Rules()
  {
    QLabel *label1 = new QLabel("RulesText", this);
    label1->show();
  }
};

class Reset : public QWidget
{
public:
  Reset()
  {
    QLabel *label1 = new QLabel("ResetText", this);
    label1->show();
  }
};

class Settings : public QWidget
{
public:
  Settings()
  {
    QLabel *label1 = new QLabel("SettingsText", this);
    label1->show();
  }
};

class FAQ : public QWidget
{
public:
  FAQ()
  {
    QLabel *label1 = new QLabel("FAQText", this);
    label1->show();
  }
};

int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  QMainWindow window;

  window.setGeometry(100, 100, 500, 400);

  QTabWidget *tabWidget = new QTabWidget(&window);

  QWidget *editorTab = new Edit();
  QWidget *rulesTab = new Rules();
  QWidget *resetTab = new Reset();
  QWidget *settingsTab = new Settings();
  QWidget *faqTab = new FAQ();

  tabWidget->addTab(editorTab, "Editor");
  tabWidget->addTab(rulesTab, "Rules");
  tabWidget->addTab(resetTab, "Reset");
  tabWidget->addTab(settingsTab, "Settings");
  tabWidget->addTab(faqTab, "FAQ");

  window.setCentralWidget(tabWidget);
  window.setWindowTitle("iptables-gui");
  window.show();

  return app.exec();
}
