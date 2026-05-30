#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

/* Projet ACF 2025 Groupe :
 *  Téo BOINOT
 * QUATTER Mael
 * Mattieu RENAUDEAU
 */
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pB_ouvrir_clicked();

    //Inversion
    QByteArray inversion(QByteArray contenu);
    //Désinversion
    QByteArray desinversion(QByteArray contenu);

    //Chiffrement
    QByteArray chiffrement(const QByteArray& key, const QByteArray& text);
    //Déchiffrement


    //Décalage
    QByteArray decalage(QByteArray contenu);
    //Contre Décalage
    QByteArray contre_decalage(QByteArray contenu);

    void on_pB_chiffrer_clicked();

    void on_pB_dechiffrer_clicked();

    void on_pB_sauv_clicked();

    void on_PB_supprimer_clicked();

private:
    Ui::Widget *ui;

    QByteArray contenu_initial;
    QByteArray contenu_final;
};
#endif // WIDGET_H
