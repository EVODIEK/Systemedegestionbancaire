// ============================================
// src/GestionPretsFrame.cpp - VERSION ULTRA-MODERNE
// ============================================
#include "GestionPretsFrame.h"
#include <wx/textdlg.h>
#include <wx/sizer.h>
#include <cstdlib>
#include <ctime>
#include <cmath>

wxBEGIN_EVENT_TABLE(GestionPretsFrame, wxFrame)
    EVT_BUTTON(ID_DemanderPret, GestionPretsFrame::OnDemanderPret)
    EVT_BUTTON(ID_RembourserPret, GestionPretsFrame::OnRembourser)
    EVT_BUTTON(ID_SimulerPret, GestionPretsFrame::OnSimuler)
    EVT_BUTTON(ID_VoirDetailsPret, GestionPretsFrame::OnVoirDetails)
    EVT_BUTTON(ID_RemboursementRapide, GestionPretsFrame::OnRemboursementRapide)
wxEND_EVENT_TABLE()

GestionPretsFrame::GestionPretsFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(1150, 800))
{
    srand(static_cast<unsigned int>(time(NULL)));

    m_prets.push_back(Pret("P001", 5000.0f, 3500.0f, "Actif", "001"));
    m_prets.push_back(Pret("P002", 10000.0f, 2500.0f, "Actif", "001"));
    m_prets.push_back(Pret("P003", 3000.0f, 0.0f, "Rembourse", "001"));
    m_prets.push_back(Pret("P004", 15000.0f, 15000.0f, "En attente", "001"));

    CreerInterface();
}

void GestionPretsFrame::CreerInterface()
{
    wxPanel* mainPanel = new wxPanel(this, wxID_ANY);
    mainPanel->SetBackgroundColour(wxColour(236, 240, 241));

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // ==================== HEADER ORANGE ====================
    wxPanel* headerPanel = new wxPanel(mainPanel, wxID_ANY);
    headerPanel->SetBackgroundColour(wxColour(230, 126, 34)); // Orange dynamique
    headerPanel->SetMinSize(wxSize(-1, 100));

    wxBoxSizer* headerSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* lblTitre = new wxStaticText(headerPanel, wxID_ANY, "  MES PRETS BANCAIRES");
    wxFont fontTitre(24, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    lblTitre->SetFont(fontTitre);
    lblTitre->SetForegroundColour(*wxWHITE);
    headerSizer->Add(lblTitre, 0, wxALL, 15);

    wxStaticText* lblSubtitle = new wxStaticText(headerPanel, wxID_ANY,
        "  Consultez vos prets, effectuez des remboursements et simulez de nouveaux projets");
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

    // Carte Nombre de prets
    wxPanel* statsNombre = new wxPanel(statsPanel, wxID_ANY);
    statsNombre->SetBackgroundColour(wxColour(52, 152, 219));
    statsNombre->SetMinSize(wxSize(250, 100));
    wxBoxSizer* s1 = new wxBoxSizer(wxVERTICAL);
    wxStaticText* t1 = new wxStaticText(statsNombre, wxID_ANY, "PRETS ACTIFS");
    wxFont f1(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    t1->SetFont(f1);
    t1->SetForegroundColour(wxColour(189, 195, 199));
    s1->Add(t1, 0, wxALIGN_CENTER | wxTOP, 20);
    lblNombrePrets = new wxStaticText(statsNombre, wxID_ANY, "0");
    wxFont fv1(30, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    lblNombrePrets->SetFont(fv1);
    lblNombrePrets->SetForegroundColour(*wxWHITE);
    s1->Add(lblNombrePrets, 0, wxALIGN_CENTER | wxBOTTOM, 20);
    statsNombre->SetSizer(s1);
    statsSizer->Add(statsNombre, 1, wxEXPAND | wxALL, 15);

    // Carte Montant total
    wxPanel* statsTotal = new wxPanel(statsPanel, wxID_ANY);
    statsTotal->SetBackgroundColour(wxColour(155, 89, 182));
    statsTotal->SetMinSize(wxSize(250, 100));
    wxBoxSizer* s2 = new wxBoxSizer(wxVERTICAL);
    wxStaticText* t2 = new wxStaticText(statsTotal, wxID_ANY, "MONTANT TOTAL EMPRUNTE");
    t2->SetFont(f1);
    t2->SetForegroundColour(wxColour(189, 195, 199));
    s2->Add(t2, 0, wxALIGN_CENTER | wxTOP, 20);
    lblMontantTotal = new wxStaticText(statsTotal, wxID_ANY, "0 FCFA");
    wxFont fv2(20, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    lblMontantTotal->SetFont(fv2);
    lblMontantTotal->SetForegroundColour(*wxWHITE);
    s2->Add(lblMontantTotal, 0, wxALIGN_CENTER | wxBOTTOM, 20);
    statsTotal->SetSizer(s2);
    statsSizer->Add(statsTotal, 1, wxEXPAND | wxALL, 15);

    // Carte Montant restant
    wxPanel* statsRestant = new wxPanel(statsPanel, wxID_ANY);
    statsRestant->SetBackgroundColour(wxColour(231, 76, 60));
    statsRestant->SetMinSize(wxSize(250, 100));
    wxBoxSizer* s3 = new wxBoxSizer(wxVERTICAL);
    wxStaticText* t3 = new wxStaticText(statsRestant, wxID_ANY, "A REMBOURSER");
    t3->SetFont(f1);
    t3->SetForegroundColour(wxColour(189, 195, 199));
    s3->Add(t3, 0, wxALIGN_CENTER | wxTOP, 20);
    lblMontantRestant = new wxStaticText(statsRestant, wxID_ANY, "0 FCFA");
    lblMontantRestant->SetFont(fv2);
    lblMontantRestant->SetForegroundColour(*wxWHITE);
    s3->Add(lblMontantRestant, 0, wxALIGN_CENTER | wxBOTTOM, 20);
    statsRestant->SetSizer(s3);
    statsSizer->Add(statsRestant, 1, wxEXPAND | wxALL, 15);

    // Carte Progression
    wxPanel* statsProgression = new wxPanel(statsPanel, wxID_ANY);
    statsProgression->SetBackgroundColour(wxColour(46, 204, 113));
    statsProgression->SetMinSize(wxSize(250, 100));
    wxBoxSizer* s4 = new wxBoxSizer(wxVERTICAL);
    wxStaticText* t4 = new wxStaticText(statsProgression, wxID_ANY, "PROGRESSION GLOBALE");
    t4->SetFont(f1);
    t4->SetForegroundColour(wxColour(189, 195, 199));
    s4->Add(t4, 0, wxALIGN_CENTER | wxTOP, 20);
    wxStaticText* v4 = new wxStaticText(statsProgression, wxID_ANY, "0%");
    v4->SetFont(fv1);
    v4->SetForegroundColour(*wxWHITE);
    s4->Add(v4, 0, wxALIGN_CENTER | wxBOTTOM, 20);
    statsProgression->SetSizer(s4);
    statsSizer->Add(statsProgression, 1, wxEXPAND | wxALL, 15);

    statsPanel->SetSizer(statsSizer);
    mainSizer->Add(statsPanel, 0, wxEXPAND);

    // ==================== ZONE PRINCIPALE ====================
    wxPanel* contentPanel = new wxPanel(mainPanel, wxID_ANY);
    contentPanel->SetBackgroundColour(*wxWHITE);

    wxBoxSizer* contentSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* lblListeTitre = new wxStaticText(contentPanel, wxID_ANY, "  VOS PRETS EN COURS ET HISTORIQUE");
    wxFont fontListe(14, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    lblListeTitre->SetFont(fontListe);
    lblListeTitre->SetForegroundColour(wxColour(52, 73, 94));
    contentSizer->Add(lblListeTitre, 0, wxALL, 20);

    listPrets = new wxListCtrl(contentPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                               wxLC_REPORT | wxLC_SINGLE_SEL | wxBORDER_SIMPLE);
    listPrets->SetBackgroundColour(wxColour(250, 250, 250));
    listPrets->InsertColumn(0, "ID Pret", wxLIST_FORMAT_LEFT, 100);
    listPrets->InsertColumn(1, "Montant Initial (FCFA)", wxLIST_FORMAT_RIGHT, 180);
    listPrets->InsertColumn(2, "Montant Restant (FCFA)", wxLIST_FORMAT_RIGHT, 180);
    listPrets->InsertColumn(3, "Progression", wxLIST_FORMAT_CENTER, 150);
    listPrets->InsertColumn(4, "Etat", wxLIST_FORMAT_CENTER, 130);
    listPrets->InsertColumn(5, "Statut", wxLIST_FORMAT_LEFT, 200);

    ActualiserPrets();
    contentSizer->Add(listPrets, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 20);

    // ==================== BOUTONS D'ACTION ====================
    wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
    wxFont fontBtn(11, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

    wxButton* btnDemander = new wxButton(contentPanel, ID_DemanderPret, "Nouveau pret",
                                        wxDefaultPosition, wxSize(180, 50));
    btnDemander->SetBackgroundColour(wxColour(52, 152, 219));
    btnDemander->SetForegroundColour(*wxWHITE);
    btnDemander->SetFont(fontBtn);
    btnSizer->Add(btnDemander, 0, wxALL, 5);

    wxButton* btnRembourser = new wxButton(contentPanel, ID_RembourserPret, "Rembourser",
                                          wxDefaultPosition, wxSize(180, 50));
    btnRembourser->SetBackgroundColour(wxColour(46, 204, 113));
    btnRembourser->SetForegroundColour(*wxWHITE);
    btnRembourser->SetFont(fontBtn);
    btnSizer->Add(btnRembourser, 0, wxALL, 5);

    wxButton* btnRapide = new wxButton(contentPanel, ID_RemboursementRapide, "Remb. Rapide",
                                      wxDefaultPosition, wxSize(180, 50));
    btnRapide->SetBackgroundColour(wxColour(39, 174, 96));
    btnRapide->SetForegroundColour(*wxWHITE);
    btnRapide->SetFont(fontBtn);
    btnSizer->Add(btnRapide, 0, wxALL, 5);

    wxButton* btnSimuler = new wxButton(contentPanel, ID_SimulerPret, "Simuler un pret",
                                       wxDefaultPosition, wxSize(180, 50));
    btnSimuler->SetBackgroundColour(wxColour(155, 89, 182));
    btnSimuler->SetForegroundColour(*wxWHITE);
    btnSimuler->SetFont(fontBtn);
    btnSizer->Add(btnSimuler, 0, wxALL, 5);

    wxButton* btnDetails = new wxButton(contentPanel, ID_VoirDetailsPret, "Voir details",
                                       wxDefaultPosition, wxSize(150, 50));
    btnDetails->SetBackgroundColour(wxColour(52, 73, 94));
    btnDetails->SetForegroundColour(*wxWHITE);
    btnDetails->SetFont(fontBtn);
    btnSizer->Add(btnDetails, 0, wxALL, 5);

    contentSizer->Add(btnSizer, 0, wxALIGN_CENTER | wxBOTTOM, 20);

    contentPanel->SetSizer(contentSizer);
    mainSizer->Add(contentPanel, 1, wxEXPAND | wxALL, 15);

    mainPanel->SetSizer(mainSizer);
    ActualiserStatistiques();
}

void GestionPretsFrame::ActualiserPrets()
{
    listPrets->DeleteAllItems();
    for(size_t i = 0; i < m_prets.size(); ++i) {
        long idx = listPrets->InsertItem(i, wxString(m_prets[i].idPret.c_str()));
        listPrets->SetItem(idx, 1, wxString::Format("%.2f", m_prets[i].montantInitial));
        listPrets->SetItem(idx, 2, wxString::Format("%.2f", m_prets[i].montantRestant));

        // Calcul de la progression
        float pourcentage = 0;
        if(m_prets[i].montantInitial > 0) {
            pourcentage = ((m_prets[i].montantInitial - m_prets[i].montantRestant) /
                          m_prets[i].montantInitial) * 100;
        }
        listPrets->SetItem(idx, 3, wxString::Format("%.1f%%", pourcentage));
        listPrets->SetItem(idx, 4, wxString(m_prets[i].etat.c_str()));

        // Statut descriptif
        if(m_prets[i].etat == "Actif") {
            listPrets->SetItem(idx, 5, "En cours de remboursement");
            listPrets->SetItemTextColour(idx, wxColour(52, 152, 219));
        } else if(m_prets[i].etat == "Rembourse") {
            listPrets->SetItem(idx, 5, "Completement rembourse");
            listPrets->SetItemTextColour(idx, wxColour(39, 174, 96));
        } else if(m_prets[i].etat == "En attente") {
            listPrets->SetItem(idx, 5, "En cours d'etude");
            listPrets->SetItemTextColour(idx, wxColour(243, 156, 18));
        } else {
            listPrets->SetItem(idx, 5, "Statut inconnu");
            listPrets->SetItemTextColour(idx, wxColour(127, 140, 141));
        }

        if(i % 2 == 0) {
            listPrets->SetItemBackgroundColour(idx, wxColour(248, 249, 250));
        }
    }
    ActualiserStatistiques();
}

void GestionPretsFrame::ActualiserStatistiques()
{
    int pretsActifs = 0;
    float totalEmprunte = 0;
    float totalRestant = 0;

    for(size_t i = 0; i < m_prets.size(); ++i) {
        if(m_prets[i].etat == "Actif") {
            pretsActifs++;
            totalEmprunte += m_prets[i].montantInitial;
            totalRestant += m_prets[i].montantRestant;
        }
    }

    float progression = 0;
    if(totalEmprunte > 0) {
        progression = ((totalEmprunte - totalRestant) / totalEmprunte) * 100;
    }

    lblNombrePrets->SetLabel(wxString::Format("%d", pretsActifs));
    lblMontantTotal->SetLabel(wxString::Format("%.0f FCFA", totalEmprunte));
    lblMontantRestant->SetLabel(wxString::Format("%.0f FCFA", totalRestant));
}

void GestionPretsFrame::OnDemanderPret(wxCommandEvent& event)
{
    wxTextEntryDialog dlg(this,
        "Montant souhaite (FCFA) :\n\n"
        "Montants disponibles :\n"
        "- Petit pret : 1 000 - 10 000 FCFA\n"
        "- Pret moyen : 10 000 - 50 000 FCFA\n"
        "- Grand pret : 50 000 - 100 000 FCFA\n",
        "Demande de pret", "10000");

    if(dlg.ShowModal() == wxID_OK) {
        double montant;
        if(!dlg.GetValue().ToDouble(&montant) || montant <= 0) {
            wxMessageBox("Montant invalide !", "Erreur", wxOK | wxICON_ERROR);
            return;
        }

        if(montant > 100000) {
            wxMessageBox("Le montant maximum est de 100 000 FCFA pour un pret en ligne.\n\n"
                        "Pour un montant superieur, veuillez prendre rendez-vous\n"
                        "avec votre conseiller bancaire.",
                        "Montant trop eleve", wxOK | wxICON_WARNING);
            return;
        }

        if(montant < 1000) {
            wxMessageBox("Le montant minimum est de 1 000 FCFA.",
                        "Montant trop faible", wxOK | wxICON_WARNING);
            return;
        }

        wxString newId = wxString::Format("P%03d", (int)m_prets.size() + 1);
        m_prets.push_back(Pret(std::string(newId.mb_str()), montant, montant, "En attente", "001"));
        ActualiserPrets();

        wxMessageBox(wxString::Format(
            "Votre demande de pret a ete enregistree avec succes !\n\n"
            "Numero de demande : %s\n"
            "Montant demande : %.2f FCFA\n\n"
            "PROCHAINES ETAPES :\n"
            "1. Etude de votre dossier (24-48h)\n"
            "2. Notification par email et SMS\n"
            "3. Signature electronique du contrat\n"
            "4. Versement des fonds sur votre compte\n\n"
            "Vous pouvez suivre l'evolution de votre demande\n"
            "dans l'onglet 'Mes Prets'.",
            newId, montant),
            "Demande enregistree", wxOK | wxICON_INFORMATION);
    }
}

void GestionPretsFrame::OnRembourser(wxCommandEvent& event)
{
    long item = listPrets->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if(item == -1) {
        wxMessageBox("Veuillez selectionner un pret dans la liste.", "Information",
                    wxOK | wxICON_INFORMATION);
        return;
    }

    if(m_prets[item].etat == "Rembourse") {
        wxMessageBox("Ce pret est deja entierement rembourse.", "Information",
                    wxOK | wxICON_INFORMATION);
        return;
    }

    if(m_prets[item].etat == "En attente") {
        wxMessageBox("Ce pret est encore en attente de validation.\n"
                    "Vous pourrez le rembourser une fois qu'il sera actif.",
                    "Pret non actif", wxOK | wxICON_INFORMATION);
        return;
    }

    wxTextEntryDialog dlg(this,
        wxString::Format(
            "REMBOURSEMENT DU PRET %s\n\n"
            "Montant restant a rembourser : %.2f FCFA\n"
            "Montant initial : %.2f FCFA\n\n"
            "Entrez le montant que vous souhaitez rembourser :",
            m_prets[item].idPret.c_str(),
            m_prets[item].montantRestant,
            m_prets[item].montantInitial),
        "Remboursement", "");

    if(dlg.ShowModal() == wxID_OK) {
        double montant;
        if(!dlg.GetValue().ToDouble(&montant) || montant <= 0) {
            wxMessageBox("Montant invalide !", "Erreur", wxOK | wxICON_ERROR);
            return;
        }

        if(montant > m_prets[item].montantRestant) {
            if(wxMessageBox(wxString::Format(
                "Le montant saisi (%.2f FCFA) depasse le montant restant (%.2f FCFA).\n\n"
                "Voulez-vous rembourser uniquement le montant restant ?",
                montant, m_prets[item].montantRestant),
                "Montant trop eleve", wxYES_NO | wxICON_QUESTION) == wxYES) {
                montant = m_prets[item].montantRestant;
            } else {
                return;
            }
        }

        m_prets[item].montantRestant -= montant;
        if(m_prets[item].montantRestant <= 0.01) {
            m_prets[item].montantRestant = 0;
            m_prets[item].etat = "Rembourse";
        }

        ActualiserPrets();

        if(m_prets[item].etat == "Rembourse") {
            wxMessageBox(wxString::Format(
                "FELICITATIONS !\n\n"
                "Remboursement de %.2f FCFA effectue avec succes !\n\n"
                "Votre pret %s est maintenant ENTIEREMENT REMBOURSE.\n\n"
                "Merci de votre confiance !\n"
                "Vous pouvez desormais demander un nouveau pret si besoin.",
                montant, m_prets[item].idPret.c_str()),
                "Pret rembourse", wxOK | wxICON_INFORMATION);
        } else {
            wxMessageBox(wxString::Format(
                "Remboursement effectue avec succes !\n\n"
                "Montant rembourse : %.2f FCFA\n"
                "Montant restant : %.2f FCFA\n"
                "Progression : %.1f%%\n\n"
                "Continuez comme ca !",
                montant, m_prets[item].montantRestant,
                ((m_prets[item].montantInitial - m_prets[item].montantRestant) /
                 m_prets[item].montantInitial) * 100),
                "Succes", wxOK | wxICON_INFORMATION);
        }
    }
}

void GestionPretsFrame::OnRemboursementRapide(wxCommandEvent& event)
{
    long item = listPrets->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if(item == -1) {
        wxMessageBox("Veuillez selectionner un pret dans la liste.", "Information",
                    wxOK | wxICON_INFORMATION);
        return;
    }

    if(m_prets[item].etat != "Actif") {
        wxMessageBox("Cette fonction est disponible uniquement pour les prets actifs.",
                    "Information", wxOK | wxICON_INFORMATION);
        return;
    }

    float montantRestant = m_prets[item].montantRestant;
    float option1 = montantRestant * 0.1f;  // 10%
    float option2 = montantRestant * 0.25f; // 25%
    float option3 = montantRestant * 0.5f;  // 50%

    wxString choices[4];
    choices[0] = wxString::Format("10%% du solde (%.2f FCFA)", option1);
    choices[1] = wxString::Format("25%% du solde (%.2f FCFA)", option2);
    choices[2] = wxString::Format("50%% du solde (%.2f FCFA)", option3);
    choices[3] = wxString::Format("Remboursement total (%.2f FCFA)", montantRestant);

    wxSingleChoiceDialog dlg(this,
        "Choisissez un montant de remboursement rapide :",
        "Remboursement rapide", 4, choices);

    if(dlg.ShowModal() == wxID_OK) {
        float montant;
        int selection = dlg.GetSelection();

        switch(selection) {
            case 0: montant = option1; break;
            case 1: montant = option2; break;
            case 2: montant = option3; break;
            case 3: montant = montantRestant; break;
            default: return;
        }

        m_prets[item].montantRestant -= montant;
        if(m_prets[item].montantRestant <= 0.01) {
            m_prets[item].montantRestant = 0;
            m_prets[item].etat = "Rembourse";
        }

        ActualiserPrets();

        if(m_prets[item].etat == "Rembourse") {
            wxMessageBox(wxString::Format(
                "PRET ENTIEREMENT REMBOURSE !\n\n"
                "Montant rembourse : %.2f FCFA\n\n"
                "Felicitations ! Votre pret est solde.",
                montant),
                "Succes", wxOK | wxICON_INFORMATION);
        } else {
            wxMessageBox(wxString::Format(
                "Remboursement rapide effectue !\n\n"
                "Montant rembourse : %.2f FCFA\n"
                "Nouveau solde : %.2f FCFA",
                montant, m_prets[item].montantRestant),
                "Succes", wxOK | wxICON_INFORMATION);
        }
    }
}

void GestionPretsFrame::OnSimuler(wxCommandEvent& event)
{
    wxTextEntryDialog dlgMontant(this,
        "Montant du pret souhaite (FCFA) :",
        "Simulation de pret", "10000");
    if(dlgMontant.ShowModal() != wxID_OK) return;

    wxTextEntryDialog dlgDuree(this,
        "Duree de remboursement (en mois) :\n\n"
        "Durees disponibles : 6, 12, 24, 36, 48 mois",
        "Simulation de pret", "24");
    if(dlgDuree.ShowModal() != wxID_OK) return;

    double montant, duree;
    if(!dlgMontant.GetValue().ToDouble(&montant) || montant <= 0 ||
       !dlgDuree.GetValue().ToDouble(&duree) || duree <= 0) {
        wxMessageBox("Valeurs invalides !", "Erreur", wxOK | wxICON_ERROR);
        return;
    }

    // Calcul avec taux variable selon montant
    double tauxAnnuel;
    if(montant < 10000) {
        tauxAnnuel = 4.5;
    } else if(montant < 50000) {
        tauxAnnuel = 3.8;
    } else {
        tauxAnnuel = 3.2;
    }

    double tauxMensuel = tauxAnnuel / 12 / 100;
    double mensualite = (montant * tauxMensuel) / (1 - pow(1 + tauxMensuel, -duree));
    double coutTotal = mensualite * duree;
    double interets = coutTotal - montant;
    double taeg = ((coutTotal / montant - 1) / (duree / 12)) * 100;

    wxString message = wxString::Format(
        "========== SIMULATION DE PRET ==========\n\n"
        "MONTANT EMPRUNTE : %.2f FCFA\n"
        "DUREE : %.0f mois (%.1f ans)\n"
        "TAUX NOMINAL ANNUEL : %.2f%%\n"
        "TAEG : %.2f%%\n\n"
        "--- REMBOURSEMENT ---\n"
        "Mensualite : %.2f FCFA\n"
        "Cout total du credit : %.2f FCFA\n"
        "Dont interets : %.2f FCFA\n"
        "Cout des interets : %.1f%%\n\n"
        "--- RECAPITULATIF ---\n"
        "Vous empruntez : %.2f FCFA\n"
        "Vous remboursez : %.2f FCFA\n"
        "En %d mensualites de %.2f FCFA\n\n"
        "Cette simulation est indicative et sans engagement.\n"
        "Les taux peuvent varier selon votre profil.\n\n"
        "Souhaitez-vous faire une demande de pret ?",
        montant, duree, duree/12, tauxAnnuel, taeg,
        mensualite, coutTotal, interets, (interets/montant)*100,
        montant, coutTotal, (int)duree, mensualite
    );

    int result = wxMessageBox(message, "Resultat de la simulation",
                              wxYES_NO | wxICON_INFORMATION);

    if(result == wxYES) {
        wxCommandEvent evt;
        OnDemanderPret(evt);
    }
}

void GestionPretsFrame::OnVoirDetails(wxCommandEvent& event)
{
    long item = listPrets->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if(item == -1) {
        wxMessageBox("Veuillez selectionner un pret dans la liste.", "Information",
                    wxOK | wxICON_INFORMATION);
        return;
    }

    float pourcentage = 0;
    if(m_prets[item].montantInitial > 0) {
        pourcentage = ((m_prets[item].montantInitial - m_prets[item].montantRestant) /
                      m_prets[item].montantInitial) * 100;
    }

    float montantRembourse = m_prets[item].montantInitial - m_prets[item].montantRestant;

    wxString details = wxString::Format(
        "========== DETAILS DU PRET ==========\n\n"
        "ID Pret : %s\n"
        "Etat : %s\n\n"
        "--- MONTANTS ---\n"
        "Montant initial : %.2f FCFA\n"
        "Montant rembourse : %.2f FCFA\n"
        "Montant restant : %.2f FCFA\n\n"
        "--- PROGRESSION ---\n"
        "Pourcentage rembourse : %.1f%%\n"
        "Pourcentage restant : %.1f%%\n\n"
        "--- INFORMATIONS ---\n"
        "Date de demande : 15/01/2025\n"
        "Date d'approbation : 17/01/2025\n"
        "Echeance prevue : 17/01/2027\n"
        "Taux d'interet : 3.5%% annuel\n"
        "Mensualite recommandee : %.2f FCFA\n\n"
        "Pour toute question, contactez votre conseiller\n"
        "au 01 23 45 67 89 ou par email.",
        m_prets[item].idPret.c_str(),
        m_prets[item].etat.c_str(),
        m_prets[item].montantInitial,
        montantRembourse,
        m_prets[item].montantRestant,
        pourcentage,
        100 - pourcentage,
        m_prets[item].montantRestant / 24
    );

    wxMessageBox(details, "Details du pret", wxOK | wxICON_INFORMATION);
}
