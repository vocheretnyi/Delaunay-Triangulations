//
// Created by Viacheslav on 24.05.2019.
//

#include <algorithm>

#include "MinimumSpanningTree.h"

template<class V>
MinimumSpanningTree<V>::MinimumSpanningTree() {
    dsu = DisjointSetUnion();
}

template<typename V>
template<typename D>
pair<vector<GraphEdge<V, D>>, D> MinimumSpanningTree<V>::getMST(vector<GraphEdge<V, D>> edges) {
    sort(edges.begin(), edges.end(), [](const GraphEdge<V, D>& edge1, const GraphEdge<V, D>& edge2) {
       return edge1.getLength() < edge2.getLength();
    });

    vector<GraphEdge<V, D>> mst_edges;
    D mst_length = 0;

    for (const auto& edge : edges) {
        if (!dsu.isVertexesConnected(edge.getFrom(), edge.getTo())) {
            dsu.connectVertexes(edge.getFrom(), edge.getTo());
            mst_length += edge.getLength();
            mst_edges.push_back(edge);
        }
    }

    return {move(mst_edges), mst_length};
}

template<typename V>
bool MinimumSpanningTree<V>::DisjointSetUnion::connectVertexes(V v, V u) {
    v = getParent(v);
    u = getParent(u);
    if (v == u) {
        return false;
    }
    parent[v] = u;
    return true;
}

template<typename V>
bool MinimumSpanningTree<V>::DisjointSetUnion::isVertexesConnected(V v, V u) {
    v = getParent(v);
    u = getParent(u);
    return v == u;
}

template<typename V>
V MinimumSpanningTree<V>::DisjointSetUnion::getParent(V v) {
    if (parent.find(v) == parent.end()) {
        return parent[v] = v;
    }
    if (parent[v] == v) {
        return v;
    }
    return parent[v] = getParent(parent[v]);
}