#include <includes.h>
#include <functions.h>

// Widgets style
// this can move to the other .h file

class myQLineEdit : public QLineEdit
{
public:
  myQLineEdit(QWidget *parent = nullptr) : QLineEdit(parent)
  {
    this->setPlaceholderText("input IP");
    this->setMaxLength(15);
    this->setMaximumWidth(200);
  }
};

// Widgets style

class Edit : public QWidget
{
  QLabel *label;
  QLabel *label2;
  QLineEdit *ipAddrEdit;
  QLineEdit *ipAddrEdit2;
public:
  Edit()
  {
// block
    label = new QLabel("Block IP-address", this);
    ipAddrEdit = new myQLineEdit(this);
// handler
    QObject::connect(ipAddrEdit, &QLineEdit::returnPressed, [=](){
      QString resStr = "sudo iptables -A INPUT -s ";
      resStr.append(ipAddrEdit->text());
      resStr.append(" -j DROP");
      system(resStr.toStdString().c_str());
      qDebug() << "text: " << ipAddrEdit->text();
      ipAddrEdit->clear();
    });

// unblock
    label2 = new QLabel("Unblock IP-address", this);
    ipAddrEdit2 = new myQLineEdit(this);
// handler2
    QObject::connect(ipAddrEdit2, &QLineEdit::returnPressed, [=](){
      QString resStr = "sudo iptables -D INPUT -s ";
      resStr.append(ipAddrEdit2->text());
      resStr.append(" -j DROP");
      system(resStr.toStdString().c_str());
      qDebug() << "text: " << ipAddrEdit2->text();
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
  ~Edit()
  {
    delete label;
    delete ipAddrEdit;
    delete label2;
    delete ipAddrEdit2;
  }
};

class Rules : public QWidget
{
public:
  QLabel *label1;

  Rules()
  {
    label1 = new QLabel(this);
    
    FILE* pipe = popen("sudo iptables -S", "r");
    char buff[1024];
    std::string res;
    while (fgets(buff, sizeof(buff), pipe) != NULL)
    { res += buff; }
    pclose(pipe);

    label1->setText(QString::fromStdString(res));
    label1->show();
  }
  ~Rules() { delete label1; }
};

class Reset : public QWidget
{
  QVBoxLayout *verticalLayout;
  QHBoxLayout *horizontalLayout;
  QPushButton *resetButton;
public:
  Reset()
  {
    verticalLayout = new QVBoxLayout(this);
    horizontalLayout = new QHBoxLayout();

    resetButton = new QPushButton("Reset Settings", this);
    resetButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    horizontalLayout->addWidget(resetButton);
    horizontalLayout->setAlignment(Qt::AlignHCenter);
    verticalLayout->addStretch();
    verticalLayout->addLayout(horizontalLayout);
    verticalLayout->addStretch();
    verticalLayout->setAlignment(Qt::AlignVCenter);

    this->show();
// handler
    QObject::connect(resetButton, &QPushButton::clicked, [&](){
        changeToDefaultRules();
        qDebug() << "[+] reset";
      });
  }
  ~Reset() { delete resetButton; }
};

class Settings : public QWidget
{
  QVBoxLayout *layout;
  QRadioButton *radio_1;
  QRadioButton *radio_2;
public:
  Settings()
  {
    layout = new QVBoxLayout(this);
    radio_1 = new QRadioButton("light", this);
    radio_2 = new QRadioButton("dark", this);

    std::string currentTheme = getTheme();
    if (currentTheme == "light")
    {
      radio_1->setChecked(true);
    }
    else if (currentTheme == "dark")
    {
      radio_2->setChecked(true);
    }

    layout->addWidget(radio_1);
    layout->addWidget(radio_2);
    layout->addStretch();

// handler
    QObject::connect(radio_1, &QRadioButton::clicked, [=](){
    QPalette palette;
        changeTheme(*qApp, palette, "light");
        saveTheme("light");
      });
    QObject::connect(radio_2, &QRadioButton::clicked, [=](){
    QPalette palette;
        changeTheme(*qApp, palette, "dark");
        saveTheme("dark");
      });
 
  }
  ~Settings() {}
};

class FAQ : public QWidget
{
  QLabel *label1;
public:
  FAQ()
  {
    label1 = new QLabel("FAQText", this);
    label1->show();
  }
  ~FAQ() { delete label1; }
};

class Window : public QMainWindow
{
public:
  Window() { this->setGeometry(100, 100, 500, 400); }
};

class Tabs : public QTabWidget
{
  QWidget *editorTab, *rulesTab, *resetTab, *settingsTab, *faqTab;
public:
  Tabs(QWidget *parent) : QTabWidget(parent)
  {
    editorTab = new Edit();
    rulesTab = new Rules();
    resetTab = new Reset();
    settingsTab = new Settings();
    faqTab = new FAQ();

    this->addTab(editorTab, "Editor");
    this->addTab(rulesTab, "Rules");
    this->addTab(resetTab, "Reset");
    this->addTab(settingsTab, "Settings");
    this->addTab(faqTab, "FAQ");
  }
};

int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  app.setStyle(QStyleFactory::create("Fusion"));

  if(!checkRoot()) { return app.exec(); }
  getDefaultRules();
  initTheme();
  std::string startTheme = getTheme();
  QPalette qpalette;
  changeTheme(app, qpalette, startTheme);
  Window window;

  Tabs tabWidget(&window); 

  window.setCentralWidget(&tabWidget);
  window.setWindowTitle("iptables-gui");
  window.show();

  return app.exec();
}
