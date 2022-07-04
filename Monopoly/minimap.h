#ifndef MINIMAP_H
#define MINIMAP_H

#include <QDialog>

namespace Ui {
class minimap;
}

class minimap : public QDialog
{
    Q_OBJECT

public:
    explicit minimap(QWidget *parent = nullptr);
    ~minimap();

private:
    Ui::minimap *ui;
};

#endif // MINIMAP_H
