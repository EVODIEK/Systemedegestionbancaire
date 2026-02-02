#include <wx/wx.h>

class TestApp : public wxApp {
public:
    virtual bool OnInit() {
        wxFrame* frame = new wxFrame(NULL, wxID_ANY, "Test EvoBank", 
                                     wxDefaultPosition, wxSize(400, 200));
        wxPanel* panel = new wxPanel(frame);
        
        wxStaticText* text = new wxStaticText(panel, wxID_ANY, 
            "✅ wxWidgets fonctionne correctement !", 
            wxPoint(50, 80));
        
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(TestApp);
