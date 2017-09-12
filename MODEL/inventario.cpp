#include "inventario.h"
#include <QFile>
#include<QMessageBox>
inventario::inventario()
{

}

// gestione file xml
void inventario::cleanfile() {
    QString artFilePath = ("../ProgettissimoP2/savedData/inventario.xml");
    QFile *artFile = new QFile(artFilePath);
    artFile->remove();
}

void inventario::saveArt() {

    xmlArtWriter = new QXmlStreamWriter();
    QString artFilePath = ("../ProgettissimoP2/savedData/inventario.xml");
    QFile *artFile = new QFile(artFilePath);
    if (!artFile->open(QIODevice::ReadWrite)) {
        QMessageBox::warning(0, "Error!", "Error saving file");
    }
    else {
        xmlArtWriter->setDevice(artFile);
        xmlArtWriter->setAutoFormatting(true);
        xmlArtWriter->writeStartDocument();

        xmlArtWriter->writeStartElement("Inventario");
        QMap<int,articolo>::iterator it;
        for(it=listainv.begin(); it!=listainv.end(); ++it) {

            xmlArtWriter->writeStartElement("Articolo");
            xmlArtWriter->writeTextElement("Codice",QString::number((*it).prod->getCodice()));
            xmlArtWriter->writeTextElement("Nome", (*it).prod->getNome());
            xmlArtWriter->writeTextElement("Marca", (*it).prod->getMarca());
            xmlArtWriter->writeTextElement("Prezzo",QString::number((*it).prod->getPrezzo()));
            xmlArtWriter->writeTextElement("Quantita", QString::number((*it).getQuantita()) );
            alimentare* A=dynamic_cast<alimentare*>(it->prod);
            if(A)
                xmlArtWriter->writeTextElement("Tipologia","Alimentare");
            else {
                bevanda* B=dynamic_cast<bevanda*>(it->prod);
                if(B)
                    xmlArtWriter->writeTextElement("Tipologia","Bevanda");
                else {
                    oggettistica* O=dynamic_cast<oggettistica*>(it->prod);
                    if(O)
                        xmlArtWriter->writeTextElement("Tipologia","Oggettistica");
                }
            }
            xmlArtWriter->writeEndElement();
        }
        //end document
        xmlArtWriter->writeEndDocument();
        artFile->close();
    }
    delete artFile;

}

void inventario::loadArt() {
    xmlArtReader = new QXmlStreamReader();
    QString filePath("../ProgettissimoP2/savedData/inventario.xml");
    QFile *file = new QFile(filePath);
    if (!file->open(QIODevice::ReadOnly | QFile::Text)) {
    }
    else {
        xmlArtReader->setDevice(file);
        xmlArtReader->readNext();
        QString nom, mar, tipo;
        int cod, quant;
        float prez;
        bool x=false;
        while(!xmlArtReader->atEnd()) { //leggi fino alla fine del documento
            if(xmlArtReader->isStartElement()) {
                if(xmlArtReader->name() == "Inventario") {
                    xmlArtReader->readNext();
                }
                if(xmlArtReader->name() == "Articolo") {
                    xmlArtReader->readNext();
                }
                if(xmlArtReader->name() == "Codice") { cod = xmlArtReader->readElementText().toInt();}
                if(xmlArtReader->name() == "Nome") { nom= xmlArtReader->readElementText();}
                if(xmlArtReader->name() == "Marca") { mar = xmlArtReader->readElementText();}
                if(xmlArtReader->name() == "Prezzo") { prez = xmlArtReader->readElementText().toFloat();}
                if(xmlArtReader->name() == "Quantita") {quant=xmlArtReader->readElementText().toInt();}
                if(xmlArtReader->name() == "Tipologia") {
                    tipo=xmlArtReader->readElementText();
                    x=true;
                }
                if(x) {
                    if(tipo=="Alimentare") {
                        alimentare* p=new alimentare(cod, nom, mar,prez);
                        articolo art(p,quant);
                        listainv.insert(cod,art);
                    }
                    else if(tipo=="Bevanda") {
                        bevanda* p=new bevanda(cod, nom, mar,prez);
                        articolo art(p,quant);
                        listainv.insert(cod,art);
                    }
                    else if(tipo=="Oggettistica") {
                        oggettistica* p=new oggettistica(cod, nom, mar,prez);
                        articolo art(p,quant);
                        listainv.insert(cod,art);
                    }
                    x=false;
                }
            }
            xmlArtReader->readNext();
        }
    }
}
