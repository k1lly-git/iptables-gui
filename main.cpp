#include <includes.h>
#include <functions.h>

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

    ipAddrEdit = new QLineEdit(this);
    ipAddrEdit->setPlaceholderText("input IP");
    ipAddrEdit->setMaxLength(15);
    ipAddrEdit->setMaximumWidth(200);

// handler
    QObject::connect(ipAddrEdit, &QLineEdit::returnPressed, [=](){
      qDebug() << "text: " << ipAddrEdit->text();
      ipAddrEdit->clear();
    });

// unblock
    label2 = new QLabel("Unblock IP-address", this);

    ipAddrEdit2 = new QLineEdit(this);
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
  QPushButton *resetButton;
public:
  Reset()
  {
    QVBoxLayout *verticalLayout = new QVBoxLayout(this);
    QHBoxLayout *horizontalLayout = new QHBoxLayout;

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
  QLabel *label1;
public:
  Settings()
  {
    label1 = new QLabel("SettingsText", this);
    label1->show();
  }
  ~Settings() { delete label1; }
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
  if(!checkRoot()) { return app.exec(); }
  getDefaultRules();
  Window window;

  Tabs tabWidget(&window); 

  window.setCentralWidget(&tabWidget);
  window.setWindowTitle("iptables-gui");
  window.show();

  return app.exec();
}
