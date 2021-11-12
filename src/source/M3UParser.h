#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <filesystem>
#include <fstream>
#include <boost/algorithm/string/trim.hpp>
#include <boost/regex.hpp>
#include <vector>

#include "Playlist.h"
#include "Logger.h"
#include "Channel.h"
#include "datatype.h"

class M3UParser
{
public:
  M3UParser();
  explicit M3UParser(std::string_view fileName);
  ~M3UParser();

  [[nodiscard]] Playlist getPlaylist() const;
  [[nodiscard]] std::vector<Channel> getChannels() const;


private:
    Channel *mChannel;
    std::string playlistName;

    Logger *mLogger;
    Playlist mPlaylist;
    std::vector<Channel> mChannels;

    void parse();
    [[nodiscard]] Playlist getListTitle(const std::string& listTitle) const;
    [[nodiscard]] std::string getGroupName(const std::string& groupName) const;
    [[nodiscard]] std::string getListName(const std::string& listName) const;
    [[nodiscard]] VlcInfo getVlcOpt(const std::string& vlcParams) const;
    Channel* getChannelInfo(std::string& channel) const;
};

#endif // PARSER_H
