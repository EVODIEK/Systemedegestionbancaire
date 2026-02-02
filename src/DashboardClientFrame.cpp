// src/DashboardClientFrame.cpp - VERSION COMPLETE ET ULTRA-ATTRACTIVE
#include "DashboardClientFrame.h"
#include "GestionCartesFrame.h"
#include "GestionPretsFrame.h"
#include <wx/textdlg.h>
#include <wx/msgdlg.h>
#include <wx/sizer.h>

wxBEGIN_EVENT_TABLE(DashboardClientFrame, wxFrame)
    EVT_BUTTON(ID_Depot, DashboardClientFrame::OnDepot)
    EVT_BUTTON(ID_Retrait, DashboardClientFrame::OnRetrait)
    EVT_BUTTON(ID_Virement, DashboardClientFrame::OnVirement)
    EVT_BUTTON(ID_GererCartes, DashboardClientFrame::OnGererCartes)
    EVT_BUTTON(ID_GererPrets, DashboardClientFrame::OnGererPrets)
wxEND_EVENT_TABLE()

DashboardClientFrame::DashboardClientFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(1150, 800))
{
    // Initialiser TOUTES les donnees AVANT de creer l'interface
    m_comptes.push_back(CompteBancaire("FR001-123-456", "Compte Courant", 1500.50f, "001"));
    m_comptes.push_back(CompteBancaire("FR002-789-012", "Compte Epargne", 3200.00f, "001"));

    m_cartes.push_back(CarteBancaire("4532-1234-5678-9010", "Visa", "Active", "FR001-123-456"));
    m_cartes.push_back(CarteBancaire("5425-2334-5566-7788", "MasterCard", "Bloquee", "FR001-123-456"));

    m_prets.push_back(Pret("P001", 5000.0f, 3500.0f, "Actif", "001"));
    m_prets.push_back(Pret("P002", 10000.0f, 2500.0f, "Actif", "001"));

    CreerInterface();
}

void DashboardClientFrame::CreerInterface()
{
    // ==================== PANEL PRINCIPAL ====================
    wxPanel* panel = new wxPanel(this, wxID_ANY);
    panel->SetBackgroundColour(wxColour(240, 242, 245));

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // ==================== HEADER BLEU MODERNE ====================
    wxPanel* headerPanel = new wxPanel(panel, wxID_ANY);
    headerPanel->SetBackgroundColour(wxColour(41, 128, 185));
    headerPanel->SetMinSize(wxSize(-1, 70));

    wxBoxSizer* headerSizer = new wxBoxSizer(wxHORIZONTAL);

    // Logo et titre
    wxStaticText* lblTitre = new wxStaticText(headerPanel, wxID_ANY, "  EvoBank - Mon Espace Bancaire");
    wxFont fontTitre(20, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    lblTitre->SetFont(fontTitre);
    lblTitre->SetForegroundColour(*wxWHITE);
    headerSizer->Add(lblTitre, 1, wxALIGN_CENTER_VERTICAL | wxALL, 15);

    // Nom utilisateur
    wxStaticText* lblUser = new wxStaticText(headerPanel, wxID_ANY, "Bienvenue, Evodie  ");
    wxFont fontUser(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    lblUser->SetFont(fontUser);
    lblUser->SetForegroundColour(wxColour(236, 240, 241));
    headerSizer->Add(lblUser, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 20);

    headerPanel->SetSizer(headerSizer);
    mainSizer->Add(headerPanel, 0, wxEXPAND);

    // ==================== CARTE SOLDE TOTAL ====================
    wxPanel* soldePanel = new wxPanel(panel, wxID_ANY);
    soldePanel->SetBackgroundColour(wxColour(52, 152, 219));
    soldePanel->SetMinSize(wxSize(-1, 100));

    // Calcul du solde total
    float soldeTotal = 0;
    for(size_t i = 0; i < m_comptes.size(); ++i) {
        soldeTotal += m_comptes[i].solde;
    }

    wxBoxSizer* soldeSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* lblSoldeTitle = new wxStaticText(soldePanel, wxID_ANY, "SOLDE TOTAL DE VOS COMPTES");
    wxFont fontSoldeTitle(11, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    lblSoldeTitle->SetFont(fontSoldeTitle);
    lblSoldeTitle->SetForegroundColour(wxColour(189, 195, 199));
    soldeSizer->Add(lblSoldeTitle, 0, wxALIGN_CENTER | wxTOP, 15);

    wxStaticText* lblSoldeValue = new wxStaticText(soldePanel, wxID_ANY,
                                                   wxString::Format("%.2f FCFA", soldeTotal));
    wxFont fontSoldeValue(32, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    lblSoldeValue->SetFont(fontSoldeValue);
    lblSoldeValue->SetForegroundColour(*wxWHITE);
    soldeSizer->Add(lblSoldeValue, 0, wxALIGN_CENTER | wxBOTTOM, 15);

    soldePanel->SetSizer(soldeSizer);
    mainSizer->Add(soldePanel, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 20);

    // ==================== SECTION COMPTES BANCAIRES ====================
    wxPanel* comptesPanel = new wxPanel(panel, wxID_ANY);
    comptesPanel->SetBackgroundColour(*wxWHITE);

    wxBoxSizer* comptesSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* lblComptes = new wxStaticText(comptesPanel, wxID_ANY, "  MES COMPTES BANCAIRES");
    wxFont fontSection(14, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    lblComptes->SetFont(fontSection);
    lblComptes->SetForegroundColour(wxColour(52, 73, 94));
    comptesSizer->Add(lblComptes, 0, wxALL, 15);

    listComptes = new wxListCtrl(comptesPanel, wxID_ANY, wxDefaultPosition, wxSize(-1, 150),
                                 wxLC_REPORT | wxLC_SINGLE_SEL | wxBORDER_NONE);
    listComptes->SetBackgroundColour(wxColour(250, 250, 250));
    listComptes->InsertColumn(0, "Numero de compte", wxLIST_FORMAT_LEFT, 280);
    listComptes->InsertColumn(1, "Type de compte", wxLIST_FORMAT_LEFT, 200);
    listComptes->InsertColumn(2, "Solde (FCFA)", wxLIST_FORMAT_RIGHT, 180);
    listComptes->InsertColumn(3, "Statut", wxLIST_FORMAT_CENTER, 120);

    wxFont fontListe(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    listComptes->SetFont(fontListe);

    for(size_t i = 0; i < m_comptes.size(); ++i) {
        long idx = listComptes->InsertItem(i, m_comptes[i].numeroCompte);
        listComptes->SetItem(idx, 1, m_comptes[i].typeCompte);
        listComptes->SetItem(idx, 2, wxString::Format("%.2f", m_comptes[i].solde));
        listComptes->SetItem(idx, 3, "Actif");

        // Colorer les lignes alternees
        if(i % 2 == 0) {
            listComptes->SetItemBackgroundColour(idx, wxColour(248, 249, 250));
        }
    }

    comptesSizer->Add(listComptes, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 15);
    comptesPanel->SetSizer(comptesSizer);
    mainSizer->Add(comptesPanel, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 20);

    // ==================== BOUTONS D'OPERATIONS XXL ====================
    wxBoxSizer* btnSizer1 = new wxBoxSizer(wxHORIZONTAL);
    wxFont fontBtn(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

    btnDepot = new wxButton(panel, ID_Depot, "  EFFECTUER UN DEPOT", wxDefaultPosition, wxSize(250, 55));
    btnDepot->SetBackgroundColour(wxColour(46, 204, 113));
    btnDepot->SetForegroundColour(*wxWHITE);
    btnDepot->SetFont(fontBtn);
    btnSizer1->Add(btnDepot, 0, wxALL, 10);

    btnRetrait = new wxButton(panel, ID_Retrait, "  EFFECTUER UN RETRAIT", wxDefaultPosition, wxSize(250, 55));
    btnRetrait->SetBackgroundColour(wxColour(231, 76, 60));
    btnRetrait->SetForegroundColour(*wxWHITE);
    btnRetrait->SetFont(fontBtn);
    btnSizer1->Add(btnRetrait, 0, wxALL, 10);

    btnVirement = new wxButton(panel, ID_Virement, "  FAIRE UN VIREMENT", wxDefaultPosition, wxSize(250, 55));
    btnVirement->SetBackgroundColour(wxColour(52, 152, 219));
    btnVirement->SetForegroundColour(*wxWHITE);
    btnVirement->SetFont(fontBtn);
    btnSizer1->Add(btnVirement, 0, wxALL, 10);

    mainSizer->Add(btnSizer1, 0, wxALIGN_CENTER | wxTOP, 10);

    // ==================== SECTION CARTES ET PRETS (2 COLONNES) ====================
    wxBoxSizer* doubleSizer = new wxBoxSizer(wxHORIZONTAL);

    // === COLONNE CARTES ===
    wxPanel* cartesPanel = new wxPanel(panel, wxID_ANY);
    cartesPanel->SetBackgroundColour(*wxWHITE);

    wxBoxSizer* cartesSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* lblCartes = new wxStaticText(cartesPanel, wxID_ANY, "  MES CARTES BANCAIRES");
    lblCartes->SetFont(fontSection);
    lblCartes->SetForegroundColour(wxColour(52, 73, 94));
    cartesSizer->Add(lblCartes, 0, wxALL, 15);

    listCartes = new wxListCtrl(cartesPanel, wxID_ANY, wxDefaultPosition, wxSize(-1, 130),
                                wxLC_REPORT | wxLC_SINGLE_SEL | wxBORDER_NONE);
    listCartes->SetBackgroundColour(wxColour(250, 250, 250));
    listCartes->InsertColumn(0, "Numero de carte", wxLIST_FORMAT_LEFT, 220);
    listCartes->InsertColumn(1, "Type", wxLIST_FORMAT_LEFT, 100);
    listCartes->InsertColumn(2, "Etat", wxLIST_FORMAT_CENTER, 100);
    listCartes->SetFont(fontListe);

    for(size_t i = 0; i < m_cartes.size(); ++i) {
        long idx = listCartes->InsertItem(i, m_cartes[i].numeroCarte);
        listCartes->SetItem(idx, 1, m_cartes[i].type);
        listCartes->SetItem(idx, 2, m_cartes[i].etat);

        // Colorier selon l'etat
        if(m_cartes[i].etat == "Active") {
            listCartes->SetItemTextColour(idx, wxColour(39, 174, 96));
        } else {
            listCartes->SetItemTextColour(idx, wxColour(231, 76, 60));
        }

        if(i % 2 == 0) {
            listCartes->SetItemBackgroundColour(idx, wxColour(248, 249, 250));
        }
    }

    cartesSizer->Add(listCartes, 0, wxEXPAND | wxLEFT | wxRIGHT, 15);

    btnGererCartes = new wxButton(cartesPanel, ID_GererCartes, "Gerer mes cartes",
                                  wxDefaultPosition, wxSize(-1, 45));
    btnGererCartes->SetBackgroundColour(wxColour(155, 89, 182));
    btnGererCartes->SetForegroundColour(*wxWHITE);
    wxFont fontBtnMedium(11, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    btnGererCartes->SetFont(fontBtnMedium);
    cartesSizer->Add(btnGererCartes, 0, wxEXPAND | wxALL, 15);

    cartesPanel->SetSizer(cartesSizer);
    doubleSizer->Add(cartesPanel, 1, wxEXPAND | wxRIGHT, 10);

    // === COLONNE PRETS ===
    wxPanel* pretsPanel = new wxPanel(panel, wxID_ANY);
    pretsPanel->SetBackgroundColour(*wxWHITE);

    wxBoxSizer* pretsSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* lblPrets = new wxStaticText(pretsPanel, wxID_ANY, "  MES PRETS EN COURS");
    lblPrets->SetFont(fontSection);
    lblPrets->SetForegroundColour(wxColour(52, 73, 94));
    pretsSizer->Add(lblPrets, 0, wxALL, 15);

    listPrets = new wxListCtrl(pretsPanel, wxID_ANY, wxDefaultPosition, wxSize(-1, 130),
                               wxLC_REPORT | wxLC_SINGLE_SEL | wxBORDER_NONE);
    listPrets->SetBackgroundColour(wxColour(250, 250, 250));
    listPrets->InsertColumn(0, "ID Pret", wxLIST_FORMAT_LEFT, 90);
    listPrets->InsertColumn(1, "Montant Initial", wxLIST_FORMAT_RIGHT, 130);
    listPrets->InsertColumn(2, "Reste a payer", wxLIST_FORMAT_RIGHT, 130);
    listPrets->SetFont(fontListe);

    for(size_t i = 0; i < m_prets.size(); ++i) {
        long idx = listPrets->InsertItem(i, m_prets[i].idPret);
        listPrets->SetItem(idx, 1, wxString::Format("%.0f FCFA", m_prets[i].montantInitial));
        listPrets->SetItem(idx, 2, wxString::Format("%.0f FCFA", m_prets[i].montantRestant));

        if(i % 2 == 0) {
            listPrets->SetItemBackgroundColour(idx, wxColour(248, 249, 250));
        }
    }

    pretsSizer->Add(listPrets, 0, wxEXPAND | wxLEFT | wxRIGHT, 15);

    btnGererPrets = new wxButton(pretsPanel, ID_GererPrets, "Gerer mes prets",
                                 wxDefaultPosition, wxSize(-1, 45));
    btnGererPrets->SetBackgroundColour(wxColour(230, 126, 34));
    btnGererPrets->SetForegroundColour(*wxWHITE);
    btnGererPrets->SetFont(fontBtnMedium);
    pretsSizer->Add(btnGererPrets, 0, wxEXPAND | wxALL, 15);

    pretsPanel->SetSizer(pretsSizer);
    doubleSizer->Add(pretsPanel, 1, wxEXPAND | wxLEFT, 10);

    mainSizer->Add(doubleSizer, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 20);

    // Espaceur en bas
    mainSizer->AddSpacer(20);

    panel->SetSizer(mainSizer);
}

void DashboardClientFrame::ActualiserComptes()
{
    if(!listComptes) return;

    listComptes->DeleteAllItems();
    for(size_t i = 0; i < m_comptes.size(); ++i) {
        long idx = listComptes->InsertItem(i, m_comptes[i].numeroCompte);
        listComptes->SetItem(idx, 1, m_comptes[i].typeCompte);
        listComptes->SetItem(idx, 2, wxString::Format("%.2f", m_comptes[i].solde));
        listComptes->SetItem(idx, 3, "Actif");

        if(i % 2 == 0) {
            listComptes->SetItemBackgroundColour(idx, wxColour(248, 249, 250));
        }
    }
}

void DashboardClientFrame::OnDepot(wxCommandEvent& event)
{
    long item = listComptes->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if(item == -1) {
        wxMessageBox("Veuillez selectionner un compte dans la liste ci-dessus.",
                    "Information", wxOK | wxICON_INFORMATION);
        return;
    }

    wxTextEntryDialog dlg(this,
        wxString::Format("Compte : %s\nSolde actuel : %.2f FCFA\n\nEntrez le montant a deposer :",
                        m_comptes[item].numeroCompte, m_comptes[item].solde),
        "Effectuer un depot", "100.00");

    if(dlg.ShowModal() == wxID_OK) {
        double montant;
        if(!dlg.GetValue().ToDouble(&montant) || montant <= 0) {
            wxMessageBox("Montant invalide ! Veuillez entrer un montant superieur a 0.",
                        "Erreur", wxOK | wxICON_ERROR);
            return;
        }

        m_comptes[item].deposer(montant);
        ActualiserComptes();

        wxMessageBox(wxString::Format(
            "DEPOT EFFECTUE AVEC SUCCES !\n\n"
            "Compte : %s\n"
            "Montant depose : %.2f FCFA\n"
            "Nouveau solde : %.2f FCFA",
            m_comptes[item].numeroCompte, montant, m_comptes[item].solde),
            "Succes", wxOK | wxICON_INFORMATION);
    }
}

void DashboardClientFrame::OnRetrait(wxCommandEvent& event)
{
    long item = listComptes->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if(item == -1) {
        wxMessageBox("Veuillez selectionner un compte dans la liste ci-dessus.",
                    "Information", wxOK | wxICON_INFORMATION);
        return;
    }

    wxTextEntryDialog dlg(this,
        wxString::Format("Compte : %s\nSolde disponible : %.2f FCFA\n\nEntrez le montant a retirer :",
                        m_comptes[item].numeroCompte, m_comptes[item].solde),
        "Effectuer un retrait", "50.00");

    if(dlg.ShowModal() == wxID_OK) {
        double montant;
        if(!dlg.GetValue().ToDouble(&montant) || montant <= 0) {
            wxMessageBox("Montant invalide ! Veuillez entrer un montant superieur a 0.",
                        "Erreur", wxOK | wxICON_ERROR);
            return;
        }

        if(montant > m_comptes[item].solde) {
            wxMessageBox(wxString::Format(
                "SOLDE INSUFFISANT !\n\n"
                "Solde disponible : %.2f FCFA\n"
                "Montant demande : %.2f FCFA\n"
                "Difference : %.2f FCFA",
                m_comptes[item].solde, montant, montant - m_comptes[item].solde),
                "Erreur", wxOK | wxICON_ERROR);
            return;
        }

        m_comptes[item].retirer(montant);
        ActualiserComptes();

        wxMessageBox(wxString::Format(
            "RETRAIT EFFECTUE AVEC SUCCES !\n\n"
            "Compte : %s\n"
            "Montant retire : %.2f FCFA\n"
            "Nouveau solde : %.2f FCFA",
            m_comptes[item].numeroCompte, montant, m_comptes[item].solde),
            "Succes", wxOK | wxICON_INFORMATION);
    }
}

void DashboardClientFrame::OnVirement(wxCommandEvent& event)
{
    long item = listComptes->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if(item == -1) {
        wxMessageBox("Veuillez selectionner le compte SOURCE dans la liste ci-dessus.",
                    "Information", wxOK | wxICON_INFORMATION);
        return;
    }

    // Construire la liste des comptes disponibles
    wxString listeComptes = "Comptes disponibles :\n";
    for(size_t i = 0; i < m_comptes.size(); ++i) {
        if(i != (size_t)item) {
            listeComptes += wxString::Format("- %s (%s)\n",
                m_comptes[i].numeroCompte, m_comptes[i].typeCompte);
        }
    }

    wxTextEntryDialog dlgDest(this,
        wxString::Format("Compte source : %s\nSolde : %.2f FCFA\n\n%s\nEntrez le numero du compte DESTINATAIRE :",
                        m_comptes[item].numeroCompte, m_comptes[item].solde, listeComptes),
        "Faire un virement - Etape 1/2");

    if(dlgDest.ShowModal() != wxID_OK) return;

    wxString numDest = dlgDest.GetValue();
    long targetIndex = -1;
    for(size_t i = 0; i < m_comptes.size(); ++i) {
        if(m_comptes[i].numeroCompte == numDest) {
            targetIndex = i;
            break;
        }
    }

    if(targetIndex == -1) {
        wxMessageBox("Compte destinataire introuvable !\n\nVerifiez le numero de compte.",
                    "Erreur", wxOK | wxICON_ERROR);
        return;
    }

    if(targetIndex == item) {
        wxMessageBox("Vous ne pouvez pas faire un virement vers le meme compte !",
                    "Erreur", wxOK | wxICON_ERROR);
        return;
    }

    wxTextEntryDialog dlgMontant(this,
        wxString::Format("Compte source : %s (Solde : %.2f FCFA)\n"
                        "Compte destinataire : %s\n\n"
                        "Entrez le montant du virement :",
                        m_comptes[item].numeroCompte, m_comptes[item].solde,
                        m_comptes[targetIndex].numeroCompte),
        "Faire un virement - Etape 2/2", "100.00");

    if(dlgMontant.ShowModal() == wxID_OK) {
        double montant;
        if(!dlgMontant.GetValue().ToDouble(&montant) || montant <= 0) {
            wxMessageBox("Montant invalide !", "Erreur", wxOK | wxICON_ERROR);
            return;
        }

        if(montant > m_comptes[item].solde) {
            wxMessageBox(wxString::Format(
                "SOLDE INSUFFISANT !\n\n"
                "Solde disponible : %.2f FCFA\n"
                "Montant demande : %.2f FCFA",
                m_comptes[item].solde, montant),
                "Erreur", wxOK | wxICON_ERROR);
            return;
        }

        m_comptes[item].retirer(montant);
        m_comptes[targetIndex].deposer(montant);
        ActualiserComptes();

        wxMessageBox(wxString::Format(
            "VIREMENT EFFECTUE AVEC SUCCES !\n\n"
            "De : %s\n"
            "Vers : %s\n"
            "Montant : %.2f FCFA\n\n"
            "Nouveau solde source : %.2f FCFA\n"
            "Nouveau solde destinataire : %.2f FCFA",
            m_comptes[item].numeroCompte,
            m_comptes[targetIndex].numeroCompte,
            montant,
            m_comptes[item].solde,
            m_comptes[targetIndex].solde),
            "Succes", wxOK | wxICON_INFORMATION);
    }
}

void DashboardClientFrame::OnGererCartes(wxCommandEvent& event)
{
    GestionCartesFrame* gestion = new GestionCartesFrame("Gestion des cartes bancaires");
    gestion->Show();
}

void DashboardClientFrame::OnGererPrets(wxCommandEvent& event)
{
    GestionPretsFrame* gestion = new GestionPretsFrame("Gestion des prets");
    gestion->Show();
}
