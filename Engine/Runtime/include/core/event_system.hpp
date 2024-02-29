#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <typeindex>
#include <unordered_map>
#include <thread>
#include <iostream>

namespace Rake::core {

/**
 * @brief Represents an event with a templated data type.
 * 
 * @tparam T The type of data associated with the event.
 */
template <typename T>
class Event final {
   private:
    T m_data;

   public:
    /**
     * @brief Represents an event with a templated data type.
     * 
     * @tparam T The type of data associated with the event.
     */
    Event(const T& _data) : m_data(_data){};

   public:
    /**
     * @brief Get the const reference to the stored data.
     * 
     * @return const T& The data associated with the event.
     */
    NODISCARD const T& GetData() const noexcept { return m_data; }

    /**
     * @brief Get the hash code of the type of the stored data.
     * 
     * @return constexpr size_t The hash code of the type.
     */
    NODISCARD constexpr size_t GetType() const noexcept { return typeid(T).hash_code(); }
};

/**
 * @brief Represents an event handler that can process events of a specific type.
 * 
 * @tparam T The type of data associated with the events handled by this handler.
 */
template <typename T>
class EventHandler {
    using Callback = std::function<void(const T&)>;

   private:
    Callback m_callback;

   public:
    /**
     * @brief Constructor to initialize the event handler with a callback.
     * 
     * @param _callback The callback function to be invoked when handling an event.
     */
    EventHandler(const Callback& _callback) : m_callback(_callback) {}

   public:
    /**
     * @brief Update the callback function of the event handler.
     * 
     * @param _callback The new callback function.
     */
    void UpdateCallback(const Callback& _callback) noexcept { m_callback = _callback; }

    /**
     * @brief Handle an event by invoking the callback with the event data.
     * 
     * @param _event The event to be handled.
     */
    void HandleEvent(const Event<T>& _event) const {
        if (m_callback) {
            m_callback(_event.GetData());
        }
    }
};

/**
 * @brief Represents an event producer that can generate and notify events to registered handlers.
 * 
 * @tparam T The type of data associated with the events.
 */
template <typename T>
class EventProducer final {
   private:
    std::queue<Event<T>> m_eventQueue;
    std::mutex m_mutex;
    std::condition_variable m_condition;

    std::unordered_map<std::thread::id, std::vector<std::shared_ptr<EventHandler<T>>>> m_eventHandlers;

   public:
    EventProducer() = default;

   public:
    /**
     * @brief Add an event handler to the list of registered handlers.
     * 
     * @param _handler The event handler to be added.
     */
    void AddHandler(const EventHandler<T>& _handler) noexcept;

    /**
     * @brief Remove the event handler associated with the current thread.
     */
    void RemoveHandler(EventHandler<Event<T>>* _handler) noexcept;

    /**
     * @brief Remove all registered event handlers.
     */
    void RemoveAllHandlers() noexcept;

    /**
     * @brief Register an event with the given data.
     * 
     * @param _data The data associated with the event.
     */
    void RegisterEvent(const T& _data) noexcept;

    /**
     * @brief Register a pre-constructed event.
     * 
     * @param _event The event to be registered.
     */
    void RegisterEvent(const Event<T>& _event) noexcept;

    /**
     * @brief Unregister all events from the queue.
     * 
     * @param _event The event to be registered.
     */
    void UnregisterAllEvents() noexcept;

    /**
     * @brief Notify all registered event handlers about pending events.
     */
    void NotifyEvents() noexcept;

   public:
    /**
     * @brief Get a view of the current event queue.
     */
    NODISCARD inline const std::queue<Event<T>>& GetEventQueue() const noexcept { return m_eventQueue; }
};

template <typename T>
void EventProducer<T>::AddHandler(const EventHandler<T>& _handler) noexcept {
    std::unique_lock<std::mutex> lock(m_mutex);

    auto threadId = std::this_thread::get_id();
    auto it = m_eventHandlers.find(threadId);

    if (it != m_eventHandlers.end()) {
        it->second.push_back(std::make_shared<EventHandler<T>>(_handler));
    } else {
        m_eventHandlers[threadId] = {std::make_shared<EventHandler<T>>(_handler)};
    }
}

template <typename T>
void EventProducer<T>::RemoveHandler(EventHandler<Event<T>>* _handler) noexcept {
    std::unique_lock<std::mutex> lock(m_mutex);

    for (auto& [tid, handlers] : m_eventHandlers) {
        auto it =
            std::find_if(handlers.begin(), handlers.end(), [_handler](const auto& h) { return h.get() == _handler; });

        if (it != handlers.end()) {
            handlers.erase(it);
            break;
        }
    }
}

template <typename T>
void EventProducer<T>::RemoveAllHandlers() noexcept {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_eventHandlers.clear();
}

template <typename T>
void EventProducer<T>::UnregisterAllEvents() noexcept {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_eventQueue = std::queue<Event<T>>();
}

template <typename T>
void EventProducer<T>::RegisterEvent(const T& _data) noexcept {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_eventQueue.push(Event(_data));
    m_condition.notify_one();
}

template <typename T>
void EventProducer<T>::RegisterEvent(const Event<T>& _event) noexcept {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_eventQueue.push(_event);
    m_condition.notify_one();
}

template <typename T>
void EventProducer<T>::NotifyEvents() noexcept {
    std::unique_lock<std::mutex> lock(m_mutex);

    while (!m_eventQueue.empty()) {
        Event<T> event = m_eventQueue.front();
        m_eventQueue.pop();

        for (const auto& [tid, handlers] : m_eventHandlers) {
            for (const auto& handler : handlers) {
                handler->HandleEvent(event);
            }
        }
    }
}

}  // namespace Rake::core
