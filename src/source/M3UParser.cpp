#include "M3UParser.h"

M3UParser::M3UParser() : mChannel{nullptr}, mChannels{}
{
    this->mLogger = new Logger{"M3U Parser"};

    // Запуск разбора файла списка
    parse();
}

M3UParser::M3UParser(std::string_view fileName) : mChannel{nullptr}, mChannels{}
{
    if (!fileName.empty())
        playlistName = fileName;

    this->mLogger = new Logger{"M3U Parser"};

    // Запуск разбора файла списка
    parse();
}

M3UParser::~M3UParser()
{
    delete this->mLogger;
    delete this->mChannel;
    this->mLogger = nullptr;
    this->mChannel = nullptr;
}

/**
 * Получить данные о списке воспроизведения
 * @return Список воспроизведения
 */
Playlist M3UParser::getPlaylist() const
{
    return this->mPlaylist;
}


/**
 * Получить список каналов из списка воспроизведения
 * @return Список каналов
 */
std::vector<Channel> M3UParser::getChannels() const
{
    return this->mChannels;
}


/**
 * Парсинг файла списка воспроизведения
 */
void M3UParser::parse()
{
    std::ifstream listFile(playlistName, std::ios::in);
    if (!listFile)
    {
        this->mLogger->error("Не удалось открыть файл [" + playlistName + "]");
        return;
    }

    this->mChannel = nullptr;

    while (listFile)
    {
        std::string line{};
        std::getline(listFile, line);

        if (line.empty())
            continue;

        /// Заголовок списка
        if (line.starts_with("#EXTM3U"))
        {
            // Поиск параметров списка при помощи регулярных выражений
            Playlist plInfo = getListTitle(line);

            this->mPlaylist.setUrlTvg(plInfo.getUrlTvg());
            this->mPlaylist.setTvgShift(plInfo.getTvgShift());
            this->mPlaylist.setCache(plInfo.getCache());
            this->mPlaylist.setDeinterlace(plInfo.getDeinterlace());
            this->mPlaylist.setAspectRatio(plInfo.getAspectRatio());
            this->mPlaylist.setCrop(plInfo.getCrop());
            this->mPlaylist.setRefreshPeriod(plInfo.getRefreshPeriod());
            this->mPlaylist.setAutoload(plInfo.isAutoload());
        }

            /// Заголовок канала
        else if (line.starts_with("#EXTINF"))
        {
            // Описание свойств канала
            Channel *chInfo = getChannelInfo(line);
            if (this->mChannel == nullptr)
                this->mChannel = new Channel;

            this->mChannel->setDuration(chInfo->getDuration());
            this->mChannel->setTvgId(chInfo->getTvgId());
            this->mChannel->setTvgName(chInfo->getTvgName());
            this->mChannel->setName(chInfo->getName());
            this->mChannel->setTvgLogo(chInfo->getTvgLogo());
            this->mChannel->setTvgShift(chInfo->getTvgShift());
            this->mChannel->setGroupName(chInfo->getGroupName());
            this->mChannel->setRadio(chInfo->isRadio());
            this->mChannel->setAudioTrack(chInfo->getAudioTrack());
            this->mChannel->setAspectRatio(chInfo->getAspectRatio());
            this->mChannel->setRecordable(chInfo->isRecordable());
            this->mChannel->setCensored(chInfo->isCensored());
            this->mChannel->setAgeRestricted(chInfo->isAgeRestricted());
            this->mChannel->setUrlM3u(chInfo->getUrlM3u());
            this->mChannel->setKeyType(chInfo->getKeyType());
            this->mChannel->setCrop(chInfo->getCrop());
            this->mChannel->setSoundType(chInfo->getSoundType());
        }

            /// Наименование списка
        else if (line.starts_with("#PLAYLIST"))
        {
            std::string listName = getListName(line);
            this->mPlaylist.setName(listName);
        }

            /// Наименование группы
        else if (line.starts_with("#EXTGRP"))
        {
            if (this->mChannel == nullptr)
                this->mChannel = new Channel;

            std::string groupName = getGroupName(line);
            this->mChannel->setGroupName(groupName);
        }

            /// Дополнительные параметры для VLC
        else if (line.starts_with("#EXTVLCOPT"))
        {
            if (this->mChannel == nullptr)
                this->mChannel = new Channel;

            VlcInfo vlc = getVlcOpt(line);
            this->mChannel->setUserAgent(vlc.userAgent);
            this->mChannel->setHttpReferrer(vlc.httpReferrer);
        }

        /// Ссылка на источник канал
        else if (line.find("://"))
        {
            // Ссылка на источник канала
            if (this->mChannel == nullptr)
                this->mChannel = new Channel;

            this->mChannel->setUrl(line);
            this->mChannels.push_back(*this->mChannel);

            delete this->mChannel;
            this->mChannel = nullptr;
        }
    }

    listFile.close();
}


/**
 * Разбор параметров заголовка списка воспроизведения
 * @param listTitle Строка с общими параметрами списка воспроизведения
 * @return Параметры списка воспроизведения
 */
Playlist M3UParser::getListTitle(const std::string& listTitle) const
{
    Playlist result{};

    if (!listTitle.empty())
    {
        // url-tvg="..." или url-xml="..." url-tvg=\"(.+?)\"
        boost::regex re("url-tvg=\"(.*)\"");
        boost::smatch regResults;

        if (boost::regex_search(listTitle, regResults, re))
        {
            std::string url = regResults[1];
            boost::trim(url);
            result.setUrlTvg(url);
        }

        re = boost::regex("url-xml=\"(.*)\"");
        if (boost::regex_search(listTitle, regResults, re))
        {
            std::string url = regResults[1];
            boost::trim(url);
            result.setUrlTvg(url);
        }

        // cache="..."
        re = boost::regex("cache=\"*(\\d*)\"*");
        if (boost::regex_search(listTitle, regResults, re))
        {
            std::string cache = regResults[1];
            boost::trim(cache);
            result.setCache(std::stoi(cache));
        }

        // deinterlace="..."
        re = boost::regex("deinterlace=\"*(\\d*)?\"*");
        if (boost::regex_search(listTitle, regResults, re))
        {
            std::string deinterlace = regResults[1];
            boost::trim(deinterlace);
            result.setDeinterlace(std::stoi(deinterlace));
        }

        // aspect-ratio="..."
        re = boost::regex("aspect-ratio=\"*(\\d+:\\d+)?\"*");
        if (boost::regex_search(listTitle, regResults, re))
        {
            std::string ratio = regResults[1];
            boost::trim(ratio);
            result.setAspectRatio(ratio);
        }

        // crop="..."
        re = boost::regex("crop=\"(.*)\"\\s");
        if (boost::regex_search(listTitle, regResults, re))
        {
            std::string crop = regResults[1];
            boost::trim(crop);
            result.setCrop(crop);
        }

        // refresh="..."
        re = boost::regex("refresh=\"*(\\d*)?\"*");
        if (boost::regex_search(listTitle, regResults, re))
        {
            std::string refresh = regResults[1];
            boost::trim(refresh);
            result.setRefreshPeriod(std::stoi(refresh));
        }

        // m3uautoload=1
        re = boost::regex("m3uautoload=\"*(\\d?)?\"*");
        if (boost::regex_search(listTitle, regResults, re))
        {
            std::string autoload = regResults[1];
            boost::trim(autoload);
            Autoload load = std::stoi(autoload) == 1 ? Autoload::Autoload : Autoload::NotAutoload;
            result.setAutoload(load);
        }

        // tvg-shift=(...-2, -1, 0, +1, +2, ...)
        re = boost::regex("tvg-shift=\"*([+|-]?\\d?)?\"*");
        if (boost::regex_search(listTitle, regResults, re))
        {
            std::string shift = regResults[1];
            boost::trim(shift);
            result.setTvgShift(std::stoi(shift));
        }
    }

    return result;
}


/**
 * Разбор строки с наименованием группы каналов
 * @param groupName Строка с заголовком группы каналов
 * @return Название группы каналов
 */
std::string M3UParser::getGroupName(const std::string& groupName) const
{
    std::string res;
    boost::regex re("#EXTGRP:(.*)");
    boost::smatch regResults;

    if (boost::regex_search(groupName, regResults, re))
    {
        res = regResults[1];
        boost::trim(res);
    }

    return res;
}


/**
 * Разбор строки с наименованием списка воспроизведения
 * @param listName Строка с наименованием списка воспроизведения
 * @return Наименование списка воспроизведения
 */
std::string M3UParser::getListName(const std::string& listName) const
{
    std::string res;
    boost::regex re("#PLAYLIST:(.*)");
    boost::smatch regResult;

    if (boost::regex_search(listName, regResult, re))
    {
        res = regResult[1];
        boost::trim(res);
    }

    return res;
}


/**
 * Разбор строки с параметрами VLC
 * @param vlcParams Строка с параметрами VLC
 * @return Параметры VLC
 */
VlcInfo M3UParser::getVlcOpt(const std::string& vlcParams) const
{
    VlcInfo res;
    boost::regex re("#EXTVLCOPT:http-user-agent=(.*)");
    boost::smatch regResult;

    if (boost::regex_search(vlcParams, regResult, re))
    {
        res.userAgent = regResult[1];
        boost::trim(res.userAgent);
    }

    re = boost::regex("#EXTVLCOPT:http-referrer=(.*)");
    if (boost::regex_search(vlcParams, regResult, re))
    {
        res.httpReferrer = regResult[1];
        boost::trim(res.httpReferrer);
    }

    return res;
}


/**
 * Разбор строки с параметрами канала
 * @param channel Строка с параметрами канала
 * @return Параметры канала
 */
Channel* M3UParser::getChannelInfo(std::string& channel) const
{
    Channel *res = new Channel();
    if (!channel.empty())
    {
        // Анализируем строку на наличие параметров списка

        // #EXTINF:...
        boost::regex re("#EXTINF:([+,-]?[0-9]+)");
        boost::smatch regResult;
        if (boost::regex_search(channel, regResult, re))
        {
            std::string val = regResult[1];
            boost::trim(val);
            res->setDuration(std::stoi(val));
        }

        // tvg-id="..."
        re = boost::regex("tvg-id=(\"|')([^\"']+)");
        if (boost::regex_search(channel, regResult, re))
        {
            std::string val = regResult[1]; // regResult[2]
            boost::trim(val);
            res->setTvgId(val);
        }

        // tvg-name="..."
        re = boost::regex("tvg-name=(\"|')([^\"']+)");
        if (boost::regex_search(channel, regResult, re))
        {
            std::string val = regResult[1]; // regResult[2]
            boost::trim(val);
            res->setTvgName(val);
        }

        // tvg-logo="..."
        re = boost::regex("tvg-logo=(\"|')([^\"']+)");
        if (boost::regex_search(channel, regResult, re))
        {
            std::string val = regResult[1]; // regResult[2]
            boost::trim(val);
            res->setTvgLogo(val);
        }

        // tvg-epg="..."
        re = boost::regex("tvg-epg=(\"|')([^\"']+)");
        if (boost::regex_search(channel, regResult, re))
        {
            std::string val = regResult[1]; // regResult[2]
            boost::trim(val);
            res->setTvgEpg(val);
        }

        // tvg-shift="..."
        re = boost::regex ("tvg-shift=(\"|')([^\"']+)");
        if (boost::regex_search(channel, regResult, re))
        {
            std::string val = regResult[1]; // regResult[2]
            boost::trim(val);
            res->setTvgShift(std::stoi(val));
        }

        // group-title="..."
        re = boost::regex("group-title=(\"|')([^\"']+)");
        if (boost::regex_search(channel, regResult, re))
        {
            std::string val = regResult[1]; // regResult[2]
            boost::trim(val);
            res->setGroupName(val);
        }

        // radio="..."
        re = boost::regex("radio=(\"|')([^\"']+)");
        if (boost::regex_search(channel, regResult, re))
        {
            std::string val = regResult[1]; // regResult[2]
            boost::trim(val);
            Radio radio = std::stoi(val) == 1 ? Radio::Radio : Radio::NotRadio;
            res->setRadio(radio);
        }

        // aspect-ratio="..."
        re = boost::regex("aspect-ratio=(\"|')([^\"']+)");
        if (boost::regex_search(channel, regResult, re))
        {
            std::string val = regResult[1]; // regResult[2]
            boost::trim(val);
            res->setAspectRatio(val);
        }

        // audio-track="..."
        re = boost::regex("audio-track=(\"|')([^\"']+)");
        if (boost::regex_search(channel, regResult, re))
        {
            std::string val = regResult[1]; // regResult[2]
            boost::trim(val);
            res->setAudioTrack(val);
        }

        // recordable="..."
        re = boost::regex("recordable=(\"|')([^\"']+)");
        if (boost::regex_search(channel, regResult, re))
        {
            std::string val = regResult[1]; // regResult[2]
            boost::trim(val);
            Recordable rec = val == "true" ? Recordable::Recordable : Recordable::NotRecordable;
            res->setRecordable(rec);
        }

        // censored="..."
        re = boost::regex("censored=(\"|')([^\"']+)");
        if (boost::regex_search(channel, regResult, re))
        {
            std::string val = regResult[1]; // regResult[2]
            boost::trim(val);
            Censored censored = std::stoi(val) == 1 ? Censored::Censored : Censored::NotCensored;
            res->setCensored(censored);
        }

        // agerestriction="..."
        re = boost::regex("agerestriction=(\"|')([^\"']+)");
        if (boost::regex_search(channel, regResult, re))
        {
            std::string val = regResult[1]; // regResult[2]
            boost::trim(val);
            AgeRestricted ageRestricted = std::stoi(val) == 1 ? AgeRestricted::Restricted : AgeRestricted::NotRestricted;
            res->setAgeRestricted(ageRestricted);
        }

        // url-m3u="..."
        re = boost::regex("url-m3u=(\"|')([^\"']+)");
        if (boost::regex_search(channel, regResult, re))
        {
            std::string val = regResult[1]; // regResult[2]
            boost::trim(val);
            res->setUrlM3u(val);
        }

        // nameaskey="..."
        re = boost::regex("nameaskey=(\"|')([^\"']+)");
        if (boost::regex_search(channel, regResult, re))
        {
            std::string val = regResult[1]; // regResult[2]
            boost::trim(val);
            KeyType keyType = std::stoi(val) == 1 ? KeyType::KeyAsName : KeyType::KeyAsSome;
            res->setKeyType(keyType);
        }

        // crop="..."
        re = boost::regex ("crop=(\"|')([^\"']+)");
        if (boost::regex_search(channel, regResult, re))
        {
            std::string val = regResult[1]; // regResult[2]
            boost::trim(val);
            res->setCrop(val);
        }

        // mono="..."
        re = boost::regex("mono=(\"|')([^\"']+)");
        if (boost::regex_search(channel, regResult, re))
        {
            std::string val = regResult[1]; // regResult[2]
            boost::trim(val);
            SoundType soundType = std::stoi(val) == 1 ? SoundType::Mono : SoundType::Stereo;
            res->setSoundType(soundType);
        }

        // Название канала после запятой
        re = boost::regex(",([^\n]*)");
        if (boost::regex_search(channel, regResult, re))
        {
            std::string val = regResult[1];
            boost::trim(val);
            res->setName(val);
        }
    }

    return res;
}
