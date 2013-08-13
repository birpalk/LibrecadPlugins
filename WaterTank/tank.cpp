/*****************************************************************************/
/*  water_tank.cpp - plugin for LibreCAD                                 */
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
#include <math.h>
#include "document_interface.h"
#include "tank.h"

QString LC_Sample::name() const
 {
     return (tr("Sample plugin"));
 }

PluginCapabilities LC_Sample::getCapabilities() const
{
    PluginCapabilities pluginCapabilities;
    pluginCapabilities.menuEntryPoints
            << PluginMenuLocation("Help", tr(" tank"));/**< here write the name which you want to display in the help toolbar*/
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
/*!
 ...This function provides the window for user to give input...
*/
lc_Sampledlg::lc_Sampledlg(QWidget *parent) :  QDialog(parent)
{
    setWindowTitle(tr("water tank details")); /**< Title of the main window */
    QLabel *label;

    QDoubleValidator *val = new QDoubleValidator(0);
    QGridLayout *mainLayout = new QGridLayout;

    label = new QLabel(tr("outerdia foundation slab:"));
    mainLayout->addWidget(label, 0, 0);/**< space in the window where to show the "outerdia foundation slab" */
    outerdai_fondslab = new QLineEdit();
    outerdai_fondslab->setValidator(val);
    mainLayout->addWidget(outerdai_fondslab, 0, 1);/**< space in window where user will enter the value for "outerdai foundation slab */


    label = new QLabel(tr("innerdia foundation slab:"));
    mainLayout->addWidget(label, 0, 2);
    innerdai_fondslab = new QLineEdit();
      innerdai_fondslab->setValidator(val);
    mainLayout->addWidget(innerdai_fondslab,0, 3);

    label = new QLabel(tr("total depth of foundation slab:"));
    mainLayout->addWidget(label, 1, 0);
    ttldpth_fondslab = new QLineEdit();
     ttldpth_fondslab->setValidator(val);
    mainLayout->addWidget( ttldpth_fondslab,1 , 1);

    label = new QLabel(tr("foundation ringbeam depth:"));
    mainLayout->addWidget(label, 1, 2);
   fondringbeam_dept = new QLineEdit();
    fondringbeam_dept ->setValidator(val);
    mainLayout->addWidget(   fondringbeam_dept, 1, 3);

    label = new QLabel(tr("outerdia ring beam:"));
    mainLayout->addWidget(label, 2, 0);
   outerdai_ringbeam= new QLineEdit();
    outerdai_ringbeam->setValidator(val);
    mainLayout->addWidget( outerdai_ringbeam, 2, 1);


    label = new QLabel(tr("size of column:"));
    mainLayout->addWidget(label, 2, 2);
   size_column = new QLineEdit();
    size_column ->setValidator(val);
    mainLayout->addWidget(    size_column, 2, 3);

    label = new QLabel(tr("ground level:"));
    mainLayout->addWidget(label, 3, 0);
   ground_lvl = new QLineEdit();
     ground_lvl->setValidator(val);
    mainLayout->addWidget(   ground_lvl, 3, 1);


    label = new QLabel(tr("staging height:"));
    mainLayout->addWidget(label, 3, 2);
  stag_height = new QLineEdit();
      stag_height->setValidator(val);
    mainLayout->addWidget(   stag_height, 3, 3);


    label = new QLabel(tr("width of gallary:"));
    mainLayout->addWidget(label, 4, 0);
    gal_width = new QLineEdit();
    gal_width->setValidator(val);
    mainLayout->addWidget(   gal_width, 4, 1);



    label = new QLabel(tr("thickness of gallary:"));
    mainLayout->addWidget(label, 4, 2);
    gal_thick = new QLineEdit();
    gal_thick->setValidator(val);
    mainLayout->addWidget(   gal_thick, 4, 3);

    label = new QLabel(tr("rise of bottom dome:"));
   mainLayout->addWidget(label, 5, 0);
    rise_botmdome= new QLineEdit();
    rise_botmdome->setValidator(val);
    mainLayout->addWidget(rise_botmdome, 5, 1);


    label = new QLabel(tr("width of bottom dome:"));
    mainLayout->addWidget(label, 5, 2);
    width_botmdome= new QLineEdit();
    width_botmdome->setValidator(val);
    mainLayout->addWidget(width_botmdome, 5, 3);


    label = new QLabel(tr(" bottom dome D:"));
    mainLayout->addWidget(label, 6, 0);
    D_botmbeam= new QLineEdit();
    D_botmbeam->setValidator(val);
    mainLayout->addWidget(D_botmbeam, 6, 1);
    
    
    label = new QLabel(tr("height of tank:"));
    mainLayout->addWidget(label, 6, 2);
    tank_height= new QLineEdit();
    tank_height->setValidator(val);
    mainLayout->addWidget(   tank_height, 6, 3);
    

    label = new QLabel(tr("thickness of tank at botm:"));
    mainLayout->addWidget(label, 7, 0);
    thick_botm = new QLineEdit();
    thick_botm ->setValidator(val);
    mainLayout->addWidget( thick_botm , 7, 1);


    label = new QLabel(tr("thickness of tank at top:"));
    mainLayout->addWidget(label, 7, 2);
    thick_top = new QLineEdit();
    thick_top ->setValidator(val);
    mainLayout->addWidget( thick_top , 7, 3);


    label = new QLabel(tr("top beam b:"));
    mainLayout->addWidget(label, 8, 0);
    top_b = new QLineEdit();
     top_b ->setValidator(val);
    mainLayout->addWidget( top_b  , 8, 1);


    label = new QLabel(tr("top beam D:"));
    mainLayout->addWidget(label, 8, 2);
    top_D = new QLineEdit();
     top_D ->setValidator(val);
    mainLayout->addWidget( top_D  , 8, 3);


    label = new QLabel(tr("rise of top dome:"));
    mainLayout->addWidget(label, 9, 0);
    rise_topdome = new QLineEdit();
    rise_topdome ->setValidator(val);
    mainLayout->addWidget(  rise_topdome , 9, 1);


    label = new QLabel(tr("thickness of top dome:"));
    mainLayout->addWidget(label, 9, 2);
    thick_topdome = new QLineEdit();
    thick_topdome ->setValidator(val);
    mainLayout->addWidget( thick_topdome , 9, 3);


    label = new QLabel(tr("thickness of parapet wall:"));
    mainLayout->addWidget(label, 10, 0);
    thick_parapet = new QLineEdit();
    thick_parapet ->setValidator(val);
    mainLayout->addWidget( thick_parapet , 10, 1);


    label = new QLabel(tr("height of parapet wall:"));
    mainLayout->addWidget(label, 10, 2);
   height_parapet = new QLineEdit();
     height_parapet ->setValidator(val);
    mainLayout->addWidget(   height_parapet , 10, 3);


    label = new QLabel(tr("depth of pcc:"));
    mainLayout->addWidget(label, 11, 0);
   depth_pcc = new QLineEdit();
      depth_pcc ->setValidator(val);
    mainLayout->addWidget(depth_pcc , 11, 1);

    label = new QLabel(tr("no.of columns"));
    mainLayout->addWidget(label, 11, 2);
   noofcolumn = new QLineEdit();
      noofcolumn ->setValidator(val);
    mainLayout->addWidget(noofcolumn ,11, 3);





    /*!
     ... two pushbuttons are provided to the user i.e accept and cancel ...
    */


    QHBoxLayout *loaccept = new QHBoxLayout;
    QPushButton *acceptbut = new QPushButton(tr("Accept"));
    loaccept->addStretch();
    loaccept->addWidget(acceptbut);
    mainLayout->addLayout(loaccept, 12, 1);

    QPushButton *cancelbut = new QPushButton(tr("Cancel"));
    QHBoxLayout *locancel = new QHBoxLayout;
    locancel->addWidget(cancelbut);
    locancel->addStretch();
    mainLayout->addLayout(locancel, 12, 2);

    setLayout(mainLayout);
    readSettings();

    connect(cancelbut, SIGNAL(clicked()), this, SLOT(reject()));
    connect(acceptbut, SIGNAL(clicked()), this, SLOT(checkAccept()));
}

/*!
 ... this function will display an error message if you leave any input field unfilled ...
*/
bool lc_Sampledlg::failGUI(QString *msg)
{
    if ( outerdai_fondslab->text().isEmpty()) {msg->insert(0, tr("Start X is empty")); return true;}

    return false;
}
/*!
 ... This is the main processing function where all calculations will take place ...
*/

void lc_Sampledlg::procesAction(Document_Interface *doc)
{
    Q_UNUSED(doc);

 double   outerdiafondslab, /**< variable for outer diameter of foundation slab */
         outerdiaringbeam,/**< variable for outer diameter of foundation ring beam */
         sizecolumn,/**< variable for size of column*/
         ttldpthfondslab,/**< variable for total depth of the foundation slab */
         fondringbeamdept,/**< variable for ofoundation beam ring depth*/
         groundlevel,/**< variable for ground level*/
         stagheight,/**< variable for stagging height */
         innerdaifondslab,/**< variable for inner diameter of foundation slab */
         galwidth,/**< variable for width of gllery */
         galthickness,/**< variable for thickness of gallery */
         risebotmdome,/**< variable for rise of bottom dome */
         widthbotmdome ,/**< variable for width of bottom dome*/
         d,/**< variable for depth of bottom beam */
         heighttank,/**< variable for height of water tank*/
         thickbotm,/**< variable for thickness of vertical wall of water tank at bottom*/
         thicktop,/**< variable for thickness of vertical wall at top */
         b1,/**< variable for width of top beam */
         d1,/**< variable for depth of top beam */
         risetopdome,/**< variable for rise of top dome */
         widthtopdome,/**< variable for width of top dome */
         thickparapet,/**< variable for thickness of the parapet wall */
         heightparapet,/**< variable for height of parapet wall */
         depthpcc,/**< variable for depth of pcc*/
         noofcolumns;/**< variable for no. of columns */


   outerdiafondslab= outerdai_fondslab ->text().toDouble();
   innerdaifondslab = innerdai_fondslab ->text().toDouble();
   ttldpthfondslab=   ttldpth_fondslab->text().toDouble();
   fondringbeamdept=   fondringbeam_dept->text().toDouble();
   outerdiaringbeam= outerdai_ringbeam ->text().toDouble();
   sizecolumn=   size_column->text().toDouble();
   groundlevel=    ground_lvl->text().toDouble();
   stagheight = stag_height ->text().toDouble();
   galwidth = gal_width ->text().toDouble();
   galthickness = gal_thick ->text().toDouble();
   risebotmdome =  rise_botmdome ->text().toDouble();
   widthbotmdome = width_botmdome->text().toDouble();
   d = D_botmbeam ->text().toDouble();
   heighttank =  tank_height ->text().toDouble();
   thickbotm = thick_botm ->text().toDouble();
   thicktop = thick_top ->text().toDouble();
   b1 = top_b->text().toDouble();
   d1 = top_D->text().toDouble();
   risetopdome = rise_topdome ->text().toDouble();
   widthtopdome= thick_topdome ->text().toDouble();
   thickparapet = thick_parapet->text().toDouble();
   heightparapet = height_parapet->text().toDouble();
   depthpcc = depth_pcc->text().toDouble();
   noofcolumns = noofcolumn->text().toDouble();



   /**********************************************
    *  foundation slab
    ***********************************************/
   QPointF coorda(0.0,0.0),/**< these are the coordinates which stores two values in them i.e x and y and QPointF is their datatype */
           coordb(0.0,ttldpthfondslab),
               coordc( outerdiafondslab,+ttldpthfondslab),
               coordd( outerdiafondslab,0.0);
    doc->addLine(&coorda, &coordb);/**< with the help of doc pointer addline() is called. */
    doc->addLine(&coordb, &coordc);
    doc->addLine(&coordc, &coordd);
    doc->addLine(&coordd, &coorda);

    /**********************************************
     *  pcc
     ***********************************************/

    QPointF coorda1(0.0,-depthpcc),coordd1(0.0,-depthpcc);
    coorda1 +=coorda,coordd1 +=coordd;
    doc->addLine(&coorda,&coorda1);
    doc->addLine(&coordd, &coordd1);
    doc->addLine(&coorda1, &coordd1);
    /**********************************************
     *  foundation beam
     * diff1 is the calculated to set the fondation ring beam on the foundation slab.
     * diff2 is calcuted to get the height of foundation ring slab.
     *footing is calcutaed by innerdaifondslab from outerdiafondslab.
     *plinth value is taken as 50.
     *All the coordinates are basically drived from the coorda, coordb,coordc, coordd.
     ***********************************************/

    double diff1=outerdiafondslab-outerdiaringbeam, diff2= fondringbeamdept-ttldpthfondslab,
           footing= (outerdiafondslab-innerdaifondslab)/2, plinth=(footing-sizecolumn-50)/2;

   QPointF coorde(plinth,0.0), coordr1(0.0,diff2/2),coordr2(sizecolumn+50,0.0),coordr3(sizecolumn+50,0.0),
           coordh(-plinth,0.0),coordr6(0.0,diff2/2),coordr4(-(sizecolumn+50),0.0),coordr5(-sizecolumn-50,0.0),
           f1(footing,0.0),f2(footing,0.0),f3(-footing,0.0),f4(-footing,0.0);

   f1 +=coorda,f2 +=coordb,f3 +=coordc,f4 +=coordd;
   doc->addLine(&f1,&f2);
   doc->addLine(&f3, &f4);
       coorde +=coordb;
       coordr1 +=coorde;
       coordr2 +=coordr1;
       coordr3 +=coorde;
       coordh +=coordc;
       coordr6 +=coordh;
       coordr4 +=coordr6;
       coordr5 +=coordh;


       doc->addLine(&coorde,&coordr1);
       doc->addLine(&coordr2, &coordr3);
       doc->addLine(&coordr4, &coordr5);
       doc->addLine(&coordr6,&coordh);
       doc->addLine(&coordr2, &coordr3);
       doc->addLine(&coordr1, &coordr6);




       /**********************************************
        * gound level
        ***********************************************/
   QPointF g1(-1000,groundlevel), g2(outerdiafondslab+2000,groundlevel);
     doc->addLine(&g1, &g2);
     /**********************************************
      *  column and bottom beam
      ***********************************************/

     double angle=360;
     QPointF coordf(25,0.0),coordg(-25,0.0), coordi(0.0,stagheight+groundlevel),
             coordk(sizecolumn,0.0),coordj(sizecolumn,0.0),
             coordl(0.0,stagheight+groundlevel),
             coordm(-sizecolumn,0.0),coordn(0.0,stagheight+groundlevel),
             coordo(0.0,-d),coordp(0.0,-d),
             circum_pt, circum_1;


   coordf +=coordr1;
   coordg +=coordr6;
   coordi +=coordf;
   coordk +=coordi;
   coordj +=coordf;
   coordl +=coordg;
   coordm +=coordg;
   coordn +=coordm;
   coordo +=coordi;
   coordp +=coordl;

   doc->addLine(&coordi, &coordf);//firstcolumn
   doc->addLine(&coordl, &coordg);//lastcolumn



   doc->addLine(&coordo, &coordp);

   int ds= angle/noofcolumns;

   {QPointF mid(outerdiaringbeam/2,1000);
       mid +=coordi;
      for (int i=0; i!=angle; i = i + ds )/**< loop for making columns */
      {
        //  circum_1.setY(mid.ry()+(outerdiaringbeam/2)*cos(i*.017455));
         circum_1.setX(mid.rx()+(outerdiaringbeam/2-sizecolumn/2)*sin(i*.017455));


          for (int j=90; j<angle; j= j+180)
          {
               circum_pt.setY(coordo.ry());
              circum_pt.setX(circum_1.rx() + sizecolumn/2*sin(j*0.017455));
              coordf.setX(circum_1.rx() + sizecolumn/2*sin(j*0.017455));
              doc->addLine (&circum_pt,&coordf);
            }


}
      /**********************************************
       * gallery
       ***********************************************/

      QPointF coordg1(-galwidth,0.0),coordg2(0.0,-galthickness),coordg3(0.0,-galthickness),
              coordg4(galwidth,0.0),coordg5(0.0,-galthickness),coordg6(0.0,-galthickness);
      coordg1 +=coordi;
      coordg2 +=coordg1;
      coordg3 +=coordi;
      coordg4 +=coordl;
      coordg5 +=coordg4;
      coordg6 +=coordl;

      doc->addLine(&coordi, &coordg1);
      doc->addLine(&coordg1, &coordg2);
      doc->addLine(&coordg2, &coordg3);
      doc->addLine(&coordi, &coordg3);
      doc->addLine(&coordl, &coordg4);
      doc->addLine(&coordg4, &coordg5);
      doc->addLine(&coordg5, &coordg6);
      doc->addLine(&coordg6, &coordl);




      /**********************************************
       * bottom dome and beam
       ***********************************************/

  double length=outerdiaringbeam-2*sizecolumn,
          radiusbotmdome=0.5*((length*length/(4*risebotmdome))+risebotmdome),/**< radius for bottom dome outer arc */
         radiusbotmdome1=0.5*((length*length/(4*risebotmdome-widthbotmdome))+risebotmdome-widthbotmdome),/**< radius for bottom dome inner arc */
          $=(radiusbotmdome-risebotmdome)/radiusbotmdome,
         $1=(radiusbotmdome1-(risebotmdome+.75*widthbotmdome))/radiusbotmdome1;
        qreal  angle1=(180/3.14)*asin($),angle2=180-((180/3.14)*asin($)),/**< angle  for bottom dome outer arc of datatype qreal */
                angle3=(180/3.14)*asin($),angle4=180-((180/3.14)*asin($));/**< angle for bottom dome inner arc */

  QPointF start;
  start.setX(coordi.rx()+outerdiaringbeam/2);
   start.setY(coordi.ry()-radiusbotmdome+risebotmdome);

   doc->addArc(&start,radiusbotmdome-widthbotmdome,angle3,angle4);
    doc->addArc(&start,radiusbotmdome,angle1,angle2);/**< an arc is added from start coordinate, having radius radiusbotmdome and angles as angle1 and angle2*/
    QPointF coordd1(0.0,-1.25*widthbotmdome),coordd2(1.5*widthbotmdome,0.0),coordd3(-1.25*widthbotmdome,0.0),coordd4(0.0,-1.25*widthbotmdome);
            coordd1 +=coordk,coordd2 +=coordk,coordd3 +=coordn,coordd4 +=coordn;

            doc->addLine(&coordj, &coordd1);
            doc->addLine(&coordd2, &coordd3);
            doc->addLine(&coordd4, &coordm);
            doc->addLine(&coordd4, &coordd1);



            /**********************************************
             * vertical wall
             ***********************************************/

    QPointF coordq(0.0,heighttank),coordr(thickbotm,0.0),coords(thicktop,-d1),
            coordt(0.0,heighttank),coordu(-thickbotm,0.0),coordv(-thicktop,-d1),
            coordw(b1-thicktop,0.0),coordx(-b1+thicktop,0.0),
            coordy(0.0,d1),coordz(0.0,d1);
             coordq +=coordi;
             coordr +=coordi;
             coords +=coordq;
             coordt +=coordl;
             coordu +=coordl;
             coordv +=coordt;
             coordw +=coords;
             coordx +=coordv;
             coordy +=coordw;
             coordz +=coordx;

             doc->addLine(&coordr, &coordk);
             doc->addLine(&coordu, &coordn);
             doc->addLine(&coordi, &coordq);/**< left wall*/
             doc->addLine(&coordr, &coords);
             doc->addLine(&coords, &coordw);
             doc->addLine(&coordw, &coordy);
             doc->addLine(&coordt, &coordl);/**< right wall*/
             doc->addLine(&coordu, &coordv);
             doc->addLine(&coordv, &coordx);
             doc->addLine(&coordx, &coordz);


             /**********************************************
              * top beam
              ***********************************************/

             double  length1=outerdiaringbeam-2*thicktop,length2=outerdiaringbeam-2*thickparapet,
                     radiustopdome=0.5*((length1*length1)/(4*risetopdome)+risebotmdome),
                    // radiustopdome1=0.5*((length2*length2)/(4*risetopdome+widthtopdome)+risetopdome+widthtopdome),
                     $2=(radiustopdome-risetopdome)/radiustopdome,$3=(radiustopdome-risetopdome)/radiustopdome;

                     qreal  angle5=(180/3.14)*asin($2),angle6=180-((180/3.14)*asin($2)),
                             angle7=(180/3.14)*asin($3),angle8=180-((180/3.14)*asin($3));


             start.setY(coordq.ry()-radiustopdome+risetopdome);
             start.setX(coordi.rx()+outerdiaringbeam/2);
              doc->addArc(&start,radiustopdome,angle5,angle6);

              //start.setY(coordq.ry()-radiustopdome1+risetopdome+widthtopdome);
              //start.setX(coordi.rx()+length2/2);
              doc->addArc(&start,radiustopdome+widthtopdome,angle7,angle8);



              /**********************************************
               * parapet wall
               ***********************************************/

              QPointF coordp1(0.0,heightparapet),coordp2(thickparapet,0.0),
                      coordp3(0.0,heightparapet),coordp4(-thickparapet,0.0),
                      coordp5(0.0,-heightparapet+widthtopdome),coordp6(0.0,-heightparapet+widthtopdome);
              coordp1 +=coordq;
              coordp2 +=coordp1;
              coordp3 +=coordt;
              coordp4 +=coordp3;
              coordp5 +=coordp2;
              coordp6 +=coordp4;

              doc->addLine(&coordp1, &coordq);
              doc->addLine(&coordp1, &coordp2);
              doc->addLine(&coordp3, &coordp4);
              doc->addLine(&coordp3, &coordt);

              doc->addLine(&coordp2, &coordp5);
              doc->addLine(&coordp6, &coordp4);

}
}
/*!
 ... this function will check weather user have select accept or cancle button on the input window   ...
*/
void lc_Sampledlg::checkAccept()
{

    errmsg.clear();
    if (failGUI(&errmsg)) {
        QMessageBox::critical ( this, "tank", errmsg );
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

/*!
 ... Function for read settings ...
*/
void lc_Sampledlg::readSettings()
 {
    QString str;
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "LibreCAD", "water_tank_plugin");
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(430,140)).toSize();

   outerdai_fondslab ->setText( settings.value("outerdia foundation slab", 11000).toString() );
   innerdai_fondslab->setText( settings.value("innerdia foundation slab", 5360).toString() );
   ttldpth_fondslab->setText( settings.value("total depth of foundation slab", 350).toString() );
   fondringbeam_dept->setText( settings.value("foundation ringbeam depth",900).toString() );
   outerdai_ringbeam ->setText( settings.value("outerdai ring beam",8630 ).toString() );
   size_column->setText( settings.value("size of column", 450).toString() );
   ground_lvl->setText( settings.value("ground level",1800).toString() );
   stag_height->setText( settings.value("staging height",25500).toString() );
   gal_width ->setText( settings.value("width of gallary",900 ).toString() );
   gal_thick->setText( settings.value("thickness of gallary", 125).toString() );
    rise_botmdome->setText( settings.value("rise of botmdome", 1400).toString() );
   width_botmdome->setText( settings.value("width of botmdome",175).toString() );
   D_botmbeam->setText( settings.value(" bottom dome D",900).toString() );
   tank_height->setText( settings.value("height of tank",6100).toString() );
   thick_botm ->setText( settings.value("thickness of tank at botm", 230).toString() );
   thick_top ->setText( settings.value("thickness of tank at top",120 ).toString() );
   top_b->setText( settings.value("top beam b", 150).toString() );
   top_D->setText( settings.value("top beam D", 260).toString() );
   rise_topdome->setText( settings.value("risr of topdome",1500).toString() );
   thick_topdome->setText( settings.value("thickness of topdome",125).toString() );
   thick_parapet->setText( settings.value("thickness of parapet wall",75).toString() );
   height_parapet->setText( settings.value("height of parapet wall",900).toString() );
   depth_pcc->setText( settings.value("thickness of topdome",150).toString() );
   noofcolumn->setText( settings.value("no of column",8).toString() );

    resize(size);
    move(pos);
 }
/*!
 ... function for write setttings ...
*/
void lc_Sampledlg::writeSettings()
 {
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "LibreCAD", "water_tank_plugin");
    settings.setValue("pos", pos());
    settings.setValue("size", size());

    settings.setValue("outerdia foundation slab", outerdai_fondslab ->text());
    settings.setValue("innerdia foundation slab",innerdai_fondslab->text());
    settings.setValue("total depth of foundation slab ", ttldpth_fondslab->text());
    settings.setValue("foundation ringbeam depth",   fondringbeam_dept->text());
    settings.setValue("outerdia ring beam", outerdai_ringbeam ->text());
    settings.setValue("size of column", size_column->text());
    settings.setValue("ground level",  ground_lvl->text());
    settings.setValue("staging height",  stag_height->text());
    settings.setValue("width of gallary", gal_width ->text());
    settings.setValue("thickness of gallary", gal_thick ->text());
    settings.setValue("rise of botmdome", rise_botmdome->text());
    settings.setValue("width of botm beam ", width_botmdome->text());
    settings.setValue(" bottom dome D", D_botmbeam->text());
    settings.setValue("height of tank", tank_height->text());
    settings.setValue("thickness of tank at botm",thick_botm ->text());
    settings.setValue("thickness of tank at top", thick_top  ->text());
    settings.setValue("top beam b", top_b ->text());
    settings.setValue("top beam D", top_D->text());
    settings.setValue("rise of top dome ", rise_topdome->text());
    settings.setValue("thickness od top dome", thick_topdome->text());
    settings.setValue("height of parapet wall",  height_parapet->text());
    settings.setValue("thickness of parapet wall", thick_parapet->text());
    settings.setValue("depth of pcc", depth_pcc->text());
    settings.setValue("no.of columns",  noofcolumn->text());

 }



#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(lc_water_tank, LC_Sample);
#endif

