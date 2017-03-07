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

int main() {



    vector<string> listaUrls;


    //listaUrls.push_back("http://portal.fei.edu.br/pt-br/paginas/home.aspx");
    string raizSite = "https://pt.wikipedia.org/wiki/Radioatividade";
    listaUrls.push_back(raizSite);


    while( !listaUrls.empty() ) {
        string resultado = getHTML(listaUrls.front().c_str());
        listaUrls.erase(listaUrls.begin());

        QString raiz = "https://pt.wikipedia.org/wiki/Radioatividade";


        QString array(resultado.c_str());

        //QWebFrame::setHtml(array,QUrl(raiz.c_str()));

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
