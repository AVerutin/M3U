#ifndef GTK4_DEFINITIONS_H
#define GTK4_DEFINITIONS_H

enum class LogType
{
    Debug = 0,
    Information,
    Warning,
    Error
};

enum class Radio
{
    Radio = true,
    NotRadio = false
};

enum class Recordable
{
    Recordable = true,
    NotRecordable = false
};

enum class Censored
{
    Censored = true,
    NotCensored = false
};

enum class AgeRestricted
{
    Restricted = true,
    NotRestricted = false
};

enum class SoundType
{
    Mono = true,
    Stereo = false
};

enum class KeyType
{
    KeyAsName = true,
    KeyAsSome = false
};

enum class Autoload
{
    Autoload = true,
    NotAutoload = false
};

#endif //GTK4_DEFINITIONS_H
