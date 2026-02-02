// src/GestionComptesFrame.cpp - VERSION SÉCURISÉE
#include "GestionComptesFrame.h"
#include <wx/textdlg.h>
#include <wx/sizer.h>

wxBEGIN_EVENT_TABLE(GestionComptesFrame, wxFrame)
    EVT_BUTTON(ID_DepotCompte, GestionComptesFrame::OnDepot)
    EVT_BUTTON(ID_RetraitCompte, GestionComptesFrame::OnRetrait)
    EVT_BUTTON(ID_VirementCompte, GestionComptesFrame::OnVirement)
    EVT_BUTTON(ID_CreerCompte, GestionComptesFrame::OnCreerCompte)
wxEND_EVENT_TABLE()

GestionComptesFrame::GestionComptesFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(950, 650))
{
    // Données par défaut
    m_comptes.push_back(CompteBancaire("FR001-123-456", "Compte Courant", 1500.50f, "001"));
    m_comptes.push_back(CompteBancaire("FR002-789-012", "Compte Épargne", 3200.00f, "001"));

    CreerInterface();
}

void GestionComptesFrame::CreerInterface()
{
    wxPanel* panel = new wxPanel(this, wxID_ANY);
    panel->SetBackgroundColour(wxColour(245, 247, 250));

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Titre
    wxStaticText* lblTitre = new wxStaticText(panel, wxID_ANY, "Gestion de mes Comptes Bancaires");
    wxFont fontTitre(16, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    lblTitre->SetFont(fontTitre);
    lblTitre->SetForegroundColour(wxColour(30, 60, 114));
    mainSizer->Add(lblTitre, 0, wxALL | wxALIGN_LEFT, 20);

    // Liste des comptes
    listComptes = new wxListCtrl(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                 wxLC_REPORT | wxLC_SINGLE_SEL);
    listComptes->SetBackgroundColour(*wxWHITE);
    listComptes->InsertColumn(0, "Numéro de compte", wxLIST_FORMAT_LEFT, 220);
    listComptes->InsertColumn(1, "Type de compte", wxLIST_FORMAT_LEFT, 180);
    listComptes->InsertColumn(2, "Solde (€)", wxLIST_FORMAT_RIGHT, 150);
    listComptes->InsertColumn(3, "Statut", wxLIST_FORMAT_CENTER, 120);

    mainSizer->Add(listComptes, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 20);

    ActualiserComptes();

    // Sizer pour les boutons
    wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
    wxFont fontBtn(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

    wxButton* btnDepot = new wxButton(panel, ID_DepotCompte, "Effectuer un Dépôt",
                                      wxDefaultPosition, wxSize(180, 45));
    btnDepot->SetBackgroundColour(wxColour(46, 204, 113));
    btnDepot->SetForegroundColour(*wxWHITE);
    btnDepot->SetFont(fontBtn);
    btnSizer->Add(btnDepot, 0, wxALL, 5);

    wxButton* btnRetrait = new wxButton(panel, ID_RetraitCompte, "Effectuer un Retrait",
                                        wxDefaultPosition, wxSize(180, 45));
    btnRetrait->SetBackgroundColour(wxColour(231, 76, 60));
    btnRetrait->SetForegroundColour(*wxWHITE);
    btnRetrait->SetFont(fontBtn);
    btnSizer->Add(btnRetrait, 0, wxALL, 5);

    wxButton* btnVirement = new wxButton(panel, ID_VirementCompte, "Faire un Virement",
                                         wxDefaultPosition, wxSize(180, 45));
    btnVirement->SetBackgroundColour(wxColour(52, 152, 219));
    btnVirement->SetForegroundColour(*wxWHITE);
    btnVirement->SetFont(fontBtn);
    btnSizer->Add(btnVirement, 0, wxALL, 5);

    wxButton* btnCreer = new wxButton(panel, ID_CreerCompte, "Ouvrir un Compte",
                                      wxDefaultPosition, wxSize(180, 45));
    btnCreer->SetBackgroundColour(wxColour(155, 89, 182));
    btnCreer->SetForegroundColour(*wxWHITE);
    btnCreer->SetFont(fontBtn);
    btnSizer->Add(btnCreer, 0, wxALL, 5);

    mainSizer->Add(btnSizer, 0, wxALIGN_CENTER | wxBOTTOM, 20);

    panel->SetSizer(mainSizer);
}

void GestionComptesFrame::ActualiserComptes()
{
    if(!listComptes) return;

    listComptes->DeleteAllItems();
    for(size_t i = 0; i < m_comptes.size(); ++i) {
        long idx = listComptes->InsertItem(i, m_comptes[i].numeroCompte);
        listComptes->SetItem(idx, 1, m_comptes[i].typeCompte);
        listComptes->SetItem(idx, 2, wxString::Format("%.2f", m_comptes[i].solde));
        listComptes->SetItem(idx, 3, "Actif");
    }
}

void GestionComptesFrame::OnDepot(wxCommandEvent& event)
{
    long item = listComptes->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if(item == -1) {
        wxMessageBox("Veuillez sélectionner un compte dans la liste.", "Information",
                     wxOK | wxICON_INFORMATION);
        return;
    }

    wxTextEntryDialog dlg(this, "Entrez le montant à déposer (€) :", "Dépôt", "100.00");
    if(dlg.ShowModal() == wxID_OK) {
        double montant;
        if(!dlg.GetValue().ToDouble(&montant) || montant <= 0) {
            wxMessageBox("Montant invalide !", "Erreur", wxOK | wxICON_ERROR);
            return;
        }

        m_comptes[item].deposer(montant);
        ActualiserComptes();
        wxMessageBox(wxString::Format("Dépôt de %.2f € effectué avec succès !\nNouveau solde : %.2f €",
                     montant, m_comptes[item].solde), "Succès", wxOK | wxICON_INFORMATION);
    }
}

void GestionComptesFrame::OnRetrait(wxCommandEvent& event)
{
    long item = listComptes->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if(item == -1) {
        wxMessageBox("Veuillez sélectionner un compte dans la liste.", "Information",
                     wxOK | wxICON_INFORMATION);
        return;
    }

    wxTextEntryDialog dlg(this, "Entrez le montant à retirer (€) :", "Retrait", "50.00");
    if(dlg.ShowModal() == wxID_OK) {
        double montant;
        if(!dlg.GetValue().ToDouble(&montant) || montant <= 0) {
            wxMessageBox("Montant invalide !", "Erreur", wxOK | wxICON_ERROR);
            return;
        }

        if(montant > m_comptes[item].solde) {
            wxMessageBox("Solde insuffisant !", "Erreur", wxOK | wxICON_ERROR);
            return;
        }

        m_comptes[item].retirer(montant);
        ActualiserComptes();
        wxMessageBox(wxString::Format("Retrait de %.2f € effectué avec succès !\nNouveau solde : %.2f €",
                     montant, m_comptes[item].solde), "Succès", wxOK | wxICON_INFORMATION);
    }
}

void GestionComptesFrame::OnVirement(wxCommandEvent& event)
{
    long item = listComptes->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if(item == -1) {
        wxMessageBox("Veuillez sélectionner le compte source.", "Information",
                     wxOK | wxICON_INFORMATION);
        return;
    }

    wxTextEntryDialog dlgDest(this, "Entrez le numéro du compte destinataire :", "Virement");
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
        wxMessageBox("Compte destinataire introuvable !", "Erreur", wxOK | wxICON_ERROR);
        return;
    }

    wxTextEntryDialog dlgMontant(this, "Entrez le montant du virement (€) :", "Virement", "100.00");
    if(dlgMontant.ShowModal() == wxID_OK) {
        double montant;
        if(!dlgMontant.GetValue().ToDouble(&montant) || montant <= 0) {
            wxMessageBox("Montant invalide !", "Erreur", wxOK | wxICON_ERROR);
            return;
        }

        if(montant > m_comptes[item].solde) {
            wxMessageBox("Solde insuffisant !", "Erreur", wxOK | wxICON_ERROR);
            return;
        }

        m_comptes[item].retirer(montant);
        m_comptes[targetIndex].deposer(montant);
        ActualiserComptes();
        wxMessageBox(wxString::Format("Virement de %.2f € effectué avec succès !", montant),
                     "Succès", wxOK | wxICON_INFORMATION);
    }
}

void GestionComptesFrame::OnCreerCompte(wxCommandEvent& event)
{
    wxString choices[] = {"Compte Courant", "Compte Épargne", "Compte Jeune"};
    wxSingleChoiceDialog dlg(this, "Choisissez le type de compte à créer :",
                             "Nouveau compte", 3, choices);

    if(dlg.ShowModal() == wxID_OK) {
        wxString newNum = wxString::Format("FR%03d-%03d-%03d",
                                          (int)m_comptes.size() + 1,
                                          rand() % 1000,
                                          rand() % 1000);
        m_comptes.push_back(CompteBancaire(std::string(newNum.mb_str()),
                                          std::string(dlg.GetStringSelection().mb_str()),
                                          0.0f, "001"));
        ActualiserComptes();
        wxMessageBox(wxString::Format("Votre nouveau %s a été créé avec succès !\nNuméro : %s",
                                     dlg.GetStringSelection(), newNum),
                    "Compte créé", wxOK | wxICON_INFORMATION);
    }
}
