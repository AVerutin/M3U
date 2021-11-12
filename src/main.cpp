#include <iostream>
#include <locale>
//#include <string>
//#include <vector>
//#include "DbConnection.h"
//#include "M3UParser.h"

#include <gtkmm-3.0/gtkmm/application.h>
#include "MainForm.h"

int main(int argc, char* argv[]) try
{
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");
    MainForm mainForm;

    return app->run(mainForm);

//    if (argc < 2)
//    {
//        std::cerr <<"File not found";
//        return EXIT_FAILURE;
//    }
//
//    std::string fileName = argv[1];
//    M3UParser parser(fileName);
//
//    Playlist playlist = parser.getPlaylist();
//    std::vector<Channel> channels = parser.getChannels();
//
//    std::cout <<"List name is : " <<playlist.getName() <<std::endl;
//    std::cout <<"List has a   : " <<channels.size() <<" channels" <<std::endl;

//    DbConnection db{};

//    Add new user
//    DbItem user{};
//    user.setAge(36);
//    user.setName("Well");
//    user.setWeight(65.8);
//    db.addUser(user);
//    std::cout <<"The new record got assigned id " <<db.lastInsertedId() <<std::endl;
//
//    std::vector<DbItem> users = db.getUsers();
//    std::cout <<"Check DbItems" <<std::endl;
//    for (const DbItem& item : users)
//    {
//        std::cout <<"[" <<item.id() <<"] ==> " <<item.name() <<"\t (" <<item.age() <<")\t weight : " <<item.weight() <<std::endl;
//    }
}
catch (const std::exception& err)
{
    std::cerr <<"Oops: " <<err.what() <<std::endl;
    return 1;
}
