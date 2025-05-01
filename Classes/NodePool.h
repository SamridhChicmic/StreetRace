#ifndef __NODE_POOL_H__
#define __NODE_POOL_H__

#include "cocos2d.h"
#include <vector>
using namespace cocos2d;


class NodePool: public Component {
public:
    NodePool();
    ~NodePool();

    // Get a node from the pool or return nullptr if empty
    Sprite* getNode();

    // Return a node to the pool
    void returnNode(Sprite* node);

    // Add a new node to the pool
    void addNode(Sprite* node);

private:
    std::vector<Sprite *> pool;
};

#endif // __NODE_POOL_H__
