/*****************************************************************************/
/*  sample.cpp - plugin example for LibreCAD                                 */
/*                                                                           */
/*  Copyright (C) 2011 Rallaz, rallazz@gmail.com                             */
/*                                                                           */
/*  This library is free software, licensed under the terms of the GNU       */
/*  General Public License as published by the Free Software Foundation,     */
/*  either version 2 of the License, or (at your option) any later version.  */
/*  You should have received a copy of the GNU General Public License        */
/*  along with this program.  If not, see <http://www.gnu.org/licenses/>.    */
/*****************************************************************************/

#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QSettings>
#include <QMessageBox>
#include <QDoubleValidator>
#include <QColor>
#include "document_interface.h"
#include "sample.h"

QString LC_Sample::name() const
 {
     return (tr("views"));
 }

PluginCapabilities LC_Sample::getCapabilities() const
{
    PluginCapabilities pluginCapabilities;
    pluginCapabilities.menuEntryPoints
            << PluginMenuLocation("Help", tr("views"));
    return pluginCapabilities;
}

void LC_Sample::execComm(Document_Interface *doc,
                             QWidget *parent, QString cmd)
{
    Q_UNUSED(doc);
    Q_UNUSED(cmd);
    lc_Sampledlg pdt(parent);
    int result =  pdt.exec();
    if (result == QDialog::Accepted)
        pdt.procesAction(doc);
}




/*****************************/
lc_Sampledlg::lc_Sampledlg(QWidget *parent) :  QDialog(parent)
{
    setWindowTitle(tr("Draw line"));
    QLabel *label;

    QDoubleValidator *val = new QDoubleValidator(0);
    QGridLayout *mainLayout = new QGridLayout;

         label = new QLabel(tr("x Coordinate"));
         mainLayout->addWidget(label, 0, 0);
         startxedit = new QLineEdit();
         startxedit->setValidator(val);
         mainLayout->addWidget(startxedit, 0, 1);

         label = new QLabel(tr("y Coordinate"));
         mainLayout->addWidget(label, 0, 2);
         startyedit = new QLineEdit();
         startyedit->setValidator(val);
         mainLayout->addWidget(startyedit, 0, 3);


         label = new QLabel(tr("Length:"));
         mainLayout->addWidget(label, 1, 0);
         lengthedit = new QLineEdit();
         lengthedit->setValidator(val);
         mainLayout->addWidget(lengthedit, 1, 1);

        label = new QLabel(tr("Height:"));
        mainLayout->addWidget(label, 1,2);
        heightedit = new QLineEdit();
        heightedit->setValidator(val);
        mainLayout->addWidget(heightedit, 1, 3);

        label = new QLabel(tr("Width:"));
        mainLayout->addWidget(label, 2, 0);
        widthedit = new QLineEdit();
        widthedit->setValidator(val);
        mainLayout->addWidget(widthedit, 2, 1);


        label = new QLabel(tr("Cylinder Height:"));
        mainLayout->addWidget(label, 2, 2);
        cycheight = new QLineEdit();
        cycheight->setValidator(val);
        mainLayout->addWidget(cycheight,2, 3);

        label = new QLabel(tr("Cylinder Radius:"));
        mainLayout->addWidget(label, 3, 0);
        cycradius = new QLineEdit();
        cycradius->setValidator(val);
        mainLayout->addWidget(cycradius, 3, 1);

        label = new QLabel(tr("Space btw views"));
        mainLayout->addWidget(label, 3, 2);
        spaceedit = new QLineEdit();
        spaceedit->setValidator(val);
        mainLayout->addWidget(spaceedit, 3, 3);

     label = new QLabel(tr("top view:"));
        mainLayout->addWidget(label, 4, 0);


        label = new QLabel(tr("layer name"));
        mainLayout->addWidget(label, 5, 0);
        layerdata1 = new QLineEdit();
        mainLayout->addWidget(layerdata1, 5, 1);

       label = new QLabel(tr("color"));
       colordat1 = new QComboBox();
       QStringList txtformats;
       txtformats<< tr("red") << tr("blue") << tr("green");
       colordat1->addItems(txtformats);

   	 mainLayout->addWidget(label,5,2);
     mainLayout->addWidget(colordat1,5,3);


    label = new QLabel(tr("front view:"));
        mainLayout->addWidget(label, 6, 0);


        label = new QLabel(tr("layer name"));
        mainLayout->addWidget(label, 7, 0);
        layerdata2 = new QLineEdit();
        mainLayout->addWidget(layerdata2, 7, 1);

       label = new QLabel(tr("color"));
      colordat2= new QComboBox();
    colordat2->addItems(txtformats);
     mainLayout->addWidget(label,7,2);
     mainLayout->addWidget(colordat2,7,3);
    


    label = new QLabel(tr("side view:"));
        mainLayout->addWidget(label, 8, 0);


        label = new QLabel(tr("layer name"));
        mainLayout->addWidget(label, 9, 0);
        layerdata3 = new QLineEdit();
        mainLayout->addWidget(layerdata3, 9, 1);

       label = new QLabel(tr("color"));

       colordat3= new QComboBox();
    colordat3->addItems(txtformats);
    
       mainLayout->addWidget(label,9,2);
     mainLayout->addWidget(colordat3,9,3);

        QHBoxLayout *loaccept = new QHBoxLayout;
        QPushButton *acceptbut = new QPushButton(tr("Accept"));
        loaccept->addStretch();
        loaccept->addWidget(acceptbut);
        mainLayout->addLayout(loaccept, 10, 1);

        QPushButton *cancelbut = new QPushButton(tr("Cancel"));
        QHBoxLayout *locancel = new QHBoxLayout;
        locancel->addWidget(cancelbut);
        locancel->addStretch();
        mainLayout->addLayout(locancel, 10, 2);

        setLayout(mainLayout);
        readSettings();

        connect(cancelbut, SIGNAL(clicked()), this, SLOT(reject()));
        connect(acceptbut, SIGNAL(clicked()), this, SLOT(checkAccept()));
    }


    bool lc_Sampledlg::failGUI(QString *msg)
    {
        if (startxedit->text().isEmpty()) {msg->insert(0, tr("x coordinate field is empty")); return true;}
        if (startyedit->text().isEmpty()) {msg->insert(0, tr("y coordinate is empty")); return true;}
        if (lengthedit->text().isEmpty()) {msg->insert(0, tr("Length is empty")); return true;}
        if (widthedit->text().isEmpty()) {msg->insert(0, tr("Width is empty")); return true;}
        if (heightedit->text().isEmpty()) {msg->insert(0, tr("Height is empty")); return true;}
        if (cycheight->text().isEmpty()) {msg->insert(0, tr("Cylinder Height is empty")); return true;}
        if (cycradius->text().isEmpty()) {msg->insert(0, tr("Cylinder Radius is empty")); return true;}
        if (spaceedit->text().isEmpty()) {msg->insert(0, tr("Space field is empty")); return true;}
        if (layerdata1->text().isEmpty()) {msg->insert(0, tr("layer name")); return true;}
        if (layerdata2->text().isEmpty()) {msg->insert(0, tr("layer name")); return true;}
        if (layerdata3->text().isEmpty()) {msg->insert(0, tr("layer name")); return true;}

        return false;
    }

    void lc_Sampledlg::procesAction(Document_Interface *doc)

    {
        Q_UNUSED(doc);
       double leng, breadth,height,r,CH,x; // r=radius, CH=Cylinder Height, x=spacing
    QString l1name, l2name, l3name;

      l1name= layerdata1->text();
      l2name= layerdata2->text();
      l3name= layerdata3->text();


        leng= lengthedit->text().toDouble();
         breadth= widthedit->text().toDouble();
         height= heightedit->text().toDouble();
         r= cycradius->text().toDouble();
         CH= cycheight->text().toDouble();
         x=spaceedit->text().toDouble();

        QColor c,c1,c2;
        doc->setLayer(l1name);
        switch (colordat1->currentIndex()) {
        case 0:
            c= QColor(255, 0, 0, 127);

            break;
        case 1:
             c= QColor( 0, 0,255, 127);
             break;
        case 2:
             c= QColor(0,255, 0, 127);
            break;
        }


         doc-> setCurrentLayerProperties(c, DPI::Width08, DPI::SolidLine);

        topview(leng,breadth,r,doc);


         doc->setLayer(l2name);
        switch (colordat2->currentIndex()) {
         case 0:
        c1= QColor(255, 0, 0, 127);

             break;
         case 1:
         c1=QColor(0, 0,255, 127);
         break;
         case 2:
         c1=QColor(0, 255,0, 127);
         break;

         }

         doc->setCurrentLayerProperties(c1, DPI::Width08, DPI::SolidLine);

        frontview( x, breadth, height,leng,CH, r ,doc);

         doc->setLayer(l3name);
        switch (colordat3->currentIndex()) {
         case 0:
        c2= QColor(255, 0, 0, 127);

             break;
         case 1:
         c2=QColor(0,  225,0, 127);
         break;
         case 2:
         c2=QColor(0,0,225, 127);
         break;


         }
           doc->setCurrentLayerProperties(c2, DPI::Width08, DPI::SolidLine);




        sideview(x,breadth,height,r,leng,CH,doc);


    }



void lc_Sampledlg::checkAccept()
{

    errmsg.clear();
    if (failGUI(&errmsg)) {
        QMessageBox::critical ( this, "views", errmsg );
        errmsg.clear();
        return;
    }
    accept();
}


lc_Sampledlg::~lc_Sampledlg()
{
}
void lc_Sampledlg::closeEvent(QCloseEvent *event)
 {
    writeSettings();
    QWidget::closeEvent(event);
 }

void lc_Sampledlg::readSettings()
 {
    QString str;
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "LibreCAD", "views");
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(430,140)).toSize();

        startxedit->setText( settings.value("x coordinate", 0).toString() );
        startyedit->setText( settings.value("y coordinate", 0).toString() );
        lengthedit->setText( settings.value("Length", 0.0).toString() );
        widthedit->setText( settings.value(" Width", 0.0).toString() );
        heightedit->setText( settings.value("Height", 0.0).toString() );
        cycheight->setText( settings.value("Cylinder Height", 0.0).toString() );
        cycradius->setText( settings.value("Cylinder Radius", 0.0).toString() );
        spaceedit->setText( settings.value("Spacing between Views", 0.0).toString() );
         layerdata1->setText( settings.value("layer name", 0.0).toString() );
          layerdata2->setText( settings.value("layer name", 0.0).toString() );
           layerdata3->setText( settings.value("layer name", 0.0).toString() );
           //colordata1->setText(setting.value("color",red).tostring());
    resize(size);
    move(pos);
 }

void lc_Sampledlg::writeSettings()
 {
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "LibreCAD", "views");
    settings.setValue("pos", pos());
    settings.setValue("size", size());

        settings.setValue("Start x coordinate",  startxedit->text());
        settings.setValue("Start y coordinate",  startyedit->text());
        settings.setValue("Length",  lengthedit->text());
        settings.setValue("Width",  widthedit->text());
        settings.setValue("Height",heightedit->text());
        settings.setValue("Cylinder Height", cycheight->text());
        settings.setValue("Cylinder Radius", cycradius->text());
         settings.setValue("layer name", layerdata1->text());
          settings.setValue("layer name", layerdata2->text());
           settings.setValue("layer name", layerdata3->text());
             //settings.setValue("color", colordata1->text());
 }

void lc_Sampledlg::topview(double leng, double breadth, double r,Document_Interface *doc)
{
    QPointF Coord_a,Coord_b(0.0,0.0+breadth),Coord_c(leng,breadth),Coord_d(0.0+leng,0);// Top View= L*B  L=30,B=20
    Coord_a.setX(startxedit->text().toDouble());
    Coord_a.setY(startyedit->text().toDouble());
    Coord_b +=Coord_a;
    Coord_c +=Coord_a;
    Coord_d +=Coord_a;
    QPointF c_center(leng/2,breadth/2);
    c_center += Coord_a;

    doc->addLine(&Coord_a, &Coord_b); // coord_a to Coord_d -> for TOP view
    doc->addLine(&Coord_b, &Coord_c);
    doc->addLine(&Coord_c, &Coord_d);
    doc->addLine(&Coord_d, &Coord_a);
    doc-> addCircle(&c_center,r);


}
void lc_Sampledlg::frontview( double x,double breadth, double height,double leng, double CH,double r,Document_Interface *doc)
{

    QPointF Coord_a;
    Coord_a.setX(startxedit->text().toDouble());
    Coord_a.setY(startyedit->text().toDouble());
    QPointF Coord_e(0.0,x+breadth), Coord_f(0.0,height);//front view
    Coord_e += Coord_a, Coord_f+= Coord_e;
    QPointF Coord_g(leng,0.0), Coord_h(leng,0.0);
    Coord_g += Coord_f,Coord_h += Coord_e;

    QPointF mid1_l(leng/2-r,0.0), mid2_l(leng/2+r,0.0); //tank  front view
    mid1_l += Coord_f, mid2_l += Coord_f;

    QPointF ch1(0.0,CH), ch2(0.0,CH);
    ch1 += mid1_l, ch2 +=mid2_l;

    doc->addLine(&Coord_e, &Coord_f);//coord_e to coor_h for Front view
    doc->addLine(&Coord_f, &Coord_g );
    doc->addLine(&Coord_g, &Coord_h);
    doc->addLine(&Coord_h, & Coord_e);

    doc->addLine(&mid1_l,&ch1); // tank of front view
    doc->addLine(&mid2_l,&ch2);
    doc->addLine(&ch1,&ch2);


}

void lc_Sampledlg::sideview(double x,double breadth,double height,double r,double leng, double CH,Document_Interface *doc)
{    QPointF Coord_a;
     Coord_a.setX(startxedit->text().toDouble());
     Coord_a.setY(startyedit->text().toDouble());

      QPointF Coord_i(leng+x,x+breadth), Coord_j(0.0,height);//side view
      Coord_i += Coord_a, Coord_j+= Coord_i;
      QPointF Coord_k(breadth,0.0), Coord_l(breadth,0.0);

      Coord_k += Coord_j,Coord_l += Coord_i;
    QPointF mid3_b(breadth/2-r,0.0), mid4_b(breadth/2+r,0.0); //tank side view
    mid3_b += Coord_j, mid4_b += Coord_j;
    QPointF ch3(0.0,CH), ch4(0.0,CH);
    ch3 += mid3_b, ch4 +=mid4_b;

    doc->addLine(&Coord_i, &Coord_j); //Coord_i to Coord_l for side view
    doc->addLine(&Coord_j, &Coord_k);
    doc->addLine(&Coord_k, &Coord_l);
    doc->addLine(&Coord_i, &Coord_l);
   doc->addLine(&mid3_b, &ch3);// side view of tank
   doc->addLine(&mid4_b,&ch4);
   doc->addLine(&ch3, &ch4);

}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(lc_sample, LC_Sample);
#endif
