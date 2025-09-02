#pragma once

#include <unordered_map>
#include <optional> // 用于C++17及以上的optional类型

// 定义扩展函数的命名空间
namespace UnorderedMapExtensions {
    // 1. 模拟tryGet：检查键是否存在，存在则返回值（通过输出参数），返回bool表示结果
    template<typename K, typename V, 
             typename Hash = std::hash<K>, 
             typename KeyEqual = std::equal_to<K>,
             typename Alloc = std::allocator<std::pair<const K, V>>>
    bool tryGetValue(const std::unordered_map<K, V, Hash, KeyEqual, Alloc>& map, 
                const K& key, 
                V& outValue) {
        auto it = map.find(key);
        if (it != map.end()) {
            outValue = it->second;
            return true;
        }
        return false;
    }

    // 2. getOrDefault：获取键的值，若不存在则返回默认值
    template<typename K, typename V, 
             typename Hash = std::hash<K>, 
             typename KeyEqual = std::equal_to<K>,
             typename Alloc = std::allocator<std::pair<const K, V>>>
    V getOrDefault(const std::unordered_map<K, V, Hash, KeyEqual, Alloc>& map, 
                   const K& key, 
                   const V& defaultValue) {
        auto it = map.find(key);
        return (it != map.end()) ? it->second : defaultValue;
    }

    // 3. contains：检查键是否存在（C++20标准库已内置contains，此处为兼容旧标准示例）
    template<typename K, typename V, 
             typename Hash = std::hash<K>, 
             typename KeyEqual = std::equal_to<K>,
             typename Alloc = std::allocator<std::pair<const K, V>>>
    bool contains(const std::unordered_map<K, V, Hash, KeyEqual, Alloc>& map, 
                  const K& key) {
        return map.find(key) != map.end();
    }

    // 4. （C++17+）tryGetOptional：返回optional类型，避免输出参数
    template<typename K, typename V, 
             typename Hash = std::hash<K>, 
             typename KeyEqual = std::equal_to<K>,
             typename Alloc = std::allocator<std::pair<const K, V>>>
    std::optional<V> tryGetOptional(const std::unordered_map<K, V, Hash, KeyEqual, Alloc>& map, 
                                    const K& key) {
        auto it = map.find(key);
        if (it != map.end()) {
            return it->second; // 存在则返回包含值的optional
        }
        return std::nullopt; // 不存在则返回空optional
    }
} // namespace UnorderedMapExtensions
