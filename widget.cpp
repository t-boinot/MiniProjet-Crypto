/* Projet ACF 2025 Groupe :
 *  Téo BOINOT
 * QUATTER Mael
 * Mattieu RENAUDEAU
 */

#include "widget.h"
#include "ui_widget.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QStringList>
#include <math.h>


//------------------------------------------------------------------------------------------------------------------
Widget::Widget(QWidget *parent) // Constructeur par défaut
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // fixer la taille de la fenetre
    setFixedSize(width(),height());

    //Griser les bouttons tant qu'aucun fichiers n'es ouvert dans l'IHM
    ui->pB_chiffrer->setEnabled(false);
    ui->pB_dechiffrer->setEnabled(false);
    ui->pB_sauv->setEnabled(false);

}

//------------------------------------------------------------------------------------------------------------------
Widget::~Widget() // Destructeur
{
    delete ui;
}

//------------------------------------------------------------------------------------------------------------------

void Widget::on_pB_ouvrir_clicked() // Bouton ouvrir qui permet d'aller chercher notre fichier
{
    // Ouvrir le fichier avec une boîte de dialogue
    QString cheminFichier = QFileDialog::getOpenFileName(this, tr("Choisissez un fichier..."), "");

    if (cheminFichier.isEmpty()) return;

    ui->ql_nomfich->setText(cheminFichier);

    // Infos sur le fichier
    QFileInfo infosFichier(cheminFichier);
    ui->ql_taille->setText(QString::number(infosFichier.size()));

    // Ouvrir le fichier
    QFile monFichier(cheminFichier);

    if (!monFichier.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir le fichier !");
        return;
    }

    // Lire et afficher le contenu
    contenu_initial = monFichier.readAll();

    ui->textB_initial->setPlainText(contenu_initial);

    //Fermer le fichier après avoir récupèrer les informations sur l'IHM
    monFichier.close();

    // Activer les boutons après ouverture du fichier
    ui->pB_chiffrer->setEnabled(true);
    ui->pB_dechiffrer->setEnabled(true);
    ui->pB_sauv->setEnabled(true);
}

//------------------------------------------------------------------------------------------------------------------

QByteArray Widget::inversion(QByteArray contenu)
{
    //Récupère la taille du fichiers
    int taille = contenu.size();

    //Divise par deux en récupèrant la moitie
    int moitie = taille/2;
    QByteArray partie1 = contenu.left(moitie);  //Récupère la moitie premier terme en commencent par la gauche
    QByteArray partie2 = contenu.mid(moitie);  //Récupère le reste des termes à partir du terme située à la moitie

    return partie2+partie1;
}

//------------------------------------------------------------------------------------------------------------------

QByteArray Widget::desinversion(QByteArray contenu)
{
    //Récupère la taille du fichiers
    int taille = contenu.size();

    //Divise par deux en récupèrant la moitie et le reste pour ensuite s'éparer en deux sans différencier si la taille est paire ou impair
    int moitie = taille/2;
    int reste = taille%2;
    QByteArray partie1 = contenu.left(moitie+reste);  //Récupère la moitie + reste premier terme en commencent par la gauche
    QByteArray partie2 = contenu.mid(moitie+reste);  //Récupère le reste des termes à partir du terme située à la moitie + reste

    return partie2+partie1;
}

//------------------------------------------------------------------------------------------------------------------

QByteArray Widget::chiffrement(const QByteArray &key, const QByteArray &text)
{


        QByteArray result; // Déclare un tableau d'octets qui contiendra le résultat du chiffrement/déchiffrement

        int key_len = key.size(); // Récupère la longueur de la clé, utilisée pour répéter la clé si elle est plus courte que le texte

        for (int i = 0; i < text.size(); ++i) {

            // Parcourt chaque octet du texte à chiffrer/déchiffrer


            unsigned char t = (unsigned char)(text[i]);

            // Récupère l’octet du texte

            unsigned char k = (unsigned char)(key[i % key_len]);
            // Récupère l’octet correspondant de la clé
                // L’opérateur % permet de recommencer au début de la clé si elle est plus courte que le texte

            result[i] = t ^ k;
            // Applique le XOR entre l’octet du texte et celui de la clé
               // -> C’est ici que se fait le chiffrement (ou le déchiffrement)
               // Comme XOR est une opération réversible : (t ^ k) ^ k = t
               // la même fonction sert pour chiffrer et déchiffrer

        }

        return result;
    }

//------------------------------------------------------------------------------------------------------------------

QByteArray Widget::decalage(QByteArray contenu)
{
    //Récupération de la valeur du décalage
    int decalage = ui->spinDecalage->value();

    //Décalage
    for (int i=0; i<contenu.size();i++)
    {
        unsigned char octet_initial = contenu[i];  //Récupère les valeurs des octet un à un
        unsigned char octet_decale = octet_initial + decalage;  //Ajoute la valeur du décalage pour des valeurs entre 0 et 255
        contenu_final.append(octet_decale);  //Modifie l'octet du fichier contenu final par l'octet décalé
    }
    return contenu_final;
}

//------------------------------------------------------------------------------------------------------------------

QByteArray Widget::contre_decalage(QByteArray contenu)
{
    //Récupération de la valeur du décalage
    int decalage = ui->spinDecalage->value();

    //Décalage
    for (int i=0; i<contenu.size();i++)
    {
        unsigned char octet_initial = contenu[i];  //Récupère les valeurs des octet un à un
        unsigned char octet_decale = octet_initial - decalage;  //Soustrait la valeur du décalage pour des valeurs entre 0 et 255

        contenu_final.append(octet_decale);  //Modifie l'octet du fichier contenu final par l'octet décalé
    }
    return contenu_final;
}



//------------------------------------------------------------------------------------------------------------------

void Widget::on_pB_chiffrer_clicked()
{
    //Autorise le chiffrement si la clé de sécurité est correct
    if (ui->lineE_cle->text() == "Veuillez saisir la clé")
    {
        QMessageBox::warning(this, "Erreur", "La Clé de chiffrement est incorrecte.");
        return;
    }

    //Utilisation de la méthode inversion
    QByteArray contenu_part1 = inversion(contenu_initial);

    //Utilisation de la méthode chiffrement
    QByteArray contenu_part2 = chiffrement(ui->lineE_cle->text().toUtf8(),contenu_part1);

    //Utilisation de la méthode décalage
    QByteArray contenu_part3 = decalage(contenu_part2);

    //Affichage du Texte final
    ui->textB_final->setPlainText(contenu_part3);
}

//------------------------------------------------------------------------------------------------------------------
  void Widget::on_pB_dechiffrer_clicked()
{
    //Supprimer le Texte précédent
    ui->textB_final->clear();

    //Autorise le déchiffrement si la clé de sécurité est correct
    if (ui->lineE_cle->text() == "Veuillez saisir la clé")
    {
        QMessageBox::warning(this, "Erreur", "La Clé de chiffrement est incorrecte.");
        return;
    }

    //Utilisation de la méthode contre_décalage
    QByteArray contenu_part1 = contre_decalage(contenu_initial);

    //Utilisation de la méthode contre_chiffrement
    QByteArray contenu_part2 = chiffrement(ui->lineE_cle->text().toUtf8(),contenu_part1);

    //Utilisation de la méthode desinversion
    QByteArray contenu_part3 = desinversion(contenu_part2);


    //Affichage du Texte final
    ui->textB_final->setPlainText(contenu_part3);

}

//------------------------------------------------------------------------------------------------------------------
void Widget::on_pB_sauv_clicked()
{
    // Choisir où sauvegarder
    QString sortie = QFileDialog::getSaveFileName(this, "Enregistrer le fichier chiffré", "", "Texte (*.txt)");
    if (sortie.isEmpty())
        return;

    QFile outFile(sortie);
    if (!outFile.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, "Erreur", "Impossible d’écrire dans le fichier.");
        return;
    }

    outFile.write(contenu_final);
    outFile.close();

    QMessageBox::information(this, "Succès", "Le fichier a été enregistré avec succès !");
}

//------------------------------------------------------------------------------------------------------------------
void Widget::on_PB_supprimer_clicked()
{
    ui->textB_final->clear();
    contenu_initial.clear();
}
//------------------------------------------------------------------------------------------------------------------
