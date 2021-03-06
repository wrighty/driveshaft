#ifndef incl_DRIVESHAFT_MAIN_LOOP_H_
#define incl_DRIVESHAFT_MAIN_LOOP_H_

#include <string>
#include <map>
#include <utility>
#include <time.h>
#include "common-defs.h"
#include "thread-registry.h"

namespace Driveshaft {

/* count-of-workers -> [job names] */
typedef std::pair<uint32_t, StringSet> PoolData;
typedef std::map<std::string, PoolData> PoolMap;

struct DriveshaftConfig {
    StringSet m_servers_list;
    int64_t m_timeout;
    std::string m_http_uri;
    PoolMap m_pool_map;
    time_t m_load_time;

    std::pair<StringSet, StringSet> compare(const DriveshaftConfig& against) const noexcept;
};

class MainLoop {

public:
    static MainLoop& getInstance(const std::string& config_file) noexcept;
    void run() noexcept;

private:
    MainLoop(const std::string& config_file) noexcept;
    bool setupSignals() const noexcept;
    void doShutdown(uint32_t wait) noexcept;
    void modifyPool(const std::string& name) noexcept;
    bool loadConfig(DriveshaftConfig& new_config) noexcept;
    void checkRunningConfigAndRegistry() noexcept;

    ~MainLoop() = default;

    MainLoop() = delete;
    MainLoop(const MainLoop&) = delete;
    MainLoop(MainLoop&&) = delete;
    MainLoop& operator=(const MainLoop&) = delete;
    MainLoop& operator=(const MainLoop&&) = delete;

    std::string m_config_filename;
    DriveshaftConfig m_config;
    ThreadRegistryPtr m_thread_registry;
};

} // namespace Driveshaft

#endif // incl_DRIVESHAFT_MAIN_REGISTRY_H_
