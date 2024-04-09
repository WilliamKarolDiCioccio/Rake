#include <vector>
#include <map>
#include <nlohmann/json.hpp>

namespace Rake::utils {

template <typename T>
concept TrivialJSONWritable = std::is_same_v<T, std::string> || std::is_arithmetic_v<T> || std::is_same_v<T, bool>;

template <typename T>
nlohmann::json VectorToJSON(const std::vector<T>& _arr)
    requires TrivialJSONWritable<T>
{
    nlohmann::json json_array;

    for (const auto& element : _arr) json_array.push_back(element);

    return json_array;
}

template <typename T>
void VectorFromJSON(std::vector<T>& _arr, const nlohmann::json& _json)
    requires TrivialJSONWritable<T>
{
    if (!_json.is_array()) return;

    for (const auto& e : _json) _arr.emplace_back(e.get<T>());
}

template <typename Key, typename Value>
nlohmann::json MapToJSON(const std::map<Key, Value>& _map)
    requires std::is_same_v<Key, std::string> && TrivialJSONWritable<Value>
{
    nlohmann::json json_map;

    for (const auto& [k, v] : _map) json_map[k] = v;

    return json_map;
}

template <typename Key, typename Value>
void MapFromJSON(std::map<Key, Value>& _map, const nlohmann::json& _json)
    requires std::is_same_v<Key, std::string> && TrivialJSONWritable<Value>
{
    if (!_json.is_structured()) return;

    for (const auto& [k, v] : _json.items()) _map[k] = v.get<Value>();
}

}  // namespace Rake::utils
