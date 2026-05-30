#  Chiffrement de fichiers — Mini-projet C++/Qt

> Mini-projet réalisé dans le cadre du BTS CIEL (Informatique & Réseaux)  
> Activité Complémentaire de Formation — 12h — Qt Creator / C++

---

##  Présentation

Application de chiffrement et déchiffrement de fichiers développée en **C++** avec **Qt Creator**.  
Elle implémente un algorithme maison en 3 étapes combinant inversion de contenu, chiffrement XOR avec clé cyclique et décalage d'octets.

L'interface graphique (IHM) permet à l'utilisateur de charger un fichier, visualiser son contenu, le chiffrer avec une clé personnalisée, puis le sauvegarder — et de vérifier le résultat en le déchiffrant.

---

##  Fonctionnalités

-  Chargement d'un fichier texte ou binaire
-  Aperçu du contenu original et chiffré
-  Clé de chiffrement personnalisable
-  Valeur de décalage configurable (0–255)
-  Sauvegarde du fichier chiffré
-  Déchiffrement et vérification de l'intégrité

---

##  Algorithme de chiffrement

Le chiffrement s'effectue en **3 étapes successives** :

### 1. Inversion
Le fichier est coupé en deux parties et les parties sont échangées.  
Si le nombre d'octets est impair, la première partie est la plus courte.

```
"BIENVENUE" → "VENUEBIEN"
```

### 2. XOR avec clé cyclique
Chaque octet du contenu inversé est combiné avec l'octet correspondant de la clé via un **OU exclusif (XOR)**.  
Si la clé est plus courte que le fichier, elle se répète cycliquement.

```
Octet du fichier : 'D' (68)  XOR  Octet de la clé : 'e' (101)  =  '!' (33)
```

### 3. Décalage
Une valeur de décalage (entier entre 0 et 255) est **ajoutée mathématiquement** à chaque octet après le XOR.

```
octet_chiffré = (octet XOR clé[k % len(clé)]) + décalage
```

### Déchiffrement
Les 3 étapes sont inversées dans l'ordre : soustraction du décalage → XOR avec la clé → ré-inversion.

---

##  Technologies utilisées

| Technologie | Usage |
|---|---|
| C++ | Logique de chiffrement, manipulation d'octets |
| Qt Creator | Interface graphique (IHM) |
| Qt Widgets | Composants UI (boutons, zones de texte, etc.) |
| QFile / QByteArray | Lecture et écriture de fichiers binaires |

---

##  Concepts abordés

- Programmation orientée objet en C++ (interfaces & implémentations)
- Manipulation de fichiers au niveau octet
- Opérations bit à bit : XOR (`^`)
- Chiffrement symétrique simplifié
- Conception d'une IHM avec Qt

---

##  Lancer le projet

### Prérequis
- Qt Creator installé (version 6.x recommandée)
- Compilateur C++ (MinGW ou MSVC sous Windows, GCC sous Linux)

### Étapes
```bash
# Cloner le dépôt
git clone https://github.com/votre-username/projet-crypto-qt.git

# Ouvrir le fichier .pro dans Qt Creator
# puis Build & Run
```

---

##  Structure du projet

```
projet-crypto-qt/
├── src/
│   ├── main.cpp
│   ├── mainwindow.cpp
│   ├── mainwindow.h
│   └── ...
├── rapport/
│   └── sujet_ACF_cryptographie.pdf
└── README.md
```

---

##  Contexte scolaire

- **Formation** : BTS CIEL – Informatique & Réseaux
- **Établissement** : Lycée Pilote Innovant International (LP2I)
- **Référentiel** : S3.1 – Modélisation orientée objet, Interfaces et implémentations
- **Durée** : 12 heures

---

## 👤 Auteur

**BOINOT Téo**  
