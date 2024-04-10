#include "RKRuntime/base.hpp"

#include <vector>
#include <algorithm>

#include "defines.hpp"

#include "pool.hpp"

namespace Rake::libraries {

/**
 * @brief Represents a Bidirectional Graph data structure.
 *
 * This class provides functionality to manage a bidirectional graph,
 * where nodes can be linked bidirectionally with other nodes.
 * It uses a MemoryPool for memory management.
 *
 * @tparam T The type of data stored in each node.
 * @tparam U The type of data stored in each link.
 */
template <typename T, typename U>
class BidirectionalGraph {
   private:
    struct Node;

    struct Link {
        U data;
        Node* ptr;

        Link() : data(U{}), ptr(nullptr) {}
        Link(const U& _data, Node* _ptr) : data(_data), ptr(_ptr) {}
    };

    struct Node {
        T data;
        std::vector<Link> links;

        Node() : data(T{}), links({}) {}
        Node(const T& _value) : data(_value) {}

        NODISCARD inline size_t degree() const noexcept { return links.size(); }
    };

    size_t m_size;
    MemoryPool<Node> m_pool;

   public:
    class Iterator final : public std::iterator<std::bidirectional_iterator_tag, T> {};

   public:
    /**
     * @brief Constructs a BidirectionalGraph with the given capacity.
     *
     * @param _capacity The initial capacity of the graph.
     */
    BidirectionalGraph(size_t _capacity) : m_size(0), m_pool(_capacity) {}

    /**
     * @brief Destroys the BidirectionalGraph and releases allocated memory.
     */
    ~BidirectionalGraph() { Clear(); }

   public:
    /**
     * @brief Inserts a new node with the given data into the graph.
     *
     * @param _nodeData The data to be stored in the new node.
     * @return Node* A pointer to the newly created node.
     */
    Node* InsertNode(const T& _nodeData);

    /**
     * @brief Links two nodes with the given link data.
     *
     * @param _node1 The first node to be linked.
     * @param _node2 The second node to be linked.
     * @param _linkData The data to be stored in the link.
     */
    void LinkNodes(Node* _node1, Node* _node2, const U& _linkData);

    /**
     * @brief Removes a node from the graph.
     *
     * This function removes the specified node from the graph
     * and also removes all links connected to that node.
     *
     * @param _node The node to be removed.
     */
    void EraseNode(Node* _node);

    /**
     * @brief Removes a link from the specified node.
     *
     * @param _node The node from which the link is to be removed.
     * @param _index The index of the link to be removed.
     */
    void EraseLink(Node* _node, size_t _index);

    /**
     * @brief Clears all nodes and links from the graph.
     *
     * This function removes all nodes and links from the graph
     * and releases all allocated memory.
     */
    void Clear() { m_pool.Clear(); }

   public:
    /**
     * @brief Returns the current number of nodes in the graph.
     *
     * @return size_t The number of nodes in the graph.
     */
    NODISCARD inline size_t size() const noexcept { return m_pool.size(); };

    /**
     * @brief Returns the current capacity of the graph.
     *
     * @return size_t The current capacity of the graph.
     */
    NODISCARD inline size_t capacity() const noexcept { return m_pool.capacity(); }
};

template <typename T, typename U>
typename BidirectionalGraph<T, U>::Node* BidirectionalGraph<T, U>::InsertNode(const T& _nodeData) {
    Node* newNode = m_pool.Construct(_nodeData);
    m_size++;
    return newNode;
}

template <typename T, typename U>
void BidirectionalGraph<T, U>::LinkNodes(Node* _node1, Node* _node2, const U& _linkData) {
    auto toNode2Link = Link(_linkData, _node2);
    _node1->links.push_back(toNode2Link);
    auto toNode1Link = Link(_linkData, _node1);
    _node2->links.push_back(toNode1Link);
}

template <typename T, typename U>
void BidirectionalGraph<T, U>::EraseNode(Node* _node) {
    if (_node == nullptr) return;

    for (auto& link : _node->links) {
        auto it = std::find_if(link.ptr->links.begin(), link.ptr->links.end(), [_node](const Link& _link) {
            return _link.ptr == _node;
        });

        if (it != link.ptr->links.end()) {
            link.ptr->links.erase(it);
        }
    }

    _node->links.clear();

    m_pool.Deallocate(_node);
    m_size--;
}

template <typename T, typename U>
void BidirectionalGraph<T, U>::EraseLink(Node* _node, size_t _index) {
    if (_index < _node->links.size()) {
        _node->links.erase(_node->links.begin() + _index);
    }
}

/**
 * @brief Represents a Unidirectional Graph data structure.
 *
 * This class provides functionality to manage a unidirectional graph,
 * where nodes can be linked unidirectionally with other nodes.
 * It uses a MemoryPool for memory management.
 *
 * @tparam T The type of data stored in each node.
 * @tparam U The type of data stored in each link.
 */
template <typename T, typename U>
class UnidirectionalGraph {
   private:
    struct Node;

    struct Link {
        U data;
        Node* ptr;

        Link() : data(U{}), ptr(nullptr) {}
        Link(const U& _data, Node* _ptr) : data(_data), ptr(_ptr) {}
    };

    struct Node {
        T data;
        std::vector<Link> links;
        std::vector<Link> ghostLinks;

        Node() : data(T{}), links({}), ghostLinks({}) {}
        Node(const T& _value) : data(_value) {}

        NODISCARD inline size_t degree() const noexcept { return links.size(); }
        NODISCARD inline size_t ghostDegree() const noexcept { return ghostLinks.size(); }
    };

    size_t m_size;
    MemoryPool<Node> m_pool;

   public:
    class Iterator final : public std::iterator<std::bidirectional_iterator_tag, T> {};

   public:
    /**
     * @brief Constructs a UnidirectionalGraph with the given capacity.
     *
     * @param _capacity The initial capacity of the graph.
     */
    UnidirectionalGraph(size_t _capacity) : m_size(0), m_pool(_capacity) {}

    /**
     * @brief Destroys the UnidirectionalGraph and releases allocated memory.
     */
    ~UnidirectionalGraph() { Clear(); }

   public:
    /**
     * @brief Inserts a new node with the given data into the graph.
     *
     * @param _nodeData The data to be stored in the new node.
     * @return Node* A pointer to the newly created node.
     */
    Node* InsertNode(const T& _nodeData);

    /**
     * @brief Links two nodes with the given link data.
     *
     * @param _node1 The first node to be linked.
     * @param _node2 The second node to be linked.
     * @param _linkData The data to be stored in the link.
     */
    void LinkNodes(Node* _node1, Node* _node2, const U& _linkData);

    /**
     * @brief Removes a node from the graph.
     *
     * This function removes the specified node from the graph
     * and also removes all links connected to that node.
     *
     * @param _node The node to be removed.
     */
    void EraseNode(Node* _node);

    /**
     * @brief Removes a link from the specified node.
     *
     * @param _node The node from which the link is to be removed.
     * @param _index The index of the link to be removed.
     */
    void EraseLink(Node* _node, size_t _index);

    /**
     * @brief Clears all nodes and links from the graph.
     *
     * This function removes all nodes and links from the graph
     * and releases all allocated memory.
     */
    void Clear() { m_pool.Clear(); }

   public:
    /**
     * @brief Returns the current number of nodes in the graph.
     *
     * @return size_t The number of nodes in the graph.
     */
    NODISCARD inline size_t size() const noexcept { return m_pool.size(); };

    /**
     * @brief Returns the current capacity of the graph.
     *
     * @return size_t The current capacity of the graph.
     */
    NODISCARD inline size_t capacity() const noexcept { return m_pool.capacity(); }
};

template <typename T, typename U>
typename UnidirectionalGraph<T, U>::Node* UnidirectionalGraph<T, U>::InsertNode(const T& _nodeData) {
    Node* newNode = m_pool.Construct(_nodeData);
    m_size++;
    return newNode;
}

template <typename T, typename U>
void UnidirectionalGraph<T, U>::LinkNodes(Node* _node1, Node* _node2, const U& _linkData) {
    auto toNode2Link = Link(_linkData, _node2);
    _node1->links.push_back(toNode2Link);
    auto toNode1Link = Link(_linkData, _node1);
    _node2->ghostLinks.push_back(toNode1Link);
}

template <typename T, typename U>
void UnidirectionalGraph<T, U>::EraseNode(Node* _node) {
    if (_node == nullptr) return;

    for (auto& link : _node->links) {
        auto it = std::find_if(link.ptr->ghostLinks.begin(), link.ptr->ghostLinks.end(), [_node](const Link& _link) {
            return _link.ptr == _node;
        });

        if (it != link.ptr->ghostLinks.end()) {
            link.ptr->ghostLinks.erase(it);
        }
    }

    _node->links.clear();
    _node->ghostLinks.clear();

    m_pool.Deallocate(_node);
    m_size--;
}

template <typename T, typename U>
void UnidirectionalGraph<T, U>::EraseLink(Node* _node, size_t _index) {
    if (_index < _node->links.size()) {
        _node->links.erase(_node->links.begin() + _index);
    }
}

}  // namespace Rake::libraries
