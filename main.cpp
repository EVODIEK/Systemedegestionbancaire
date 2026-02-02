// main.cpp - VERSION ULTRA-SÉCURISÉE TOUT-EN-UN
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/textdlg.h>
#include <vector>
#include <string>

// ========== CLASSES DE DONNÉES ==========
class CompteBancaire {
public:
    std::string numeroCompte;
    std::string typeCompte;
    float solde;
    
    CompteBancaire(const std::string& num, const std::string& type, float s) 
        : numeroCompte(num), typeCompte(type), solde(s) {}
    
    void deposer(float montant) { solde += montant; }
    void retirer(float montant) { if(solde >= montant) solde -= montant; }
};

// ========== FENÊTRE LOGIN ==========
class LoginFrame : public wxFrame {
public:
    LoginFrame() : wxFrame(NULL, wxID_ANY, "EvoBank - Connexion", 
                           wxDefaultPosition, wxSize(450, 350))
    {
        wxPanel* panel = new wxPanel(this);
        panel->SetBackgroundColour(wxColour(245, 247, 250));
        
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
        
        // Titre
        wxStaticText* titre = new wxStaticText(panel, wxID_ANY, "Bienvenue à EvoBank");
        wxFont fontTitre(16, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        titre->SetFont(fontTitre);
        titre->SetForegroundColour(wxColour(30, 60, 114));
        sizer->Add(titre, 0, wxALL | wxALIGN_CENTER, 20);
        
        // Nom utilisateur
        sizer->Add(new wxStaticText(panel, wxID_ANY, "Nom d'utilisateur :"), 0, wxLEFT | wxTOP, 20);
        txtUser = new wxTextCtrl(panel, wxID_ANY, "evodie");
        sizer->Add(txtUser, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 20);
        
        // Mot de passe
        sizer->Add(new wxStaticText(panel, wxID_ANY, "Mot de passe :"), 0, wxLEFT | wxTOP, 20);
        txtPass = new wxTextCtrl(panel, wxID_ANY, "1234", wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
        sizer->Add(txtPass, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 20);
        
        // Rôle
        sizer->Add(new wxStaticText(panel, wxID_ANY, "Type de compte :"), 0, wxLEFT | wxTOP, 20);
        wxString roles[] = {"Client", "Administrateur"};
        choiceRole = new wxChoice(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 2, roles);
        choiceRole->SetSelection(0);
        sizer->Add(choiceRole, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 20);
        
        // Bouton connexion
        wxButton* btnLogin = new wxButton(panel, wxID_ANY, "Se connecter");
        btnLogin->SetBackgroundColour(wxColour(52, 152, 219));
        btnLogin->SetForegroundColour(*wxWHITE);
        btnLogin->Bind(wxEVT_BUTTON, &LoginFrame::OnLogin, this);
        sizer->Add(btnLogin, 0, wxALIGN_CENTER | wxALL, 20);
        
        panel->SetSizer(sizer);
    }
    
private:
    wxTextCtrl* txtUser;
    wxTextCtrl* txtPass;
    wxChoice* choiceRole;
    
    void OnLogin(wxCommandEvent& event);
};

// ========== FENÊTRE DASHBOARD ==========
class DashboardFrame : public wxFrame {
public:
    DashboardFrame() : wxFrame(NULL, wxID_ANY, "Tableau de bord - EvoBank", 
                               wxDefaultPosition, wxSize(900, 600))
    {
        // Initialiser les données
        comptes.push_back(CompteBancaire("FR001-123-456", "Compte Courant", 1500.50f));
        comptes.push_back(CompteBancaire("FR002-789-012", "Compte Épargne", 3200.00f));
        
        wxPanel* panel = new wxPanel(this);
        panel->SetBackgroundColour(wxColour(240, 242, 245));
        
        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
        
        // Titre
        wxStaticText* titre = new wxStaticText(panel, wxID_ANY, "Mon Espace Bancaire");
        wxFont fontTitre(18, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        titre->SetFont(fontTitre);
        titre->SetForegroundColour(wxColour(30, 60, 114));
        mainSizer->Add(titre, 0, wxALL, 20);
        
        // Liste des comptes
        mainSizer->Add(new wxStaticText(panel, wxID_ANY, "Mes Comptes Bancaires"), 
                      0, wxLEFT | wxRIGHT, 20);
        
        listComptes = new wxListCtrl(panel, wxID_ANY, wxDefaultPosition, wxSize(-1, 150), 
                                     wxLC_REPORT | wxLC_SINGLE_SEL);
        listComptes->SetBackgroundColour(*wxWHITE);
        listComptes->InsertColumn(0, "Numéro", wxLIST_FORMAT_LEFT, 200);
        listComptes->InsertColumn(1, "Type", wxLIST_FORMAT_LEFT, 150);
        listComptes->InsertColumn(2, "Solde (€)", wxLIST_FORMAT_RIGHT, 150);
        
        ActualiserComptes();
        
        mainSizer->Add(listComptes, 0, wxEXPAND | wxALL, 20);
        
        // Boutons
        wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
        
        wxButton* btnDepot = new wxButton(panel, wxID_ANY, "Dépôt", wxDefaultPosition, wxSize(120, 40));
        btnDepot->SetBackgroundColour(wxColour(46, 204, 113));
        btnDepot->SetForegroundColour(*wxWHITE);
        btnDepot->Bind(wxEVT_BUTTON, &DashboardFrame::OnDepot, this);
        btnSizer->Add(btnDepot, 0, wxALL, 5);
        
        wxButton* btnRetrait = new wxButton(panel, wxID_ANY, "Retrait", wxDefaultPosition, wxSize(120, 40));
        btnRetrait->SetBackgroundColour(wxColour(231, 76, 60));
        btnRetrait->SetForegroundColour(*wxWHITE);
        btnRetrait->Bind(wxEVT_BUTTON, &DashboardFrame::OnRetrait, this);
        btnSizer->Add(btnRetrait, 0, wxALL, 5);
        
        wxButton* btnVirement = new wxButton(panel, wxID_ANY, "Virement", wxDefaultPosition, wxSize(120, 40));
        btnVirement->SetBackgroundColour(wxColour(52, 152, 219));
        btnVirement->SetForegroundColour(*wxWHITE);
        btnVirement->Bind(wxEVT_BUTTON, &DashboardFrame::OnVirement, this);
        btnSizer->Add(btnVirement, 0, wxALL, 5);
        
        mainSizer->Add(btnSizer, 0, wxALIGN_CENTER | wxBOTTOM, 20);
        
        panel->SetSizer(mainSizer);
    }
    
private:
    std::vector<CompteBancaire> comptes;
    wxListCtrl* listComptes;
    
    void ActualiserComptes() {
        listComptes->DeleteAllItems();
        for(size_t i = 0; i < comptes.size(); ++i) {
            long idx = listComptes->InsertItem(i, comptes[i].numeroCompte);
            listComptes->SetItem(idx, 1, comptes[i].typeCompte);
            listComptes->SetItem(idx, 2, wxString::Format("%.2f", comptes[i].solde));
        }
    }
    
    void OnDepot(wxCommandEvent& event) {
        long item = listComptes->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
        if(item == -1) {
            wxMessageBox("Sélectionnez un compte !", "Information", wxOK | wxICON_INFORMATION);
            return;
        }
        
        wxTextEntryDialog dlg(this, "Montant à déposer (€) :", "Dépôt", "100.00");
        if(dlg.ShowModal() == wxID_OK) {
            double montant;
            if(dlg.GetValue().ToDouble(&montant) && montant > 0) {
                comptes[item].deposer(montant);
                ActualiserComptes();
                wxMessageBox(wxString::Format("Dépôt de %.2f € effectué !\nNouveau solde : %.2f €", 
                            montant, comptes[item].solde), "Succès", wxOK | wxICON_INFORMATION);
            } else {
                wxMessageBox("Montant invalide !", "Erreur", wxOK | wxICON_ERROR);
            }
        }
    }
    
    void OnRetrait(wxCommandEvent& event) {
        long item = listComptes->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
        if(item == -1) {
            wxMessageBox("Sélectionnez un compte !", "Information", wxOK | wxICON_INFORMATION);
            return;
        }
        
        wxTextEntryDialog dlg(this, "Montant à retirer (€) :", "Retrait", "50.00");
        if(dlg.ShowModal() == wxID_OK) {
            double montant;
            if(dlg.GetValue().ToDouble(&montant) && montant > 0) {
                if(montant > comptes[item].solde) {
                    wxMessageBox("Solde insuffisant !", "Erreur", wxOK | wxICON_ERROR);
                    return;
                }
                comptes[item].retirer(montant);
                ActualiserComptes();
                wxMessageBox(wxString::Format("Retrait de %.2f € effectué !\nNouveau solde : %.2f €", 
                            montant, comptes[item].solde), "Succès", wxOK | wxICON_INFORMATION);
            } else {
                wxMessageBox("Montant invalide !", "Erreur", wxOK | wxICON_ERROR);
            }
        }
    }
    
    void OnVirement(wxCommandEvent& event) {
        long item = listComptes->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
        if(item == -1) {
            wxMessageBox("Sélectionnez le compte source !", "Information", wxOK | wxICON_INFORMATION);
            return;
        }
        
        wxTextEntryDialog dlgDest(this, "Numéro du compte destinataire :", "Virement");
        if(dlgDest.ShowModal() != wxID_OK) return;
        
        long targetIndex = -1;
        for(size_t i = 0; i < comptes.size(); ++i) {
            if(comptes[i].numeroCompte == dlgDest.GetValue()) {
                targetIndex = i;
                break;
            }
        }
        
        if(targetIndex == -1) {
            wxMessageBox("Compte destinataire introuvable !", "Erreur", wxOK | wxICON_ERROR);
            return;
        }
        
        wxTextEntryDialog dlgMontant(this, "Montant du virement (€) :", "Virement", "100.00");
        if(dlgMontant.ShowModal() == wxID_OK) {
            double montant;
            if(dlgMontant.GetValue().ToDouble(&montant) && montant > 0) {
                if(montant > comptes[item].solde) {
                    wxMessageBox("Solde insuffisant !", "Erreur", wxOK | wxICON_ERROR);
                    return;
                }
                comptes[item].retirer(montant);
                comptes[targetIndex].deposer(montant);
                ActualiserComptes();
                wxMessageBox(wxString::Format("Virement de %.2f € effectué !", montant), 
                            "Succès", wxOK | wxICON_INFORMATION);
            } else {
                wxMessageBox("Montant invalide !", "Erreur", wxOK | wxICON_ERROR);
            }
        }
    }
};

// ========== IMPLÉMENTATION LOGIN ==========
void LoginFrame::OnLogin(wxCommandEvent& event) {
    if(txtUser->GetValue().IsEmpty() || txtPass->GetValue().IsEmpty()) {
        wxMessageBox("Remplissez tous les champs !", "Erreur", wxOK | wxICON_ERROR);
        return;
    }
    
    DashboardFrame* dash = new DashboardFrame();
    dash->Show();
    this->Close();
}

// ========== APPLICATION ==========
class BanqueApp : public wxApp {
public:
    virtual bool OnInit() {
        LoginFrame* login = new LoginFrame();
        login->Show();
        return true;
    }
};

wxIMPLEMENT_APP(BanqueApp);
