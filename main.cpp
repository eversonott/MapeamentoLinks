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
#include <lemon/list_graph.h>
#include <lemon/concepts/graph.h>
#include <map>

//svm

using namespace std;
using namespace lemon;

void processaPagina(QWebPage &p, vector<string> &lista, map<string, ListDigraph::Node> &mapLista, ListDigraph &g) {
    string fromUrl = p.mainFrame()->url().toString().toStdString();
    if (mapLista.find(fromUrl) == mapLista.end()) {
        mapLista[fromUrl] = g.addNode();
    }
    ListDigraph::Node noFrom = mapLista[fromUrl];

    for (auto l : p.mainFrame()->findAllElements("a")) {
        string toUrl = l.attribute("href").toStdString();
        lista.push_back(toUrl);


        if (mapLista.find(toUrl) == mapLista.end()) {
            mapLista[toUrl] = g.addNode();
        }

        ListDigraph::Node noTo = mapLista[toUrl];
        g.addArc(noFrom, noTo);

    }

}

void proximoLink(vector<string> *lista, QWebPage *p, map<string, ListDigraph::Node> *mapLista, ListDigraph *g) {


    p->mainFrame()->load(QUrl(lista->front().c_str()));
    lista->erase(lista->begin());
    //proximoLink(lista,p);

}


int main(int argc, char *argv[]) {

    vector<string> lista;
    ListDigraph g;
    map<string, ListDigraph::Node> mapLista;
    //google = 1034 nós
    //google = 1051 nós e 2341 arcos
    string raiz = "https://www.google.com.br";

    lista.push_back(raiz);

    QApplication app(argc, argv);


    QWebPage p;


    p.mainFrame()->load(QUrl(lista.front().c_str()));
    lista.erase(lista.begin());


    if (p.mainFrame() == NULL) {
        cout << "null";
    }

    QObject::connect(&p, &QWebPage::loadProgress, [](int i) {
        //cout << "progresso " << i << "\n";
        //fflush(stdout);
    });


    QObject::connect(&p, &QWebPage::loadFinished, [&lista, &p, &g, &mapLista](bool acabou) {

        processaPagina(p, lista, mapLista, g);

        for (int i = 0; i < lista.size(); i++) {
            cout << lista.at(i) << endl;
        }

        cout <<"nos"<< lemon::countNodes(g) << endl;
        cout <<"arcos"<< lemon::countArcs(g)<<endl;
        fflush(stdout);
        p.mainFrame()->load(QUrl(lista.front().c_str()));
        lista.erase(lista.begin());
    });

    return app.exec();

}
