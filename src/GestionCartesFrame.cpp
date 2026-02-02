// ============================================
// src/GestionCartesFrame.cpp - VERSION ULTRA-MODERNE
// ============================================
#include "GestionCartesFrame.h"
#include <wx/textdlg.h>
#include <wx/sizer.h>
#include <cstdlib>
#include <ctime>

wxBEGIN_EVENT_TABLE(GestionCartesFrame, wxFrame)
    EVT_BUTTON(ID_ActiverCarte, GestionCartesFrame::OnActiver)
    EVT_BUTTON(ID_DesactiverCarte, GestionCartesFrame::OnDesactiver)
    EVT_BUTTON(ID_BloquerCarte, GestionCartesFrame::OnBloquer)
    EVT_BUTTON(ID_DemanderCarte, GestionCartesFrame::OnDemanderCarte)
    EVT_BUTTON(ID_VoirDetails, GestionCartesFrame::OnVoirDetails)
wxEND_EVENT_TABLE()

GestionCartesFrame::GestionCartesFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(1100, 750))
{
    srand(static_cast<unsigned int>(time(NULL)));

    m_cartes.push_back(CarteBancaire("4532-1234-5678-9010", "Visa", "Active", "FR001-123-456"));
    m_cartes.push_back(CarteBancaire("5425-2334-5566-7788", "MasterCard", "Bloquee", "FR001-123-456"));
    m_cartes.push_back(CarteBancaire("4916-3456-7890-1234", "Visa", "Active", "FR002-789-012"));

    CreerInterface();
}

void GestionCartesFrame::CreerInterface()
{
    wxPanel* mainPanel = new wxPanel(this, wxID_ANY);
    mainPanel->SetBackgroundColour(wxColour(236, 240, 241));

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // ==================== HEADER VIOLET ====================
    wxPanel* headerPanel = new wxPanel(mainPanel, wxID_ANY);
    headerPanel->SetBackgroundColour(wxColour(142, 68, 173)); // Violet elegant
    headerPanel->SetMinSize(wxSize(-1, 100));

    wxBoxSizer* headerSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* lblTitre = new wxStaticText(headerPanel, wxID_ANY, "  MES CARTES BANCAIRES");
    wxFont fontTitre(24, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    lblTitre->SetFont(fontTitre);
    lblTitre->SetForegroundColour(*wxWHITE);
    headerSizer->Add(lblTitre, 0, wxALL, 15);

    wxStaticText* lblSubtitle = new wxStaticText(headerPanel, wxID_ANY,
        "  Gerez vos cartes bancaires en toute securite");
    wxFont fontSubtitle(11, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    lblSubtitle->SetFont(fontSubtitle);
    lblSubtitle->SetForegroundColour(wxColour(230, 230, 230));
    headerSizer->Add(lblSubtitle, 0, wxLEFT | wxBOTTOM, 15);

    headerPanel->SetSizer(headerSizer);
    mainSizer->Add(headerPanel, 0, wxEXPAND);

    // ==================== STATISTIQUES ====================
    wxPanel* statsPanel = new wxPanel(mainPanel, wxID_ANY);
    statsPanel->SetBackgroundColour(wxColour(236, 240, 241));

    wxBoxSizer* statsSizer = new wxBoxSizer(wxHORIZONTAL);

    // Carte Total
    wxPanel* statsTotal = new wxPanel(statsPanel, wxID_ANY);
    statsTotal->SetBackgroundColour(wxColour(52, 152, 219));
    statsTotal->SetMinSize(wxSize(280, 100));
    wxBoxSizer* s1 = new wxBoxSizer(wxVERTICAL);
    wxStaticText* t1 = new wxStaticText(statsTotal, wxID_ANY, "CARTES TOTALES");
    wxFont f1(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    t1->SetFont(f1);
    t1->SetForegroundColour(wxColour(189, 195, 199));
    s1->Add(t1, 0, wxALIGN_CENTER | wxTOP, 20);
    lblNombreCartes = new wxStaticText(statsTotal, wxID_ANY, "0");
    wxFont fv1(30, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    lblNombreCartes->SetFont(fv1);
    lblNombreCartes->SetForegroundColour(*wxWHITE);
    s1->Add(lblNombreCartes, 0, wxALIGN_CENTER | wxBOTTOM, 20);
    statsTotal->SetSizer(s1);
    statsSizer->Add(statsTotal, 1, wxEXPAND | wxALL, 15);

    // Carte Actives
    wxPanel* statsActives = new wxPanel(statsPanel, wxID_ANY);
    statsActives->SetBackgroundColour(wxColour(46, 204, 113));
    statsActives->SetMinSize(wxSize(280, 100));
    wxBoxSizer* s2 = new wxBoxSizer(wxVERTICAL);
    wxStaticText* t2 = new wxStaticText(statsActives, wxID_ANY, "CARTES ACTIVES");
    t2->SetFont(f1);
    t2->SetForegroundColour(wxColour(189, 195, 199));
    s2->Add(t2, 0, wxALIGN_CENTER | wxTOP, 20);
    lblCartesActives = new wxStaticText(statsActives, wxID_ANY, "0");
    lblCartesActives->SetFont(fv1);
    lblCartesActives->SetForegroundColour(*wxWHITE);
    s2->Add(lblCartesActives, 0, wxALIGN_CENTER | wxBOTTOM, 20);
    statsActives->SetSizer(s2);
    statsSizer->Add(statsActives, 1, wxEXPAND | wxALL, 15);

    // Carte Info
    wxPanel* statsInfo = new wxPanel(statsPanel, wxID_ANY);
    statsInfo->SetBackgroundColour(wxColour(230, 126, 34));
    statsInfo->SetMinSize(wxSize(280, 100));
    wxBoxSizer* s3 = new wxBoxSizer(wxVERTICAL);
    wxStaticText* t3 = new wxStaticText(statsInfo, wxID_ANY, "SECURITE");
    t3->SetFont(f1);
    t3->SetForegroundColour(wxColour(189, 195, 199));
    s3->Add(t3, 0, wxALIGN_CENTER | wxTOP, 20);
    wxStaticText* v3 = new wxStaticText(statsInfo, wxID_ANY, "100%");
    v3->SetFont(fv1);
    v3->SetForegroundColour(*wxWHITE);
    s3->Add(v3, 0, wxALIGN_CENTER | wxBOTTOM, 20);
    statsInfo->SetSizer(s3);
    statsSizer->Add(statsInfo, 1, wxEXPAND | wxALL, 15);

    statsPanel->SetSizer(statsSizer);
    mainSizer->Add(statsPanel, 0, wxEXPAND);

    // ==================== ZONE PRINCIPALE ====================
    wxPanel* contentPanel = new wxPanel(mainPanel, wxID_ANY);
    contentPanel->SetBackgroundColour(*wxWHITE);

    wxBoxSizer* contentSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* lblListeTitre = new wxStaticText(contentPanel, wxID_ANY, "  VOS CARTES BANCAIRES");
    wxFont fontListe(14, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    lblListeTitre->SetFont(fontListe);
    lblListeTitre->SetForegroundColour(wxColour(52, 73, 94));
    contentSizer->Add(lblListeTitre, 0, wxALL, 20);

    listCartes = new wxListCtrl(contentPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                wxLC_REPORT | wxLC_SINGLE_SEL | wxBORDER_SIMPLE);
    listCartes->SetBackgroundColour(wxColour(250, 250, 250));
    listCartes->InsertColumn(0, "Numero de carte", wxLIST_FORMAT_LEFT, 250);
    listCartes->InsertColumn(1, "Type", wxLIST_FORMAT_LEFT, 150);
    listCartes->InsertColumn(2, "Etat", wxLIST_FORMAT_CENTER, 130);
    listCartes->InsertColumn(3, "Compte associe", wxLIST_FORMAT_LEFT, 200);
    listCartes->InsertColumn(4, "Statut", wxLIST_FORMAT_CENTER, 150);

    ActualiserCartes();
    contentSizer->Add(listCartes, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 20);

    // ==================== BOUTONS D'ACTION ====================
    wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
    wxFont fontBtn(11, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

    wxButton* btnActiver = new wxButton(contentPanel, ID_ActiverCarte, "Activer",
                                       wxDefaultPosition, wxSize(150, 50));
    btnActiver->SetBackgroundColour(wxColour(46, 204, 113));
    btnActiver->SetForegroundColour(*wxWHITE);
    btnActiver->SetFont(fontBtn);
    btnSizer->Add(btnActiver, 0, wxALL, 5);

    wxButton* btnDesactiver = new wxButton(contentPanel, ID_DesactiverCarte, "Desactiver",
                                          wxDefaultPosition, wxSize(150, 50));
    btnDesactiver->SetBackgroundColour(wxColour(243, 156, 18));
    btnDesactiver->SetForegroundColour(*wxWHITE);
    btnDesactiver->SetFont(fontBtn);
    btnSizer->Add(btnDesactiver, 0, wxALL, 5);

    wxButton* btnBloquer = new wxButton(contentPanel, ID_BloquerCarte, "Bloquer",
                                       wxDefaultPosition, wxSize(150, 50));
    btnBloquer->SetBackgroundColour(wxColour(231, 76, 60));
    btnBloquer->SetForegroundColour(*wxWHITE);
    btnBloquer->SetFont(fontBtn);
    btnSizer->Add(btnBloquer, 0, wxALL, 5);

    wxButton* btnDemander = new wxButton(contentPanel, ID_DemanderCarte, "Nouvelle carte",
                                        wxDefaultPosition, wxSize(180, 50));
    btnDemander->SetBackgroundColour(wxColour(52, 152, 219));
    btnDemander->SetForegroundColour(*wxWHITE);
    btnDemander->SetFont(fontBtn);
    btnSizer->Add(btnDemander, 0, wxALL, 5);

    wxButton* btnDetails = new wxButton(contentPanel, ID_VoirDetails, "Voir details",
                                       wxDefaultPosition, wxSize(150, 50));
    btnDetails->SetBackgroundColour(wxColour(155, 89, 182));
    btnDetails->SetForegroundColour(*wxWHITE);
    btnDetails->SetFont(fontBtn);
    btnSizer->Add(btnDetails, 0, wxALL, 5);

    contentSizer->Add(btnSizer, 0, wxALIGN_CENTER | wxBOTTOM, 20);

    contentPanel->SetSizer(contentSizer);
    mainSizer->Add(contentPanel, 1, wxEXPAND | wxALL, 15);

    mainPanel->SetSizer(mainSizer);
    ActualiserStatistiques();
}

void GestionCartesFrame::ActualiserCartes()
{
    listCartes->DeleteAllItems();
    for(size_t i = 0; i < m_cartes.size(); ++i) {
        long idx = listCartes->InsertItem(i, wxString(m_cartes[i].numeroCarte.c_str()));
        listCartes->SetItem(idx, 1, wxString(m_cartes[i].type.c_str()));
        listCartes->SetItem(idx, 2, wxString(m_cartes[i].etat.c_str()));
        listCartes->SetItem(idx, 3, wxString(m_cartes[i].numeroCompte.c_str()));

        // Statut visuel
        if(m_cartes[i].etat == "Active") {
            listCartes->SetItem(idx, 4, "Utilisable");
            listCartes->SetItemTextColour(idx, wxColour(39, 174, 96));
        } else if(m_cartes[i].etat == "Bloquee") {
            listCartes->SetItem(idx, 4, "Bloquee - Inutilisable");
            listCartes->SetItemTextColour(idx, wxColour(231, 76, 60));
        } else {
            listCartes->SetItem(idx, 4, "Desactivee");
            listCartes->SetItemTextColour(idx, wxColour(243, 156, 18));
        }

        if(i % 2 == 0) {
            listCartes->SetItemBackgroundColour(idx, wxColour(248, 249, 250));
        }
    }
    ActualiserStatistiques();
}

void GestionCartesFrame::ActualiserStatistiques()
{
    int actives = 0;
    for(size_t i = 0; i < m_cartes.size(); ++i) {
        if(m_cartes[i].etat == "Active") actives++;
    }

    lblNombreCartes->SetLabel(wxString::Format("%d", (int)m_cartes.size()));
    lblCartesActives->SetLabel(wxString::Format("%d", actives));
}

void GestionCartesFrame::OnActiver(wxCommandEvent& event)
{
    long item = listCartes->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if(item == -1) {
        wxMessageBox("Veuillez selectionner une carte dans la liste.", "Information",
                    wxOK | wxICON_INFORMATION);
        return;
    }

    if(m_cartes[item].etat == "Active") {
        wxMessageBox("Cette carte est deja active.", "Information", wxOK | wxICON_INFORMATION);
        return;
    }

    m_cartes[item].etat = "Active";
    ActualiserCartes();
    wxMessageBox(wxString::Format("Carte %s activee avec succes !\n\nVous pouvez maintenant l'utiliser pour vos paiements.",
                m_cartes[item].numeroCarte.c_str()),
                "Carte activee", wxOK | wxICON_INFORMATION);
}

void GestionCartesFrame::OnDesactiver(wxCommandEvent& event)
{
    long item = listCartes->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if(item == -1) {
        wxMessageBox("Veuillez selectionner une carte dans la liste.", "Information",
                    wxOK | wxICON_INFORMATION);
        return;
    }

    if(m_cartes[item].etat == "Desactivee") {
        wxMessageBox("Cette carte est deja desactivee.", "Information", wxOK | wxICON_INFORMATION);
        return;
    }

    if(wxMessageBox("Etes-vous sur de vouloir desactiver cette carte ?\n\nVous pourrez la reactiver a tout moment.",
                   "Confirmation", wxYES_NO | wxICON_QUESTION) == wxYES) {
        m_cartes[item].etat = "Desactivee";
        ActualiserCartes();
        wxMessageBox("Carte desactivee avec succes !", "Succes", wxOK | wxICON_INFORMATION);
    }
}

void GestionCartesFrame::OnBloquer(wxCommandEvent& event)
{
    long item = listCartes->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if(item == -1) {
        wxMessageBox("Veuillez selectionner une carte dans la liste.", "Information",
                    wxOK | wxICON_INFORMATION);
        return;
    }

    if(m_cartes[item].etat == "Bloquee") {
        wxMessageBox("Cette carte est deja bloquee.", "Information", wxOK | wxICON_INFORMATION);
        return;
    }

    if(wxMessageBox("ATTENTION : Etes-vous sur de vouloir BLOQUER cette carte ?\n\n"
                   "Cette action est DEFINITIVE et irreversible.\n"
                   "Vous devrez commander une nouvelle carte.\n\n"
                   "En cas de perte ou vol, confirmez le blocage.",
                   "Blocage definitif", wxYES_NO | wxICON_WARNING) == wxYES) {
        m_cartes[item].etat = "Bloquee";
        ActualiserCartes();
        wxMessageBox("Carte bloquee avec succes !\n\n"
                    "Pour plus de securite, nous vous recommandons de commander\n"
                    "une nouvelle carte en cliquant sur 'Nouvelle carte'.",
                    "Carte bloquee", wxOK | wxICON_INFORMATION);
    }
}

void GestionCartesFrame::OnDemanderCarte(wxCommandEvent& event)
{
    wxString choices[] = {"Visa Classic", "Visa Premier", "MasterCard Standard", "MasterCard Gold"};
    wxSingleChoiceDialog dlg(this,
        "Choisissez le type de carte :\n\n"
        "- Visa Classic / MasterCard Standard : Gratuite\n"
        "- Visa Premier / MasterCard Gold : 5 EUR/mois\n",
        "Commander une nouvelle carte", 4, choices);

    if(dlg.ShowModal() == wxID_OK) {
        wxString type = dlg.GetStringSelection();
        if(type.Find("Premier") != wxNOT_FOUND || type.Find("Gold") != wxNOT_FOUND) {
            type = (type.Find("Visa") != wxNOT_FOUND) ? "Visa" : "MasterCard";
        } else {
            type = (type.Find("Visa") != wxNOT_FOUND) ? "Visa" : "MasterCard";
        }

        wxString newNum = wxString::Format("%04d-%04d-%04d-%04d",
                                          4000 + rand() % 1000, rand() % 10000,
                                          rand() % 10000, rand() % 10000);

        m_cartes.push_back(CarteBancaire(std::string(newNum.mb_str()),
                                        std::string(type.mb_str()),
                                        "Active", "FR001-123-456"));
        ActualiserCartes();

        wxMessageBox(wxString::Format("Nouvelle carte commandee avec succes !\n\n"
                                     "Type : %s\n"
                                     "Numero : %s\n\n"
                                     "Vous la recevrez sous 5 a 7 jours ouvres a votre domicile.\n"
                                     "Le code PIN vous sera envoye separement par courrier securise.",
                                     dlg.GetStringSelection(), newNum),
                    "Commande confirmee", wxOK | wxICON_INFORMATION);
    }
}

void GestionCartesFrame::OnVoirDetails(wxCommandEvent& event)
{
    long item = listCartes->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if(item == -1) {
        wxMessageBox("Veuillez selectionner une carte dans la liste.", "Information",
                    wxOK | wxICON_INFORMATION);
        return;
    }

    wxString details = wxString::Format(
        "========== DETAILS DE LA CARTE ==========\n\n"
        "Numero : %s\n"
        "Type : %s\n"
        "Etat : %s\n"
        "Compte associe : %s\n\n"
        "Date d'expiration : 12/2028\n"
        "Code de securite : ***\n"
        "Plafond mensuel : 3000 EUR\n"
        "Plafond hebdomadaire : 1000 EUR\n"
        "Plafond journalier : 500 EUR\n\n"
        "Options activees :\n"
        "  - Paiement sans contact\n"
        "  - Paiement en ligne\n"
        "  - Retrait ATM international\n\n"
        "Pour modifier vos plafonds, contactez votre conseiller.",
        m_cartes[item].numeroCarte.c_str(),
        m_cartes[item].type.c_str(),
        m_cartes[item].etat.c_str(),
        m_cartes[item].numeroCompte.c_str()
    );

    wxMessageBox(details, "Details de la carte", wxOK | wxICON_INFORMATION);
}
