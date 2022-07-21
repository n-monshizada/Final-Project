#include <QRandomGenerator>

#include "mainwindow.h"
#include "settings.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    _scene = new QGraphicsScene();
    _scene->setSceneRect(0, 0, 750, 750);
    _scene->clearFocus();

    _view = new QGraphicsView(_scene);
    _view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _view->setFixedSize(750, 750);

    setCentralWidget(_view);
    setWindowTitle(tr("Bomberman(Kharazmi University)"));
    setWindowIcon(QPixmap(":img/img/bomb.png"));

    initFields(3);

    _playersCount = sizes::Players;
    _player1 = new Player(0, 0);
    connect(_player1, SIGNAL(playerDied()), this, SLOT(playerDied()));
    _fields[0][0]->playerOn(_player1);
    _player2 = new Player(sizes::Columns - 1, sizes::Rows - 1);
    connect(_player2, SIGNAL(playerDied()), this, SLOT(playerDied()));
    _fields[sizes::Rows - 1][sizes::Columns - 1]->playerOn(_player2);
    _scene->addItem(_player1);
    _scene->addItem(_player2);

    setFocus();
}



void MainWindow::initFields(int frequency) {
    for (int i = 0; i < sizes::Rows; i++) {
        _fields.push_back(std::vector<Field *>());
        for(int j = 0; j < sizes::Columns; j++) {
            Field *newField = new Field(j * sizes::FieldSize, i * sizes::FieldSize);
            _fields[static_cast<std::size_t>(i)].push_back(newField);
            _scene->addItem(newField);
            //generating UndestroyableBlocks
            if (i % 2 && j % 2) {
                newField->setUnDestroyableBlock(new UnDestroyableBlock());
            }
            //generating DestoryableBlocks
            else if ((i > 1 || j > 1) && (i < sizes::Rows - 2 || j < sizes::Columns - 2)) {
                if(QRandomGenerator::global()->bounded(frequency)) { //put bigger number to generate blocks more often
                    newField->setDestoryableBlock(new DestroyableBlock());
                }
            }
        }
    }
}
