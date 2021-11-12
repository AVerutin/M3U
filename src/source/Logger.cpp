#include "Logger.h"

Logger::Logger(std::string unitName) : m_unitName{std::move(unitName)}
{
}

Logger::~Logger() = default;

/**
 * Вывод отладочного сообщения в файл.
 * @param msg текст сообщения.
 * @return true if the flags are valid, false otherwise.
 */
void Logger::debug(const std::string& msg)
{
    writeMessage(msg, LogType::Debug);
}

/**
 * Вывод информационного сообщения
 * @param msg Текст сообщения
 */
void Logger::info(const std::string& msg)
{
    writeMessage(msg, LogType::Information);
}

/**
 * Вывод предупреждающего сообщения
 * @param msg Текст сообщения
 */
void Logger::warn(const std::string& msg)
{
    writeMessage(msg, LogType::Warning);
}

/**
 * Вывод сообщения об ошибке
 * @param msg Текст сообщения
 */
void Logger::error(const std::string& msg)
{
    writeMessage(msg, LogType::Error);
}

/**
 * Запись сообщения в файл
 * @param msg Текст сообщения
 * @param logType Тип сообщения
 */
void Logger::writeMessage(const std::string& msg, LogType logType)
{
    std::string type;

    // Определение типа информационного сообщения
    switch (logType)
    {
        case LogType::Debug : type = "DEB"; break;
        case LogType::Information : type = "INF"; break;
        case LogType::Warning : type = "WRN"; break;
        case LogType::Error : type = "ERR"; break;
    }

    // Получение времени вывода сообщения
    std::time_t time = std::time(nullptr);
    std::tm now = *std::localtime(&time);
    auto date = std::put_time(&now, "%d.%m.%Y %H:%M:%S");

    // Формирование строки сообщения
    std::stringstream message;
    message <<"[" <<date <<"] ( "<<type <<" : " <<this->m_unitName <<" ) => Message: " <<msg;

    // Запись сообщения в файл
    std::string log = logName();
    std::ofstream out(log, std::ios::app);

    // Если файл удалось открыть
    if (out.is_open())
        out <<message.str() << std::endl;

    out.close();
}

/**
 * Сформировать имя файла лога по текущей дате
 * @return Имя файла лога
 */
std::string Logger::logName()
{
    // Получить текущую дату
    std::time_t time = std::time(nullptr);
    std::tm now = *std::localtime(&time);
    auto date = std::put_time(&now, "%Y-%m-%d");

    // Получить имя каталога для сохранения логов
    std::filesystem::path full_path = std::filesystem::current_path();
    std::string path = full_path.string() + "\\Logs\\";

    // Проверим, существует ли каталог для хранения логов
    if (!std::filesystem::exists(path))
        std::filesystem::create_directories(path);

    // Сформируем полное имя файла
    std::stringstream logName;
    logName <<path <<date <<".log";

    return logName.str();
}
