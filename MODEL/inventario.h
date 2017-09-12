#ifndef INVENTARIO_H
#define INVENTARIO_H

#include<QMap>
#include "articolo.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include "alimentare.h"
#include "bevanda.h"
#include "oggettistica.h"

class inventario
{
private:
    QXmlStreamWriter* xmlArtWriter;
    QXmlStreamReader* xmlArtReader;
public:
    QMap<int,articolo> listainv;

    inventario();

    void cleanfile();
    void saveArt();
    void loadArt();
};

#endif // INVENTARIO_H
