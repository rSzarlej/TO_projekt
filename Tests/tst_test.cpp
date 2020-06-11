#include <QtTest>
#include "NewFile/newfile.h"
#include "NewFile/newfile2d.h"
#include "NewFile/newfile3d.h"
#include "NewFile/newfiletxt.h"
#include "mainsource.h"

// add necessary includes here

class test : public QObject
{
    Q_OBJECT

public:
    test();
    ~test();

private slots:
    void test_loadFiles();
    void test_loadFilesErrors();

};



test::test()
{

}

test::~test()
{

}

void test::test_loadFiles()
{
    MainSource ms;
    QString retInfo;
    ms.addFileToList("obraz", ":/TestFiles/image1.png", "komentarz", retInfo);
    ms.addFileToList("model", ":/TestFiles/model.OBJ", "komentarz", retInfo);
    ms.addFileToList("text", ":/TestFiles/tekstowy.txt", "komentarz", retInfo);

    QCOMPARE(ms.getFile("obraz")->getFType(), file2d);
    QCOMPARE(ms.getFile("model")->getFType(), file3d);
    QCOMPARE(ms.getFile("text")->getFType(), fileTxt);

    QCOMPARE(ms.getFile("obraz")->getComment(), "komentarz");
    QCOMPARE(ms.getFile("model")->getComment(), "komentarz");
    QCOMPARE(ms.getFile("text")->getComment(), "komentarz");

    ms.removeFileFromList("obraz");

    NewFilePtr tmp = ms.getFile("obraz");
    QCOMPARE(tmp.isNull(), true);
}

void test::test_loadFilesErrors()
{
    MainSource ms;
    QString retInfo;

    ms.addFileToList("test", ":/TestFiles/notexists.png", "komentarz", retInfo);

    QCOMPARE(ms.getFile("test").isNull(), true);
    QCOMPARE(retInfo, "File not exists: :/TestFiles/notexists.png");

    ms.addFileToList("test", ":/TestFiles/test.xml", "komentarz", retInfo);
    QCOMPARE(ms.getFile("test").isNull(), true);
    QCOMPARE(retInfo, "Unknown file");

    ms.addFileToList("test", ":/TestFiles/image1.png", "komentarz", retInfo);
    QCOMPARE(ms.getFile("test").isNull(), false);

    ms.addFileToList("test", ":/TestFiles/image1.png", "komentarz", retInfo);
    QCOMPARE(retInfo, "Name already on list.");
}

QTEST_APPLESS_MAIN(test)

#include "tst_test.moc"
