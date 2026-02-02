// ============================================
// src/AdminFrame.cpp - VERSION ULTRA-MODERNE CORRIGEE
// ============================================
#include "AdminFrame.h"
#include <wx/textdlg.h>
#include <wx/sizer.h>
#include <cstdlib>
#include <ctime>

wxBEGIN_EVENT_TABLE(AdminFrame, wxFrame)
    EVT_BUTTON(ID_AjouterClient, AdminFrame::OnAjouterClient)
    EVT_BUTTON(ID_SupprimerClient, AdminFrame::OnSupprimerClient)
    EVT_BUTTON(ID_ModifierClient, AdminFrame::OnModifierClient)
    EVT_BUTTON(ID_AjouterCompte, AdminFrame::OnAjouterCompte)
    EVT_BUTTON(ID_FermerCompte, AdminFrame::OnFermerCompte)
    EVT_BUTTON(ID_BloquerCarte, AdminFrame::OnBloquerCarte)
    EVT_BUTTON(ID_DebloquerCarte, AdminFrame::OnDebloquerCarte)
    EVT_BUTTON(ID_RenouvelerCarte, AdminFrame::OnRenouvelarCarte)
    EVT_BUTTON(ID_ValiderPret, AdminFrame::OnValiderPret)
    EVT_BUTTON(ID_RefuserPret, AdminFrame::OnRefuserPret)
wxEND_EVENT_TABLE()

AdminFrame::AdminFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(1200, 800))
{
    // Initialiser le generateur de nombres aleatoires
    srand(static_cast<unsigned int>(time(NULL)));

    // Donnees par defaut (sans accents pour eviter problemes Unicode)
    m_clients.push_back(Client("001", "Kpodegbe", "Evodie", "evodie@evobank.com"));
    m_clients.push_back(Client("002", "Dupont", "Jean", "jean.dupont@evobank.com"));
    m_clients.push_back(Client("003", "Martin", "Marie", "marie.martin@evobank.com"));
    m_clients.push_back(Client("004", "Bernard", "Paul", "paul.bernard@evobank.com"));

    m_comptes.push_back(CompteBancaire("FR001-123-456", "Compte Courant", 1500.50f, "001"));
    m_comptes.push_back(CompteBancaire("FR002-789-012", "Compte Epargne", 3200.00f, "001"));
    m_comptes.push_back(CompteBancaire("FR003-456-789", "Compte Courant", 850.00f, "002"));
    m_comptes.push_back(CompteBancaire("FR004-111-222", "Compte Epargne", 5400.00f, "003"));
    m_comptes.push_back(CompteBancaire("FR005-333-444", "Compte Courant", 2100.00f, "004"));

    m_cartes.push_back(CarteBancaire("4532-1234-5678-9010", "Visa", "Active", "FR001-123-456"));
    m_cartes.push_back(CarteBancaire("5425-2334-5566-7788", "MasterCard", "Bloquee", "FR001-123-456"));
    m_cartes.push_back(CarteBancaire("4916-3456-7890-1234", "Visa", "Active", "FR003-456-789"));
    m_cartes.push_back(CarteBancaire("5200-4567-8901-2345", "MasterCard", "Active", "FR005-333-444"));

    m_prets.push_back(Pret("P001", 5000.0f, 3500.0f, "Actif", "001"));
    m_prets.push_back(Pret("P002", 10000.0f, 2500.0f, "Actif", "001"));
    m_prets.push_back(Pret("P003", 3000.0f, 0.0f, "Rembourse", "002"));
    m_prets.push_back(Pret("P004", 7500.0f, 7500.0f, "En attente", "004"));

    CreerInterface();
}

void AdminFrame::CreerInterface()
{
    wxPanel* mainPanel = new wxPanel(this, wxID_ANY);
    mainPanel->SetBackgroundColour(wxColour(236, 240, 241));

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // ==================== HEADER ROUGE ADMIN ====================
    wxPanel* headerPanel = new wxPanel(mainPanel, wxID_ANY);
    headerPanel->SetBackgroundColour(wxColour(192, 57, 43)); // Rouge admin
    headerPanel->SetMinSize(wxSize(-1, 80));

    wxBoxSizer* headerSizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText* lblTitre = new wxStaticText(headerPanel, wxID_ANY, "  EVOBANK - PANNEAU D'ADMINISTRATION");
    wxFont fontTitre(22, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    lblTitre->SetFont(fontTitre);
    lblTitre->SetForegroundColour(*wxWHITE);
    headerSizer->Add(lblTitre, 1, wxALIGN_CENTER_VERTICAL | wxALL, 20);

    wxStaticText* lblAdmin = new wxStaticText(headerPanel, wxID_ANY, "Administrateur  ");
    wxFont fontAdmin(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    lblAdmin->SetFont(fontAdmin);
    lblAdmin->SetForegroundColour(wxColour(236, 240, 241));
    headerSizer->Add(lblAdmin, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 30);

    headerPanel->SetSizer(headerSizer);
    mainSizer->Add(headerPanel, 0, wxEXPAND);

    // ==================== STATISTIQUES RAPIDES ====================
    wxPanel* statsPanel = new wxPanel(mainPanel, wxID_ANY);
    statsPanel->SetBackgroundColour(wxColour(236, 240, 241));

    wxBoxSizer* statsSizer = new wxBoxSizer(wxHORIZONTAL);

    // Carte Clients
    wxPanel* statsClients = new wxPanel(statsPanel, wxID_ANY);
    statsClients->SetBackgroundColour(wxColour(52, 152, 219));
    statsClients->SetMinSize(wxSize(250, 80));
    wxBoxSizer* s1 = new wxBoxSizer(wxVERTICAL);
    wxStaticText* t1 = new wxStaticText(statsClients, wxID_ANY, "CLIENTS TOTAUX");
    wxFont f1(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    t1->SetFont(f1);
    t1->SetForegroundColour(wxColour(189, 195, 199));
    s1->Add(t1, 0, wxALIGN_CENTER | wxTOP, 15);
    wxStaticText* v1 = new wxStaticText(statsClients, wxID_ANY, wxString::Format("%d", (int)m_clients.size()));
    wxFont fv1(26, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    v1->SetFont(fv1);
    v1->SetForegroundColour(*wxWHITE);
    s1->Add(v1, 0, wxALIGN_CENTER | wxBOTTOM, 15);
    statsClients->SetSizer(s1);
    statsSizer->Add(statsClients, 1, wxEXPAND | wxALL, 10);

    // Carte Comptes
    wxPanel* statsComptes = new wxPanel(statsPanel, wxID_ANY);
    statsComptes->SetBackgroundColour(wxColour(46, 204, 113));
    statsComptes->SetMinSize(wxSize(250, 80));
    wxBoxSizer* s2 = new wxBoxSizer(wxVERTICAL);
    wxStaticText* t2 = new wxStaticText(statsComptes, wxID_ANY, "COMPTES ACTIFS");
    t2->SetFont(f1);
    t2->SetForegroundColour(wxColour(189, 195, 199));
    s2->Add(t2, 0, wxALIGN_CENTER | wxTOP, 15);
    wxStaticText* v2 = new wxStaticText(statsComptes, wxID_ANY, wxString::Format("%d", (int)m_comptes.size()));
    v2->SetFont(fv1);
    v2->SetForegroundColour(*wxWHITE);
    s2->Add(v2, 0, wxALIGN_CENTER | wxBOTTOM, 15);
    statsComptes->SetSizer(s2);
    statsSizer->Add(statsComptes, 1, wxEXPAND | wxALL, 10);

    // Carte Cartes
    wxPanel* statsCartes = new wxPanel(statsPanel, wxID_ANY);
    statsCartes->SetBackgroundColour(wxColour(155, 89, 182));
    statsCartes->SetMinSize(wxSize(250, 80));
    wxBoxSizer* s3 = new wxBoxSizer(wxVERTICAL);
    wxStaticText* t3 = new wxStaticText(statsCartes, wxID_ANY, "CARTES EMISES");
    t3->SetFont(f1);
    t3->SetForegroundColour(wxColour(189, 195, 199));
    s3->Add(t3, 0, wxALIGN_CENTER | wxTOP, 15);
    wxStaticText* v3 = new wxStaticText(statsCartes, wxID_ANY, wxString::Format("%d", (int)m_cartes.size()));
    v3->SetFont(fv1);
    v3->SetForegroundColour(*wxWHITE);
    s3->Add(v3, 0, wxALIGN_CENTER | wxBOTTOM, 15);
    statsCartes->SetSizer(s3);
    statsSizer->Add(statsCartes, 1, wxEXPAND | wxALL, 10);

    // Carte Prets
    wxPanel* statsPrets = new wxPanel(statsPanel, wxID_ANY);
    statsPrets->SetBackgroundColour(wxColour(230, 126, 34));
    statsPrets->SetMinSize(wxSize(250, 80));
    wxBoxSizer* s4 = new wxBoxSizer(wxVERTICAL);
    wxStaticText* t4 = new wxStaticText(statsPrets, wxID_ANY, "PRETS EN COURS");
    t4->SetFont(f1);
    t4->SetForegroundColour(wxColour(189, 195, 199));
    s4->Add(t4, 0, wxALIGN_CENTER | wxTOP, 15);
    int pretsActifs = 0;
    for(size_t i = 0; i < m_prets.size(); ++i) {
        if(m_prets[i].etat == "Actif" || m_prets[i].etat == "En attente") pretsActifs++;
    }
    wxStaticText* v4 = new wxStaticText(statsPrets, wxID_ANY, wxString::Format("%d", pretsActifs));
    v4->SetFont(fv1);
    v4->SetForegroundColour(*wxWHITE);
    s4->Add(v4, 0, wxALIGN_CENTER | wxBOTTOM, 15);
    statsPrets->SetSizer(s4);
    statsSizer->Add(statsPrets, 1, wxEXPAND | wxALL, 10);

    statsPanel->SetSizer(statsSizer);
    mainSizer->Add(statsPanel, 0, wxEXPAND);

    // ==================== NOTEBOOK AVEC ONGLETS ====================
    notebook = new wxNotebook(mainPanel, wxID_ANY);
    notebook->SetBackgroundColour(*wxWHITE);

    wxPanel* panelClients = new wxPanel(notebook);
    wxPanel* panelComptes = new wxPanel(notebook);
    wxPanel* panelCartes = new wxPanel(notebook);
    wxPanel* panelPrets = new wxPanel(notebook);

    notebook->AddPage(panelClients, "  CLIENTS  ");
    notebook->AddPage(panelComptes, "  COMPTES  ");
    notebook->AddPage(panelCartes, "  CARTES  ");
    notebook->AddPage(panelPrets, "  PRETS  ");

    CreerOngletClients(panelClients);
    CreerOngletComptes(panelComptes);
    CreerOngletCartes(panelCartes);
    CreerOngletPrets(panelPrets);

    mainSizer->Add(notebook, 1, wxEXPAND | wxALL, 20);
    mainPanel->SetSizer(mainSizer);
}

void AdminFrame::CreerOngletClients(wxPanel* parent)
{
    parent->SetBackgroundColour(*wxWHITE);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* lbl = new wxStaticText(parent, wxID_ANY, "  GESTION DES CLIENTS");
    wxFont font(15, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    lbl->SetFont(font);
    lbl->SetForegroundColour(wxColour(52, 73, 94));
    sizer->Add(lbl, 0, wxALL, 20);

    listClients = new wxListCtrl(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                 wxLC_REPORT | wxLC_SINGLE_SEL | wxBORDER_SIMPLE);
    listClients->SetBackgroundColour(wxColour(250, 250, 250));
    listClients->InsertColumn(0, "ID Client", wxLIST_FORMAT_LEFT, 100);
    listClients->InsertColumn(1, "Nom", wxLIST_FORMAT_LEFT, 200);
    listClients->InsertColumn(2, "Prenom", wxLIST_FORMAT_LEFT, 200);
    listClients->InsertColumn(3, "Email", wxLIST_FORMAT_LEFT, 300);
    listClients->InsertColumn(4, "Statut", wxLIST_FORMAT_CENTER, 120);

    ActualiserClients();
    sizer->Add(listClients, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 20);

    wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
    wxFont fontBtn(11, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

    wxButton* btnAjouter = new wxButton(parent, ID_AjouterClient, "Ajouter un client",
                                        wxDefaultPosition, wxSize(180, 45));
    btnAjouter->SetBackgroundColour(wxColour(46, 204, 113));
    btnAjouter->SetForegroundColour(*wxWHITE);
    btnAjouter->SetFont(fontBtn);
    btnSizer->Add(btnAjouter, 0, wxALL, 5);

    wxButton* btnModifier = new wxButton(parent, ID_ModifierClient, "Modifier",
                                         wxDefaultPosition, wxSize(180, 45));
    btnModifier->SetBackgroundColour(wxColour(52, 152, 219));
    btnModifier->SetForegroundColour(*wxWHITE);
    btnModifier->SetFont(fontBtn);
    btnSizer->Add(btnModifier, 0, wxALL, 5);

    wxButton* btnSupprimer = new wxButton(parent, ID_SupprimerClient, "Supprimer",
                                         wxDefaultPosition, wxSize(180, 45));
    btnSupprimer->SetBackgroundColour(wxColour(231, 76, 60));
    btnSupprimer->SetForegroundColour(*wxWHITE);
    btnSupprimer->SetFont(fontBtn);
    btnSizer->Add(btnSupprimer, 0, wxALL, 5);

    sizer->Add(btnSizer, 0, wxALIGN_CENTER | wxBOTTOM, 20);
    parent->SetSizer(sizer);
}

void AdminFrame::CreerOngletComptes(wxPanel* parent)
{
    parent->SetBackgroundColour(*wxWHITE);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* lbl = new wxStaticText(parent, wxID_ANY, "  GESTION DES COMPTES BANCAIRES");
    wxFont font(15, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    lbl->SetFont(font);
    lbl->SetForegroundColour(wxColour(52, 73, 94));
    sizer->Add(lbl, 0, wxALL, 20);

    listComptesAdmin = new wxListCtrl(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                      wxLC_REPORT | wxLC_SINGLE_SEL | wxBORDER_SIMPLE);
    listComptesAdmin->SetBackgroundColour(wxColour(250, 250, 250));
    listComptesAdmin->InsertColumn(0, "Numero Compte", wxLIST_FORMAT_LEFT, 220);
    listComptesAdmin->InsertColumn(1, "Type", wxLIST_FORMAT_LEFT, 180);
    listComptesAdmin->InsertColumn(2, "Solde (FCFA)", wxLIST_FORMAT_RIGHT, 150);
    listComptesAdmin->InsertColumn(3, "ID Client", wxLIST_FORMAT_LEFT, 120);
    listComptesAdmin->InsertColumn(4, "Statut", wxLIST_FORMAT_CENTER, 120);

    ActualiserComptes();
    sizer->Add(listComptesAdmin, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 20);

    wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
    wxFont fontBtn(11, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

    wxButton* btnCreer = new wxButton(parent, ID_AjouterCompte, "Creer un compte",
                                       wxDefaultPosition, wxSize(200, 45));
    btnCreer->SetBackgroundColour(wxColour(46, 204, 113));
    btnCreer->SetForegroundColour(*wxWHITE);
    btnCreer->SetFont(fontBtn);
    btnSizer->Add(btnCreer, 0, wxALL, 5);

    wxButton* btnFermer = new wxButton(parent, ID_FermerCompte, "Fermer le compte",
                                       wxDefaultPosition, wxSize(200, 45));
    btnFermer->SetBackgroundColour(wxColour(231, 76, 60));
    btnFermer->SetForegroundColour(*wxWHITE);
    btnFermer->SetFont(fontBtn);
    btnSizer->Add(btnFermer, 0, wxALL, 5);

    sizer->Add(btnSizer, 0, wxALIGN_CENTER | wxBOTTOM, 20);
    parent->SetSizer(sizer);
}

void AdminFrame::CreerOngletCartes(wxPanel* parent)
{
    parent->SetBackgroundColour(*wxWHITE);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* lbl = new wxStaticText(parent, wxID_ANY, "  GESTION DES CARTES BANCAIRES");
    wxFont font(15, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    lbl->SetFont(font);
    lbl->SetForegroundColour(wxColour(52, 73, 94));
    sizer->Add(lbl, 0, wxALL, 20);

    listCartesAdmin = new wxListCtrl(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                     wxLC_REPORT | wxLC_SINGLE_SEL | wxBORDER_SIMPLE);
    listCartesAdmin->SetBackgroundColour(wxColour(250, 250, 250));
    listCartesAdmin->InsertColumn(0, "Numero Carte", wxLIST_FORMAT_LEFT, 250);
    listCartesAdmin->InsertColumn(1, "Type", wxLIST_FORMAT_LEFT, 150);
    listCartesAdmin->InsertColumn(2, "Etat", wxLIST_FORMAT_CENTER, 120);
    listCartesAdmin->InsertColumn(3, "Compte associe", wxLIST_FORMAT_LEFT, 220);

    ActualiserCartes();
    sizer->Add(listCartesAdmin, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 20);

    wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
    wxFont fontBtn(11, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

    wxButton* btnBloquer = new wxButton(parent, ID_BloquerCarte, "Bloquer",
                                       wxDefaultPosition, wxSize(160, 45));
    btnBloquer->SetBackgroundColour(wxColour(231, 76, 60));
    btnBloquer->SetForegroundColour(*wxWHITE);
    btnBloquer->SetFont(fontBtn);
    btnSizer->Add(btnBloquer, 0, wxALL, 5);

    wxButton* btnDebloquer = new wxButton(parent, ID_DebloquerCarte, "Debloquer",
                                         wxDefaultPosition, wxSize(160, 45));
    btnDebloquer->SetBackgroundColour(wxColour(46, 204, 113));
    btnDebloquer->SetForegroundColour(*wxWHITE);
    btnDebloquer->SetFont(fontBtn);
    btnSizer->Add(btnDebloquer, 0, wxALL, 5);

    wxButton* btnRenouveler = new wxButton(parent, ID_RenouvelerCarte, "Renouveler",
                                          wxDefaultPosition, wxSize(160, 45));
    btnRenouveler->SetBackgroundColour(wxColour(52, 152, 219));
    btnRenouveler->SetForegroundColour(*wxWHITE);
    btnRenouveler->SetFont(fontBtn);
    btnSizer->Add(btnRenouveler, 0, wxALL, 5);

    sizer->Add(btnSizer, 0, wxALIGN_CENTER | wxBOTTOM, 20);
    parent->SetSizer(sizer);
}

void AdminFrame::CreerOngletPrets(wxPanel* parent)
{
    parent->SetBackgroundColour(*wxWHITE);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* lbl = new wxStaticText(parent, wxID_ANY, "  GESTION DES PRETS");
    wxFont font(15, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    lbl->SetFont(font);
    lbl->SetForegroundColour(wxColour(52, 73, 94));
    sizer->Add(lbl, 0, wxALL, 20);

    listPretsAdmin = new wxListCtrl(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                    wxLC_REPORT | wxLC_SINGLE_SEL | wxBORDER_SIMPLE);
    listPretsAdmin->SetBackgroundColour(wxColour(250, 250, 250));
    listPretsAdmin->InsertColumn(0, "ID Pret", wxLIST_FORMAT_LEFT, 100);
    listPretsAdmin->InsertColumn(1, "Montant Initial (FCFA)", wxLIST_FORMAT_RIGHT, 180);
    listPretsAdmin->InsertColumn(2, "Montant Restant (FCFA)", wxLIST_FORMAT_RIGHT, 180);
    listPretsAdmin->InsertColumn(3, "Etat", wxLIST_FORMAT_CENTER, 120);
    listPretsAdmin->InsertColumn(4, "ID Client", wxLIST_FORMAT_LEFT, 120);

    ActualiserPrets();
    sizer->Add(listPretsAdmin, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 20);

    wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
    wxFont fontBtn(11, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

    wxButton* btnValider = new wxButton(parent, ID_ValiderPret, "Valider un pret",
                                       wxDefaultPosition, wxSize(200, 45));
    btnValider->SetBackgroundColour(wxColour(46, 204, 113));
    btnValider->SetForegroundColour(*wxWHITE);
    btnValider->SetFont(fontBtn);
    btnSizer->Add(btnValider, 0, wxALL, 5);

    wxButton* btnRefuser = new wxButton(parent, ID_RefuserPret, "Refuser / Annuler",
                                       wxDefaultPosition, wxSize(200, 45));
    btnRefuser->SetBackgroundColour(wxColour(231, 76, 60));
    btnRefuser->SetForegroundColour(*wxWHITE);
    btnRefuser->SetFont(fontBtn);
    btnSizer->Add(btnRefuser, 0, wxALL, 5);

    sizer->Add(btnSizer, 0, wxALIGN_CENTER | wxBOTTOM, 20);
    parent->SetSizer(sizer);
}

// ==================== METHODES D'ACTUALISATION ====================

void AdminFrame::ActualiserClients()
{
    listClients->DeleteAllItems();
    for(size_t i = 0; i < m_clients.size(); ++i) {
        long idx = listClients->InsertItem(i, m_clients[i].idClient);
        listClients->SetItem(idx, 1, m_clients[i].nom);
        listClients->SetItem(idx, 2, m_clients[i].prenom);
        listClients->SetItem(idx, 3, m_clients[i].email);
        listClients->SetItem(idx, 4, "Actif");

        if(i % 2 == 0) {
            listClients->SetItemBackgroundColour(idx, wxColour(248, 249, 250));
        }
    }
}

void AdminFrame::ActualiserComptes()
{
    listComptesAdmin->DeleteAllItems();
    for(size_t i = 0; i < m_comptes.size(); ++i) {
        long idx = listComptesAdmin->InsertItem(i, m_comptes[i].numeroCompte);
        listComptesAdmin->SetItem(idx, 1, m_comptes[i].typeCompte);
        listComptesAdmin->SetItem(idx, 2, wxString::Format("%.2f", m_comptes[i].solde));
        listComptesAdmin->SetItem(idx, 3, m_comptes[i].idClient);
        listComptesAdmin->SetItem(idx, 4, "Actif");

        if(i % 2 == 0) {
            listComptesAdmin->SetItemBackgroundColour(idx, wxColour(248, 249, 250));
        }
    }
}

void AdminFrame::ActualiserCartes()
{
    listCartesAdmin->DeleteAllItems();
    for(size_t i = 0; i < m_cartes.size(); ++i) {
        long idx = listCartesAdmin->InsertItem(i, m_cartes[i].numeroCarte);
        listCartesAdmin->SetItem(idx, 1, m_cartes[i].type);
        listCartesAdmin->SetItem(idx, 2, m_cartes[i].etat);
        listCartesAdmin->SetItem(idx, 3, m_cartes[i].numeroCompte);

        // Colorier selon l'etat
        if(m_cartes[i].etat == "Active") {
            listCartesAdmin->SetItemTextColour(idx, wxColour(39, 174, 96));
        } else {
            listCartesAdmin->SetItemTextColour(idx, wxColour(231, 76, 60));
        }

        if(i % 2 == 0) {
            listCartesAdmin->SetItemBackgroundColour(idx, wxColour(248, 249, 250));
        }
    }
}

void AdminFrame::ActualiserPrets()
{
    listPretsAdmin->DeleteAllItems();
    for(size_t i = 0; i < m_prets.size(); ++i) {
        long idx = listPretsAdmin->InsertItem(i, m_prets[i].idPret);
        listPretsAdmin->SetItem(idx, 1, wxString::Format("%.2f", m_prets[i].montantInitial));
        listPretsAdmin->SetItem(idx, 2, wxString::Format("%.2f", m_prets[i].montantRestant));
        listPretsAdmin->SetItem(idx, 3, m_prets[i].etat);
        listPretsAdmin->SetItem(idx, 4, m_prets[i].idClient);

        // Colorier selon l'etat
        if(m_prets[i].etat == "Actif") {
            listPretsAdmin->SetItemTextColour(idx, wxColour(52, 152, 219));
        } else if(m_prets[i].etat == "Rembourse") {
            listPretsAdmin->SetItemTextColour(idx, wxColour(39, 174, 96));
        } else {
            listPretsAdmin->SetItemTextColour(idx, wxColour(243, 156, 18));
        }

        if(i % 2 == 0) {
            listPretsAdmin->SetItemBackgroundColour(idx, wxColour(248, 249, 250));
        }
    }
}

// ==================== GESTION DES CLIENTS ====================

void AdminFrame::OnAjouterClient(wxCommandEvent& event)
{
    wxTextEntryDialog dlgNom(this, "Nom du nouveau client :", "Ajouter un client");
    if(dlgNom.ShowModal() != wxID_OK) return;

    wxTextEntryDialog dlgPrenom(this, "Prenom du client :", "Ajouter un client");
    if(dlgPrenom.ShowModal() != wxID_OK) return;

    wxTextEntryDialog dlgEmail(this, "Adresse email :", "Ajouter un client");
    if(dlgEmail.ShowModal() != wxID_OK) return;

    wxString newId = wxString::Format("00%d", (int)m_clients.size() + 1);
    m_clients.push_back(Client(std::string(newId.mb_str()),
                              std::string(dlgNom.GetValue().mb_str()),
                              std::string(dlgPrenom.GetValue().mb_str()),
                              std::string(dlgEmail.GetValue().mb_str())));
    ActualiserClients();
    wxMessageBox(wxString::Format("Client %s %s ajoute avec succes !\nID : %s",
                dlgPrenom.GetValue(), dlgNom.GetValue(), newId),
                "Succes", wxOK | wxICON_INFORMATION);
}

void AdminFrame::OnModifierClient(wxCommandEvent& event)
{
    long item = listClients->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if(item == -1) {
        wxMessageBox("Veuillez selectionner un client a modifier.", "Information",
                    wxOK | wxICON_INFORMATION);
        return;
    }

    wxTextEntryDialog dlgEmail(this,
        wxString::Format("Client : %s %s\nNouvelle adresse email :",
                        m_clients[item].prenom.c_str(), m_clients[item].nom.c_str()),
        "Modifier le client", wxString(m_clients[item].email.c_str()));

    if(dlgEmail.ShowModal() == wxID_OK) {
        m_clients[item].email = std::string(dlgEmail.GetValue().mb_str());
        ActualiserClients();
        wxMessageBox("Email modifie avec succes !", "Succes", wxOK | wxICON_INFORMATION);
    }
}

void AdminFrame::OnSupprimerClient(wxCommandEvent& event)
{
    long item = listClients->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if(item == -1) {
        wxMessageBox("Veuillez selectionner un client a supprimer.", "Information",
                    wxOK | wxICON_INFORMATION);
        return;
    }

    if(wxMessageBox(wxString::Format("Etes-vous sur de vouloir supprimer le client :\n\n%s %s (%s) ?\n\nCette action est IRREVERSIBLE !",
                    m_clients[item].prenom.c_str(), m_clients[item].nom.c_str(), m_clients[item].idClient.c_str()),
                    "Confirmation de suppression",
                    wxYES_NO | wxICON_WARNING) == wxYES) {
        m_clients.erase(m_clients.begin() + item);
        ActualiserClients();
        wxMessageBox("Client supprime avec succes !", "Succes", wxOK | wxICON_INFORMATION);
    }
}

// ==================== GESTION DES COMPTES ====================

void AdminFrame::OnAjouterCompte(wxCommandEvent& event)
{
    wxTextEntryDialog dlgId(this, "Entrez l'ID du client proprietaire :", "Creer un compte");
    if(dlgId.ShowModal() != wxID_OK) return;

    wxString choices[] = {"Compte Courant", "Compte Epargne", "Compte Jeune"};
    wxSingleChoiceDialog dlgType(this, "Choisissez le type de compte :", "Creer un compte", 3, choices);
    if(dlgType.ShowModal() != wxID_OK) return;

    wxString newNum = wxString::Format("FR%03d-%03d-%03d", (int)m_comptes.size() + 1,
                                       rand() % 1000, rand() % 1000);
    m_comptes.push_back(CompteBancaire(std::string(newNum.mb_str()),
                                       std::string(dlgType.GetStringSelection().mb_str()),
                                       0.0f,
                                       std::string(dlgId.GetValue().mb_str())));
    ActualiserComptes();
    wxMessageBox(wxString::Format("Compte cree avec succes !\n\nNumero : %s\nType : %s\nClient : %s",
                newNum, dlgType.GetStringSelection(), dlgId.GetValue()),
                "Succes", wxOK | wxICON_INFORMATION);
}

void AdminFrame::OnFermerCompte(wxCommandEvent& event)
{
    long item = listComptesAdmin->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if(item == -1) {
        wxMessageBox("Veuillez selectionner un compte a fermer.", "Information",
                    wxOK | wxICON_INFORMATION);
        return;
    }

    if(m_comptes[item].solde > 0) {
        wxMessageBox(wxString::Format("Impossible de fermer ce compte !\n\nSolde restant : %.2f FCFA\n\nVeuillez d'abord transferer les fonds.",
                    m_comptes[item].solde),
                    "Erreur", wxOK | wxICON_ERROR);
        return;
    }

    if(wxMessageBox(wxString::Format("Etes-vous sur de vouloir fermer le compte :\n\n%s ?",
                    m_comptes[item].numeroCompte.c_str()),
                    "Confirmation", wxYES_NO | wxICON_QUESTION) == wxYES) {
        m_comptes.erase(m_comptes.begin() + item);
        ActualiserComptes();
        wxMessageBox("Compte ferme avec succes !", "Succes", wxOK | wxICON_INFORMATION);
    }
}

// ==================== GESTION DES CARTES ====================

void AdminFrame::OnBloquerCarte(wxCommandEvent& event)
{
    long item = listCartesAdmin->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if(item == -1) {
        wxMessageBox("Veuillez selectionner une carte a bloquer.", "Information",
                    wxOK | wxICON_INFORMATION);
        return;
    }

    if(m_cartes[item].etat == "Bloquee") {
        wxMessageBox("Cette carte est deja bloquee.", "Information", wxOK | wxICON_INFORMATION);
        return;
    }

    m_cartes[item].etat = "Bloquee";
    ActualiserCartes();
    wxMessageBox(wxString::Format("Carte %s bloquee avec succes !", m_cartes[item].numeroCarte.c_str()),
                "Succes", wxOK | wxICON_INFORMATION);
}

void AdminFrame::OnDebloquerCarte(wxCommandEvent& event)
{
    long item = listCartesAdmin->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if(item == -1) {
        wxMessageBox("Veuillez selectionner une carte a debloquer.", "Information",
                    wxOK | wxICON_INFORMATION);
        return;
    }

    if(m_cartes[item].etat == "Active") {
        wxMessageBox("Cette carte est deja active.", "Information", wxOK | wxICON_INFORMATION);
        return;
    }

    m_cartes[item].etat = "Active";
    ActualiserCartes();
    wxMessageBox(wxString::Format("Carte %s debloquee avec succes !", m_cartes[item].numeroCarte.c_str()),
                "Succes", wxOK | wxICON_INFORMATION);
}

void AdminFrame::OnRenouvelarCarte(wxCommandEvent& event)
{
    long item = listCartesAdmin->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if(item == -1) {
        wxMessageBox("Veuillez selectionner une carte a renouveler.", "Information",
                    wxOK | wxICON_INFORMATION);
        return;
    }

    wxString oldNum = wxString(m_cartes[item].numeroCarte.c_str());
    wxString newNum = wxString::Format("%04d-%04d-%04d-%04d",
                                      4000 + rand() % 1000, rand() % 10000,
                                      rand() % 10000, rand() % 10000);

    m_cartes[item].numeroCarte = std::string(newNum.mb_str());
    m_cartes[item].etat = "Active";
    ActualiserCartes();

    wxMessageBox(wxString::Format("Carte renouvelee avec succes !\n\nAncien numero : %s\nNouveau numero : %s",
                oldNum, newNum),
                "Succes", wxOK | wxICON_INFORMATION);
}

// ==================== GESTION DES PRETS ====================

void AdminFrame::OnValiderPret(wxCommandEvent& event)
{
    wxTextEntryDialog dlgClient(this, "Entrez l'ID du client :", "Valider un pret");
    if(dlgClient.ShowModal() != wxID_OK) return;

    wxTextEntryDialog dlgMontant(this, "Montant du pret a accorder (FCFA) :", "Valider un pret", "5000.00");
    if(dlgMontant.ShowModal() != wxID_OK) return;

    double montant;
    if(!dlgMontant.GetValue().ToDouble(&montant) || montant <= 0) {
        wxMessageBox("Montant invalide !", "Erreur", wxOK | wxICON_ERROR);
        return;
    }

    if(montant > 100000) {
        wxMessageBox("Le montant maximum autorise est de 100 000 FCFA.", "Erreur",
                    wxOK | wxICON_ERROR);
        return;
    }

    wxString newId = wxString::Format("P%03d", (int)m_prets.size() + 1);
    m_prets.push_back(Pret(std::string(newId.mb_str()), montant, montant, "Actif",
                          std::string(dlgClient.GetValue().mb_str())));
    ActualiserPrets();
    wxMessageBox(wxString::Format("Pret valide avec succes !\n\nID Pret : %s\nMontant : %.2f FCFA\nClient : %s",
                newId, montant, dlgClient.GetValue()),
                "Succes", wxOK | wxICON_INFORMATION);
}

void AdminFrame::OnRefuserPret(wxCommandEvent& event)
{
    long item = listPretsAdmin->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if(item == -1) {
        wxMessageBox("Veuillez selectionner un pret a refuser/annuler.", "Information",
                    wxOK | wxICON_INFORMATION);
        return;
    }

    if(m_prets[item].etat == "Rembourse") {
        wxMessageBox("Ce pret est deja rembourse.", "Information", wxOK | wxICON_INFORMATION);
        return;
    }

    if(wxMessageBox(wxString::Format("Etes-vous sur de vouloir annuler le pret %s ?",
                    m_prets[item].idPret.c_str()),
                    "Confirmation", wxYES_NO | wxICON_QUESTION) == wxYES) {
        m_prets.erase(m_prets.begin() + item);
        ActualiserPrets();
        wxMessageBox("Pret annule avec succes !", "Succes", wxOK | wxICON_INFORMATION);
    }
}
