// ============================================
// include/GestionPretsFrame.h - VERSION ULTRA-MODERNE
// ============================================
#ifndef GESTIONPRETSFRAME_H
#define GESTIONPRETSFRAME_H

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/gauge.h>
#include <vector>
#include <cmath>
#include "Pret.h"

class GestionPretsFrame : public wxFrame {
public:
    GestionPretsFrame(const wxString& title);

private:
    std::vector<Pret> m_prets;
    wxListCtrl* listPrets;
    wxStaticText* lblNombrePrets;
    wxStaticText* lblMontantTotal;
    wxStaticText* lblMontantRestant;

    void CreerInterface();
    void OnDemanderPret(wxCommandEvent& event);
    void OnRembourser(wxCommandEvent& event);
    void OnSimuler(wxCommandEvent& event);
    void OnVoirDetails(wxCommandEvent& event);
    void OnRemboursementRapide(wxCommandEvent& event);
    void ActualiserPrets();
    void ActualiserStatistiques();

    wxDECLARE_EVENT_TABLE();
};

enum {
    ID_DemanderPret = wxID_HIGHEST + 500,
    ID_RembourserPret,
    ID_SimulerPret,
    ID_VoirDetailsPret,
    ID_RemboursementRapide
};

#endif
