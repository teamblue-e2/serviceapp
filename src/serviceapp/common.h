#ifndef __serviceapp__common_
#define __serviceapp__common_

#ifndef NO_PYTHON
#include <Python.h>
#endif

#ifndef NO_UCHARDET
#include <uchardet/uchardet.h>
#endif

#include <algorithm>
#include <cctype>
#include <functional>
#include <locale>
#include <map>
#include <string>
#include <vector>
#include <sstream>
class SettingEntry;

typedef std::map<std::string, std::string> HeaderMap;
typedef std::map<std::string, SettingEntry> SettingMap;
typedef SettingMap::const_iterator SettingIter;

class IOption
{
public:
	virtual int update(const std::string&, const std::string&) = 0;
    virtual void print() const = 0;
};

class SettingEntry
{
public:
    SettingEntry();
    SettingEntry(const std::string &app_arg, int value, const std::string value_type);
    SettingEntry(const std::string &app_arg, const std::string &value, const std::string value_type);
    SettingEntry(const std::string &app_arg, const std::string value_type);
    void setValue(int value);
    void setValue(std::string value);
    std::string getAppArg() const;
    std::string getValue() const;
    int getValueInt() const;
    std::string toString() const;
    std::string getType() const;
    bool isSet() const;
private:
    bool m_is_set;
    std::string m_app_arg;
    std::string m_string_value;
    int m_int_value;
    std::string m_value_type;
};

class Url
{
    std::string m_url;
    std::string m_proto;
    std::string m_host;
    unsigned int m_port;
    std::string m_path;
    std::string m_query;
    std::string m_fragment;
    std::string url() const;
    std::string host() const;
    unsigned int port() const;
    std::string path() const;
    std::string query() const;
    std::string fragment() const;
    void parseUrl(const std::string url);

public:
    Url(const std::string &url);
    std::string url(){return m_url;}
    std::string proto(){return m_proto;}
    std::string host(){return m_host;}
    int port(){return m_port;}
    std::string path(){return m_path;}
    std::string query(){return m_query;}
    std::string fragment(){return m_fragment;}
};

void splitExtension(const std::string &path, std::string &basename, std::string &extension);
void splitPath(const std::string &path, std::string &dirpath, std::string &filename);
int listDir(const std::string &dirpath, std::vector<std::string> *directories, std::vector<std::string> *files);

#ifndef NO_UCHARDET
int detectEncoding(const std::string &content, std::string &encoding);
#endif

#ifndef NO_PYTHON
int convertToUTF8(const std::string &input_string, const std::string &input_encoding, std::string &output_string);
int convertToUTF8(const std::string &input_string, std::string &output_string);
#endif
HeaderMap getHeaders(const std::string& url);

inline std::string &rtrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}
#endif
