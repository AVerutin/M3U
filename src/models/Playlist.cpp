#include "Playlist.h"

Playlist::Playlist() :
    mBaseId{0},
    mName{},
    mUrlTvg{},
    mTvgShift{0},
    mCache{0},
    mDeinterlace{0},
    mAspectRatio{"16:9"},
    mCrop{},
    mRefreshPeriod{0},
    mAutoload{Autoload::NotAutoload}
{}


/// Установить уникальный идентификатор
void Playlist::setBaseId(int id)
{
    this->mBaseId = id;
}


/// Получить уникальный идентификатор
int Playlist::getBaseId() const
{
    return this->mBaseId;
}


/// Наименование списка воспроизведения
void Playlist::setName(std::string_view name)
{
    this->mName = name;
}

std::string Playlist::getName() const
{
    return this->mName;
}


/// Ссылка на программу передач
void Playlist::setUrlTvg(std::string_view url)
{
    this->mUrlTvg = url;
}

std::string Playlist::getUrlTvg() const
{
    return this->mUrlTvg;
}


/// Сдвиг времени в программе
void Playlist::setTvgShift(int shift)
{
    this->mTvgShift = shift;
}

int Playlist::getTvgShift() const
{
    return this->mTvgShift;
}


/// Размер кеша
void Playlist::setCache(int cache)
{
    this->mCache = cache;
}

int Playlist::getCache() const
{
    return this->mCache;
}


/// Режим черезстрочности
void Playlist::setDeinterlace(int interlace)
{
    this->mDeinterlace = interlace;
}

int Playlist::getDeinterlace() const
{
    return this->mDeinterlace;
}


/// Соотношение сторон
void Playlist::setAspectRatio(std::string_view aspect)
{
    this->mAspectRatio = aspect;
}

std::string Playlist::getAspectRatio() const
{
    return this->mAspectRatio;
}


/// Обрезка
void Playlist::setCrop(std::string_view crop)
{
    this->mCrop = crop;
}

std::string Playlist::getCrop() const
{
    return this->mCrop;
}


/// Период обновления
void Playlist::setRefreshPeriod(int period)
{
    this->mRefreshPeriod = period;
}

int Playlist::getRefreshPeriod() const
{
    return this->mRefreshPeriod;
}


/// Автозагрузка списка
void Playlist::setAutoload(Autoload autoload)
{
    this->mAutoload = autoload;
}

Autoload Playlist::isAutoload() const
{
    return this->mAutoload;
}
