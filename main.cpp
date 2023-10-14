#include <includes.h>

class Edit : public QWidget
{
public:
  Edit()
  {
// block
    QLabel *label = new QLabel("Block IP-address", this);

    QLineEdit *ipAddrEdit = new QLineEdit(this);
    ipAddrEdit->setPlaceholderText("input IP");
    ipAddrEdit->setMaxLength(15);
    ipAddrEdit->setMaximumWidth(200);

// handler
    QObject::connect(ipAddrEdit, &QLineEdit::returnPressed, [=](){
      qDebug() << "text: " << ipAddrEdit->text();
      ipAddrEdit->clear();
    });

// unblock
    QLabel *label2 = new QLabel("Unblock IP-address", this);

    QLineEdit *ipAddrEdit2 = new QLineEdit(this);
    ipAddrEdit2->setPlaceholderText("input IP");
    ipAddrEdit2->setMaxLength(15);
    ipAddrEdit2->setMaximumWidth(200);

// handler2
    QObject::connect(ipAddrEdit2, &QLineEdit::returnPressed, [=](){
      qDebug() << "text2: " << ipAddrEdit2->text();
      ipAddrEdit2->clear();
    });

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(ipAddrEdit);
    layout->addSpacing(5);
    layout->addWidget(label2);
    layout->addWidget(ipAddrEdit2);
    layout->addStretch(1);
    setLayout(layout);
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
