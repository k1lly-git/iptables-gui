#include <QApplication>
#include <QMainWindow>
#include <QWidget>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  QMainWindow window;
  window.setGeometry(100, 100, 500, 400);
  window.show();
  
  return app.exec();
}
