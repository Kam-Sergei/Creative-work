#include "calculator.h"
#include <QApplication>
#include <QLabel>
#include <QSplashScreen>
#include <QPainter>
#include <QTime>

static const int LOAD_TIME_MSEC = 5 * 1000;
static const int PROGRESS_X_PX = 168;
static const int PROGRESS_Y_PX = 88;
static const int PROGRESS_WIDTH_PX = 318;
static const int PROGRESS_HEIGHT_PX = 24;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pix( ":/button_images/images/Log_cal.png" );
    QSplashScreen splashScreen( pix );
    splashScreen.show();
    a.processEvents();
    QTime time;
    time.start();
    while( time.elapsed() < LOAD_TIME_MSEC )
    {
        const int progress = static_cast< double >( time.elapsed() ) / LOAD_TIME_MSEC * 100.0;
        splashScreen.showMessage( QObject::trUtf8( "Загружено: %1%" ).arg( progress ), Qt::AlignBottom | Qt::AlignRight );
        QPainter painter;
        painter.begin( &pix );
        painter.fillRect( PROGRESS_X_PX, PROGRESS_Y_PX, progress / 100.0 * PROGRESS_WIDTH_PX, PROGRESS_HEIGHT_PX, Qt::blue );
        painter.end();
        splashScreen.setPixmap( pix );
        a.processEvents();
    }
    splashScreen.close();
    calculator w;
    w.show();
    return a.exec();
}
