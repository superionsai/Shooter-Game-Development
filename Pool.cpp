#pragma once
#include <unordered_map>
#include <queue>
#include <string>
#include "Vector3.h"

class Pool {
private:
    static std::unordered_map<std::string, std::queue<void*>> pools;

public:
    static void* Get(const std::string& prefab, const Vector3& pos) {
        if (!pools[prefab].empty()) {
            void* obj = pools[prefab].front();
            pools[prefab].pop();
            // Reset position with pos if needed
            return obj;
        }
        // TODO: create new instance of prefab
        return nullptr;
    }

    static void Return(const std::string& prefab, void* instance) {
        pools[prefab].push(instance);
    }
};

std::unordered_map<std::string, std::queue<void*>> Pool::pools;
