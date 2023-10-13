#include <includes.h>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  QMainWindow window;
  window.setGeometry(100, 100, 500, 400);
  window.show();
  
  QLabel *label = new QLabel("Text", &window);
  label->show();

  QPushButton *button = new QPushButton("button1", &window);
  button->setObjectName("but");

// Обработчик
  QObject::connect(button, &QPushButton::clicked, [&](){
    qDebug() << "true";  
  });

  button->resize(200, 100);
  button->move(window.width() / 2 - button->width() / 2, window.height() / 2 - button->height() / 2);
  button->show();

  return app.exec();
}
