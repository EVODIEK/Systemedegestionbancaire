// src/LoginFrame.cpp - VERSION ULTRA-ATTRACTIVE
#include "LoginFrame.h"
#include "DashboardClientFrame.h"
#include "AdminFrame.h"
#include <wx/sizer.h>

wxBEGIN_EVENT_TABLE(LoginFrame, wxFrame)
    EVT_BUTTON(ID_Login, LoginFrame::OnLogin)
wxEND_EVENT_TABLE()

LoginFrame::LoginFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(500, 450))
{
    // Panel principal
    wxPanel* panel = new wxPanel(this, wxID_ANY);
    panel->SetBackgroundColour(wxColour(236, 240, 241));

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // ==================== HEADER AVEC LOGO ====================
    wxPanel* headerPanel = new wxPanel(panel, wxID_ANY);
    headerPanel->SetBackgroundColour(wxColour(41, 128, 185));
    headerPanel->SetMinSize(wxSize(-1, 100));

    wxBoxSizer* headerSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* lblLogo = new wxStaticText(headerPanel, wxID_ANY, "EvoBank");
    wxFont fontLogo(32, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    lblLogo->SetFont(fontLogo);
    lblLogo->SetForegroundColour(*wxWHITE);
    headerSizer->Add(lblLogo, 1, wxALIGN_CENTER | wxTOP, 25);

    wxStaticText* lblTagline = new wxStaticText(headerPanel, wxID_ANY, "Votre banque digitale");
    wxFont fontTagline(11, wxFONTFAMILY_SWISS, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_NORMAL);
    lblTagline->SetFont(fontTagline);
    lblTagline->SetForegroundColour(wxColour(189, 195, 199));
    headerSizer->Add(lblTagline, 0, wxALIGN_CENTER | wxBOTTOM, 15);

    headerPanel->SetSizer(headerSizer);
    mainSizer->Add(headerPanel, 0, wxEXPAND);

    // ==================== ZONE DE CONNEXION ====================
    wxPanel* formPanel = new wxPanel(panel, wxID_ANY);
    formPanel->SetBackgroundColour(*wxWHITE);

    wxBoxSizer* formSizer = new wxBoxSizer(wxVERTICAL);

    // Titre de connexion
    wxStaticText* lblConnexion = new wxStaticText(formPanel, wxID_ANY, "Connexion");
    wxFont fontConnexion(18, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    lblConnexion->SetFont(fontConnexion);
    lblConnexion->SetForegroundColour(wxColour(52, 73, 94));
    formSizer->Add(lblConnexion, 0, wxALIGN_CENTER | wxTOP, 30);

    formSizer->AddSpacer(20);

    // Nom d'utilisateur
    wxStaticText* lblUser = new wxStaticText(formPanel, wxID_ANY, "Nom d'utilisateur");
    wxFont fontLabel(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    lblUser->SetFont(fontLabel);
    lblUser->SetForegroundColour(wxColour(127, 140, 141));
    formSizer->Add(lblUser, 0, wxLEFT | wxRIGHT, 40);

    txtUser = new wxTextCtrl(formPanel, wxID_ANY, "evodie",
                            wxDefaultPosition, wxSize(-1, 35));
    wxFont fontInput(11, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    txtUser->SetFont(fontInput);
    formSizer->Add(txtUser, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 40);

    formSizer->AddSpacer(15);

    // Mot de passe
    wxStaticText* lblPass = new wxStaticText(formPanel, wxID_ANY, "Mot de passe");
    lblPass->SetFont(fontLabel);
    lblPass->SetForegroundColour(wxColour(127, 140, 141));
    formSizer->Add(lblPass, 0, wxLEFT | wxRIGHT, 40);

    txtPassword = new wxTextCtrl(formPanel, wxID_ANY, "1234",
                                 wxDefaultPosition, wxSize(-1, 35), wxTE_PASSWORD);
    txtPassword->SetFont(fontInput);
    formSizer->Add(txtPassword, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 40);

    formSizer->AddSpacer(15);

    // Type de compte
    wxStaticText* lblRole = new wxStaticText(formPanel, wxID_ANY, "Type de compte");
    lblRole->SetFont(fontLabel);
    lblRole->SetForegroundColour(wxColour(127, 140, 141));
    formSizer->Add(lblRole, 0, wxLEFT | wxRIGHT, 40);

    wxString roles[] = {"Client", "Administrateur"};
    choiceRole = new wxChoice(formPanel, wxID_ANY, wxDefaultPosition, wxSize(-1, 35), 2, roles);
    choiceRole->SetSelection(0);
    choiceRole->SetFont(fontInput);
    formSizer->Add(choiceRole, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 40);

    formSizer->AddSpacer(25);

    // Bouton de connexion stylise
    btnLogin = new wxButton(formPanel, ID_Login, "SE CONNECTER",
                           wxDefaultPosition, wxSize(-1, 45));
    btnLogin->SetBackgroundColour(wxColour(46, 204, 113));
    btnLogin->SetForegroundColour(*wxWHITE);
    wxFont fontBtn(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    btnLogin->SetFont(fontBtn);
    formSizer->Add(btnLogin, 0, wxEXPAND | wxLEFT | wxRIGHT, 40);

    formSizer->AddSpacer(30);

    formPanel->SetSizer(formSizer);
    mainSizer->Add(formPanel, 1, wxEXPAND | wxALL, 20);

    // Footer
    wxStaticText* lblFooter = new wxStaticText(panel, wxID_ANY,
                                               "EvoBank 2025 - Tous droits reserves");
    wxFont fontFooter(9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    lblFooter->SetFont(fontFooter);
    lblFooter->SetForegroundColour(wxColour(149, 165, 166));
    mainSizer->Add(lblFooter, 0, wxALIGN_CENTER | wxBOTTOM, 10);

    panel->SetSizer(mainSizer);
    Centre();
}

void LoginFrame::OnLogin(wxCommandEvent& event)
{
    if(txtUser->GetValue().IsEmpty() || txtPassword->GetValue().IsEmpty()) {
        wxMessageBox("Veuillez remplir tous les champs !", "Erreur",
                    wxOK | wxICON_ERROR);
        return;
    }

    int role = choiceRole->GetSelection();

    if(role == 0) { // Client
        DashboardClientFrame* dash = new DashboardClientFrame("Tableau de bord - Client");
        dash->Show();
        this->Close();
    } else { // Administrateur
        AdminFrame* admin = new AdminFrame("Administration");
        admin->Show();
        this->Close();
    }
}
