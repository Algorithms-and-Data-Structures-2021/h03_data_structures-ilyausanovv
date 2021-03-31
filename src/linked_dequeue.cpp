#include "linked_dequeue.hpp"

#include <stdexcept>  // logic_error

namespace itis {

    void LinkedDequeue::Enqueue(Element e) {
        if(size_ == 0){
            DoublyNode *new_node = new DoublyNode(e, nullptr, nullptr);
            back_ = new_node;
            front_ = new_node;
        }else{
            DoublyNode *new_node = new DoublyNode(e, back_, nullptr);
            back_->next = new_node;
            back_ = new_node;
        }

        size_++;
    }

    void LinkedDequeue::EnqueueFront(Element e) {
        if(size_ == 0){
            DoublyNode *new_node = new DoublyNode(e, nullptr, nullptr);
            back_ = new_node;
            front_ = new_node;
        }else{
            DoublyNode *new_node = new DoublyNode(e, nullptr, front_);
            front_->previous = new_node;
            front_ = new_node;
        }

        size_++;
    }

    void LinkedDequeue::Dequeue() {
        if (size_ == 0) {
            throw std::logic_error("cannot not dequeue from empty queue");
        }

        if (size_ == 1) {
            delete front_;
            front_ = nullptr;
            back_ = nullptr;
        }
        if (size_ == 2) {
            delete front_;
            front_ = back_;
        }
        if (size_ > 2) {
            DoublyNode *second_node = front_->next;
            delete front_;
            front_ = second_node;
        }

        size_--;
    }

    void LinkedDequeue::DequeueBack() {
        if (size_ == 0) {
            throw std::logic_error("cannot not dequeue from empty queue");
        }

        if(size_ == 1){
            delete front_;
            front_ = nullptr;
            back_ = nullptr;
        }

        if (size_ > 1){
            DoublyNode *preback_node = back_->previous;
            delete back_;
            back_ = preback_node;
            back_->next = nullptr;
        }

        size_--;
    }

    void LinkedDequeue::Clear() {
        for(DoublyNode *curr_node = back_; curr_node != nullptr; /**/) {
            DoublyNode *node = curr_node;
            curr_node = curr_node->next;
            delete node;
        }


        size_ = 0;
        front_ = nullptr;
        back_ = nullptr;
    }

// === РЕАЛИЗОВАНО ===

    LinkedDequeue::~LinkedDequeue() {
        Clear();
    }

    std::optional<Element> LinkedDequeue::front() const {
        return front_ == nullptr ? std::nullopt : std::make_optional(front_->data);
    }

    std::optional<Element> LinkedDequeue::back() const {
        return back_ == nullptr ? std::nullopt : std::make_optional(back_->data);
    }

    bool LinkedDequeue::IsEmpty() const {
        return size_ == 0;
    }

    int LinkedDequeue::size() const {
        return size_;
    }

// === НЕОБХОДИМО ДЛЯ ТЕСТИРОВАНИЯ ===

    std::ostream &operator<<(std::ostream &os, const LinkedDequeue &queue) {
        os << "size: " << queue.size_ << '\n';
        for (auto current_node = queue.front_; current_node != nullptr; current_node = current_node->previous) {
            if (current_node == queue.front_) os << "[FRONT] ";
            if (current_node == queue.back_) os << "[BACK] ";
            os << enum2str(current_node->data) << '\n';
        }
        return os;
    }

}  // namespace itis