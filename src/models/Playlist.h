#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
#include <vector>
#include "Channel.h"


class Playlist
{
public:
    Playlist();
    void setBaseId(int);
    [[nodiscard]] int getBaseId() const;
    void setName(std::string_view name);
    [[nodiscard]] std::string getName() const;
    void setUrlTvg(std::string_view url);
    [[nodiscard]] std::string getUrlTvg() const;
    void setTvgShift(int shift);
    [[nodiscard]] int getTvgShift() const;
    void setCache(int cache);
    [[nodiscard]] int getCache() const;
    void setDeinterlace(int interlace);
    [[nodiscard]] int getDeinterlace() const;
    void setAspectRatio(std::string_view aspect);
    [[nodiscard]] std::string getAspectRatio() const;
    void setCrop(std::string_view crop);
    [[nodiscard]] std::string getCrop() const;
    void setRefreshPeriod(int period);
    [[nodiscard]] int getRefreshPeriod() const;
    void setAutoload(Autoload autoload);
    [[nodiscard]] Autoload isAutoload() const;

private:
    int mBaseId;
    std::string mName;
    std::string mUrlTvg;
    int mTvgShift;
    int mCache;
    int mDeinterlace;
    std::string mAspectRatio;
    std::string mCrop;
    int mRefreshPeriod;
    Autoload mAutoload;
};

#endif // PLAYLIST_H
