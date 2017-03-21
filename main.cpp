#include <iostream>
#include <curl/curl.h>
#include <string>
#include <Qt>
#include <QDomDocument>

#include <QtCore>
#include <vector>
#include <QtXml>
#include <QString>
#include <QByteArray>
#include <QtWebKit/QtWebKit>
#include <QWebFrame>
#include <QWebPage>
#include <QWebView>
#include <QWebFrame>
#include <QUrl>
#include <QtWidgets/QApplication>
#include <QList>

//svm
using namespace std;


void proximoLink(vector<string> * lista, QWebPage *p){

    p->mainFrame()->load(QUrl(lista->front().c_str()));
    for( auto l : p->mainFrame()->findAllElements("a")){
        lista->push_back(l.attribute("href").toStdString());
    }
    lista->erase(lista->begin());
    //proximoLink(lista,p);

}


int main(int argc, char *argv[]) {

    vector<string> lista;
    string raiz ="https://www.google.com.br";

    lista.push_back(raiz);
    QApplication app(argc, argv);



            QWebPage p;
            p.mainFrame()->load(QUrl(lista.front().c_str()));
            lista.erase(lista.begin());
            if (p.mainFrame() == NULL) {
                cout << "null";
            }

            QObject::connect(&p, &QWebPage::loadProgress, [](int i) {
                cout << "progresso " << i << "\n";
                fflush(stdout);
            });


            QObject::connect(&p, &QWebPage::loadFinished, [&lista, &p](bool acabou) {

                for (auto l : p.mainFrame()->findAllElements("a")) {
                    lista.push_back(l.attribute("href").toStdString());
                }

                proximoLink(&lista,&p);
                for (int i = 0; i < lista.size(); i++) {

                    cout<<lista.at(i)<< endl;

                }

                fflush(stdout);


            });






            //p.mainFrame()->findAllElements("a");




    return app.exec();

}
