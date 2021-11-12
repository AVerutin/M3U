#ifndef CHANNEL_H
#define CHANNEL_H

#include <string>
#include "Definitions.h"

class Channel
{
public:
    Channel();
    void setBaseId(int id);
    [[nodiscard]] int getBaseId() const;
    void setName(std::string_view name);
    [[nodiscard]] std::string getName() const;
    void setPosition(int position);
    [[nodiscard]] int getPosition() const;
    void setDuration(int duration);
    [[nodiscard]] int getDuration() const;
    void setTvgId(std::string_view tvgId);
    [[nodiscard]] std::string getTvgId() const ;
    void setTvgName(std::string_view tvgName);
    [[nodiscard]] std::string getTvgName() const;
    void setTvgLogo(std::string_view tbgLogo);
    [[nodiscard]] std::string getTvgLogo() const;
    void setTvgEpg(std::string_view tvgEpg);
    [[nodiscard]] std::string getTvgEpg() const;
    void setTvgShift(int tvgShift);
    [[nodiscard]] int getTvgShift() const;
    void setGroupName(std::string_view groupName);
    [[nodiscard]] std::string getGroupName() const;
    void setGroupUid(int id);
    [[nodiscard]] int getGroupUid() const;
    void setAudioTrack(std::string_view audio);
    [[nodiscard]] std::string getAudioTrack() const;
    void setAudioTrackUid(int audioId);
    [[nodiscard]] int getAudioTrackUid() const;
    void setRadio(Radio radio);
    [[nodiscard]] Radio isRadio() const;
    void setAspectRatio(std::string_view aspect);
    [[nodiscard]] std::string getAspectRatio() const;
    void setCrop(std::string_view crop);
    [[nodiscard]] std::string getCrop() const;
    void setRecordable(Recordable recordable);
    [[nodiscard]] Recordable isRecordable() const;
    void setCensored(Censored censored);
    [[nodiscard]] Censored isCensored() const;
    void setAgeRestricted(AgeRestricted restricted);
    [[nodiscard]] AgeRestricted isAgeRestricted() const;
    void setSoundType(SoundType soundType);
    [[nodiscard]] SoundType getSoundType() const;
    void setKeyType(KeyType keyType);
    [[nodiscard]] KeyType getKeyType() const;
    void setUrlM3u(std::string_view urlM3U);
    [[nodiscard]] std::string getUrlM3u() const;
    void setUrl(std::string_view url);
    [[nodiscard]] std::string getUrl() const;
    void setUserAgent(std::string_view userAgent);
    [[nodiscard]] std::string getUserAgent() const;
    void setHttpReferrer(std::string_view httpReferrer);
    [[nodiscard]] std::string getHttpReferrer() const;

    Channel &operator=(const Channel& channel);

private:
    int mBaseId;
    std::string mName;
    int mPosition;
    int mDuration;
    std::string mTvgId;
    std::string mTvgName;
    std::string mTvgLogo;
    std::string mTvgEpg;
    int mTvgShift;
    std::string mGroupName;
    int mGroupUid;
    std::string mAudioTrack;
    int mAudioTrackUid;
    Radio mRadio;
    std::string mAspect;
    std::string mCrop;
    Recordable mRecordable;
    Censored mCensored;
    AgeRestricted mAgeRestricted;
    SoundType mSoundType;
    KeyType mKeyType;
    std::string mUrlM3u;
    std::string mUrl;
    std::string mUserAgent;
    std::string mHttpReferrer;
};

#endif // CHANNEL_H
