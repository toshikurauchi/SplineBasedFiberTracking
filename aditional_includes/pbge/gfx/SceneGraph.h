
#ifndef gfxsnode_h_
#define gfxsnode_h_

#include <vector>

#include "math3d/math3d.h"

#include "pbge/core/core.h"

namespace pbge {
    class Node;

    class PBGE_EXPORT SceneGraph{
    public:
        static const int ROOT = 0;

        SceneGraph(Node * node) {
            nodes.push_back(node);
        }

        ~SceneGraph();

        Node * getSceneGraphRoot() {
            return nodes.at(0);
        }

        Node * appendChildTo(int index, Node * child);

        Node * appendChildTo(Node * parent, Node * child);

        Node * getGraphNode(int index);

        void setAmbientLightColor(const math3d::vector4 & color);

        void setAmbientLightColor(const float & red, const float & green, const float & blue, const float & alpha);

        const math3d::vector4 getAmbientLightColor() const;
    private:
        math3d::vector4 ambientLight;
        std::vector<Node*> nodes;
    };
}
#endif

