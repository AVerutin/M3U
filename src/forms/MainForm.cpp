#include "MainForm.h"

MainForm::MainForm()
{
    this->mLogger = new Logger("Main Form");

    std::string imgFile = std::filesystem::current_path().string() + "\\info.xpm";
    m_button.add_pixlabel(imgFile, "cool button");

    this->set_title("Главное окно");
    this->set_border_width(10);
    this->set_resizable(false);

    m_button.signal_clicked().connect( sigc::mem_fun(*this, &MainForm::on_button_clicked) );

    this->add(m_button);
    this->show_all_children();
}

MainForm::~MainForm() = default;

void MainForm::on_button_clicked()
{
    this->close();
}
