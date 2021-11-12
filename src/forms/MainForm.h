#ifndef M3U_MAINFORM_H
#define M3U_MAINFORM_H

#include <filesystem>
#include <gtkmm-3.0/gtkmm/window.h>
#include <gtkmm-3.0/gtkmm/box.h>
#include <gtkmm-3.0/gtkmm/button.h>
#include "Logger.h"

class MainForm : public Gtk::Window
{
public:
    MainForm();
    ~MainForm() override;

protected:
    //Signal handlers:
    void on_button_clicked();

    //Child widgets:
    Gtk::Button m_button;
    Logger *mLogger;
};


#endif //M3U_MAINFORM_H
