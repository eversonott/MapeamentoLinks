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

size_t func(void* dados, size_t size, size_t nemb, string *saida){
    saida->append( (char*)dados, size*nemb );

    return size*nemb;
}
string getHTML(const char* url){

    std::string STR;
    CURL *curl= curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, func);
    curl_easy_setopt(curl,CURLOPT_WRITEDATA, &STR);

    curl_easy_perform(curl);
    curl_easy_cleanup(curl);


    return STR;
}


//Qlist<QString>* listaUrl;

vector<string> lista;
/*void proxima(auto p){
    p.mainFrame()->load(QUrl("https://www.google.com.br"))
}
*/

int main(int argc, char *argv[]) {

    vector<string> lista;
    string raiz ="https://www.google.com.br";

    lista.push_back(raiz);

        while(!lista.empty()) {
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

                //cout << p.mainFrame()->toPlainText().toStdString();
                for (auto l : p.mainFrame()->findAllElements("a")) {
                    //cout << l.attribute("href").toStdString() << endl;

                    lista.push_back(l.attribute("href").toStdString());


                }
                //cout<<lista.front();
                //cout<<lista.size();

                for (int i = 0; i < lista.size(); i++) {

                    cout << lista.at(i) << endl;

                }
                cout<<lista.size();

                //cout << "teste" << p.mainFrame()->toHtml().toStdString() << "\n";
                fflush(stdout);
                //proxima();

            });

            //proxima();



            //p.mainFrame()->findAllElements("a");

            return app.exec();
        }



}

int main2() {



    vector<string> listaUrls;


    //listaUrls.push_back("http://portal.fei.edu.br/pt-br/paginas/home.aspx");
    string raizSite = "https://pt.wikipedia.org/wiki/Radioatividade";
    listaUrls.push_back(raizSite);


    while( !listaUrls.empty() ) {
        string resultado = getHTML(listaUrls.front().c_str());
        listaUrls.erase(listaUrls.begin());

        QString raiz = "https://pt.wikipedia.org/wiki/Radioatividade";


        QString array(resultado.c_str());

        

        QDomDocument d("doc");


        if (!d.setContent(array)) {
            cout << "Erro de parsing" << endl;

        }

        QDomNodeList nodes = d.elementsByTagName("a");
        for (int i = 0; i < nodes.count(); i++) {
            QDomNode elm = nodes.at(i);
            if (elm.isElement()) {
                QString url = elm.toElement().attribute("href");


                if(url.startsWith("/") && !url.startsWith("//")){
                    url = raiz + url;
                }


                listaUrls.push_back(url.toStdString());
                cout <<i<<" "<< url.toStdString()<<endl;

            }

        }
        cout<<"Itens do vetor" <<listaUrls.size()<<endl;



    }

}
