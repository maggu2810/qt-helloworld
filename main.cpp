#include <QApplication>
#include <QMainWindow>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QPainterPath>
#include <QPainter>

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    QMainWindow mainWindows;

    QWidget *window = new QWidget(&mainWindows);
    QHBoxLayout *layout = new QHBoxLayout(window);

    const QPixmap pm1{":/res/c1.png"};
    const QPixmap pm2{(":/res/c2.png")};

    QPushButton *button = new QPushButton("button", window);
    QLineEdit *lineEdit = new QLineEdit(window);
    QLabel *label = new QLabel("label", window);
    QLabel *labelPm1 = new QLabel(window);
    labelPm1->setPixmap(pm1);
    QLabel *labelPm2 = new QLabel(window);
    labelPm2->setPixmap(pm2);

    layout->addWidget(button);
    layout->addWidget(lineEdit);
    layout->addWidget(label);
    layout->addWidget(labelPm1);
    layout->addWidget(labelPm2);

    mainWindows.setCentralWidget(window);
    mainWindows.resize(800, 600);
    mainWindows.show();
    return app.exec();
}
