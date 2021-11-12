#include "Channel.h"

Channel::Channel() :
    mBaseId{0},
    mName{},
    mPosition{1},
    mDuration{0},
    mTvgId{},
    mTvgName{0},
    mTvgLogo{},
    mTvgEpg{},
    mTvgShift{0},
    mGroupName{},
    mGroupUid{0},
    mAudioTrack{"RU"},
    mAudioTrackUid{},
    mRadio{Radio::NotRadio},
    mAspect{"16:9"},
    mCrop{},
    mRecordable{Recordable::NotRecordable},
    mCensored{Censored::NotCensored},
    mAgeRestricted{AgeRestricted::NotRestricted},
    mSoundType{SoundType::Stereo},
    mKeyType{KeyType::KeyAsSome},
    mUrlM3u{},
    mUrl{},
    mUserAgent{},
    mHttpReferrer{}
{}


/// Установить уникальный идентификатор канала
void Channel::setBaseId(int uid)
{
    this->mBaseId = uid;
}


/// Получить уникальный идентификатор канала
int Channel::getBaseId() const
{
    return this->mBaseId;
}


/// Наименование канала
void Channel::setName(std::string_view n)
{
    if (n.size()>0)
        this->mName = n;
}

std::string Channel::getName() const
{
    return this->mName;
}


/// Номер позиции
void Channel::setPosition(int pos)
{
    if (pos>0)
        this->mPosition = pos;
}

int Channel::getPosition() const
{
    return this->mPosition;
}


/// Длительность трека
void Channel::setDuration(int dur)
{
    this->mDuration = dur;
}

int Channel::getDuration() const
{
    return this->mDuration;
}


/// tvg_id
void Channel::setTvgId(std::string_view id)
{
    this->mTvgId = id;
}

std::string Channel::getTvgId() const
{
    return this->mTvgId;
}

/// tvg_name
void Channel::setTvgName(std::string_view n)
{
    this->mTvgName = n;
}

std::string Channel::getTvgName() const
{
    return this->mTvgName;
}


/// tvg_logo
void Channel::setTvgLogo(std::string_view logo)
{
    this->mTvgLogo = logo;
}

std::string Channel::getTvgLogo() const
{
    return this->mTvgLogo;
}


/// tvg_epg
void Channel::setTvgEpg(std::string_view epg)
{
    this->mTvgEpg = epg;
}

std::string Channel::getTvgEpg() const
{
    return this->mTvgEpg;
}


/// tvg_shift
void Channel::setTvgShift(int shift)
{
    this->mTvgShift = shift;
}

int Channel::getTvgShift() const
{
    return this->mTvgShift;
}


/// group_name
void Channel::setGroupName(std::string_view group)
{
    this->mGroupName = group;
}

std::string Channel::getGroupName() const
{
    return this->mGroupName;
}


/// Внешний ключ на таблицу групп
void Channel::setGroupUid(int id)
{
    this->mGroupUid = id;
}

int Channel::getGroupUid() const
{
    return this->mGroupUid;
}


/// audiotrack
void Channel::setAudioTrack(std::string_view track)
{
    this->mAudioTrack = track;
}

std::string Channel::getAudioTrack() const
{
    return this->mAudioTrack;
}


/// Внешний ключ на таблицу звуковых дорожек
void Channel::setAudioTrackUid(int id)
{
    this->mAudioTrackUid = id;
}

int Channel::getAudioTrackUid() const
{
    return this->mAudioTrackUid;
}


/// radio
void Channel::setRadio(Radio radio)
{
    this->mRadio = radio;
}

Radio Channel::isRadio() const
{
    return this->mRadio;
}


/// aspect_ratio
void Channel::setAspectRatio(std::string_view ratio)
{
    this->mAspect = ratio;
}

std::string Channel::getAspectRatio() const
{
    return this->mAspect;
}


/// crop
void Channel::setCrop(std::string_view cr)
{
    this->mCrop = cr;
}

std::string Channel::getCrop() const
{
    return this->mCrop;
}


/// recordable
void Channel::setRecordable(Recordable record)
{
    this->mRecordable = record;
}

Recordable Channel::isRecordable() const
{
    return this->mRecordable;
}


/// censored
void Channel::setCensored(Censored censored)
{
    this->mCensored = censored;
}

Censored Channel::isCensored() const
{
    return this->mCensored;
}


/// age_restricted
void Channel::setAgeRestricted(AgeRestricted restricted)
{
    this->mAgeRestricted = restricted;
}

AgeRestricted Channel::isAgeRestricted() const
{
    return this->mAgeRestricted;
}


/// mono
void Channel::setSoundType(SoundType soundType)
{
    this->mSoundType = soundType;
}

SoundType Channel::getSoundType() const
{
    return this->mSoundType;
}


/// name_as_key
void Channel::setKeyType(KeyType keyType)
{
    this->mKeyType = keyType;
}

KeyType Channel::getKeyType() const
{
    return this->mKeyType;
}


/// url_m3u
void Channel::setUrlM3u(std::string_view u)
{
    this->mUrlM3u = u;
}

std::string Channel::getUrlM3u() const
{
    return this->mUrlM3u;
}


/// channel source
void Channel::setUrl(std::string_view source)
{
    this->mUrl = source;
}

std::string Channel::getUrl() const
{
    return this->mUrl;
}


/// vlc_opt user_agent
void Channel::setUserAgent(std::string_view agent)
{
    this->mUserAgent = agent;
}

std::string Channel::getUserAgent() const
{
    return this->mUserAgent;
}


/// vlc_opt http_referrer
void Channel::setHttpReferrer(std::string_view referrer)
{
    this->mHttpReferrer = referrer;
}

std::string Channel::getHttpReferrer() const
{
    return this->mHttpReferrer;
}


/// Перегрузка оператора присваиванию
Channel &Channel::operator=(const Channel& channel)
{
    this->mName = channel.mName;
    this->mPosition = channel.mPosition;
    this->mDuration = channel.mDuration;
    this->mTvgId = channel.mTvgId;
    this->mTvgName = channel.mTvgName;
    this->mTvgLogo = channel.mTvgLogo;
    this->mTvgEpg = channel.mTvgEpg;
    this->mTvgShift = channel.mTvgShift;
    this->mGroupUid = channel.mGroupUid;
    this->mGroupName = channel.mGroupName;
    this->mAudioTrackUid = channel.mAudioTrackUid;
    this->mAudioTrack = channel.mAudioTrack;
    this->mAspect = channel.mAspect;
    this->mCrop = channel.mCrop;
    this->mRecordable = channel.mRecordable;
    this->mCensored = channel.mCensored;
    this->mAgeRestricted = channel.mAgeRestricted;
    this->mSoundType = channel.mSoundType;
    this->mKeyType = channel.mKeyType;
    this->mUrlM3u = channel.mUrlM3u;
    this->mUrl = channel.mUrl;
    this->mUserAgent = channel.mUserAgent;
    this->mHttpReferrer = channel.mHttpReferrer;

    return *this;
}


// /// Перегрузка оператора сравнения
//bool operator==(const Channel &left, const Channel &right)
//{
//    bool result = false;
//    result = left.getName() == right.getName();

//    return result;
//}
