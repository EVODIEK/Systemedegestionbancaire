# EvoBank (BanqueApp)

Application de bureau de **gestion bancaire** développée en **C++** avec la bibliothèque graphique **wxWidgets**. Elle propose deux espaces : un espace **Client** (comptes, opérations, cartes, prêts) et un espace **Administrateur** (gestion des clients, comptes, cartes et prêts).

> Projet d'étude réalisé sous Ubuntu avec Code::Blocks. Les données sont fictives et stockées en mémoire (pas de base de données).

## Sommaire

1. [Aperçu](#aperçu)
2. [Fonctionnalités](#fonctionnalités)
3. [Structure du projet](#structure-du-projet)
4. [Prérequis](#prérequis)
5. [Compilation et lancement](#compilation-et-lancement)
6. [Utilisation](#utilisation)
7. [Architecture technique](#architecture-technique)
8. [Limites actuelles](#limites-actuelles)
9. [Pistes d'amélioration](#pistes-damélioration)
10. [Auteur](#auteur)

## Aperçu

Au lancement, un écran de connexion permet de choisir le type de compte (Client ou Administrateur). Chaque espace ouvre une fenêtre dédiée, avec des listes (wxListCtrl), des boutons d'action et des boîtes de dialogue pour saisir les montants.

<!-- Ajoute tes captures d'écran dans docs/screenshots/ puis décommente :
![Connexion](docs/screenshots/login.png)
![Espace client](docs/screenshots/client.png)
![Espace administrateur](docs/screenshots/admin.png)
-->

## Fonctionnalités

### Écran de connexion (`LoginFrame`)
- Saisie du nom d'utilisateur et du mot de passe (valeurs de test préremplies : `evodie` / `1234`)
- Choix du type de compte : **Client** ou **Administrateur**
- Vérification que les champs ne sont pas vides

### Espace Client (`DashboardClientFrame`)
- Affichage du **solde total** et de la liste des comptes
- **Dépôt** sur un compte sélectionné
- **Retrait** avec vérification du solde disponible
- **Virement** entre comptes (saisie du numéro du compte destinataire, contrôle du solde et refus du virement vers le même compte)
- Aperçu des **cartes** et des **prêts**
- Accès aux écrans de gestion des cartes et des prêts

### Gestion des cartes (`GestionCartesFrame`)
- Statistiques : nombre de cartes et cartes actives
- **Activer**, **désactiver** ou **bloquer** une carte (le blocage demande une confirmation)
- **Commander une nouvelle carte** (numéro généré aléatoirement)
- **Voir les détails** d'une carte
- Couleurs selon l'état : active (vert), bloquée (rouge), désactivée (orange)

### Gestion des prêts (`GestionPretsFrame`)
- Statistiques : prêts actifs, montant emprunté, montant restant
- **Demander un prêt** (de 1 000 à 100 000 FCFA, statut "En attente")
- **Rembourser** un prêt (montant libre)
- **Remboursement rapide** : 10 %, 25 %, 50 % ou totalité du solde restant
- **Simulateur de prêt** : calcul de la mensualité, du coût total et des intérêts (taux de 4,5 %, 3,8 % ou 3,2 % selon le montant)
- **Voir les détails** d'un prêt et suivi du pourcentage remboursé

### Espace Administrateur (`AdminFrame`)
Tableau de bord avec 4 indicateurs (clients, comptes, cartes, prêts en cours) et 4 onglets :

| Onglet | Actions |
|--------|---------|
| Clients | Ajouter, modifier l'email, supprimer (avec confirmation) |
| Comptes | Créer un compte (Courant, Épargne, Jeune), fermer un compte (uniquement si le solde est nul) |
| Cartes | Bloquer, débloquer, renouveler |
| Prêts | Valider un prêt (montant maximum 100 000 FCFA), refuser ou annuler un prêt |

### Écran de gestion des comptes (`GestionComptesFrame`)
Dépôt, retrait, virement et ouverture de compte. Cet écran est codé mais n'est pas encore relié au menu de l'application (voir les limites).

## Structure du projet

```
BanqueApp/
├── include/                      # Fichiers d'en-tête (.h)
│   ├── App.h
│   ├── Client.h
│   ├── CompteBancaire.h
│   ├── CarteBancaire.h
│   ├── Pret.h
│   ├── LoginFrame.h
│   ├── DashboardClientFrame.h
│   ├── AdminFrame.h
│   ├── GestionComptesFrame.h
│   ├── GestionCartesFrame.h
│   └── GestionPretsFrame.h
├── src/                          # Fichiers sources (.cpp)
│   ├── App.cpp                   # Point d'entrée (wxIMPLEMENT_APP)
│   ├── Client.cpp
│   ├── CompteBancaire.cpp
│   ├── CarteBancaire.cpp
│   ├── Pret.cpp
│   ├── LoginFrame.cpp
│   ├── DashboardClientFrame.cpp
│   ├── AdminFrame.cpp
│   ├── GestionComptesFrame.cpp
│   ├── GestionCartesFrame.cpp
│   └── GestionPretsFrame.cpp
├── BanqueApp.cbp                 # Projet Code::Blocks
└── README.md
```

## Prérequis

- Système : Linux (testé sous Ubuntu 22.04)
- Compilateur : `g++` avec support C++11 ou supérieur
- Bibliothèque : **wxWidgets 3.0 ou 3.2** (version GTK3)

Installation sous Ubuntu / Debian :

```bash
sudo apt update
sudo apt install build-essential libwxgtk3.2-dev
# Si le paquet est introuvable, essayer : sudo apt install libwxgtk3.0-gtk3-dev
```

Vérification :

```bash
wx-config --version
```

## Compilation et lancement

### En ligne de commande

```bash
git clone https://github.com/TON_PSEUDO/BanqueApp.git
cd BanqueApp
g++ -g -Wall src/*.cpp -Iinclude `wx-config --cxxflags --libs` -o BanqueApp
./BanqueApp
```

### Avec Code::Blocks

1. Ouvrir `BanqueApp.cbp`
2. Dans **Project > Build options**, vérifier :
   - Compiler, autres options : `` `wx-config --cxxflags` ``
   - Linker, autres options : `` `wx-config --libs` ``
   - Search directories (compiler) : `include`
3. Lancer avec **Build and run** (F9)

> Le projet ne doit contenir qu'un seul point d'entrée (`src/App.cpp`). Si d'anciens fichiers générés par l'assistant (`main.cpp`, etc.) sont présents, il faut les retirer du projet.

## Utilisation

1. Lancer l'application : l'écran **EvoBank - Connexion** s'affiche.
2. Garder les identifiants préremplis (`evodie` / `1234`) ou saisir n'importe quelles valeurs non vides.
3. Choisir **Client** ou **Administrateur**, puis cliquer sur **SE CONNECTER**.
4. Dans l'espace client, sélectionner un compte dans la liste avant un dépôt, un retrait ou un virement.

### Données de test

| Élément | Exemples |
|---------|----------|
| Comptes | `FR001-123-456` (Courant, 1500,50), `FR002-789-012` (Épargne, 3200,00) |
| Cartes | Visa `4532-1234-5678-9010` (active), MasterCard `5425-2334-5566-7788` (bloquée) |
| Prêts | `P001` (5 000, restant 3 500), `P002` (10 000, restant 2 500) |

## Architecture technique

- **Modèles** (`include/`, classes simples entièrement définies dans les en-têtes) : `Client`, `CompteBancaire`, `CarteBancaire`, `Pret`. Les champs texte utilisent `wxString` pour gérer correctement les caractères Unicode.
- **Vues** : une classe héritant de `wxFrame` par écran, construite avec des `wxSizer` (mise en page adaptable) et des `wxListCtrl`.
- **Événements** : tables d'événements wxWidgets (`wxBEGIN_EVENT_TABLE`) et identifiants déclarés dans des `enum` propres à chaque écran.
- **Données** : stockées dans des `std::vector` en mémoire, initialisées avec des valeurs de test dans les constructeurs.
- **Point d'entrée** : `BanqueApp` (classe dérivée de `wxApp`) ouvre `LoginFrame`.

## Limites actuelles

- **Pas de persistance** : toutes les données sont perdues à la fermeture.
- **Pas d'authentification réelle** : tout couple identifiant / mot de passe non vide est accepté.
- **Données non partagées** : chaque fenêtre (tableau de bord, cartes, prêts, administration) possède sa propre copie des données, donc une modification dans une fenêtre n'apparaît pas dans les autres.
- **Devises mélangées** : la plupart des écrans utilisent le FCFA, mais certains textes affichent encore l'euro.
- **Écran `GestionComptesFrame`** non relié au reste de l'application.
- Le solde total du tableau de bord client n'est pas recalculé après une opération.
- Les montants sont stockés en `float` (à remplacer par un type plus précis pour un usage réel).

## Pistes d'amélioration

- Sauvegarde des données (fichier JSON ou base **SQLite**)
- Authentification avec mots de passe hachés et gestion de sessions
- Couche de données partagée entre toutes les fenêtres (classe `Banque` commune)
- Historique des transactions
- Uniformisation de la devise et du format des montants
- Tests unitaires sur les classes métier

## Auteur

**Sena Evodie Kpodegbe**, étudiante en Génie Électrique à l'EPAC (Université d'Abomey-Calavi, Bénin).

## Licence

Projet académique. Licence à définir (par exemple MIT).
