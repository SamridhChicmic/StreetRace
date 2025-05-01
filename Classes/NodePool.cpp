#include "cocos2d.h"
#include "NodePool.h"

NodePool::NodePool() = default;
NodePool:: ~NodePool() {
        // Cleanup all nodes in the pool
        for (auto node : pool) {
            node->release();
        }
    }

    // Get a node from the pool or create a new one if the pool is empty
    Sprite* NodePool:: getNode() {
        if (!pool.empty()) {
            Sprite* node = pool.back();
            pool.pop_back();
            return node;
        }
        return nullptr;  // Pool is empty
    }

    // Return a node back to the pool
    void  NodePool:: returnNode(Sprite* node) {
        pool.push_back(node);
    }

    // Add a new node to the pool
    void NodePool:: addNode(Sprite* node) {
        node->retain();
        pool.push_back(node);
    }


