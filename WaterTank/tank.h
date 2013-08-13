/*****************************************************************************/
/*  water_tank.h - plugin example for LibreCAD                                   */
/*                                                                           */
/*  Copyright (C) 2011 Rallaz, rallazz@gmail.com                             */
/*                                                                           */
/*  This library is free software, licensed under the terms of the GNU       */
/*  General Public License as published by the Free Software Foundation,     */
/*  either version 2 of the License, or (at your option) any later version.  */
/*  You should have received a copy of the GNU General Public License        */
/*  along with this program.  If not, see <http://www.gnu.org/licenses/>.    */
/*****************************************************************************/

#ifndef SAMPLE_H
#define SAMPLE_H

#include "qc_plugininterface.h"
#include <QDialog>
class QLineEdit;

class LC_Sample : public QObject, QC_PluginInterface
{
    Q_OBJECT
     Q_INTERFACES(QC_PluginInterface)
#if QT_VERSION >= 0x050000
     Q_PLUGIN_METADATA(IID "org.librecad.water_tank" FILE  "water_tank.json")
#endif

 public:
    virtual PluginCapabilities getCapabilities() const;
    virtual QString name() const;
    virtual void execComm(Document_Interface *doc,
                                       QWidget *parent, QString cmd);
};

class lc_Sampledlg : public QDialog
{
    Q_OBJECT

public:
    explicit lc_Sampledlg(QWidget *parent = 0);
    ~lc_Sampledlg();

public slots:
//    void procesAction(QStringList *commandList);
    void procesAction(Document_Interface *doc);
    void checkAccept();

protected:
    void closeEvent(QCloseEvent *event);

private:
    void readSettings();
    void writeSettings();
    bool failGUI(QString *msg);

private:
    QString errmsg;
    QLineEdit *outerdai_fondslab;
    QLineEdit * innerdai_fondslab;
    QLineEdit *ttldpth_fondslab;
    QLineEdit *fondringbeam_dept;
    QLineEdit *outerdai_ringbeam;
    QLineEdit * size_column;
    QLineEdit *ground_lvl;
    QLineEdit *stag_height;
    QLineEdit *gal_width;
    QLineEdit *gal_thick;
    QLineEdit *rise_botmdome;
    QLineEdit *width_botmdome;
    QLineEdit *D_botmbeam;
    QLineEdit *tank_height;
    QLineEdit *thick_botm ;
    QLineEdit *thick_top ;
    QLineEdit *top_b;
    QLineEdit *top_D ;
    QLineEdit *rise_topdome;
    QLineEdit *thick_topdome ;
    QLineEdit * thick_parapet;
    QLineEdit *height_parapet;
    QLineEdit *depth_pcc;
    QLineEdit * noofcolumn;
};

#endif // SAMPLE_H
