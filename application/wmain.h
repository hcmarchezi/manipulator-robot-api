#ifndef WMAIN_H
#define WMAIN_H

#include <QMainWindow>

#include "appmain.h"

namespace Ui {
class WMain;
}

namespace HIC
{
    class WMain : public QMainWindow
    {
        Q_OBJECT

    public:
        explicit WMain(QWidget *parent = 0);
        ~WMain();

    protected:
        void loadLinkTypes();

        Ui::WMain *ui;
        TMC::AppMain _application;

    protected slots:
        void rotXSliderValueChanged(int value);
        void rotYSliderValueChanged(int value);
        void rotZSliderValueChanged(int value);

        void transXSliderValueChanged(int value);
        void transYSliderValueChanged(int value);
        void transZSliderValueChanged(int value);

    };
}

#endif // WMAIN_H
