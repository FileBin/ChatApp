#include <QCoreApplication>
#include <QDebug>
#include <QTimer>
#include <numeric>

// runner for tests
class TestRunner : public QObject {
    Q_OBJECT
  public:
    typedef bool (*test_func)();
    std::vector<test_func> tests;
    TestRunner(QObject *parent, std::vector<test_func> tests) : QObject(parent), tests(tests) {}

  public slots:
    void run() {
        for (auto test : tests) {
            if (test()) {
                qInfo() << "Test passed!";
            } else {
                qInfo() << "Test failed!";
            }
        }
        emit finished();
    }

  signals:
    void finished();
};

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    TestRunner *runner = new TestRunner(&a, {});
    QObject::connect(runner, SIGNAL(finished()), &a, SLOT(quit()));

    // This will run the task from the application event loop.
    QTimer::singleShot(0, runner, SLOT(run()));
    return a.exec();
}

#include "main.moc"
